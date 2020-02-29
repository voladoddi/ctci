#include <limits.h>
#include <iterator>
#include "sorts.h"
#include "util.h"  // {TODO : Why does the linker fail in calling print_vector from here?}


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
    for (int i = 0; i < number_list.size()-1; i++) {
        for (int j = 0; j < number_list.size()-i-1; j++) {
            if (number_list[j]>number_list[j+1]) {
                int temp = number_list[j];
                number_list[j] = number_list[j+1];
                number_list[j+1] = temp;
            }
        }
    }
}

void Sorter::insertionSort()
{
    int i, j , key_to_insert;
    for (i = 1; i < number_list.size(); i++) {
        key_to_insert = number_list[i];
        j = i-1;
        while( (j >= 0) && number_list[j]>key_to_insert) { // keep moving all elements to right if they're greater
            number_list[j+1] = number_list[j];
            j--;
        }
        //insert
        number_list[j+1] = key_to_insert; // All elements until j have been moved. Now it's at i-1. Therefore, insert at 'i'.
    }
}

int main()
{
    // initial vector declaration and initialization
    std::vector<int> V{3,10,6,3,80,9};

    // sorter class object initialization
    Sorter sorter(V);

    // Perform first brute force 'child's sorting' mechanism : Selection sort
    sorter.selectionSort();
    sorter.print_vector(sorter.fetch_vector()); // print to confirm {TODO: Add time measured}
    sorter.reset_vector(V);
    
    // Perform second brute force : Bubble sort
    sorter.bubbleSort();
    sorter.print_vector(sorter.fetch_vector());
    sorter.reset_vector(V);

    // Perform a slightly better sort : Insertion sort
    sorter.insertionSort();
    sorter.print_vector(sorter.fetch_vector());
    sorter.reset_vector(V);

    return 0;
}