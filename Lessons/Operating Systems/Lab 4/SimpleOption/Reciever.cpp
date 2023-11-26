#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

const wchar_t* MutexName = L"SharedMutex";
const wchar_t* SemaphoreName = L"SenderSemaphore";

void readMessage(std::wstring fileName)
{
    HANDLE hMutex = OpenMutex(NULL, FALSE, MutexName);
    std::ifstream messageFile(fileName, std::ios::binary | std::ios::in);
    std::string message;
    getline(messageFile, message);
    std::cout << "Recieved message:\n";
    std::cout << message << std::endl;  
    ReleaseMutex(hMutex);
    CloseHandle(hMutex);
    messageFile.close();
    return;
}


int main() {

    std::wstring fileName;

    int numSenders;

    // Вводим с консоли имя бинарного файла и количество записей
    std::wcout << L"Enter the name of the binary file: ";
    std::wcin >> fileName;
 

    // Создаем бинарный файл для сообщений

    std::wcout << L"Enter the number of Sender processes: ";
    std::wcin >> numSenders;

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    
    // Создаем именованный мьютекс
    HANDLE hMutex = CreateMutex(NULL, TRUE, MutexName);
    if (!hMutex) {
        std::cerr << "Failed to create mutex in Receiver: " << GetLastError() << std::endl;
        return 0;
    }

    // Создаем или открываем именованный семафор
    HANDLE hSemaphore = CreateSemaphore(NULL, 0, numSenders, SemaphoreName);

    std::wstring command;
    for (int i = 0; i < numSenders; ++i) {

        command = L"Sender.exe " + fileName;
        if (!CreateProcess(NULL, &command[0], NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
            std::cerr << "Failed to create a Sender process." << std::endl;
            return 1;
        }
    }

    for (int i = 0; i < numSenders; i++)
    {
        WaitForSingleObject(hSemaphore, INFINITE);
    }

    while (true)
    {
        int input;
        std::cout << "Choose the option:\n";
        std::cout << "1. Read the message from file\n";
        std::cout << "2. Exit\n";
        
        std::cin >> input;
        switch (input)
        {
        case 1:
        {
            readMessage(fileName);
            break;
        }
        case 2:
        {
            // Закрываем хэндлы процесса Receiver
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);

            // Закрываем хэндлы
            CloseHandle(hMutex);
            CloseHandle(hSemaphore);
            return 0;
        }
        default:
        {
            std::cout << "Wrong choice\n";
            // Закрываем хэндлы процесса Receiver
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);

            // Закрываем хэндлы
            CloseHandle(hMutex);
            CloseHandle(hSemaphore);
           
            return 0;
        }



        }

    }

    
    
    
    // Закрываем хэндлы процесса Receiver
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess); 

    // Закрываем хэндлы
    CloseHandle(hMutex);
    CloseHandle(hSemaphore);
    return 0;
}
