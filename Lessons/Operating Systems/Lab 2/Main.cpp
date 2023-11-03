#include <iostream>

#include <windows.h>


LPVOID WINAPI min_max(int* Mass)
{
	int temp_max= Mass[5];
	int temp_min= Mass[5];
	int tempIndMax = 5;
	int tempIndMin = 5;
	for (int i = 5; i < Mass[0] + 5; i++)
	{
		if (temp_max < Mass[i])
		{
			temp_max = Mass[i];
			tempIndMax = i;
		}
		Sleep(7);
		if (temp_min > Mass[i])
			{
			temp_min = Mass[i];
			tempIndMin = i;
		}
		Sleep(7);
	}
	Mass[1] = temp_min;
	Mass[2] = temp_max;
	Mass[3] = tempIndMin;
	Mass[4] = tempIndMax;
	std::cout << tempIndMin << " " <<tempIndMax<< "\n";
	return 0;
}

DWORD WINAPI average(int* Mass)
{
	long long sum = 0;
	for (int i = 0; i < Mass[0]; i++)
	{
		sum += Mass[i+5];
		Sleep(12);
	}
	std::cout << (int)sum / Mass[0]<< "\n";
	return (DWORD) sum / Mass[0];
}

int main() {


	setlocale(LC_ALL, "Rus");
	int n;
	int max;
	int min;
	int indMax;
	int indMin;
	int aver;
	std::cout << "¬ведите размерность массива\n";
	std::cin >> n;
	int* Mass = new int[n + 5];
	Mass[0] = n;

	for (int i = 0; i < n; i++)
	{
		std::cout << "¬ведите элемент: " << i << "\n";
		std::cin >> Mass[i + 5];
	}

	HANDLE hMin_max;
	DWORD IDMin_max;

	HANDLE hAverage;
	DWORD IDAverage;

	hMin_max = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)min_max, (void*)Mass, 0, &IDMin_max);
	hAverage = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)average, (void*)Mass, 0, &IDAverage);

	WaitForSingleObject(hMin_max, INFINITE);
	WaitForSingleObject(hAverage, INFINITE);
	
	GetExitCodeThread(hAverage, (LPDWORD)&aver);
	std::cout <<"Average" << aver << "\n";
	CloseHandle(hMin_max);
	CloseHandle(hAverage);
	indMax = Mass[4];
	indMin = Mass[3];
	Mass[indMax] = aver;
	Mass[indMin] = aver;
	for (int i = 0; i < n; i++)
	{
		std::cout << Mass[i + 5] << " ";
	}

}