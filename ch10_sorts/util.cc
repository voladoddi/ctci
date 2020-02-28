#include "util.h"

void print_vector(const std::vector<int> & v)
{
    std::cout << "Vector elements : ";
    for (auto elem: v) {
        std::cout << elem << " " << std::endl;
    }
}