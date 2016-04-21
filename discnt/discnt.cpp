//
//  main_dscnt.cpp
//  Numbers
//
//  Created by Bogdan Shubravyi on 4/21/16.
//  Copyright © 2016 Bogdan Shubravyi. All rights reserved.
//

//
//  main.cpp
//  Numbers
//
//  Created by Bogdan Shubravyi on 4/14/16.
//  Copyright © 2016 Bogdan Shubravyi. All rights reserved.
//


#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <iomanip>

#include <unistd.h>

using namespace std;

double calculateSum(vector<int> *numbers, int divider, double percentage)
{
    double result = 0.0;
    
    long n = numbers->size();
    long max_elements = n / divider;
    
    for (int i = 0; i < max_elements; i++)
    {
        result += numbers->at(i) * percentage;
    }
    
    for (int i = (int)max_elements; i < n; i++)
    {
        result += numbers->at(i);
    }
    
    return result;
}

void quick_sort(vector<int> *numbers, int left, int right, int stop_index)
{
    if (left > stop_index || right < stop_index) {
        return;
    }
    
    int i = left, j = right;
    int tmp;
    int pivot = numbers->at((left + right) / 2);
    
    while (i <= j)
    {
        while (numbers->at(i) > pivot) i++;
        while (numbers->at(j) < pivot) j--;
        
        if (i <= j) {
            tmp = numbers->at(i);
            numbers->at(i) = numbers->at(j);
            numbers->at(j) = tmp;
            i++;
            j--;
        }
    };
    
    if (left < j)
        quick_sort(numbers, left, j, stop_index);
    if (i < right)
        quick_sort(numbers, i, right, stop_index);
}

int main(int argc, const char * argv[])
{
    vector<int> *numbers = new vector<int>();
    
    ifstream in("discnt.in",ios::in);
    
    int number;
    
    while (in >> number) {
        numbers->push_back(number);
    }
    in.close();
    
    int discount = numbers->at(numbers->size() - 1);
    numbers->pop_back();
    
    const int divider = 3;
    int stop_index = (int)numbers->size() / divider;
    int n = (int)numbers->size() - 1;
    
    quick_sort(numbers, 0, n, stop_index);
    
    double result = calculateSum(numbers, divider, 1.0 - (discount / 100.0));
    
    ofstream output;
    output.open ("discnt.out");
    output << setprecision(2) << fixed << result;
    
    output.close();
    
    cin.get();
    
    return 0;
}

