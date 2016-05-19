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
 1 (9) 10 2 3
 2 (1999999998) 2 1000000000 999999999
 3 (2) 4 1 1
 4 (229777903466) 32416188257 105143 15489949
 5 (1000000000) 100 1000000000 1
 6 (999999999) 1 1 999999999
 7 (1000000000000000) 1000000000000 1000000000 1000000000
 8 (1000000) 1000000000000 1 1
 9 (1) 1 1 1
 10 (26) 626 1 1
 11 (999000000) 1000000000000 999 999
 12 (999000000000) 998001 1000000000 1000000000
 */

long long calculate(long long n, long long w, long long h)
{
    long long min_index = 1;
    long long max_index = 1;
    long long sum = 1;
    
    long long min = std::min(w,h);
    long long max = std::max(w,h);
    
    long long max_value = max_index * max;
    long long min_value = min_index * min;
    
    while (sum < n)
    {
        if (min_value > max_value )
        {
            max_index++;
            max_value += max;
            
            sum += min_index;
        }
        else {
            min_index++;
            min_value += min;
            
            sum += max_index;
        }
    }
    
    long long result = std::max(min_value, max_value);
    
    return result;
}

int main(int argc, const char * argv[])
{
    vector<long long> *numbers = new vector<long long>();
    
    ifstream in("bugtrk.in", ios::in);
    
    long long number;
    while (in >> number) {
        numbers->push_back(number);
    }
    in.close();
    
    long long n, w, h;
    
    n = numbers->at(0);
    w = numbers->at(1);
    h = numbers->at(2);
    
    long long result = calculate(n, w, h);
    
    ofstream output;
    output.open ("bugtrk.out");
    output<<result;
    output.close();
    
    return 0;
}

