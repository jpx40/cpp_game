



#include "util.hpp"
#include <regex>
#include <string_view>
#include <vector>




template<typename T>
std::tuple<std::sregex_iterator,std::sregex_iterator> regex_iter(std::string s, std::regex re, std::function<T (String)> f) {
    
    std::vector<T> vec;
    auto reg = std::sregex_iterator(s.begin(),s.end(),re);
    
    auto end = std::sregex_iterator();
    
    for (var i = reg ; i != end; i++) {
        
        std::smatch match = *i;
               std::string match_str = match.str();
              vec.push_back(f(match_str));
        
    }
    
    
    return vec;
}

void regex_iter(std::string s, std::regex re, std::function<void (String)> f) {
    
    auto reg = std::sregex_iterator(s.begin(),s.end(),re);
    
    auto end = std::sregex_iterator();
    
    for (var i = reg ; i != end; i++) {
        
        std::smatch match = *i;
               std::string match_str = match.str();
             f(match_str);
        
    }

}


std::sregex_iterator  new_regex_iter(std::string s, std::regex re) {
    
   
    let reg = std::sregex_iterator(s.begin(),s.end(),re);

    
    return reg;
}