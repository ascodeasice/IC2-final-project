#include "StringProcessor.h"

#include <string>
#include <vector>
using namespace std;

string StringProcessor::replace(string str, string str1, string str2) {
    while (str.find(str1) != string::npos) {
        str.replace(str.find(str1), str1.length(), str2);
    }
    return str;
}

vector<string> StringProcessor::split(string str, char c) {
    vector<string> svec;
    int i = 0;
    int j = 0;
    while (j < str.length()) {
        if (str[j] == c) {
            svec.push_back(str.substr(i, j - i));  // pos and len of string
            i = j + 1;
        }
        j++;
    }
    return svec;
}