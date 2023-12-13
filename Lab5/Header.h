#pragma once


char lpszInMessage[80];
int readingMessage(HANDLE hNamedPipe, char* inMessage);
int requestProcessing(char* inMessage);
int writingMessage(HANDLE hNamedPipe);
int waitingClient(HANDLE hNamedPipe);
int readRequest();
int modifyRequest(HANDLE);
using namespace std;


extern char c; // ��������� ������
extern STARTUPINFO startupInfo;
extern DWORD dwBytesRead; // ��� ����� ����������� ������
extern char OutMessage[80]; // �������� ���������
extern HANDLE* hNamedPipes;
extern char InMessage[80];
extern int index;




char inMessage[10];
int processingThread(int i)
{
	if (waitingClient(hNamedPipes[i]) == 1)
		return 0;
	while (true)
	{
		// ������ ��������� �� �������
		if (readingMessage(hNamedPipes[i], inMessage) == 1)
			return 0;

		int desicion = requestProcessing(inMessage);
		std::cout << "desicion: " << desicion << "\n";
		if (desicion == 2)
		{
			if (readRequest() == 1)
				return 0;
			// ������� ���������� �� ������� ��������� �� �������
			std::cout << "The server has receivrd the following message from a client: "
				<< endl << "\t" << inMessage << endl;

			// �������� �������
			if (writingMessage(hNamedPipes[i]) == 1)
				return 0;
			// ������� ��������� ������� ��������� �� �������
			std::cout << "The server send the following message to a client: "
				<< std::endl << "\t" << OutMessage << endl;
		}
		else if (desicion == 0)
		{
			std::cout << "In case, when desicion = 0\n";
			if (modifyRequest(hNamedPipes[i]) == 1)
				return 0;
			std::cout << "After Modifying\n";
		}
		else
			return 0;
	}
	return 0;
}