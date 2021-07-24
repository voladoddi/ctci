#include <limits.h>
#include <iterator>
#include <type_traits>
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

// ------------------------------------------ SUBOPTIMAL SORTS ----------------- {TODO: Update notes on when to use which, time/space}
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

// ------------------------------------------------- EFFICIENT SORTS ------------------------------------------
void Sorter::mergeSortHelper(std::vector<int> &num_list, int start, int end )
{
    if (end >= start) {
        return;
    }
    
    std::cout << "start : " << start << " end: " << end;
    for (int b = start; b <=end; b++) {
        std::cout << num_list[b];
    }
    std::cout << std::endl;

    int mid = start + (end-start)/2;
    mergeSortHelper(num_list,  start,  mid);
    mergeSortHelper(num_list, mid+1, end);

    std::vector<int>aux(end-start+1,0);
    int i = start;
    int j = mid + 1;
    int k = 0;

    while(i <= mid && j <= end) {
        if(num_list[i]<=num_list[j]) {
            aux[k++] = num_list[i++];
        } else {
            aux[k++] = num_list[j++];
        }
    }
    while(i<=mid){
        aux[k++]=num_list[i++];
    }
    while(j<=end) {
        aux[k++] = num_list[j++];
    }

    for (int e = start; e <=end; e++) {
        num_list[e] = aux[e];
    }
}

void Sorter::mergeSort()
{
    Sorter::mergeSortHelper(number_list, 0, number_list.size()-1);
}

// -------------------------------- Quick sort  --------------------------------------------------------

/* --------- Recursive ------------------*/
// Pivot on the first element

// Pick a random pivot

// Pivot on the last element
int static partition(std::vector<int> &num_list, int start, int end)
{
    int i = 0;
    int pivot_element = num_list[end];
    for(int j = i+1; j < end; j++) {
        if (num_list[j] < pivot_element) {
            std::swap(num_list[++i], num_list[j]);
        }
    }
    std::swap(num_list[i+1], num_list[end]);
    return i+1;
}

void Sorter::quickSortHelper(std::vector<int> &num_list, int start, int end)
{
     if (start>=end) {
         return;
     }
     int pivot = partition(num_list, start, end);
     quickSortHelper(num_list, start, pivot-1);
     quickSortHelper(num_list, pivot+1, end);
}

/* ------------------ Iterative ------------------- */

void Sorter::quickSort()
{
    Sorter::quickSortHelper(number_list, 0, number_list.size()-1);
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

    // --------------- DIVIDE AND CONQUER ---------------------

    // Merge sort 
    sorter.mergeSort();
    sorter.print_vector(sorter.fetch_vector());
    sorter.reset_vector(V);

    // Quick sort
    sorter.quickSort();
    sorter.print_vector(sorter.fetch_vector());
    sorter.reset_vector(V);

    return 0;
}