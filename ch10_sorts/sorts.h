#ifndef H_SORTER_
#define H_SORTER_

#include <iostream>
#include <numeric>
#include <vector>

// {TODO} Design better. Which elements
class Sorter
{
    private:
    std:: vector<int> number_list;
    

    public:
    Sorter(std::vector<int> v): number_list(v) {};

    const std::vector<int>& fetch_vector();
    void print_vector(const std::vector<int> & v);
    void reset_vector(std::vector<int> & vec);

    // Suboptimal brute force sorts
    void bubbleSort();         // Brute
    void selectionSort();      // Brute
    void insertionSort();      // Decrease-and-conquer

    // Optimal sorting
    void quickSort();                             // Divide and conquer
    void quickSortHelper(std::vector<int> &num_list, int start, int end);
    void mergeSort();                             // Divide and conquer
    void mergeSortHelper(std::vector<int> &num_list, int start, int end );
    void heapSort();                              // Transform and conquer

    
};

#endif