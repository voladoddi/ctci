#ifndef H_SORTER_
#define H_SORTER_

#include <iostream>
#include <numeric>
#include <vector>


class Sorter
{
    private:
    std:: vector<int> number_list;
    void reset_vector(std::vector<int> & vec);

    public:
    Sorter(std::vector<int> v): number_list(v) {};

    const std::vector<int>& fetch_vector();
    void print_vector(const std::vector<int> & v);

    // Suboptimal brute force sorts
    void bubbleSort();         // Brute
    void selectionSort();      // Brute
    void insertionSort();      // Decrease-and-conquer

    // Optimal sorting
    void quickSort();                             // Divide and conquer
    void MergeSort();                             // Divide and conquer
    void HeapSort();                              // Transform and conquer

    
};

#endif