#include <string>
#include <vector>
using namespace std;

#ifndef STRINGPROCESSOR
#define STRINGPROCESSOR
class StringProcessor {
   public:
    static string replace(string, string, string);          // replace all str1 to str2
    static vector<string> split(string str, char c = '$');  // return vector of splitted string by character
};
#endif