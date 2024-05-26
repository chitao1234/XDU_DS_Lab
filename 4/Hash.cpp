#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// 哈希表节点
struct HashNode {
    long number;
    string name;
    string address;
    HashNode *next;
};

// 以姓名为关键字，采用链地址法解决冲突
class HashTable1 {
   private:
    static const int TABLE_SIZE = 100;  
    HashNode *table[TABLE_SIZE];      

   public:
    HashTable1() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    int hashFunction(string userName) {
        int sum = 0;
        for (char c : userName) {
            sum += c;
        }
        return sum % TABLE_SIZE;
    }

    void insertRecord(long number, string name, string address) {
        int index = hashFunction(name);
        HashNode *newNode = new HashNode;
        newNode->number = number;
        newNode->name = name;
        newNode->address = address;
        newNode->next = nullptr;

        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

    HashNode *searchName(string name) {
        int index = hashFunction(name);
        HashNode *current = table[index];
        while (current != nullptr) {
            if (current->name == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};

// 以电话号码为关键字，采用线性探查法解决冲突
class HashTable2 {
   private:
    static const int TABLE_SIZE = 100; 
    HashNode *table[TABLE_SIZE];

   public:
    HashTable2() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    int hashFunction(long number) {
        return number % TABLE_SIZE;
    }

    void insertRecord(long number, string name, string address) {
        int index = hashFunction(number);
        int probe = 1;
        while (table[index] != nullptr) {
            index = (index + probe) % TABLE_SIZE;
            probe++;
        }

        HashNode *newNode = new HashNode;
        newNode->number = number;
        newNode->name = name;
        newNode->address = address;
        table[index] = newNode;
    }

    HashNode *searchNumber(long number) {
        int index = hashFunction(number);
        int probe = 1;
        while (table[index] != nullptr) {
            if (table[index]->number == number) {
                return table[index];
            }
            index = (index + probe) % TABLE_SIZE;
            probe++;
        }
        return nullptr;
    }
};

int main() {
    HashTable1 hashTable1;
    HashTable2 hashTable2;
    ifstream inputFile("data.txt");
    long number;
    string name, address;

    // 从数据文件中读取记录并插入哈希表
    while (inputFile >> number >> name >> address) {
        hashTable1.insertRecord(number, name, address);
        hashTable2.insertRecord(number, name, address);
    }
    inputFile.close();

    cout << "Input Choice: " << endl
         << "1. search by number" << endl
         << "2. search by name" << endl
         << "3. quit" << endl;
    HashNode *found;
    int choice = 0;
    while (cin >> choice && choice != 3) {
        if (choice == 1) {
            // 从键盘输入待查找的记录
            cout << "Input Number: ";
            cin >> number;
            found = hashTable2.searchNumber(number);
            if (found != nullptr) {
                cout << "Found!" << endl;
                cout << "Number: " << found->number << endl;
                cout << "Name: " << found->name << endl;
                cout << "Address: " << found->address << endl;
            } else {
                cout << "Not found!" << endl;
            }
        } else if (choice == 2) {
            cout << "Input Name: ";
            cin >> name;
            found = hashTable1.searchName(name);
            if (found != nullptr) {
                cout << "Found!" << endl;
                cout << "Number: " << found->number << endl;
                cout << "Name: " << found->name << endl;
                cout << "Address: " << found->address << endl;
            } else {
                cout << "Not found!" << endl;
            }
        }
        cout << "Input Choice: " << endl
             << "1. search by number" << endl
             << "2. search by name" << endl
             << "3. quit" << endl;
    }
    return 0;
}
