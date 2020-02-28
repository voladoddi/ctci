#include <limits.h>
#include <iterator>
#include "sorts.h"
#include "util.h"


const std::vector<int>&  Sorter::fetch_vector()
{
    return number_list;

}

void Sorter::print_vector(const std::vector<int> & v)
{
    std::cout << "Vector elements : ";
    for (auto elem: v) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

void Sorter::reset_vector(std::vector<int> & vec)
{
    std::vector<int>::iterator vec_it, number_list_it;
    for (vec_it = vec.begin(), number_list_it = number_list.begin();
         vec_it<vec.end() && number_list_it<number_list.end(); vec_it++, number_list_it++) {
        *number_list_it = *vec_it;
    }
}

void Sorter::selectionSort()
{
    int min = INT_MAX;

    for (int i = 0; i < number_list.size(); i++) {
        int min_idx = i;
        for (int j = i+1; j < number_list.size(); j++) {
            if (number_list[j]<number_list[min_idx]) {
                min_idx = j;

                int temp = number_list[min_idx];
                number_list[min_idx] = number_list[i];
                number_list[i] = temp;
                
            }
        }

    }
}

void Sorter::bubbleSort()
{

}

void Sorter::insertionSort()
{

}

int main()
{
    // initial vector declaration and initialization
    std::vector<int> V{3,10,6,3,80,9};

    // sorter class object initialization
    Sorter sorter(V);

    // Perform first brute force 'child's sorting' mechanism
    sorter.selectionSort();
    sorter.print_vector(sorter.fetch_vector()); // print to confirm



    
    
}