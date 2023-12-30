#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
int res = 0;
struct st
{
	bool isoperated;
	int StartNumber;
	int JumpNumber;
	std::string name;
	double res;
};

double doing(int a, std::vector<double>& vect)
{
	double res;
	switch (a)
	{
	case 1:
		res = 0.0;
		for (int i = 0; i < vect.size(); i++)
		{
			res += vect[i];
		}
		return res;
	case 2:
		res = 1.0;
		for (int i = 0; i < vect.size(); i++)
		{
			res *= vect[i];
		}
		return res;
	case 3:
		res = 0.0;
		for (int i = 0; i < vect.size(); i++)
		{
			res += vect[i] * vect[i];
		}
		return res;
	default:
		break;
	}
	return 0;
}
bool chek(std::string name)
{
	std::ifstream m;
	m.open(name);
	if (m.is_open())
	{
		m.close();
		return true;
	}
	m.close();
	return false;
}
DWORD WINAPI thr(LPVOID d)
{
	st* data = (st*)d;
	int k = 0;
	std::ifstream in;
	std::string e("\\"), r("in_"), t(".dat");
	while (chek(data->name + e + r + std::to_string(data->StartNumber + data->JumpNumber * k) + t))
	{
		in.open(data->name + e + r + std::to_string(data->StartNumber + data->JumpNumber * k) + t);
	
		int a;
		double x;
		double y;
		in >> a;
		std::vector<double> vect;

		while (!in.eof())
		{
			in >> x;
			vect.push_back(x);
		}
		data->res += doing(a, vect);
		k++;
		in.close();
	}
	data->isoperated = true;
	return 0;
}

class MakeThreads
{
	std::string NameOfDir;
	int CountOfThreads;
	DWORD* ips;
	st* data;
	HANDLE* thrs;
public:
	MakeThreads(std::string namef, int countt)
	{
		NameOfDir = namef;
		CountOfThreads = countt;
		double res = 0;
		data = new st[countt];
		ips = new DWORD[countt];
		thrs = new HANDLE[countt];
	}
	void making()
	{

		for (int i = 1; i <= CountOfThreads; i++)
		{
			std::string t = std::to_string(i + 1);
			SECURITY_ATTRIBUTES sa;
			data[i - 1].JumpNumber = CountOfThreads;
			data[i - 1].StartNumber = i;
			data[i - 1].name = NameOfDir;
			data[i - 1].isoperated = false;
			data[i - 1].res = 0;
			sa.bInheritHandle = TRUE;
			ZeroMemory(&sa, sizeof(SECURITY_ATTRIBUTES));
			thrs[i - 1] = CreateThread(&sa, 0, thr, (LPVOID)&data[i - 1], 0, &ips[i - 1]);
			if (thrs[i - 1] == NULL)
			{
			 std::cout << std::endl << "Thread " << (i - 1) << " is not created." << std::endl;
			}
		}
	}
	double calc()
	{
		double res = 0;
		int i = 0;
		while (true)
		{
			if (data[i].isoperated)
			{
				res += data[i].res;
				i++;
			}
			if (i == CountOfThreads)
			{
				break;
			}
		}
		return res;
	}
	bool chek(std::string name)
	{
		std::ifstream m;
		m.open(name);
		if (m.is_open())
		{
			m.close();
			return true;
		}
		m.close();
		return false;
	}
	double doing(int a, double x, double y)
	{
		switch (a)
		{
		case 1:
			return x + y;
		case 2:
			return x * y;
		case 3:
			return x * x + y * y;
		default:
			break;
		}
		return 0;
	}
	~MakeThreads()
	{
		for (int i = 0; i < CountOfThreads; i++)
		{
			if (thrs[i] != NULL) 
			{
			 CloseHandle(thrs[i]);
			}
		}
	}
};

int main()
{
	std::fstream in("");
	std::string path;
	int count;
	std::cout << "Enter the path: ";
	std::cin >> path;
	std::cout << "Enter the count: ";
	std::cin >> count;
	MakeThreads maker(path, count);
	maker.making();
	double res = maker.calc();
	std::string h = path + "\\out.dat";
	std::ofstream out(h);
	std::cout << res << "\n";
	out << res;
	out.close();
}