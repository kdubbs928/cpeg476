//File containing method to parse a file and return a list containing all of the words in the file.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> readFile(string name){
    vector<string> allWords;
    string word;
    ifstream file;

    file.open(name);

    while (file >> word){
        allWords.push_back(word);
    }
    return allWords;
}

int main(int argc, char* argv[]){
  string name = argv[1];
  vector<string> words;
  map<string, vector<string> > markovChain;

  words = readFile(name);

  for(int i = 0; i < words.size(); i++){
    cout << words[i] << endl;
    markovChain[words[i]].push_back(words[i+1]);
  }

  for(map<string, vector<string> >::const_iterator it = markovChain.begin(); it != markovChain.end(); ++it){
    cout << "[ " << it->first << " ] [ ";
    for(vector<string>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2){
      cout << *it2 << " ";
    }
    cout << "]" << endl;
  }

  return 0;
}
