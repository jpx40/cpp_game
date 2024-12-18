
#include <tuple>

#include <array>
#include <map>
#include <string>
#include <vector>
using String = std::string;
// using Vector = std::vector<class Tp>;
// 
#define Vector vector
#define Array std::array
#define Map std::map

// using Map = std::map<class A, class B, class C, class D>;

#define var auto 
#define let   const auto
#define func auto
#define fn []
#define fn_ref [&]
#define Tuple std::tupel

#define Str const char* 
#include <regex>

std::tuple<std::sregex_iterator,std::sregex_iterator> regex_iter(std::string s, std::regex re);
