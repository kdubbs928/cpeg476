#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

bool isEndWord(string word){
  int n = word.length();
  char cWord[n + 1];
  strcpy(cWord, word.c_str());
  char lastChar = cWord[word.length() - 1];

  if(lastChar == '.'){
    return true;
  }
  else{
    return false;
  }
}

bool isStartWord(string word){
  return isupper(word[0]);
}
