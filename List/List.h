#pragma once

#include <iostream>
#include <fstream>

////����� ����������////
class ListException {
public:
    ListException();
    ListException(std::string info);
    void ShowInfo();
private:
    std::string info;
};

////����� ������////
template<typename T> 
class List {
public:
    List(); // ����������� �� ���������
    List(int MAX_DATA_SIZE); // �����������, ������������ ��������� ����. ������ ������� ����������
    ~List(); // ����������
    int GetSize() {return this->Size;} // ������� ����� ������ 
    void push_back(T *data); // �������� � ����� 
    void push_front(T *data); // �������� � ������
    void pop_front(); // ������� �� ������
    void pop_back(); // ������� � �����
    void insert(T *data, int index_1, int index_2); // ������� �� �������
    void removeAt(int index_1, int index_2); // �������� �� �������
    void sort(); // ������ ����������
    void node_sort(); // ���������� ���� �����
    void save_insert(T *data, int index); // ������� � ����������� �������
    void clear(); // ��������� �������� ������
    void Print(); // ������� ������ �� �����
    T **&operator[](const int index); // �������� ����������
    void WriteBin(std::string path); // ������ � �������� ����
    void ReadBin(std::string path); // ������ � ��������� �����
    void balance(); // ������������

private:
    //��������� ���� ������
    struct Node {
    public:
        T** data; // ������ ����������
        Node *pNext; // ��������� �� ����. �������
        int dataSize; // ������� ������ ������� ����������

        Node();

        Node(T *value);

        void PushToData(T *value) { // �������� � ����� �������
            if (data == nullptr) {
                data = new T*[dataSize + 1];
                data[dataSize - 1] = value;
                data[dataSize] = nullptr;
                return;
            }
            T **temp = new T*[dataSize + 2];
            for (int i = 0; i < dataSize; i++) {
                temp[i] = data[i];
            }
            temp[dataSize] = value;
            temp[dataSize + 1] = nullptr;
            delete[] data;
            data = temp;
            dataSize++;
        }

        void PushDataFront(T *value) { // �������� � ������ �������
            if (data == nullptr) {
                data = new T*[dataSize + 1];
                data[dataSize - 1] = value;
                data[dataSize] = nullptr;
                return;
            }
            T **temp = new T*[dataSize + 2];
            temp[0] = value;
            for (int i = 1; i < dataSize + 2; i++) {
                temp[i] = data[i-1];
            }
            delete[] data;
            data = temp;
            dataSize++;
        }

        void PopDataFront() { // ������� �� ������ �������
            if (dataSize == 0) throw ListException("Nothing to pop");
            delete data[0];
            T **temp = new T*[dataSize];
            for (int i = 1; i < dataSize + 1; i++) {
                temp[i-1] = data[i];
            }
            delete[] data;
            data = temp;
            dataSize--;
        }

        void PopDataBack() { // ������� � ����� �������
            if (dataSize == 0) throw ListException("Nothing to pop");
            dataSize--;
            T **temp = new T*[dataSize + 1];
            for (int i = 0; i < dataSize; i++) {
                temp[i] = data[i];
            }
            temp[dataSize] = nullptr;
            delete[] data;
            data = temp;
        }

        void InsertData(T *value, int index) { // �������� � ������ �� �������
            if (index < 0 || index > dataSize - 1) throw ListException("Invalid index");
            dataSize++;
            T **temp = new T*[dataSize + 1];
            for (int i = 0; i < index; i++) {
                temp[i] = data[i];
            }
            temp[index] = value;
            for (int i = index + 1; i < dataSize + 1; i++) {
                temp[i] = data[i - 1];
            }
            
            delete[] data;
            data = temp;
        }

        void RemoveData(int index) { // ������� �� ������� �� �������
            if (index < 0 || index > dataSize - 1) throw ListException("Invalid index");
            if (dataSize == 0) throw ListException("Nothing to remove");
            delete data[index];
            dataSize--;
            for (int i = index; i < dataSize; i++) {
                data[i] = data[i + 1];
            }
            data[dataSize] = nullptr;
        }

        void SortData() { // ������������� ������
            for (int i = 0; i < dataSize; i++) {
                for (int j = 0; j < dataSize - 1; j++) {
                    if (*data[j] > *data[j + 1]) {
                        T temp = *data[j];
                        *data[j] = *data[j + 1];
                        *data[j + 1] = temp;
                    }
                }
            }       
        }

        void PrintData() { // ������� ������ �� �����
            for (int i = 0; i < dataSize; i++) {
                std::cout << *data[i] << " ";
            }
            std::cout << std::endl;
        }

    };

    int Size; // ������ ������
    int MAX_DATA_SIZE; // ������������ ������ ������� ����������
    Node *head; // ��������� �� 1-� ������� ������
};

////������������ � ����������//////
template <typename T>
inline List<T>::List() {
    this->Size = 0;
    this->MAX_DATA_SIZE = 1;
    this->head = nullptr;
}

template <typename T>
inline List<T>::List(int MAX_DATA_SIZE) {
    this->Size = 0;
    this->MAX_DATA_SIZE = MAX_DATA_SIZE;
    this->head = nullptr;
}

template <typename T>
inline List<T>::~List() {
    clear();
}

////�������� �������� �������////
template <typename T>
inline void List<T>::push_back(T *data) {
    if (head == nullptr) {
        this->head = new Node(data);
        Size++;
    } else {
        Node *current = this->head;
        while (current->pNext != nullptr) {
            current = current->pNext;
        }
        if (current->dataSize < MAX_DATA_SIZE) { // ���� �� ��������� �����������, ��������� ������
            current->PushToData(data);
        } else {
            current->pNext = new Node(data); // ������� ����� ������� ������
            MAX_DATA_SIZE = MAX_DATA_SIZE * 2;
            Size++;
        }
    }
}

template <typename T>
inline void List<T>::push_front(T *value) {
    if (head == nullptr || head->dataSize > 1 ) {
        Node *temp = head;
        head = new Node(value);
        head->pNext = temp;
        Size++;
    } else if(head->pNext == nullptr || head->dataSize < head->pNext->dataSize / 2 ) {
        head->PushDataFront(value);
    } else {
        head->PushDataFront(value);
        Node *current = head;
        //���� ������ ������� �������, �������� ��������� ������� �������//
        while (current->dataSize > current->pNext->dataSize / 2 ) { 
            T *last = current->data[current->dataSize - 1];
            current->PopDataBack();
            current = current->pNext;
            current->PushDataFront(last);
            if (current->pNext == nullptr) {
                if (current->dataSize <= MAX_DATA_SIZE) {
                    break;
                } else {
                    T *last = current->data[current->dataSize - 1];
                    current->PopDataBack();
                    current->pNext = new Node(last);
                    Size++;
                    MAX_DATA_SIZE = MAX_DATA_SIZE * 2;
                    break;
                }
            }
        }

    }
}

template <typename T>
inline void List<T>::pop_front() {
    if (Size == 0) throw ListException("Nothing to pop");
    if (head->dataSize > 1) {
        head->PopDataFront();
    } else {
        Node *temp = head;
        head = head->pNext;
        delete temp;
        Size--;
        
    }
}

template <typename T>
inline void List<T>::pop_back() {
    if (Size == 0) throw ListException("Nothing to pop");
    Node *last;
    for (last = head; last->pNext != nullptr; last = last->pNext);
    removeAt(Size - 1, last->dataSize - 1);
}

template <typename T>
inline void List<T>::insert(T *value, int index_1, int index_2) {
    if (index_1 < 0 || index_1 > Size - 1) throw ListException("Invalid index");
    if (index_1 == 0 && index_2 == 0) {
        push_front(value);
    } else {
        Node *current = head;
		for (int i = 0; i < index_1; i++) {
			current = current->pNext;
		}
        current->InsertData(value, index_2);
        //���� ������ ������� �������, �������� ��������� ������� �������//
        while (current->dataSize > current->pNext->dataSize / 2 ) {
            T *last = current->data[current->dataSize - 1];
            current->PopDataBack();
            current = current->pNext;
            current->PushDataFront(last);
            if (current->pNext == nullptr) {
                if (current->dataSize <= MAX_DATA_SIZE) {
                    break;
                } else {
                    T *last = current->data[current->dataSize - 1];
                    current->PopDataBack();
                    current->pNext = new Node(last);
                    Size++;
                    MAX_DATA_SIZE = MAX_DATA_SIZE * 2;
                    break;
                }
            }
        }
    }
}

template <typename T>
inline void List<T>::removeAt(int index_1, int index_2) {
    if (index_1 < 0 || index_1 > Size - 1) throw ListException("Invalid index");
    if (index_1 == 0) {
        if (index_2 == 0) {
            pop_front();
        } else {
            head->RemoveData(index_2);
        }
    } else {
        Node *previous = this->head;
		for (int i = 0; i < index_1 - 1; i++) {
			previous = previous->pNext;
		}
        Node *toDelete = previous->pNext;

        if (toDelete->dataSize > 1)
        {
            toDelete->RemoveData(index_2);
        }
        else
        {
            previous->pNext = toDelete->pNext;
		    delete toDelete;
            Size--;
            MAX_DATA_SIZE = MAX_DATA_SIZE / 2;
        }
    }
}

template <typename T>
inline void List<T>::sort() {
    //������� ������� ��� �������� ������ � ���� ������ ����������//
    int line_size = 0;
    for (Node *current = head; current != nullptr; current = current->pNext) {
        line_size += current->dataSize;
    }
    T **line = new T*[line_size];
    int line_index = 0;
    for (Node *current = head; current != nullptr; current = current->pNext) {
        for (int i = 0; i < current->dataSize; i++, line_index++) {
            line[line_index] = current->data[i];
        }
    }
    //���������� ���������//
    for (int i = 0; i < line_size; i++) {
        for (int j = 0; j < line_size - 1; j++) {
            if (*line[j] > *line[j + 1]) {
                T temp = *line[j];
                *line[j] = *line[j + 1];
                *line[j + 1] = temp;
            }
        }
    }
}

template <typename T>
inline void List<T>::node_sort() {
    for (Node *current = head; current != nullptr; current = current->pNext) {
        current->SortData();
    }
}

template <typename T>
inline void List<T>::save_insert(T *value, int index) {
    if (index < 0 || index > Size - 1) throw ListException("Invalid index");
    int count = 0;
    Node *current = head;
	for (int i = 0; i < index; i++) {
		current = current->pNext;
	}
    current->SortData();
    for (int j = 0; j < current->dataSize; j++) {
        if (*current->data[j] > *value) break;
        count++;
    }
    insert(value, index, count);

}

template <typename T>
inline void List<T>::clear() {
    while(Size) {
        pop_front();
    }
    MAX_DATA_SIZE = 1;
}

template <typename T>
inline void List<T>::Print() {
    int counter = 0;
    Node *current = this->head;
    while (counter < Size) {
         std::cout << "L" << counter + 1 << std::endl;
        current->PrintData();
        counter++;
        current = current->pNext;
    }
    std::cout << std::endl;
}

template <typename T>
inline T **&List<T>::operator[](const int index) {
    if (index < 0 || index > Size) throw ListException("Invalid index");
    int counter = 0;
    Node *current = this->head;
    
    while (counter <= index) {
        if (counter == index) {
            break;
        }
        counter++;
        current = current->pNext;
    }
    return current->data;
}

template <typename T>
inline void List<T>::WriteBin(std::string path) {
    //������� ������� ��� �������� ������ � ���� ������ ����������//
    int line_size = 0;
    for (Node *current = head; current != nullptr; current = current->pNext) {
        line_size += current->dataSize;
    }
    T **line = new T*[line_size];
    int line_index = 0;
    for (Node *current = head; current != nullptr; current = current->pNext) {
        for (int i = 0; i < current->dataSize; i++, line_index++)
        {
            line[line_index] = current->data[i];
        }
    }
    //������� �������� �� ������� � ����//
    std::ofstream fout;
    fout.open(path, std::ios::binary | std::ofstream::app);
    if (!fout.is_open()) {
        std::cout << "Can't open the file" << std::endl;
    } else {
        fout.write((char*)&line_size, sizeof(int));
        for (int i = 0; i < line_size; i++) {
            T value = *line[i];
            fout.write((char*)&value, sizeof(T));
        }
    }
}

template <typename T>
inline void List<T>::ReadBin(std::string path) {
    std::ifstream fin;
    fin.open(path, std::ios::binary | std::ifstream::in);
    if (!fin.is_open()) {
        std::cout << "Can't open the file" << std::endl;
    } else {
        int size; // �������� ���������� ���������
        fin.read((char*)&size, sizeof(int));
        for (int i = 0; i < size; i++) {
            T value;
            fin.read((char*)&value, sizeof(T));
            T *toPush = new T(value);
            push_back(toPush); // ��������� �������� � ������
        }
        
    }
}

template <typename T>
inline void List<T>::balance() {
    //������� ������� ��� �������� ������ � ���� ������ ����������//
    int line_size = 0;
    for (Node *current = head; current != nullptr; current = current->pNext) {
        line_size += current->dataSize;
    }
    T **line = new T*[line_size];
    int line_index = 0;
    for (Node *current = head; current != nullptr; current = current->pNext) {
        for (int i = 0; i < current->dataSize; i++, line_index++)
        {
            T *value = new T(*current->data[i]); // ��������� ������ � ������
            line[line_index] = value;
        }
    }
    clear(); // ������� ������ ������
    for (int i = 0; i < line_size; i++) {
        push_back(line[i]); // ��������� �� �������, ���������� �����������
    }
}

////����������������� ������������ � ������////
template <typename T>
inline List<T>::Node::Node() {
    this->dataSize = 0;
    this->data = nullptr;
    this->pNext = nullptr;
}

template <typename T>
inline List<T>::Node::Node(T *value) {
    this->dataSize = 1;
    this->data = new T*[this->dataSize + 1];
    this->data[this->dataSize - 1] = value;
    this->data[this->dataSize] = nullptr;
    this->pNext = nullptr;
}
