#include <iostream>

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Insert at the end
    void insert(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Delete a node by value
    void deleteNode(int val) {
        Node* current = head;
        while (current) {
            if (current->data == val) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next; // Updating head if it's the first node
                }
                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev; // Updating tail if it's the last node
                }
                delete current;
                return;
            }
            current = current->next;
        }
    }

    // Print the list from head to tail
    void printForward() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Print the list from tail to head
    void printBackward() const {
        Node* current = tail;
        while (current) {
            std::cout << current->data << " ";
            current = current->prev;
        }
        std::cout << std::endl;
    }

    ~DoublyLinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    DoublyLinkedList dll;

    dll.insert(10);
    dll.insert(20);
    dll.insert(30);

    std::cout << "Forward print: ";
    dll.printForward(); // Output: 10 20 30

    std::cout << "Backward print: ";
    dll.printBackward(); // Output: 30 20 10

    dll.deleteNode(20);
    std::cout << "After deleting 20: ";
    dll.printForward(); // Output: 10 30

    return 0;
}
