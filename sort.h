#ifndef SORT_H
#define SORT_H

#include<vector>

class Sort
{
public:
    Sort() = delete;
    static void bubbleSort(std::vector<int>&);
    static void insertionSort(std::vector<int>&);
    static void selectionSort(std::vector<int>&);
};


#endif // SORT_H
