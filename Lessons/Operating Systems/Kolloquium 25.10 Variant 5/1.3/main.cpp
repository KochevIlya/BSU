#include <iostream>
#include "Header.h"

int main() {
    setlocale(LC_ALL, "Rus");
    int n;
    std::cout << "������� ���������� ��������� � ������� ������: ";
    std::cin >> n;

    if (n <= 0) {
        std::cerr << "�������� ���������� ���������. ���������� ���������." << std::endl;
        return 1;
    }

    Node* head = nullptr;
    Node* tail = nullptr;

    std::cout << "������� �������� �������� ������ ����� ������: ";
    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;

        if (i == 0) {
            head = tail = new Node(value);
        }
        else {
            tail->next = new Node(value);
            tail = tail->next;
        }
    }

    std::cout << "�������� ������: ";
    printList(head);

   
    head = reverseListRecursive(head);

    std::cout << "����������� ������: ";
    printList(head);

  
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
