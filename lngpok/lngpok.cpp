//
//  main_lngpok.cpp
//  Numbers
//
//  Created by Bogdan Shubravyi on 4/26/16.
//  Copyright © 2016 Bogdan Shubravyi. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <iomanip>
#include <unistd.h>

/*
 1 (7) - 0 10 15 50 0 14 9 12 40
 2 (3) - 1 1 1 2 1 1 3
 3 (4) - 5 6 5 6 5 6 5 6 5 6 5 0 0
 4 (7) - 0 0 0 1 3 5 7 10 15 20
 5 (6) - 0 0 0 1 3 7 8
 6 (12)- 0 0 0 0 0 0 1 2 3 7 8 10 15
 7 (6) - 0 0 0 1 4 7 9 11 15 19
 8 (1) - 0
 9 (5) - 0 0 0 0 0
 10 (4)- 1 0 1 0 1 0 1
 11 (6)- 100 101 102 103 104 105 104 103 102 101
 12 (16)- 105 104 103 102 101 100 99 98 97 96 95 94 93 92 91 90
 13 (175) -
 14 (2) -
 15 (1024) -
 
 */

using namespace std;

struct search_result
{
    int next_group_index;
    int total;
};

search_result initialize_search_info()
{
    search_result info;
    info.next_group_index = 0;
    info.total = 0;
    return info;
}

void quick_sort(vector<int> *numbers, int left, int right)
{
    int i = left, j = right;
    int tmp;
    int pivot = numbers->at((left + right) / 2);
    
    while (i <= j) {
        while (numbers->at(i) < pivot)
            i++;
        while (numbers->at(j) > pivot)
            j--;
        if (i <= j) {
            tmp = numbers->at(i);
            numbers->at(i) = numbers->at(j);
            numbers->at(j) = tmp;
            i++;
            j--;
        }
    };
    
    if (left < j)
        quick_sort(numbers, left, j);
    if (i < right)
        quick_sort(numbers, i, right);
}


void sort(vector<int> *numbers)
{
    int n = (int)numbers->size();
    quick_sort(numbers, 0, n - 1);
}

void remove_duplicates(vector<int> *numbers)
{
    int i = 0;
    while (i < numbers->size() - 1)
    {
        if (numbers->at(i) == numbers->at(i + 1)) {
            numbers->erase (numbers->begin() + i + 1);
        }
        else {
            ++i;
        }
    }
}

int get_number_of_zeros(vector<int> *numbers)
{
    int result = 0;
    
    for (int i = 0;i < numbers->size(); ++i) {
        if (numbers->at(i) == 0) {
            ++result;
        }
    }
    return result;
}

int group_ending_index(vector<int> *numbers, int start_index)
{
    int index = start_index;
    
    for (int i = start_index; i < numbers->size() - 1; ++i)
    {
        int left  = numbers->at(i) + 1;
        int right = numbers->at(i + 1);
        if (left == right) {
            index = i + 1;
        }
        else {
            break;
        }
    }
    
    return index;
}

int find_max_length(vector<int> *numbers)
{
    if (numbers->size() == 0) {
        return 0;
    }
    
    int i = 0;
    
    int current = 1;
    int max = 1;
    
    while (i < numbers->size() - 1)
    {
        if ((numbers->at(i) + 1) == numbers->at(i + 1)) {
            current++;
        }
        else {
            current = 1;
        }
        
        if (current > max) {
            max = current;
        }
        ++i;
    }
    
    return max;
}

search_result step(vector<int> *numbers, int beginning_index, int total)
{
    search_result result = initialize_search_info();
    
    int count = (int)numbers->size();
    int index = beginning_index;
    int available_total = total;
    
    int length = 0;
    
    int last, first, step_total;
    bool is_first = true;
    
    while (available_total > 0 && index < count)
    {
        int ending_index = group_ending_index(numbers, index);
        
        if (is_first) {
            length += (ending_index - index + 1);
        }
        
        int next_beginning_index = ending_index + 1;
        
        if (is_first) {
            is_first = false;
            result.next_group_index = next_beginning_index;
        }
        if (next_beginning_index >= count) {
            break;
        }
        
        last  = numbers->at(ending_index);
        first = numbers->at(next_beginning_index);
        
        step_total = first - last - 1;
        
        if (step_total > available_total) {
            break;
        }
        int next_ending_index = group_ending_index(numbers, next_beginning_index);
        
        length += (next_ending_index - next_beginning_index + 1);
        length += step_total;
        available_total -= step_total;
        
        index = next_ending_index;
    }
    
    length += available_total;
    
    result.total = length;
    
    return result;
}

int calculate(vector<int> *numbers, int total)
{
    int count = (int)numbers->size();
    if (0 == count) {
        return total;
    }
    if (0 == total) {
        return find_max_length(numbers);
    }
    
    int result = 0;
    
    int index = 0;
    
    while (index < count)
    {
        search_result r = step(numbers, index, total);
        
        if (r.total > result) {
            result = r.total;
        }
        index = r.next_group_index;
    }
    
    return result;
}

int main(int argc, const char * argv[])
{
    vector<int> *numbers = new vector<int>();
    
    ifstream in("lngpok.in",ios::in);
    
    int number;
    while (in >> number) {
        numbers->push_back(number);
    }
    in.close();
    
    sort(numbers);
    
    int number_of_zeros = get_number_of_zeros(numbers);
    
    remove_duplicates(numbers);
    if (numbers->size() >= 1) {
        if (numbers->at(0) == 0) {
            numbers->erase(numbers->begin());
        }
    }
    
    int result = calculate(numbers, number_of_zeros);
    
    ofstream output;
    output.open ("lngpok.out");
    
    output << result;
    
    output.close();
    
    return 0;
}

















