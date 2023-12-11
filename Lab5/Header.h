#pragma once
char lpszInMessage[80];
int readingMessage(HANDLE hNamedPipe);
int requestProcessing();
int writingMessage(HANDLE hNamedPipe);
int waitingClient(HANDLE hNamedPipe);
using namespace std;


extern char c; // служебный символ
extern SECURITY_ATTRIBUTES sa; // атрибуты защиты
extern SECURITY_DESCRIPTOR sd; // дескриптор защиты
extern STARTUPINFO startupInfo;
extern DWORD dwBytesRead; // для числа прочитанных байтов
extern char lpszOutMessage[]; // обратное сообщение
extern DWORD dwBytesWrite; // для числа записанных байтов
extern int processAmount;
extern PROCESS_INFORMATION processInfo;
extern HANDLE* processHandles;
extern const wchar_t* pipeNameBase;
extern HANDLE* hNamedPipes;

int processingThread(int i)
{
	std::cout << "The server is waiting for connection with a client." << i << "\n" << endl;
	if (waitingClient(hNamedPipes[i]) == 1)
		return 0;

	while (true)
	{
		
		// читаем сообщение от клиента
		if (readingMessage(hNamedPipes[i]) == 1)
			return 0;

		if (requestProcessing() == 1)
			return 0;

		// выводим полученное от клиента сообщение на консоль
		std::cout << "The server has receivrd the following message from a client: "
			<< endl << "\t" << lpszInMessage << endl;


		// отвечаем клиенту
		if (writingMessage(hNamedPipes[i]) == 1)
			return 0;

		// выводим посланное клиенту сообщение на консоль
		std::cout << "The server send the following message to a client: "
			<< std::endl << "\t" << lpszOutMessage << endl;
	}
	return 0;
}