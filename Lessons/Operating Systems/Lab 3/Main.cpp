#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>

CRITICAL_SECTION cs;
HANDLE* hStartMarker;
HANDLE* hMarkerCantResume;
HANDLE* hMarkerRestart;
HANDLE* hMarkerStop;
HANDLE hMarkerStoped;

int* Mass;
int MassNumber;

void ThreadMarker(LPVOID param)
{	
	int number = (int)param;

	WaitForSingleObject(hStartMarker[number - 1], INFINITE);
	ResetEvent(hStartMarker[number - 1]);

	srand(number);
	int count = 0;
	std::vector<int> changedIndexes;
	
	while (true)
	{
		int randomNuber = std::rand();
		int modul = randomNuber % MassNumber;
		EnterCriticalSection(&cs);
		if (Mass[modul] == 0)
		{
			Sleep(5);
			Mass[modul] = number;
			changedIndexes.push_back(modul);
			LeaveCriticalSection(&cs);
			Sleep(5);
			count++;
		}
		else
		{
			LeaveCriticalSection(&cs);
			std::cout << "Serial Number:" << number <<"\n";
			std::cout << "Amount of marked elements: " << count << "\n";
			std::cout << "Index of not marked element: " << modul << "\n";
			
			HANDLE events[2] = { hMarkerRestart[number - 1], hMarkerStop[number - 1] };
			SetEvent(hMarkerCantResume[number - 1]);
			DWORD result = WaitForMultipleObjects(2, events, FALSE, INFINITE);
			{
				if (result == 0)
				{
					ResetEvent(hMarkerRestart[number - 1]);
				}
				else if (result == 1)
				{
					for (int i = 0; i < changedIndexes.size(); i++)
					{
						EnterCriticalSection(&cs);
						Mass[changedIndexes[i]] = 0;
						LeaveCriticalSection(&cs);
					}
					ResetEvent(hMarkerStop[number - 1]);
					SetEvent(hMarkerStoped);
					changedIndexes.clear();
					return;
				}
				else
				{
					LeaveCriticalSection(&cs);
					std::cerr << "Wrong Response\n";
					return;
				}
			}
		}
	}


}

int main()
{
	int n;
	std::cout << "Enter amount of elements n: ";
	std::cin >> n;

	MassNumber = n;
	Mass = new int[n];
	for (int i = 0; i < n; i++)
		Mass[i] = 0;
	
	InitializeCriticalSection(&cs);
	int threadsAmount;
	std::cout << "Enter amount of threads marker: ";
	std::cin >> threadsAmount;
	
	HANDLE* hThread = new HANDLE[threadsAmount];
	DWORD* dwThread = new DWORD[threadsAmount];
	hMarkerRestart = new HANDLE[threadsAmount];
	hMarkerStop = new HANDLE[threadsAmount];
	hMarkerCantResume = new HANDLE[threadsAmount];
	hStartMarker = new HANDLE[threadsAmount];
	int* another = new int[threadsAmount];


	for (int i = 0; i < threadsAmount; i++)
	{
		another[i] = i + 1; 
	}

	for (int i = 0; i < threadsAmount; i++)
	{
		hMarkerRestart[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		hMarkerStop[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		hMarkerCantResume[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		hStartMarker[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
	}
	hMarkerStoped = CreateEvent(NULL, FALSE, FALSE, NULL);

	std::vector<int> existedMarkers;
	for (int i = 0; i < threadsAmount; i++)
		existedMarkers.push_back(i);

	for (int i = 0; i < threadsAmount; i++)
	{
		hThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadMarker, (void*) another[i], 0, &dwThread[i]);
	}

	//Создание потоков успешно


	for (int i = 0; i < threadsAmount; i++)
	{
		SetEvent(hStartMarker[i]);
	}

	//Передача сигнала успешно


	while (true)
	{
		for (int i = 0; i < existedMarkers.size(); i++)
			if (existedMarkers[i] == -1)
				SetEvent(hMarkerCantResume[i]);
		if (WaitForMultipleObjects(threadsAmount, hMarkerCantResume, TRUE, INFINITE) == WAIT_FAILED)
		{
			std::cout << "Wait for multiple objects failed." << std::endl;
			std::cout << "Press any key to exit." << std::endl;
		}
		for (int i = 0; i < existedMarkers.size(); i++)
				ResetEvent(hMarkerCantResume[i]);
		std::cout << "Massive after Makers' work:\n";
		for (int i = 0; i < n; i++)
		{
			std::cout << Mass[i] << " ";
		}
		std::cout << "\n";
		std::cout << "Enter the number of thread, that will stoped:\n";
		std::cout << "Not stoped markers yet:\n";
		for (int i = 0; i < existedMarkers.size(); i++)
			if (existedMarkers[i] != -1)
				std::cout << existedMarkers[i] << " ";
		std::cout << "\n";

		int stopedThread;
		std::cin >> stopedThread;

		for (int i = 0; i < existedMarkers.size(); i++)
		{
			if (existedMarkers[i] == stopedThread)
				existedMarkers[i] = -1;
		}

		SetEvent(hMarkerStop[stopedThread]);
		WaitForSingleObject(hMarkerStoped, INFINITE);
		ResetEvent(hMarkerStoped);


		std::cout << "The massive after Stoping next marker:\n";
		for (int i = 0; i < n; i++)
		{
			std::cout << Mass[i] << " ";
		}
		std::cout << "\n";

		bool flag = false;
		for (int i = 0; i < existedMarkers.size(); i++)
		{
			if (existedMarkers[i] != -1)
				flag = true;
		}

		if (flag == false)
		{
			std::cout << "All Markers are close\n";
			for (int i = 0; i < threadsAmount; i++)
			{
				std::cout << "Closing handle " << i << "\n";
				CloseHandle(hThread[i]);
			}
			DeleteCriticalSection(&cs);
			return 0;
		}

		for (int i = 0; i < existedMarkers.size(); i++)
		{
			if (existedMarkers[i] != -1)
			{
				SetEvent(hMarkerRestart[i]);
			}
		}
	}
}