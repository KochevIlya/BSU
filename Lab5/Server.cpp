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



char c; // служебный символ
SECURITY_ATTRIBUTES sa; // атрибуты защиты
SECURITY_DESCRIPTOR sd; // дескриптор защиты
STARTUPINFO startupInfo;
char lpszInMessage[80]; // для сообщения от клиента
DWORD dwBytesRead; // для числа прочитанных байтов
char lpszOutMessage[] = "The server has received a message."; // обратное сообщение
DWORD dwBytesWrite; // для числа записанных байтов
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
			pipeName.c_str(), // имя канала
			PIPE_ACCESS_DUPLEX, // читаем из канала и пишем в канал
			PIPE_TYPE_MESSAGE | PIPE_WAIT, // синхронная передача сообщений
			PIPE_UNLIMITED_INSTANCES, // максимальное количество экземпляров канала
			0, // размер выходного буфера по умолчанию
			0, // размер входного буфера по умолчанию
			INFINITE, // клиент ждет связь 500 мс
			&sa // доступ для всех пользователей
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

			hNamedPipes[i], // дескриптор канала
			(LPOVERLAPPED)NULL // связь синхронная
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

		hNamedPipe, // дескриптор канала
		lpszInMessage, // адрес буфера для ввода данных
		sizeof(lpszInMessage), // число читаемых байтов
		&dwBytesRead, // число прочитанных байтов
		(LPOVERLAPPED)NULL // передача данных синхронная
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

		hNamedPipe, // дескриптор канала
		lpszOutMessage, // адрес буфера для вывода данных
		sizeof(lpszOutMessage), // число записываемых байтов
		&dwBytesWrite, // число записанных байтов
		(LPOVERLAPPED)NULL // передача данных синхронная
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
	

	
	// инициализация атрибутов защиты
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = FALSE; // дескриптор канала ненаследуемый
	
	// инициализируем дескриптор защиты
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	
	// устанавливаем атрибуты защиты, разрешая доступ всем пользователям
	SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
	sa.lpSecurityDescriptor = &sd;

	// создаем именованный канал для чтения
	cout << "Enter the amount of procces Clients: ";
	cin >> processAmount;

	if (creatingPipe() == 1)
		return 0;
	
	//Cоздаём процессы клиентов
	if (creatingProcess() == 1)
		return 0;


	// ждем, пока клиент свяжется с каналом
	cout << "The server is waiting for connection with a client." << endl;
	if (waitingClient() == 1)
		return 0;
	cout << "Connected\n";


	//Работаем, пока все процессы не закроются.
	while (true)
	{
		// читаем сообщение от клиента
		if (readingMessage(hNamedPipes[0]) == 1)
			return 0;
		if (requestProcessing() == 1)
			return 0;

		// выводим полученное от клиента сообщение на консоль
		cout << "The server has receivrd the following message from a client: "
			<< endl << "\t" << lpszInMessage << endl;


		// отвечаем клиенту
		if (writingMessage(hNamedPipes[0]) == 1)
			return 0;

		// выводим посланное клиенту сообщение на консоль
		cout << "The server send the following message to a client: "
			<< endl << "\t" << lpszOutMessage << endl;

	}
	// закрываем дескриптор канала
	for (int i = 0; i < processAmount; i++)
	{

		CloseHandle(hNamedPipes[i]);
	}
	// завершаем процесс
	cout << "Press any char to finish the server: ";
	cin >> c;
	return 0;
}