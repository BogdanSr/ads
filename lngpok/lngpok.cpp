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

//#include "Utils.h"

#include <unistd.h>
char *getcwd(char *buf, size_t size);

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

struct Search_Info
{
    int beginning_index;
    int ending_index;
    int used_total;
};

Search_Info initialize_search_info() {
    Search_Info info;
    info.beginning_index = 0;
    info.ending_index = 0;
    info.used_total = 0;
    return info;
}

void quickSort(vector<int> *numbers, int left, int right)
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
        quickSort(numbers, left, j);
    if (i < right)
        quickSort(numbers, i, right);
}


void sort(vector<int> *numbers)
{
    int n = (int)numbers->size();
    quickSort(numbers, 0, n - 1);
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

int group_beginning_index(vector<int> *numbers, int end_index)
{
    int index = end_index;
    
    for (int i = end_index; i > 0; --i)
    {
        int left  = numbers->at(i) - 1;
        int right = numbers->at(i - 1);
        if (left == right) {
            index = i - 1;
        }
        else {
            break;
        }
    }
    
    return index;
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

Search_Info next_index(vector<int> *numbers, int index, int total)
{
    int available_items = total;
    
    int max_left_beginning = 0;
    int max_left_ending = 0;
    int max_right_beginning = 0;
    int max_right_ending = 0;
    int max_hole_length = 0;
    
    int max_length = 0;
    bool changed = false;
    
    Search_Info result = initialize_search_info();
    
    while (!changed)
    {
        int left_ending = group_ending_index(numbers, index);
        
        int right_beginning = left_ending + 1;
        
        if (right_beginning >= numbers->size() - 1) {
            break;
        }
        
        int right_ending = group_ending_index(numbers, right_beginning);
        
        int last_left_element   = numbers->at(left_ending);
        int first_right_element = numbers->at(right_beginning);
        
        int hole_length = first_right_element - last_left_element - 1;
        
        // not enough space
        if (hole_length > available_items) {
            index = left_ending + 1;
            continue;
        }
        
        int chunk_length = hole_length + (left_ending - index + 1) + (right_ending - right_beginning + 1);
      
        if (true)
        {
            max_length = chunk_length;
            
            max_left_beginning = index;
            max_left_ending = left_ending;
            
            max_right_beginning = right_beginning;
            max_right_ending = right_ending;
            
            max_hole_length = hole_length;
            
            changed = true;
        }
        
        index = left_ending + 1;
    }
    
    if (changed)
    {
        int value = numbers->at(max_left_ending);
        for (int i = max_right_beginning; i < max_right_beginning + max_hole_length; ++i)
        {
            numbers->insert(numbers->begin() + i, ++value);
        }
        available_items -= max_hole_length;
    }
    
    result.beginning_index = max_left_beginning;
    result.ending_index = max_right_ending + max_hole_length;
    result.used_total = max_hole_length;
    
    return result;
}


Search_Info move_right(vector<int> *numbers, int index, int total)
{
    Search_Info result = initialize_search_info();
    
    int left_index = index + 1;
    
    if (left_index >= numbers->size()) {
        return result;
    }
    
    int right_index = group_ending_index (numbers, left_index);
    
    result.beginning_index = left_index;
    result.ending_index = right_index;
    
    int left  = numbers->at(left_index);
    int main  = numbers->at(index);
    
    int used_total = left - main - 1;
    if (used_total <= total) {
        result.used_total = left - main - 1;
    }
    
    return result;
}

Search_Info move_left(vector<int> *numbers, int index, int total)
{
    Search_Info result = initialize_search_info();
    
    int left_index = index - 1;
    
    if (left_index < 0) {
        return result;
    }
    
    int right_index = group_beginning_index(numbers, left_index);
    
    result.beginning_index = right_index;
    result.ending_index = left_index;
    
    int right  = numbers->at(left_index);
    int main   = numbers->at(index);
    
    int used_total = main - right - 1;
    
    if (used_total <= total) {
        result.used_total = used_total;
    }

    return result;
}


Search_Info step(vector<int> *numbers, int left_index, int right_index, int total)
{
    Search_Info result = initialize_search_info();
    
    Search_Info right = move_right(numbers, right_index, total);
    Search_Info left  = move_left (numbers, left_index, total);
    
    if (right.used_total == 0 && left.used_total == 0) {
        return result;
    }

    bool use_left  = right.used_total == 0;
    
    int right_diff = (right.ending_index - right.beginning_index) - right.used_total;
    int left_diff  = (left.ending_index -   left.beginning_index) - left.used_total;
    
    int hole_beginnig;
    
    int left_bound, right_bound, used_total;
    
    if (left_diff >= right_diff && use_left) {
        hole_beginnig = left.ending_index + 1;
        
        used_total = left.used_total;
        left_bound = left.beginning_index;
        right_bound = right_index + used_total;
    }
    else {
        hole_beginnig = right_index + 1;
        
        used_total = right.used_total;
        left_bound = left_index;
        right_bound = right.ending_index + used_total;
    }
    
    int value = numbers->at(hole_beginnig - 1);
    for (int i = hole_beginnig; i < hole_beginnig + used_total; ++i)
    {
        numbers->insert(numbers->begin() + i, ++value);
    }
    
    result.used_total = used_total;
    result.beginning_index = left_bound;
    result.ending_index = right_bound;

    return result;
}

int calculate(vector<int> *numbers, int total)
{
    int result = 0;
    
    if (numbers->size() == 0) {
        return total;
    }
    
    if (total == 0) {
        int r = find_max_length(numbers);
        return r;
    }
    
    int index = 0;

    while (index < numbers->size())
    {
        vector<int> *copy = new vector<int>(*numbers);
        
        Search_Info info = next_index(copy, index, total);
        
        if (info.used_total == 0) {
            int r = find_max_length(numbers) + total;
            if (r > result) {
                result = r;
            }
            break;
        }

        index = info.ending_index - info.used_total;
        
        int available_total = total - info.used_total;
        while (available_total > 0)
        {
            Search_Info temp_info = step(copy, info.beginning_index, info.ending_index, available_total);
            
            if (temp_info.used_total == 0) {
                break;
            }
            
            info = temp_info;
            available_total -= info.used_total;
        }
        
        int r = find_max_length(copy) + available_total;
        if (r > result) {
            result = r;
        }
        delete copy;
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
    
    //delete vector
    cin.get();
    
    return 0;
}

















