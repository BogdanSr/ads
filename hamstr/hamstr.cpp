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

using namespace std;

/*
 1 (2)
 2 (3)
 3 (1)
 4 (5)
 5 (5)
 6 (10)
 7 (2)
 8 (0)
 9 (1)
 10 (9)
 11 (31623)
 12 (732)
 */

// TODO: CACHE SUM FOR COUNT, IMPROVE SORTING

class Hamster {
public:
    long long H;
    long long G;
};

inline long long sum(Hamster* hamster, int count)
{
    return hamster->H + (hamster->G * (count - 1));
}

inline bool compare(Hamster *lhs, Hamster *rhs, int count)
{
    long long l_sum = sum(lhs, count);
    long long r_sum = sum(rhs, count);
    
    return l_sum > r_sum;
}

void quickSort(Hamster **items, int left, int right, int count, int stop_index)
{
    if (left > stop_index || right < stop_index) {
        return;
    }
    
    int i = left, j = right;
    Hamster *tmp;
    Hamster *pivot = items[(left + right) / 2];
    
    while (i <= j) {
        while (compare(items[i], pivot, count)) {
            i++;
        }
        while (compare(pivot,items[j], count)) {
            j--;
        }
        if (i <= j) {
            tmp = items[i];
            items[i] = items[j];
            items[j] = tmp;
            i++;
            j--;
        }
    };
    
    if (left < j)
        quickSort(items, left, j, count, stop_index);
    if (i < right)
        quickSort(items, i, right, count, stop_index);
}

void sort(Hamster **items, int count, int max_count)
{
    if (count <= 0) return;
    int stop_index = count - max_count;
    quickSort(items, 0, count - 1, max_count, stop_index);
}

bool check_if_enough_total(Hamster **items, int count, int available_total, int start_index, int c)
{
    long long result = 0;
    
    for (int i = start_index; i < count; ++i)
    {
        result += sum(items[i], c);
        
        if (result > available_total) {
            return false;
        }
    }
    return true;
}

int main(int argc, const char * argv[])
{
    vector<int> *numbers = new vector<int>();
    
    ifstream in("hamstr.in", ios::in);
    
    int number;
    
    while (in >> number) {
        numbers->push_back(number);
    }
    
    in.close();
    
    int food = numbers->at(0);
    numbers->erase(numbers->begin());
    int count = numbers->at(0);
    numbers->erase(numbers->begin());
    
    Hamster **items = new Hamster*[count];
    
    for (int i = 0; i < count; ++i)
    {
        Hamster *item = new Hamster();
        int c = 2 * i;
        item->H = numbers->at(c);
        item->G = numbers->at(c + 1);
        items[i] = item;
    }
    delete numbers;
    
    int left = 0;
    int right = count - 1;
    int result = 0;
    
    while (left >= 0 && right <= count && left <= right)
    {
        int index = (left + right) / 2;
        int c = count - index;
        
        sort(items, count, c);
        
        bool enough_total = check_if_enough_total(items, count, food, index, c);
        
        if (enough_total)
        {
            if (c > result) {
                result = c;
            }
            right = index - 1;
        }
        else {
            left = index + 1;
        }
    }
    
    ofstream output;
    output.open ("hamstr.out");
    
    output << result;

    output.close();
    
    return 0;
}

