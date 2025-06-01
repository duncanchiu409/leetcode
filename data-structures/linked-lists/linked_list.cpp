class LinkedList {
public:
    class Node {
        public:
            int value;
            Node* next;

        Node(int val){
            this->value = val;
            this->next = NULL;
        }
    };

    Node* head;
    int length;

    LinkedList() {
        this->head = NULL;
        this->length = 0;
    }

    int get(int index) {
        if(index >= this->length){
            return -1;
        } else {
            Node* tmp_node = this->head;
            int tmp_index = 0;
            while(tmp_node != NULL){
                if(tmp_index == index){
                    return tmp_node->value;
                }
                tmp_node = tmp_node->next;
                ++tmp_index;
            }
            return -1;
        }
    }

    void insertHead(int val) {
        Node* new_node = new Node(val);
        new_node->next = this->head;
        this->head = new_node;
        ++this->length;
    }

    void insertTail(int val) {
        if(this->length == 0){
            Node* new_node = new Node(val);
            this->head = new_node;
            ++this->length;
        } else {
            Node* new_node = new Node(val);
            Node* tmp_node = this->head;
            while(tmp_node->next != NULL){
                tmp_node = tmp_node->next;
            }
            tmp_node->next = new_node;
            ++this->length;
        }
    }

    bool remove(int index) {
        if(index >= this->length){
            return false;
        } else {
            if(index == 0){
                Node* release_node = this->head;
                this->head = this->head->next;
                --this->length;
                delete release_node;
                return true;
            } else if(index == this->length-1){
                Node* tmp_node = this->head;
                int tmp_index = 0;
                while(tmp_index < this->length-1){
                    tmp_node = tmp_node->next;
                    ++tmp_index;
                }
                delete tmp_node->next;
                tmp_node->next = NULL;
                --this->length;
                return true;
            } else {
                Node* tmp_node = this->head;
                int tmp_index = 0;
                while(tmp_index < index-1){
                    tmp_node = tmp_node->next;
                    ++tmp_index;
                }
                Node* release_node = tmp_node->next;
                tmp_node->next = release_node->next;
                delete release_node;
                --this->length;
                return true;
            }
        }
    }

    vector<int> getValues() {
        vector<int> result;
        Node* tmp_node = this->head;
        while(tmp_node != NULL){
            result.push_back(tmp_node->value);
            tmp_node = tmp_node->next;
        }
        return result;
    }
};