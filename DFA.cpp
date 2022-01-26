#include "DFA.h"

DFA::DFA(){
  m_newKeys = new vector<pair<vector<int>,string>>();
}

DFA::~DFA(){
  delete m_q;
}

void DFA::setAlphabet(vector<char> alphabet){
  m_alphabet = alphabet;
}

void DFA::setStartStates(vector<int> startStates){
  m_startStates = startStates;
}

void DFA::setQ(vector<vector<int>>* states){
  m_q = states;
}

void DFA::setTransitions(map<pair<vector<int>,string>,vector<int>> transitions){
  m_transition = transitions;
}

void DFA::setAccept(vector<vector<int>> acceptStates){
  m_acceptStates = acceptStates;
}

void DFA::setNewKeys(vector<pair<vector<int>,string>> newKeys){
  for(int i = 0; i < newKeys.size(); i++){
    m_newKeys->push_back(newKeys[i]);
  }
}

vector<vector<int>>* DFA::getStates(){
  return m_q;
}

vector<pair<vector<int>,string>>* DFA::getNewKeys(){
  return m_newKeys;
}
