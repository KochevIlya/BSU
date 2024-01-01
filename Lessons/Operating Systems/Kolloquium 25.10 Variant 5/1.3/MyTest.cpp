#define BOOST_TEST_MODULE MyTest
#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include "Header.h"
// ��� ��� � ������������ ��������� ���� � �������

BOOST_AUTO_TEST_SUITE(LinkedListTests)

BOOST_AUTO_TEST_CASE(TestReverseList)
{
    // ������� ������� ������: 1 -> 2 -> 3 -> 4 -> 5
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

    // ������������� ������� ������
    head = reverseListRecursive(head);

    // ���������, ��� ������� ������ ������ ���������
    BOOST_CHECK_EQUAL(head->data, 5);
    BOOST_CHECK_EQUAL(head->next->data, 4);
    BOOST_CHECK_EQUAL(head->next->next->data, 3);
    BOOST_CHECK_EQUAL(head->next->next->next->data, 2);
    BOOST_CHECK_EQUAL(head->next->next->next->next->data, 1);

    // ������� ������
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

BOOST_AUTO_TEST_CASE(TestEmptyList)
{
    // ��������� �������� ������� �������� ������
    Node* head = nullptr;
    head = reverseListRecursive(head);

    // ��� ������� ������ �������� �� ������ ������� ���������
    BOOST_CHECK_EQUAL(head, nullptr);
}

BOOST_AUTO_TEST_CASE(TestSingleElementList)
{
    // ��������� �������� ������ � ������������ ���������
    Node* head = new Node(42);
    head = reverseListRecursive(head);

    // �������� ������ � ����� ��������� �� ������ ������� ���������
    BOOST_CHECK_EQUAL(head->data, 42);

    // ������� ������
    delete head;
}

// �������������� ����� ����� ���� ���������

BOOST_AUTO_TEST_SUITE_END()

