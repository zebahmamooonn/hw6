#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>
#include <cctype>
#include <string>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(!debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

      std::vector<unsigned long long> w(5,0);
      std::string key = k; 

      for(size_t i = 0; i < key.length(); i++){
        key[i] = tolower(key[i]); 
      }

      int totalGroups = (key.size() + 5) / 6;
      int groupIdx = 4; 

      for(int i = key.size(); i > 0 && groupIdx >= 0; i -= 6, groupIdx--){
        unsigned long long value = 0; 
        int start = std::max(0, i - 6);
        for (int j = start; j < i; j++){
          value = value * 36 +letterDigitToNumber(key[j]); 
        }
        w[groupIdx] = value; 
      }

      unsigned long long hashValue = 0;
      for(int i = 0; i < 5; i++){
        hashValue += rValues[i] *w[i]; 
      }
      return static_cast<HASH_INDEX_T>(hashValue); 
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

      if(isalpha(letter)){
        return tolower(letter) - 'a'; 
      }
      else if(isdigit(letter)){
        return 26 + (letter - '0'); 
      }
      return 0; 
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
