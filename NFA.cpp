#include "NFA.h"

NFA::NFA(){
}

NFA::NFA(vector<int> q, vector<char> alphabet, int startState, map<string,vector<int>> transition, vector<int> acceptStates, vector<string> stateInputPairs){
  m_q = q;
  m_alphabet = alphabet;
  m_startState = startState;
  m_transition = transition;
  m_acceptStates = acceptStates;
  m_stateInputPairs = stateInputPairs;
}

NFA::~NFA(){
}

int NFA::getStartState(){
  return m_startState;
}

map<string,vector<int>> NFA::getTransitions(){
  return m_transition;
}

vector<string> NFA::getStateInputPairs(){
  return m_stateInputPairs;
}

vector<char> NFA::getAlphabet(){
  return m_alphabet;
}

vector<int> NFA::getAcceptStates(){
  return m_acceptStates;
}
