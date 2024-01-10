#include "Menu.h"

void menu() {
    std::cout << "----------MENU----------" << std::endl;
    std::cout << "Operations:" << std::endl;
    std::cout << "1) Create list" << std::endl;
    std::cout << "2) Get size" << std::endl;
    std::cout << "3) Push back" << std::endl;
    std::cout << "4) Push front" << std::endl;
    std::cout << "5) Pop front" << std::endl;
    std::cout << "6) Pop back" << std::endl;
    std::cout << "7) Insert" << std::endl;
    std::cout << "8) Remove at" << std::endl;
    std::cout << "9) Sort" << std::endl;
    std::cout << "10) Node sort" << std::endl;
    std::cout << "11) Save insert" << std::endl;
    std::cout << "12) Clear" << std::endl;
    std::cout << "13) Print" << std::endl;
    std::cout << "14) Write to bin" << std::endl;
    std::cout << "15) Read from bin" << std::endl;
    std::cout << "16) Balance" << std::endl;
    std::cout << "0) Exit" << std::endl;

    List<std::string> ls;
    List<std::string> fromBin;
    while (true) {
        try {
            int command, index1, index2;
            std::cout << "Enter command number -> ";
            std::cin >> command;
            if (std::cin.fail()) {
                throw std::runtime_error("Incorrect input!");
            }
            switch (command) {
            case 0:
                exit(0);
            case 1:
                ls.push_back(new std::string("aaa"));
                ls.push_back(new std::string("sdfd"));
                ls.push_back(new std::string("bbb"));
                ls.push_back(new std::string("qwer"));
                ls.push_back(new std::string("z"));
                ls.push_back(new std::string("nmvv"));
                ls.push_back(new std::string("xoop"));
                std::cout << "List has been created" << std::endl;
                break;
            case 2:
                std::cout << "Size: " << ls.GetSize() << std::endl;
                break;
            case 3:
                std::cout << "Before: " << std::endl;
                ls.Print();
                ls.push_back(new std::string("toBack"));
                std::cout << "After: " << std::endl;
                ls.Print();
                break;
            case 4:
                std::cout << "Before: " << std::endl;
                ls.Print();
                ls.push_front(new std::string("toFront"));
                std::cout << "After: " << std::endl;
                ls.Print();
                break;
            case 5:
                std::cout << "Before: " << std::endl;
                ls.Print();
                ls.pop_front();
                std::cout << "After: " << std::endl;
                ls.Print();
                break;
            case 6:
                std::cout << "Before: " << std::endl;
                ls.Print();
                ls.pop_back();
                std::cout << "After: " << std::endl;
                ls.Print();
                break;
            case 7:
                std::cout << "Index 1: ";
                std::cin >> index1;
                std::cout << "Index 2: ";
                std::cin >> index2;
                std::cout << "Before: " << std::endl;
                ls.Print();
                ls.insert(new std::string("toInsert"), index1, index2);
                std::cout << "After: " << std::endl;
                ls.Print();
                break;
            case 8:
                std::cout << "Index 1: ";
                std::cin >> index1;
                std::cout << "Index 2: ";
                std::cin >> index2;
                std::cout << "Before: " << std::endl;
                ls.Print();
                ls.removeAt(index1, index2);
                std::cout << "After: " << std::endl;
                ls.Print();
                break;
            case 9:
                std::cout << "Unsorted: " << std::endl;
                ls.Print();
                ls.sort();
                std::cout << "After: " << std::endl;
                ls.Print();
                break;
            case 10:
                std::cout << "Unsorted: " << std::endl;
                ls.Print();
                ls.node_sort();
                std::cout << "After: " << std::endl;
                ls.Print();
                break;
            case 11:
                std::cout << "Index: ";
                std::cin >> index1;
                std::cout << "Before: " << std::endl;
                ls.Print();
                ls.save_insert(new std::string("SaveInsert"), index1);
                std::cout << "After: " << std::endl;
                ls.Print();
                break;
            case 12:
                ls.clear();
                std::cout << "List has been cleared" << std::endl;
                break;
            case 13:
                ls.Print();
                break;
            case 14:
                ls.WriteBin("test.bin");
                std::cout << "List has been written to binnary" << std::endl;
                break;
            case 15:
                fromBin.ReadBin("test.bin");
                std::cout << "List from binnary:" << std::endl;
                fromBin.Print();
                break;
            case 16:
                std::cout << "Before: " << std::endl;
                ls.Print();
                ls.balance();
                std::cout << "After: " << std::endl;
                ls.Print();
                break;
            default:
                std::cout << "Unknown command" << std::endl;
                break;  
            }
        } catch(const std::exception &e) {
            std::cout << "Error: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
    }
}