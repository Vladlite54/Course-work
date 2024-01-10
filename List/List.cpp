#include "List.h"

ListException::ListException() {
    this->info = "No info";
}

ListException::ListException(std::string info) {
    this->info = info;
}

void ListException::ShowInfo() {
    std::cout << "Called exception: " << info << std::endl;
}
