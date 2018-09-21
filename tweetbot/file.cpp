// This is the main program to run the tweet generator
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
  if(argc != 4){
    cout << "The number of arguments is invalid. Please enter 3 arguments formatted as follows:\n account handle, markov level, number of tweets" << endl;
    return -1;
  }
  else{
    for(int i = 0; i < argc; i++){
        cout << argv[i] << endl;
    }
  }
  return 0;
}
