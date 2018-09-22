//File containing several methods to aid in making a markov chain from text

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

map<string, vector<string> > makeDict(vector<string> allWords){
  map<string, vector<string> > markovChain;

  for(vector<string>::const_iterator myit = allWords.begin(); myit != allWords.end(); ++myit){
    vector<string>::const_iterator nextVal = myit;
    nextVal++;
    markovChain[*myit].push_back(*nextVal);
  }
  return markovChain;
}

int main(int argc, char* argv[]){
    string filename = argv[1];

    vector<string> wordList = readFile(filename);
    map<string, vector<string> > markovDict = makeDict(wordList);

    for(map<string, vector<string> >::const_iterator it = markovDict.begin(); it != markovDict.end(); ++it){
      cout << "[ " << it->first << " ] [ ";
      for(vector<string>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2){
        cout << *it2 << " ";
      }
      cout << "]" << endl;
    }
    return 0;
}
