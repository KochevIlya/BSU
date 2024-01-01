#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include "Header.h"
namespace mp = boost::multiprecision;

// Функция для вычисления факториала числа с использованием boost::multiprecision
// Функция для получения первых n факториалов с использованием boost::multiprecision
std::vector<mp::cpp_int> generateFactorials(int n) {
    std::vector<mp::cpp_int> factorials;

    for (int i = 0; i < n; ++i) {
        factorials.push_back(calculateFactorial(i + 1));
    }

    return factorials;
}

int main() {
    // Вводим натуральное число n
    int n;
    setlocale(LC_ALL, "Rus");
    std::cout << "Введите натуральное число n: ";
    std::cin >> n;

    // Генерируем факториалы и выводим результат
    std::vector<mp::cpp_int> result = generateFactorials(n);

    std::cout << "Первые " << n << " факториалов: ";
    for (int i = 0; i < n; ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << "\n";
    std::cout << "Введите символ, чтобы завершить выполнение: ";
    char ch = '0';
    std::cin >> ch;
    return 0;
}
