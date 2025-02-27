#include <iostream>
#include <ctime>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <map>
#include <cstdio>
#include <format>
#include <initializer_list>
#include <unordered_set>
#include <cmath>




using namespace std;


#define pb push_back


// Function to get the length of a number at given position in string
int getNumberLength(const string& s, int pos) {
    int len = 0;
    while (pos < s.length() && isdigit(s[pos])) {
        len++;
        pos++;
    }
    return len;
}


// Function to decode RLE and find total pattern length
long long decodeRLELength(const string& s) {
    long long totalLen = 0;
    int i = 0;
    while (i < s.length()) {
        if (isalpha(s[i])) {
            int numLen = getNumberLength(s, i + 1);
            string numStr = s.substr(i + 1, numLen);
            totalLen += stoll(numStr);
            i += numLen + 1;
        }
    }
    return totalLen;
}


// Function to find character at given position
char findCharAtPosition(const string& s, long long c) {
    // First find the length of one complete pattern
    long long patternLen = decodeRLELength(s);
   
    // Adjust c to be within one pattern length
    c = c % patternLen;
   
    // Now find the character at position c
    long long currentPos = 0;
    int i = 0;
   
    while (i < s.length()) {
        if (isalpha(s[i])) {
            char currentChar = s[i];
            int numLen = getNumberLength(s, i + 1);
            string numStr = s.substr(i + 1, numLen);
            long long repeats = stoll(numStr);
           
            if (currentPos + repeats > c) {
                return currentChar;
            }
           
            currentPos += repeats;
            i += numLen + 1;
        }
    }
   
    return ' '; // Should never reach here
}  


int main() {
    string s;
    long long c;
   
    // Read input
    cin >> s >> c;
   
    
    // Find and output the character at position c
    char result = findCharAtPosition(s, c);
    cout << result << endl;
   
   return 0;
}
