#include <windows.h>
#include <iostream>
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
HANDLE hNamedPipe;
char lpszInMessage[80]; // дл€ сообщени€ от клиента
DWORD dwBytesRead; // дл€ числа прочитанных байтов
char lpszOutMessage[] = "The server has received a message."; // обратное сообщение
DWORD dwBytesWrite; // дл€ числа записанных байтов
int processAmount;
STARTUPINFO startupInfo;
PROCESS_INFORMATION processInfo;
HANDLE* processHandles;



int creatingPipe()
{
		hNamedPipe = CreateNamedPipe(
			L"\\\\.\\pipe\\demo_pipe", // им€ канала
			PIPE_ACCESS_DUPLEX, // читаем из канала и пишем в канал
			PIPE_TYPE_MESSAGE | PIPE_WAIT, // синхронна€ передача сообщений
			PIPE_UNLIMITED_INSTANCES, // максимальное количество экземпл€ров канала
			0, // размер выходного буфера по умолчанию
			0, // размер входного буфера по умолчанию
			INFINITE, // клиент ждет св€зь 500 мс
			&sa // доступ дл€ всех пользователей
		);

		if (hNamedPipe == INVALID_HANDLE_VALUE)
		{
			cerr << "Creation of the named pipe failed." << endl
				<< "The last error code: " << GetLastError() << endl;
			cout << "Press any char to finish server: ";
			cin >> c;
			return 1;
		}
	return 0;
}

int waitingClient()
{
		if (!ConnectNamedPipe(

			hNamedPipe, // дескриптор канала
			(LPOVERLAPPED)NULL // св€зь синхронна€
		))
		{
			cerr << "The connection failed." << endl
				<< "The last error code: " << GetLastError() << endl;
			CloseHandle(hNamedPipe);
			cout << "Press any char to finish the server: ";
			cin >> c;
			return 1;
		}
		return 0;
	
}

int creatingProcess()
{
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	ZeroMemory(&sa, sizeof(SECURITY_ATTRIBUTES));
	std::wstring command = L"Client.exe";
	processHandles = new HANDLE[processAmount];
	for (int i = 0; i < processAmount; i++)
	{
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

int readingMessage()
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
		cout << "Press any char to finish the server: ";
		cin >> c;
		return 1;
	}
	return 0;
}

int writingMessage()
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
	

	
	// инициализаци€ атрибутов защиты
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = FALSE; // дескриптор канала ненаследуемый
	
	// инициализируем дескриптор защиты
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	
	// устанавливаем атрибуты защиты, разреша€ доступ всем пользовател€м
	SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
	sa.lpSecurityDescriptor = &sd;

	// создаем именованный канал дл€ чтени€
	if (creatingPipe() == 1)
		return 0;
	
	//CоздаЄм процессы клиентов
	cout << "Enter the amount of procces Clients: ";
	cin >> processAmount;
	if (creatingProcess() == 1)
		return 0;


	// ждем, пока клиент св€жетс€ с каналом
	cout << "The server is waiting for connection with a client." << endl;
	if (waitingClient() == 1)
		return 0;
	cout << "Connected\n";

	while (true)
	{
		// читаем сообщение от клиента
		if (readingMessage() == 1)
			return 0;
		if (requestProcessing() == 1)
			return 0;

		// выводим полученное от клиента сообщение на консоль
		cout << "The server has receivrd the following message from a client: "
			<< endl << "\t" << lpszInMessage << endl;


		// отвечаем клиенту
		if (writingMessage() == 1)
			return 0;

		// выводим посланное клиенту сообщение на консоль
		cout << "The server send the following message to a client: "
			<< endl << "\t" << lpszOutMessage << endl;

	}
	// закрываем дескриптор канала
	CloseHandle(hNamedPipe);
	
	// завершаем процесс
	cout << "Press any char to finish the server: ";
	cin >> c;
	return 0;
}