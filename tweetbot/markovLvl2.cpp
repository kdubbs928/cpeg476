/* markovLvl2.cpp
   A program that takes in a text file and generates text based on a level 2 markov chain
   Compiled and working on macOs
   By Kyle Weidmann & Matt Stout
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>

using namespace std;

//Checks if the word begins with a capital
bool isStartWord(string word){
  return isupper(word[0]);
}

//Concatinates two strings together with a space
string concatinize(string st1, string st2){
  string newString = st1 + " " + st2;
  return newString;
}

//Changes the key for the markov chain by shifting by 1
string changeKey(string st1, string st2){
  istringstream iss(st1);
  string word;
  vector<string> words;
  while(iss >> word){
    words.push_back(word);
  }
  return words[1] + " " + st2;
}

//Reads in a file and generates a vector containing all of the words in order of their appearance.
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

//Creates a mapping of strings to vectors of strings representing a level 2 markov chain
map<string, vector<string> > makeDict(vector<string> allWords){
  map<string, vector<string> > markovChain;

  for(vector<string>::const_iterator myit = allWords.begin(); myit != allWords.end(); ++myit){
    vector<string>::const_iterator nextVal = myit;
    vector<string>::const_iterator nextVal2 = myit;
    nextVal++;
    nextVal2 += 2;
    markovChain[concatinize(*myit,*nextVal)].push_back(*nextVal2);
  }
  return markovChain;
}

//Generates a vector of strings containing the text from a markov chain
//Length is number of characters
vector<string> generate(map<string, vector<string> > markovDict, int length){
  srand((unsigned)time(0));                       //initialize the random gen
  int startPlace;                                 //index of starting key
  vector<string> newText(0);                 //vector containing words in new text

  vector<string> keys;                            //vector containing all of the keys in the mapping
  for(map<string, vector<string> >::iterator it = markovDict.begin(); it != markovDict.end(); ++it) {
    keys.push_back(it->first);
  }

  //begin looping to begin text generation
  bool atStart = true;                            //beginning flag
  int genLen = 0;                                 //current length of chain
  string currentWord;
  vector<string> possChoice;
  int randWord;
  while(genLen <= length){
    if(atStart){
      startPlace = rand() % keys.size();
      if(isStartWord(keys[startPlace])){          //check for the first starting word
        newText.push_back(keys[startPlace]);
        atStart = false;
        cout <<currentWord << endl;
        currentWord = keys[startPlace];
        genLen += currentWord.length();
      }
    }
    else if(!atStart){                            //begin building text by following dict
      possChoice = markovDict[currentWord];
      randWord = rand() % possChoice.size();
      newText.push_back(possChoice[randWord]);
      currentWord = changeKey(currentWord,possChoice[randWord]);
      genLen += currentWord.length();
    }
  }

  //trim words in the dict to under the char limit
  genLen -= (newText.size()-1);
  while(genLen > length){
    genLen -= newText.back().length();
    newText.pop_back();
  }

  return newText;
}

int main(int argc, char* argv[]){
    if(argc != 3){
      cout << "Arguments entered incorrectly.... Aborting" << endl;
      cout << "Please enter arguments in format ./a.out something.txt length" << endl;
      return -1;
    }
    string filename = argv[1];

    vector<string> wordList = readFile(filename);
    map<string, vector<string> > markovDict = makeDict(wordList);

    vector<string> myText = generate(markovDict, atoi(argv[2]));

    //print tweet
    for(vector<string>::const_iterator it3 = myText.begin(); it3 != myText.end(); ++it3){
      cout << *it3 << " ";
    }
    cout << endl;
    return 0;
}
