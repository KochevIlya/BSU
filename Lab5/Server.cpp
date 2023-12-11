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


char c; // служебный символ
SECURITY_ATTRIBUTES sa; // атрибуты защиты
SECURITY_DESCRIPTOR sd; // дескриптор защиты
STARTUPINFO startupInfo;
DWORD dwBytesRead; // дл€ числа прочитанных байтов
char lpszOutMessage[] = "The server has received a message."; // обратное сообщение
DWORD dwBytesWrite; // дл€ числа записанных байтов
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
			pipeName.c_str(), // им€ канала
			PIPE_ACCESS_DUPLEX, // читаем из канала и пишем в канал
			PIPE_TYPE_MESSAGE | PIPE_WAIT, // синхронна€ передача сообщений
			PIPE_UNLIMITED_INSTANCES, // максимальное количество экземпл€ров канала
			0, // размер выходного буфера по умолчанию
			0, // размер входного буфера по умолчанию
			INFINITE, // клиент ждет св€зь 500 мс
			&sa // доступ дл€ всех пользователей
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

			hNamedPipe, // дескриптор канала
			(LPOVERLAPPED)NULL // св€зь синхронна€
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

		hNamedPipe, // дескриптор канала
		lpszInMessage, // адрес буфера дл€ ввода данных
		sizeof(lpszInMessage), // число читаемых байтов
		&dwBytesRead, // число прочитанных байтов
		(LPOVERLAPPED)NULL // передача данных синхронна€
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

		hNamedPipe, // дескриптор канала
		lpszOutMessage, // адрес буфера дл€ вывода данных
		sizeof(lpszOutMessage), // число записываемых байтов
		&dwBytesWrite, // число записанных байтов
		(LPOVERLAPPED)NULL // передача данных синхронна€
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
	

	
	// инициализаци€ атрибутов защиты
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = FALSE; // дескриптор канала ненаследуемый
	
	// инициализируем дескриптор защиты
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	
	// устанавливаем атрибуты защиты, разреша€ доступ всем пользовател€м
	SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
	sa.lpSecurityDescriptor = &sd;

	// создаем именованный канал дл€ чтени€
	std::cout << "Enter the amount of procces Clients: ";
	std::cin >> processAmount;

	if (creatingPipe() == 1)
		return 0;
	
	//CоздаЄм процессы клиентов
	if (creatingProcess() == 1)
		return 0;

	std::cout << "Connected\n";
	if (creatingThreads() == 1)
		return 0;
	WaitForMultipleObjects(processAmount, hThreads, TRUE, INFINITE);
	std::cout << "CLosing the Threads\n";
	// закрываем дескриптор канала
	for (int i = 0; i < processAmount; i++)
	{
		CloseHandle(hNamedPipes[i]);
	}
	// завершаем процесс
	std::cout << "Press any char to finish the server: ";
	std::cin >> c;
	return 0;
}