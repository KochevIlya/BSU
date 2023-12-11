#include <windows.h>
#include <iostream>
#include <string>
#include "Header.h";
using namespace std;

struct employee
{
	int id;
	char name[10];
	double hours;
};
struct Command
{
	int id;
	int request;

	std::string convert()
	{
		std::string str = std::to_string(request) + " " + std::to_string(id);
		return  str;
	};
	Command()
	{
		this->id = -1;
		this->request = 0;
	}
};


char c; // ��������� ������
SECURITY_ATTRIBUTES sa; // �������� ������
SECURITY_DESCRIPTOR sd; // ���������� ������
STARTUPINFO startupInfo;
DWORD dwBytesRead; // ��� ����� ����������� ������
char lpszOutMessage[] = "The server has received a message."; // �������� ���������
DWORD dwBytesWrite; // ��� ����� ���������� ������
int processAmount;
PROCESS_INFORMATION processInfo;
HANDLE* processHandles;
const wchar_t* pipeNameBase = L"\\\\.\\pipe\\demo_pipe";
HANDLE* hNamedPipes;
HANDLE* hThreads;




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
			std::cout << "Press any char to finish server: ";
			std::cin >> c;
			return 1;
		}
	}
	return 0;
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

int waitingClient(HANDLE hNamedPipe)
{
		if (!ConnectNamedPipe(

			hNamedPipe, // ���������� ������
			(LPOVERLAPPED)NULL // ����� ����������
		))
		{
			cerr << "The connection failed." << endl
				<< "The last error code: " << GetLastError() << endl;
			CloseHandle(hNamedPipe);
			std::cout << "Press any char to finish the server: ";
			std::cin >> c;
			return 1;
		}
		return 0;
}

int creatingThreads()
{	
	DWORD* IDThreads = new DWORD[processAmount];
	hThreads = new HANDLE[processAmount];
	for (int i = 0; i < processAmount; i++)
	{
		std::cout << "Creating Thread\n";
		hThreads[i] = CreateThread(&sa, 0, (LPTHREAD_START_ROUTINE)processingThread, (void*)i, 0, &IDThreads[i]);
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
		std::cout << "Press any char to finish the server: ";
		std::cin >> c;
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
		std::cout << "Press any char to finish the server: ";
		std::cin >> c;
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
	std::cout << "Enter the amount of procces Clients: ";
	std::cin >> processAmount;

	if (creatingPipe() == 1)
		return 0;
	
	//C����� �������� ��������
	if (creatingProcess() == 1)
		return 0;

	std::cout << "Connected\n";
	if (creatingThreads() == 1)
		return 0;
	WaitForMultipleObjects(processAmount, hThreads, TRUE, INFINITE);
	std::cout << "CLosing the Threads\n";
	// ��������� ���������� ������
	for (int i = 0; i < processAmount; i++)
	{
		CloseHandle(hNamedPipes[i]);
	}
	// ��������� �������
	std::cout << "Press any char to finish the server: ";
	std::cin >> c;
	return 0;
}