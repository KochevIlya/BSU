#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include "Header.h"
namespace mp = boost::multiprecision;

// ������� ��� ���������� ���������� ����� � �������������� boost::multiprecision
// ������� ��� ��������� ������ n ����������� � �������������� boost::multiprecision
std::vector<mp::cpp_int> generateFactorials(int n) {
    std::vector<mp::cpp_int> factorials;

    for (int i = 0; i < n; ++i) {
        factorials.push_back(calculateFactorial(i + 1));
    }

    return factorials;
}

int main() {
    // ������ ����������� ����� n
    int n;
    setlocale(LC_ALL, "Rus");
    std::cout << "������� ����������� ����� n: ";
    std::cin >> n;

    // ���������� ���������� � ������� ���������
    std::vector<mp::cpp_int> result = generateFactorials(n);

    std::cout << "������ " << n << " �����������: ";
    for (int i = 0; i < n; ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << "\n";
    std::cout << "������� ������, ����� ��������� ����������: ";
    char ch = '0';
    std::cin >> ch;
    return 0;
}
