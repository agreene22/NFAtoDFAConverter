#include "FileProcessor.h"
#include <map>
#include <sstream>
#include <vector>

FileProcessor::FileProcessor(){
  m_inFile = "";
  m_outFile = "DFA.dfa";
}

FileProcessor::FileProcessor(string inFile, string outFile){
  m_inFile = inFile;
  m_outFile = outFile;
}

FileProcessor::~FileProcessor(){

}

NFA* FileProcessor::readFile(){
  int lineCount = 0;
  vector<int> states;
  vector<char> alphabet;
  vector<int> acceptStates;
  vector<string> keys;
  map<string,vector<int>> transition;
  string input;
  int currState;
  int startState;
  int stateLines = 0;

  inFS.open(m_inFile); //opening file stream

  bool s = false;

  if(!inFS.is_open()){
    cout << "Error: Could not open file." << endl;
    exit(1);
  }
  cout << "Processing file." << endl;

  while(!inFS.eof()){

    // set of states
    inFS >> input;
    while(input[0] == '{'){
      for(int i = 0; i < input.length(); i++){
        if(input[i] == '{'){
          s = true;
          continue;
        }
        if(s == true){
          states.push_back((int) input[i]);
          s = false;
        }
      }
      inFS >> input;
      stateLines++;
    }

    // finite alphabet
    while(input[0] != '{'){
      for(int i = 0; i < input.length(); i++){
        if(isalpha(input[i])){
          alphabet.push_back(input[i]);
        }
      }
      inFS >> input;
    }

    // start state
    startState = ((int) input[1] - 48);

    // set of accept states
    inFS >> input;
    int size = input.length();
    while(input[size-1] != ','){
      for(int i = 0; i < input.length(); i++){
        if(input[i] == '{'){
          s = true;
          continue;
        }
        if(s == true){
          acceptStates.push_back((int) input[i]);
          s = false;
        }
      }
      inFS >> input;
      if(input[3] == ','){
        break;
      }
    }

    bool loop = false;
    while(!inFS.eof()){
      char state = input[1];
      inFS >> input;
      string val = input;
      string k = "";
      k = k + state + val;
      keys.push_back(k);

      inFS >> input;
      inFS >> input;
      vector<int> v;
      int s = ((int) input[1] - 48);
      v.push_back(s);

      pair<string,vector<int>> currPair (k,v);
      if(loop == false){
        transition.insert(currPair);
        loop = true;
        inFS >> input;
        continue;
      }

      bool found = false;
      for(int i = 0; i < transition.size(); i++){
        if(keys[i] == k){
          found = true;
          vector<int> compareV = transition[k];
          for(int j = 0; j < v.size(); j++){
            compareV.push_back(s);
          }
          transition[k] = compareV;
          break;
        }
      }
      if(found == false){
        transition.insert(currPair);
      }
      found = false;

      inFS >> input;
    }

  }

  NFA* nfa = new NFA(states,alphabet,startState,transition,acceptStates,keys);

  inFS.close();

  return nfa;
}

void FileProcessor::writeFile(DFA* dfa){

  // outFS.open(m_outFile);
  //
  // vector<pair<vector<int>,string>> keys;
  // // cout << "ik its here" << endl;
  // keys = *dfa->getNewKeys();
  //
  // cout << "open" << endl;
  // if(!outFS.is_open()){
  //   cout << "Error writing to DFA file" << endl;
  //   exit(1);
  // }
  // cout << "Keys: " << keys.size() << endl;
  // for(int i = 0; i < keys.size(); i ++){
  //   cout << "In loop" << endl;
  //   string currState = "{";
  //   for(int j = 0; j < get<0>(keys[i]).size(); j++){
  //     currState += to_string(get<0>(keys[i])[j]);
  //     if(j != get<0>(keys[i]).size() -1){
  //       currState += ", ";
  //     }
  //   }
  //   currState += "}\t";
  //   outFS << currState;
  //   cout << currState << endl;
  // }
  //
  // outFS.close();

}
