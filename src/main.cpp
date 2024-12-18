#include "util.hpp"
#include <_stdio.h>
#include <regex>

#include <tuple>
// reading a text file
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


String read_file(const char* path) {
    
    
    string line;
    ifstream myfile (path);
    String buffer;
    if (myfile.is_open())
    {
      while ( getline (myfile,line) )
      {
        buffer.append(line+ "\n");
      }
      myfile.close();
    }
  
    else cout << "Unable to open file"; 
    return line;
}




int main(void) {
    
    
    let re = regex("(\\.+)");
    let buf = read_file("re.txt");
    
    cout << buf;
    let  [iter, end] = regex_iter(buf, re);

    for (var i = iter; i != end; i++) {
        
        std::smatch match = *i;
               std::string match_str = match.str();
              
                   std::cout << "  " << match_str << '\n';
        
    }
    
    
    
    return 0;
}

