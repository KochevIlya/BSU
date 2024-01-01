#pragma once
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

void printList(Node* head) {
    while (head != nullptr) {
        std::cout << head->data << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

Node* reverseListRecursive(Node* current, Node* prev = nullptr) {
    if (current == nullptr) {
        return prev;
    }


    Node* nextNode = current->next;


    current->next = prev;


    return reverseListRecursive(nextNode, current);
}