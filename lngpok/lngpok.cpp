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

using namespace std;

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

int calculate(vector<int> *numbers, int total)
{
    int result = 0 ;
    int available_items = total;
    
    while (available_items > 0 && numbers->size() > 0)
    {
        int index = 0;
        
        int max_left_beginning = 0;
        int max_left_ending = 0;
        int max_right_beginning = 0;
        int max_right_ending = 0;
        int max_hole_length = 0;
        
        int max_length = 0;
        bool changed = false;
        
        while (index < numbers->size() - 1)
        {
            int left_ending = group_ending_index(numbers, index);
            
            int right_beginning = left_ending + 1;
            
            // TODO: XZ
            if (right_beginning >= numbers->size() - 1) {
                break;
            }
            
            int right_ending = group_ending_index(numbers, right_beginning);
            
            int last_left_element   = numbers->at(left_ending);
            int first_right_element = numbers->at(right_beginning);
            
            int hole_length = first_right_element - last_left_element - 1;
            
            int chunk_length = hole_length + (left_ending - index + 1) + (right_ending - right_beginning + 1);
            
            bool delta_length = (chunk_length - hole_length) > (max_length - max_hole_length);
            
            if (chunk_length > max_length && delta_length && hole_length <= available_items)
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
        else {
            break;
        }
    }
    
    int max = find_max_length(numbers);
    
    result = max + available_items;
    
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
    
    output<<result;
    
    output.close();
    
    //delete vector
    cin.get();
    
    return 0;
}

















