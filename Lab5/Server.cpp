#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

struct employee
{
	int id;
	char name[10];
	double hours;
};



char c; // ��������� ������
SECURITY_ATTRIBUTES sa; // �������� ������
SECURITY_DESCRIPTOR sd; // ���������� ������
STARTUPINFO startupInfo;
char lpszInMessage[80]; // ��� ��������� �� �������
DWORD dwBytesRead; // ��� ����� ����������� ������
char lpszOutMessage[] = "The server has received a message."; // �������� ���������
DWORD dwBytesWrite; // ��� ����� ���������� ������
int processAmount;
PROCESS_INFORMATION processInfo;
HANDLE* processHandles;
const wchar_t* pipeNameBase = L"\\\\.\\pipe\\demo_pipe";
HANDLE* hNamedPipes;




int creatingPipe()
{
	hNamedPipes = new HANDLE[processAmount];
	for (int i = 0; i < processAmount; i++)
	{
		std::wstring pipeName = pipeNameBase + std::to_wstring(i);
		std::wcout << pipeName << "\n";
		hNamedPipes[i] = CreateNamedPipe(
			pipeName.c_str(), // ��� ������
			PIPE_ACCESS_DUPLEX, // ������ �� ������ � ����� � �����
			PIPE_TYPE_MESSAGE | PIPE_WAIT, // ���������� �������� ���������
			PIPE_UNLIMITED_INSTANCES, // ������������ ���������� ����������� ������
			0, // ������ ��������� ������ �� ���������
			0, // ������ �������� ������ �� ���������
			INFINITE, // ������ ���� ����� 500 ��
			&sa // ������ ��� ���� �������������
		);

		if (hNamedPipes[i] == INVALID_HANDLE_VALUE)
		{
			cerr << "Creation of the named pipe failed." << endl
				<< "The last error code: " << GetLastError() << endl;
			cout << "Press any char to finish server: ";
			cin >> c;
			return 1;
		}
	}
	return 0;
}

int waitingClient()
{
	for (int i = 0; i < processAmount; i++)
	{
		if (!ConnectNamedPipe(

			hNamedPipes[i], // ���������� ������
			(LPOVERLAPPED)NULL // ����� ����������
		))
		{
			cerr << "The connection failed." << endl
				<< "The last error code: " << GetLastError() << endl;
			CloseHandle(hNamedPipes[i]);
			cout << "Press any char to finish the server: ";
			cin >> c;
			return 1;
		}
		return 0;
	}
}

int creatingProcess()
{
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	ZeroMemory(&sa, sizeof(SECURITY_ATTRIBUTES));
	processHandles = new HANDLE[processAmount];
	for (int i = 0; i < processAmount; i++)
	{
		std::wstring command = L"Client.exe ";
		command += std::to_wstring(i);

		if (!CreateProcess(NULL, &command[0], &sa, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo))
		{
			std::cerr << "Failed to create a Client process." << std::endl;
			std::cerr << GetLastError();
			return 1;
		}
		processHandles[i] = processInfo.hProcess;
	}

	return 0;
}

int readingMessage(HANDLE hNamedPipe)
{
	if (!ReadFile(

		hNamedPipe, // ���������� ������
		lpszInMessage, // ����� ������ ��� ����� ������
		sizeof(lpszInMessage), // ����� �������� ������
		&dwBytesRead, // ����� ����������� ������
		(LPOVERLAPPED)NULL // �������� ������ ����������
	))
	{
		cerr << "Data reading from the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;

		CloseHandle(hNamedPipe);
		cout << "Press any char to finish the server: ";
		cin >> c;
		return 1;
	}
	return 0;
}

int writingMessage(HANDLE hNamedPipe)
{
	if (!WriteFile(

		hNamedPipe, // ���������� ������
		lpszOutMessage, // ����� ������ ��� ������ ������
		sizeof(lpszOutMessage), // ����� ������������ ������
		&dwBytesWrite, // ����� ���������� ������
		(LPOVERLAPPED)NULL // �������� ������ ����������
	))
	{
		cerr << "Data writing to the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		cout << "Press any char to finish the server: ";
		cin >> c;
		return 1;
	}
	return 0;
}

int requestProcessing()
{

	return 0;
}


int main()
{
	

	
	// ������������� ��������� ������
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = FALSE; // ���������� ������ �������������
	
	// �������������� ���������� ������
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	
	// ������������� �������� ������, �������� ������ ���� �������������
	SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
	sa.lpSecurityDescriptor = &sd;

	// ������� ����������� ����� ��� ������
	cout << "Enter the amount of procces Clients: ";
	cin >> processAmount;

	if (creatingPipe() == 1)
		return 0;
	
	//C����� �������� ��������
	if (creatingProcess() == 1)
		return 0;


	// ����, ���� ������ �������� � �������
	cout << "The server is waiting for connection with a client." << endl;
	if (waitingClient() == 1)
		return 0;
	cout << "Connected\n";


	//��������, ���� ��� �������� �� ���������.
	while (true)
	{
		// ������ ��������� �� �������
		if (readingMessage(hNamedPipes[0]) == 1)
			return 0;
		if (requestProcessing() == 1)
			return 0;

		// ������� ���������� �� ������� ��������� �� �������
		cout << "The server has receivrd the following message from a client: "
			<< endl << "\t" << lpszInMessage << endl;


		// �������� �������
		if (writingMessage(hNamedPipes[0]) == 1)
			return 0;

		// ������� ��������� ������� ��������� �� �������
		cout << "The server send the following message to a client: "
			<< endl << "\t" << lpszOutMessage << endl;

	}
	// ��������� ���������� ������
	for (int i = 0; i < processAmount; i++)
	{

		CloseHandle(hNamedPipes[i]);
	}
	// ��������� �������
	cout << "Press any char to finish the server: ";
	cin >> c;
	return 0;
}