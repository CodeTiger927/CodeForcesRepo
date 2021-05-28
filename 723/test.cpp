// C++ implementation of the above approach
#include <bits/stdc++.h>
using namespace std;
  
// Function that returns true if s1
// and s2 are anagrams of each other
bool isAnagram(string s1, string s2)
{
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    if (s1 == s2)
        return 1;
    return 0;
}
  
// Function to return the minimum swaps required
int CountSteps(string s1, string s2, int size)
{
    int i = 0, j = 0;
    int result = 0;
  
    // Iterate over the first string and convert
    // every element equal to the second string
    while (i < size) {
        j = i;
  
        // Find index element of first string which
        // is equal to the ith element of second string
        while (s1[j] != s2[i]) {
            j += 1;
        }
  
        // Swap adjacent elements in first string so
        // that element at ith position becomes equal
        while (i < j) {
  
            // Swap elements using temporary variable
            char temp = s1[j];
            s1[j] = s1[j - 1];
            s1[j - 1] = temp;
            j -= 1;
            result += 1;
        }
        i += 1;
    }
    return result;
}
  
// Driver code
int main()
{
    string s1 = "NNTTAAOO";
    string s2 = "OAANTTON";
  
    int size = s2.size();
  
    // If both the strings are anagrams
    // of each other then only they
    // can be made equal
    if (isAnagram(s1, s2))
        cout << CountSteps(s1, s2, size);
    else
        cout << -1;
  
    return 0;
}