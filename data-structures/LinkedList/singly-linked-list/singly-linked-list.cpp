#include <iostream>

class Node {
  public:
    int value;
    Node* next;

    Node(int val) {
      this->value = val;
      this->next = NULL;
    }
};

class SinglyLinkedList {
  public:
    Node* head;
    int length;

    SinglyLinkedList() {
      this->head = NULL;
      this->length = 0;
    }

    int get(int index) {
      if(index >= this->length) {
        return -1;
      } else {
        int tmp_index = 0;
        Node* tmp_node = this->head;
        while(tmp_node != NULL) {
          if(tmp_index == index) {
            return tmp_node->value;
          }
          tmp_node = tmp_node->next;
          tmp_index++;
        }
        return -1;
      }
    }

    // Insert a new node at the head of the list
    // Time Complexity: O(1)
    // Space Complexity: O(1)
    void insertHead(int val) {
      Node* new_node = new Node(val);
      new_node->next = this->head;
      this->head = new_node;
      ++this->length;
    }

    // Insert a new node at the tail of the list
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    void insertTail(int val) {
      Node* tmp_node = this->head;
      while(tmp_node->next != NULL) {
        tmp_node = tmp_node->next;
      }
      Node* new_node = new Node(val);
      tmp_node->next = new_node;
      ++this->length;
    }

    // Insert a new node at the specified index or at the tail of the list
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    void insert(int val, int index) {
      if(index >= this->length) {
        this->insertTail(val);
      } else if (index == 0) {
        this->insertHead(val);
      } else {
        int tmp_index = 0;
        Node* tmp_node = this->head;

        while(tmp_index < index-1) {
          tmp_node = tmp_node->next;
          ++tmp_index;
        }

        Node* new_node = new Node(val);
        new_node->next = tmp_node->next;
        tmp_node->next = new_node;
        ++this->length;
      }
    }

    // Delete the head node
    // Time Complexity: O(1)
    // Space Complexity: O(1)
    void deleteHead() {
      if(this->length == 0) {
        return;
      } else {
        Node* tmp_node = this->head;
        this->head = this->head->next;
        delete tmp_node;
      }
    }

    // Delete the tail node
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    void deleteTail() {
      if(this->length == 0) {
        return;
      } else if (this->length == 1) {
        this->deleteHead();
      } else {
        Node* tmp_node = this->head;
        while(tmp_node->next->next != NULL) {
          tmp_node = tmp_node->next;
        }
        Node* tmp_delete_node = tmp_node->next;
        tmp_node->next = NULL;
        delete tmp_delete_node;
        --this->length;
      }
    }

    // Delete the node at the specified index
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    void delete(int index) {
      if(index >= this->length) {
        this->deleteTail();
      } else if (index == 0) {
        this->deleteHead();
      } else {
        int tmp_index = 0;
        Node* tmp_node = this->head;
        while(tmp_index < index-1) {
          tmp_node = tmp_node->next;
          ++tmp_index;
        }
        Node* tmp_delete_node = tmp_node->next;
        tmp_node->next = tmp_node->next->next;
        delete tmp_delete_node;
        --this->length;
      }
    }

    void printList() {
      Node* tmp_node = this->head;
      while(tmp_node != NULL) {
        std::cout << tmp_node->value << " ";
        tmp_node = tmp_node->next;
      }
      std::cout << std::endl;
    }
};
