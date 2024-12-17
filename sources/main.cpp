#include "iter.hpp"
#include "util.hpp"
#include <cstdio>
#include <iostream>
#include <map>
#include <string>

using namespace std;
int main(void) {
    
    
    
    std::map<string, int> test_map;
    
    var i = 1;
    test_map["1"] = 1;
    
    test_map =Iter::iter(test_map)
        .map([&] (  pair<string, int> v) {
            v.second += 12;
            return v;
            }).collect<map<string, int>>();
    
    
    cout << test_map["1"];
    // Iter::range(0,10).for_each([]( int i) {std::cout << i;});
    
    return 0;
}