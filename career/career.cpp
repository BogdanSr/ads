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
#include <queue>
#include <map>
#include <string.h>
#include <iomanip>
#include <iterator>
#include <ctime>
#include <stdio.h>

#include <sstream>
#include <string>

#include <unistd.h>

using namespace std;

void print_array(vector<int> *numbers, int count)
{
    int cur_pos = 0;
    for (int i = cur_pos; i < count; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            cout<<numbers->at(cur_pos)<<" ";
            cur_pos++;
        }
        cout<<endl;
    }
}


void print_array_reversed(vector<int> *numbers, int count)
{
    int cur_pos = (int)numbers->size() - 1;
    
    for (int i = count - 1; i >= 0; --i)
    {
        for (int j = 0; j <= i; ++j)
        {
            cout<<numbers->at(cur_pos)<<" ";
            cur_pos--;
        }
        cout<<endl;
    }
}


long long solve(vector<int> *numbers, int count)
{
    long long result = 0;
    
    long long solutions[count];
    
    int cur_pos = (int)numbers->size() - 1;
    
    // First row
    for (int j = 0; j <= count - 1; ++j)
    {
        solutions[j] = numbers->at(cur_pos);
        cur_pos--;
    }
    
    // All the rest
    for (int i = count - 2; i >= 0; --i)
    {
        for (int j = 0; j <= i; ++j)
        {
            long long case1 = solutions[j];
            long long case2 = solutions[j + 1];
            
            long long max = std::max(case1, case2);
            
            long long solution = max + numbers->at(cur_pos);
            
            solutions[j] = solution;
            
            cur_pos--;
        }
    }
    
    return solutions[0];
}

int main(int argc, const char * argv[])
{
    vector<int> *numbers = new vector<int>();
    
    ifstream in("career.in",ios::in);
    
    int number;
    
    while (in >> number) {
        numbers->push_back(number);
    }
    in.close();
    
    int count = numbers->at(0);
    numbers->erase(numbers->begin());

    long long result = solve(numbers, count);

    ofstream output;
    output.open ("career.out");
    
    output << result;

    output.close();

    return 0;
}

