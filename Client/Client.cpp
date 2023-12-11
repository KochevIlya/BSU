#include <Windows.h>
#include <iostream>
#include <string>

#pragma warning (disable : 4996)

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


using namespace std;

	char c; // служебный символ
	HANDLE hNamedPipe;
	char machineName[80];
	char pipeName[80];
	char lpszOutMessage[] = "How do you do server?"; // сообщение серверу
	DWORD dwBytesWritten; // для числа записанных байтов
	char lpszInMessage[80]; // для сообщения от сервера
	DWORD dwBytesRead; // для числа прочитанных байтов
	int index;
int pipeConnecting()
{
	std::wstring pipeName = L"\\\\.\\pipe\\demo_pipe" + std::to_wstring(index);
	std::wcout << pipeName<< "\n";
	hNamedPipe = CreateFile(
		pipeName.c_str(), // имя канала
		GENERIC_READ | GENERIC_WRITE, // читаем и записываем в канал
		FILE_SHARE_READ | FILE_SHARE_WRITE, // разрешаем чтение и запись в канал
		(LPSECURITY_ATTRIBUTES)NULL, // защита по умолчанию
		OPEN_EXISTING, // открываем существующий канал
		FILE_ATTRIBUTE_NORMAL, // атрибуты по умолчанию
		(HANDLE)NULL // дополнительных атрибутов нет
	);
	// проверяем связь с каналом
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
		hNamedPipe, // дескриптор канала
		lpszOutMessage, // данные
		sizeof(lpszOutMessage), // размер данных
		&dwBytesWritten, // количество записанных байтов
		(LPOVERLAPPED)NULL // синхронная запись
	))
	{

		// ошибка записи
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
		hNamedPipe, // дескриптор канала
		lpszInMessage, // данные
		sizeof(lpszInMessage), // размер данных
		&dwBytesRead, // количество записанных байт
		(LPOVERLAPPED)NULL // синхронная запись
	))
	{

		// ошибка записи
		cerr << "Reading to the named pipe failed: " << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any char to finish the client: ";
		cin >> c;

		CloseHandle(hNamedPipe);
		return 1;
	}
	return 0;
}

int createRequest(const int num, const int id)
{
	Command command = Command();
	std::string	str = "";
	switch (num)
	{
	case 1:
		command.request = 1;
		command.id = id;
		str = command.convert();
		strcpy(lpszOutMessage, str.c_str());
		std::cout << "Converted command: " << command.convert() << "\n";
		std::cout << lpszOutMessage << "\n";
		break;
	case 2:
		command.request = 2;
		command.id = id;
		str = command.convert();
		strcpy(lpszOutMessage, str.c_str());
		std::cout << lpszOutMessage << "\n";
		break;
	default:
		std::cout << "Something went wrong\n";
		return 1;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	index = atoi(argv[1]);
	// связываемся с именованным каналом
	if (pipeConnecting() == 1)
		return 0;
	
	while (true)
	{
		//Выбираем опцию
		cout << "Enter the option: \n1. Modify\n2. Read\n3. Quit\nYour option: ";

		cin >> c;
		int id;
		switch (c)
		{	
			// пишем в именованный канал
		case '1':
			
			std::cout << "Enter the id of Employee that you want to change: ";
			std::cin >> id;
			if (createRequest(1, id) == 1)
				return 0;
			if (writingMessage() == 1)
				return 0;
			if (readingMessage() == 1)
				return 0;
			break;
		


		// читаем из именованного канала
		case '2':
			std::cout << "Enter the id of Employee that you want to read: ";
			std::cin >> id;

			cout << "Waiting Server response\n";
			if (createRequest(2, id) == 1)
				return 0;
			if (writingMessage() == 1)
				return 0;
			if (readingMessage() == 1)
				return 0;

			// выводим полученное сообщение на консоль
			cout << "The client has received the following message from a server: "
				<< endl << "\t" << lpszInMessage << endl;
			break;
		case '3':
			CloseHandle(hNamedPipe);
			// завершаем процесс
			cout << "Press any char to finish the client: ";
			cin >> c;
			return 0;
		default:
			cout << "Wrong choice, try again\n";
			break;
		}
	}
}