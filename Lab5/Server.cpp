#include <windows.h>
#include <iostream>
#include <string>
#include "Header.h";
#include <fstream>;

#pragma warning (disable : 4996)
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

char c;
char* tempStr;// служебный символ
SECURITY_ATTRIBUTES sa; // атрибуты защиты
SECURITY_DESCRIPTOR sd; // дескриптор защиты
STARTUPINFO startupInfo;
DWORD dwBytesRead; // дл€ числа прочитанных байтов
char OutMessage[80]; // обратное сообщение
char InMessage[80];
DWORD dwBytesWrite; // дл€ числа записанных байтов
int processAmount;
PROCESS_INFORMATION processInfo;
HANDLE* processHandles;
const wchar_t* pipeNameBase = L"\\\\.\\pipe\\demo_pipe";
HANDLE* hNamedPipes;
HANDLE* hThreads;
std::string fileName;
ifstream IFile;
ofstream OFile;
int notesAmmount;	

int prepearingFiles()
{
	std::cout << "Enter the Input file name: ";
	std::cin >> fileName;
	IFile = ifstream(fileName, std::ios::binary);
	OFile = ofstream(fileName, std::ios::binary);
	std::cout << "Enter the ammount of employees: ";
	std::cin >> notesAmmount;
	for (int i = 0; i < notesAmmount; i++)
	{
		employee temp = employee();
		temp.id = i;
		std::cout << "Enter the Data\n";
		std::cout << "ID: " << i << "\n";
		std::cout << "Name: ";
		std::cin >> temp.name;
		std::cout << "Hours: ";
		std::cin >> temp.hours;
		OFile.write((char*)&temp, sizeof(employee));
	}
	OFile.close();

	for (int i = 0; i < notesAmmount; i++)
	{
		employee temp = employee();
		IFile.read((char*)&temp, sizeof(employee));
		std::cout << temp.id << " " << temp.hours << " " << temp.name << "\n";
	}
	IFile.close();
	return 0;
}

int creatingPipe()
{
	hNamedPipes = new HANDLE[processAmount];
	for (int i = 0; i < processAmount; i++)
	{
		std::wstring pipeName = pipeNameBase + std::to_wstring(i);
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
		hThreads[i] = CreateThread(&sa, 0, (LPTHREAD_START_ROUTINE)processingThread, (void*)i, 0, &IDThreads[i]);
	}
	return 0;
}

int readingMessage(HANDLE hNamedPipe, char* inMessage)
{

	if (!ReadFile(

		hNamedPipe, // дескриптор канала
		inMessage, // адрес буфера дл€ ввода данных
		sizeof(InMessage), // число читаемых байтов
		&dwBytesRead, // число прочитанных байтов
		(LPOVERLAPPED)NULL // передача данных синхронна€
	))
	{
		if (GetLastError() == 109)
		{
			std::cout << "One process Closed\n";
			return 1;
		}
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
	std::cout << "IN Message writing\n";

	if (!WriteFile(

		hNamedPipe, // дескриптор канала
		OutMessage, // адрес буфера дл€ вывода данных
		sizeof(OutMessage), // число записываемых байтов
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
	std::cout << "Message writed\n";
	return 0;
}

int requestProcessing(char* inMessage, int& index)
{
	std::string str = inMessage;

	switch (inMessage[0])
	{
	case '1':
		str = str.substr(2);
		index = stoi(str);
		break;
	case '2':
		str = str.substr(2);
		index = stoi(str);
		break;
	default:
		return 1;
	}
	return 0;

}

int processRequest(int& index)
{
	std::cout << "In process Request\n";
	employee temp = employee();
	IFile.open(fileName, std::ios::binary);
	IFile.seekg(index * sizeof(employee));

	IFile.read((char*)&temp, sizeof(employee));
	std::string str = "ID: " + std::to_string(temp.id) + " Name: " + temp.name + " Hours: " + std::to_string(temp.hours);
	strcpy(OutMessage, str.c_str());
	std::cout << OutMessage << "\n";
	IFile.close();
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

	if (prepearingFiles() == 1)
		return 0;
	

	// создаем именованный канал дл€ чтени€
	std::cout << "Enter the amount of procces Clients: ";
	std::cin >> processAmount;

	if (creatingPipe() == 1)
		return 0;
	
	//CоздаЄм процессы клиентов
	if (creatingProcess() == 1)
		return 0;

	if (creatingThreads() == 1)
		return 0;

	std::cout << "Connected\n";
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