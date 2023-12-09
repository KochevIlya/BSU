#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <Windows.h>

const wchar_t* MutexName = L"SharedMutex";
const wchar_t* SemaphoreName = L"SenderSemaphore";
const wchar_t* MessageSemaphore = L"MessageSemaphore";
const wchar_t* MessageEvent = L"MessageEvent";
const wchar_t* SenderWait = L"SenderWait";

HANDLE hEvent;
HANDLE hSemaphore;
std::string fileName;

void sendMessage(std::string message)
{
    if (!(hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, MessageSemaphore)))
    {
        std::cout << "something went wrong with semaphore\n";
    }

    
    DWORD result = WaitForSingleObject(hSemaphore, 0);

    if (result == WAIT_OBJECT_0) {
        
        std::ofstream out(fileName, std::ios::binary | std::ios::app);
        if (!out) {
            std::cerr << "Something went wrong" << std::endl;
            out.close();
            return;
        }
        out.write(message.c_str(), 21);
        out.close();

        hEvent = OpenEvent(EVENT_ALL_ACCESS, TRUE, MessageEvent);
        SetEvent(hEvent);
        CloseHandle(hEvent);

        return;
        
    }
    else if (result == WAIT_TIMEOUT) {
        std::cout << "Semaphore is not available (count is zero)" << std::endl;
        WaitForSingleObject(hSemaphore, INFINITE);
        std::ofstream out(fileName, std::ios::binary | std::ios::app);
        if (!out) {
            std::cerr << "Something went wrong" << std::endl;
            out.close();
            return;
        }
        out.write(message.c_str(), 21);
        out.close();
        hEvent = OpenEvent(EVENT_ALL_ACCESS, TRUE, MessageEvent);
        SetEvent(hEvent);
        CloseHandle(hEvent);
        return;
    }
    else {
        std::cerr << "Error while waiting for semaphore" << std::endl;
    }

    std::ofstream out(fileName, std::ios::binary | std::ios::app);
    if (!out) {
        std::cerr << "Something went wrong" << std::endl;
        out.close();
        return ;
    }
    out.write(message.c_str(), 21);
    out.close();
    return;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: Sender.exe <file_name>" << std::endl;
        return 1;
    }

    fileName = argv[1];
    
    hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, SemaphoreName);
    
    ReleaseSemaphore(hSemaphore, 1, NULL);
    
    CloseHandle(hSemaphore);

    
    while (true)
    {
        char input;
        std::cout << "Choose the option:\n";
        std::cout << "1. Send the message from file\n";
        std::cout << "2. Exit\n";
        std::cin >> input;
        std::string inputMessage = "";
        std::cin.ignore();
        switch (input)
        {
        case '1':
            std::getline(std::cin, inputMessage);
            if (inputMessage.length() > 20)
            {
                std::cout << "You entered message with more than 20 symbols, Sending error\n";
                break;
            }
            sendMessage(inputMessage);
            break;
        case '2':

            CloseHandle(hSemaphore);
            return 0;
        default:
            std::cout << "Wrong choice\n"; 
            break;
        }
    }
    return 0;
}
