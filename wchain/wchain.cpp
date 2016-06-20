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

int find_max_word_length(vector<std::string> *words)
{
    int max = (int)words->at(0).size();
    
    for (int i = 1;i < words->size(); ++i) {
        int size = (int)words->at(i).size();
        if (size > max) {
            max = size;
        }
    }
    return max;
}

vector<vector<std::string> *> *buckets_with_words(vector<std::string> *words, int max_size)
{
    vector<vector<std::string> *> *result = new vector<vector<std::string> *>();
    
    for (int i = 0; i < max_size; ++i) {
        vector<std::string> *temp_vector = new vector<std::string>();
        result->push_back(temp_vector);
    }
    
    int size = (int)words->size();
    for (int i = 0; i < size; ++i) {
        std::string s = words->at(i);
        
        result->at(s.length() - 1)->push_back(s);
    }
    
    return result;
}

int get_next_not_empty_bucket_index(vector<vector<std::string> *> *buckets, int starting_from_index)
{
    int result = starting_from_index;
    
    while (buckets->at(result)->size() == 0) {
        result++;
    }
    return result;
}

bool can_string_be_chained_with_string(std::string string1, std::string string2)
{
    int number_of_missmatches = 0;
    int s1_index = 0;
    int s2_index = 0;
    
    for (; s2_index < string2.size(); ) {
        
        if (string1[s1_index] == string2[s2_index]) {
            ++s1_index;
            ++s2_index;
        }
        else {
            ++s1_index;
            ++number_of_missmatches;
        }
        
        if (number_of_missmatches == 2) {
            return false;
        }
    }
    
    return true;
}

int can_string_be_chained_with_bucket(std::string string, vector<std::string> *bucket, vector<int> *base_solutions)
{
    int max_index = -1;
    int max = 0;
    for (int i = 0; i < bucket->size(); ++i) {
        if (can_string_be_chained_with_string(string, bucket->at(i))) {
            
            int points = base_solutions->at(i);
            
            if (points > max) {
                max = points;
                max_index = i;
            }
        }
    }
    return max_index;
}

long long find_max(vector<vector<int> *> *solutions)
{
    long long result = 0;
    
    for (int i = 0; i < solutions->size(); ++i) {
        vector<int> *bucket = solutions->at(i);
        for (int j = 0; j < bucket->size(); ++j) {
            if (result < bucket->at(j)) {
                result = bucket->at(j);
            }
        }
    }
    
    return result;
}

long long solve(vector<std::string> *words)
{
    long long result = 0;
    
    int max = find_max_word_length(words);
    
    vector<vector<std::string> *> *buckets = buckets_with_words(words, max);
    
    vector<vector<int> *> *solutions = new vector<vector<int> *>();
    for (int i = 0; i < max; ++i) {
        vector<int> *temp_vector = new vector<int>();
        solutions->push_back(temp_vector);
    }
    
    int prev_index = 0;
    int index = get_next_not_empty_bucket_index(buckets, 0);
    
    vector<std::string> *base_bucket = buckets->at(index);
    
    for (int i = 0; i < base_bucket->size(); ++i) {
        solutions->at(index)->push_back(1);
    }
    
    while (index + 1 < max) {
        prev_index = index;
        index = get_next_not_empty_bucket_index(buckets, index + 1);
        
        vector<std::string> *bucket = buckets->at(index);
        
        if (index > prev_index + 1) {
            for (int i = 0; i < bucket->size(); ++i) {
                solutions->at(index)->push_back(1);
            }
            continue;
        }
        
        for (int i = 0; i < bucket->size(); ++i) {
            
            vector<int> *base_solutions = solutions->at(index - 1);
            
            int chain_index = can_string_be_chained_with_bucket(bucket->at(i), base_bucket, base_solutions);
            if (chain_index != -1) {
                int prev_solution = base_solutions->at(chain_index);
                solutions->at(index)->push_back(prev_solution + 1);
            }
            else {
                solutions->at(index)->push_back(1);
            }
            
        }
        
        base_bucket = bucket;
    }
    
    result = find_max(solutions);
    
    return result;
}

int main(int argc, const char * argv[])
{
    std::ifstream in("wchain.in");
    
    // initialize the vector from the values in the file:
    std::vector<string> lines{ std::istream_iterator<string>(in),
        std::istream_iterator<string>() };
    
    lines.erase(lines.begin());
    
    long long result = solve(&lines);

    ofstream output;
    output.open ("wchain.out");
    
    output << result;

    output.close();

    return 0;
}



