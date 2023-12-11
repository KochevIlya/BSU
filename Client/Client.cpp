#include <windows.h>
#include <iostream>

#pragma warning (disable : 4996)


using namespace std;

char c; // ��������� ������
HANDLE hNamedPipe;
char machineName[80];
char pipeName[80];
char lpszOutMessage[] = "How do you do server?"; // ��������� �������
DWORD dwBytesWritten; // ��� ����� ���������� ������
char lpszInMessage[80]; // ��� ��������� �� �������
DWORD dwBytesRead; // ��� ����� ����������� ������

int pipeConnecting()
{
	hNamedPipe = CreateFile(
		L"\\\\.\\pipe\\demo_pipe", // ��� ������
		GENERIC_READ | GENERIC_WRITE, // ������ � ���������� � �����
		FILE_SHARE_READ | FILE_SHARE_WRITE, // ��������� ������ � ������ � �����
		(LPSECURITY_ATTRIBUTES)NULL, // ������ �� ���������
		OPEN_EXISTING, // ��������� ������������ �����
		FILE_ATTRIBUTE_NORMAL, // �������� �� ���������
		(HANDLE)NULL // �������������� ��������� ���
	);
	// ��������� ����� � �������
	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		cerr << "Connection with the named pipe failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any char to finish the client: ";
		cin >> c;
		return 1;
	}
	return 0;
}

int writingMessage()
{
	if (!WriteFile(
		hNamedPipe, // ���������� ������
		lpszOutMessage, // ������
		sizeof(lpszOutMessage), // ������ ������
		&dwBytesWritten, // ���������� ���������� ������
		(LPOVERLAPPED)NULL // ���������� ������
	))
	{

		// ������ ������
		cerr << "Writing to the named pipe failed: " << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any char to finish the client: ";
		cin >> c;
		CloseHandle(hNamedPipe);
		return 1;
	}
	return 0;
}

int readingMessage()
{
	if (!ReadFile(
		hNamedPipe, // ���������� ������
		lpszInMessage, // ������
		sizeof(lpszInMessage), // ������ ������
		&dwBytesRead, // ���������� ���������� ����
		(LPOVERLAPPED)NULL // ���������� ������
	))
	{

		// ������ ������
		cerr << "Reading to the named pipe failed: " << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any char to finish the client: ";
		cin >> c;

		CloseHandle(hNamedPipe);
		return 1;
	}
	return 0;
}

int createRequest(const int num)
{
	switch (num)
	{
	case 1:
		strcpy(lpszOutMessage, "Writing");
		break;
	case 2:
		strcpy(lpszOutMessage, "Reading");
		break;
	default:
		std::cout << "Something went wrong\n";
		return 1;
	}

	return 0;
}

int main()
{
	// ����������� � ����������� �������
	if (pipeConnecting() == 1)
		return 0;

	while (true)
	{
		//�������� �����
		cout << "Enter the option: \n1. Modify\n2. Read\n3. Quit\nYour option: ";

		cin >> c;
		switch (c)
		{
		case '1':
			// ����� � ����������� �����
			if (createRequest(1) == 1)
				return 0;
			if (writingMessage() == 1)
				return 0;
			if (readingMessage() == 1)
				return 0;
			break;
		case '2':
			// ������ �� ������������ ������
			cout << "Waiting Server response\n";
			if (createRequest(2) == 1)
				return 0;
			if (writingMessage() == 1)
				return 0;
			if (readingMessage() == 1)
				return 0;

			
			// ������� ���������� ��������� �� �������
			cout << "The client has received the following message from a server: "
				<< endl << "\t" << lpszInMessage << endl;
			break;
		case '3':
			CloseHandle(hNamedPipe);
			// ��������� �������
			cout << "Press any char to finish the client: ";
			cin >> c;
			return 0;
		default:
			cout << "Wrong choice, try again\n";
			break;
		}
	}
}