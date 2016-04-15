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

void sortItems(vector<int> *numbers, int divider)
{
    long n = numbers->size();
    long max_elements = n / divider;
    
    for (int i = 0; i < max_elements; i++)
    {
        int iMin = i;
        
        for (int j = i + 1; j < n; j++)
        {
            if (numbers->at(j) > numbers->at(iMin)) {
                iMin = j;
            }
        }
        swap(numbers->at(i), numbers->at(iMin));
    }
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
    
    sortItems(numbers, divider);
    
    double result = calculateSum(numbers, divider, 1.0 - (discount / 100.0));
    
    ofstream output;
    output.open ("discnt.out");
    output << setprecision(2) << fixed << result;
    output.close();
    
    return 0;
}
















