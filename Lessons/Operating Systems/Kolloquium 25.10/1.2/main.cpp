#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/container/flat_set.hpp>
#include "Header.h"

int main() {
    std::vector<int> input;
    setlocale(LC_ALL, "Rus");
    
    std::cout << "������� ���������� ��������: ";
    int count;
    try {
        std::cin >> count;
    }
    catch(...)
    {
        std::cout << "�� ����� �������� �����:(";
        return 1;
    }
    std::cout << "������� ��������: ";
    for (int i = 0; i < count; i++)
    {
        std::cout << i << ". ";
        int element;
        try {
            std::cin >> element;
        }
        catch (...)
        {
            std::cout << "�� ����� �������� �����:(";
            return 1;
        }
        input.push_back(element);
    }
    input = { 1, 2, 3, 4, 2, 5, 6, 1, 7, 8, 9, 9, 4 };

    std::vector<int> result = removeDuplicates(input);

    std::cout << "�������� ������: ";
    for (int num : input) {
        std::cout << num << " ";
    }

    std::cout << "\n������ ��� ����������: ";
    for (int num : result) {
        std::cout << num << " ";
    }

    return 0;
}
