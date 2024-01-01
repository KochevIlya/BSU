#define BOOST_TEST_MODULE MyTest
#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include "Header.h"
// Ваш код с определением структуры узла и функций

BOOST_AUTO_TEST_SUITE(LinkedListTests)

BOOST_AUTO_TEST_CASE(TestReverseList)
{
    // Создаем связный список: 1 -> 2 -> 3 -> 4 -> 5
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

    // Разворачиваем связный список
    head = reverseListRecursive(head);

    // Проверяем, что связный список теперь развернут
    BOOST_CHECK_EQUAL(head->data, 5);
    BOOST_CHECK_EQUAL(head->next->data, 4);
    BOOST_CHECK_EQUAL(head->next->next->data, 3);
    BOOST_CHECK_EQUAL(head->next->next->next->data, 2);
    BOOST_CHECK_EQUAL(head->next->next->next->next->data, 1);

    // Очищаем память
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

BOOST_AUTO_TEST_CASE(TestEmptyList)
{
    // Тестируем разворот пустого связного списка
    Node* head = nullptr;
    head = reverseListRecursive(head);

    // Для пустого списка разворот не должен повлечь изменений
    BOOST_CHECK_EQUAL(head, nullptr);
}

BOOST_AUTO_TEST_CASE(TestSingleElementList)
{
    // Тестируем разворот списка с единственным элементом
    Node* head = new Node(42);
    head = reverseListRecursive(head);

    // Разворот списка с одним элементом не должен повлечь изменений
    BOOST_CHECK_EQUAL(head->data, 42);

    // Очищаем память
    delete head;
}

// Дополнительные тесты могут быть добавлены

BOOST_AUTO_TEST_SUITE_END()

