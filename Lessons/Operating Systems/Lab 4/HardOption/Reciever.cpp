#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <locale>
#include <codecvt>

const wchar_t* MutexName = L"SharedMutex";
const wchar_t* SemaphoreName = L"SenderSemaphore";
const wchar_t* MessageSemaphore = L"MessageSemaphore";
const wchar_t* WaitingEvent = L"WaitingEvent";
const wchar_t* MessageEvent = L"MessageEvent";
const wchar_t* RecieverWait = L"RecieverWait";

int countLines = 0;
HANDLE hEvent;
std::ifstream file;
HANDLE hSemaphore;
void readMessages(std::wstring fileName)
{

    file.open(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    file.seekg(countLines * 21);
    char buffer[21];
    if (!file.read(buffer, 21))
    {
        hEvent = CreateEvent(NULL, FALSE, FALSE, MessageEvent);
        std::cout << "We couldn't read this now\n";
        file.close();
        WaitForSingleObject(hEvent, INFINITE);
        file.open(fileName, std::ios::binary);
        file.seekg(countLines * 21);
        file.read(buffer, 21);
        std::cout << buffer << "\n";
        ReleaseSemaphore(hSemaphore, 1, NULL);
        countLines++;
    }
    else
    {
        std::cout << buffer << "\n";
        ReleaseSemaphore(hSemaphore, 1, NULL);
        countLines++;
    }
    file.close();
    return;
}


int main() {

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES sa;
    ZeroMemory(&sa, sizeof(SECURITY_ATTRIBUTES));
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    std::wstring fileName;

    int numSenders;
    int numMessages;

    // Вводим с консоли имя бинарного файла и количество записей
    std::wcout << L"Enter the name of the binary file: ";
    std::wcin >> fileName;

    std::ofstream fil;
    fil.open(fileName, std::ios::binary | std::ios::out | std::ios::trunc);
    fil.close();

    std::wcout << L"Enter the number of Sender processes: ";
    std::wcin >> numSenders;

    std::cout << "Enter the amount of messages\n";
    std::cin >> numMessages;
    
    hSemaphore = CreateSemaphore(NULL, 0, numSenders, SemaphoreName);

    std::wstring command;
    for (int i = 0; i < numSenders; ++i) {
        command = L"Sender.exe " + fileName;
        if (!CreateProcess(NULL, &command[0], &sa, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
            std::cerr << "Failed to create a Sender process." << std::endl;
            return 1;
        }
    }

    for (int i = 0; i < numSenders; i++)
    {
        WaitForSingleObject(hSemaphore, INFINITE);
    }
    CloseHandle(hSemaphore);
    hSemaphore = CreateSemaphore(&sa, numMessages, numMessages, MessageSemaphore);

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
            readMessages(fileName);
            break;
        case 2:
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);
            CloseHandle(hSemaphore);
            return 0;
        default:
            std::cout << "Wrong choice\n";
            break;
        }

    }
    
    return 0;
}
