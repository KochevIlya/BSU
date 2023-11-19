#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

const wchar_t* MutexName = L"SharedMutex";
const wchar_t* SemaphoreName = L"SenderSemaphore";

void sendMessage(std::string fileName, const std::string& message)
{
    std::ofstream messageFile(fileName, std::ios::binary | std::ios::out);
    
    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, MutexName);
    if (!hMutex) {
        std::cerr << "Failed to open mutex in Sender: " << GetLastError() << std::endl;
        messageFile.close();
        return;
    }

    size_t size = message.size();
    messageFile.write(reinterpret_cast<const char*>(&size), sizeof(size));

    messageFile.write(message.c_str(), size);

    ReleaseMutex(hMutex);
    CloseHandle(hMutex);

    messageFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: Sender.exe <file_name>" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];
    

    // Создаем или открываем именованный семафор
    HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, SemaphoreName);

    // Отправляем сигнал на готовность к работе процессу Receiver
    ReleaseSemaphore(hSemaphore, 1, NULL);

    while (true)
    {
        int input;
        std::cout << "Choose the option:\n";
        std::cout << "1. Send the message from file\n";
        std::cout << "2. Exit\n";
        std::cin >> input;


        switch (input)
        {
        case 1:
        {
            std::string message;
            std::cout << "Enter the message:\n";
            std::cin.ignore();
            std::getline(std::cin, message);
            sendMessage(fileName, message); 
            break;
        }
        case 2:
        {         
            CloseHandle(hSemaphore);
            return 0;
        }
        default:
        {
            std::cout << "Wrong choice\n";         
            Sleep(20000);
            CloseHandle(hSemaphore);
            return 0;
        }
        }
    }
    CloseHandle(hSemaphore);
    return 0;
}
