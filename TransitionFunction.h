#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <fstream>
#include "NFA.h"
#include "DFA.h"

using namespace std;

class TransitionFunction{
public:
  TransitionFunction();
  TransitionFunction(NFA* nfa);
  ~TransitionFunction();

  vector<int> epsilonClosure();
  DFA* generateDFA();
  map<pair<vector<int>,string>,vector<int>> createTransition(vector<char> alpha, string currLet, vector<int> currStates, map<pair<vector<int>,string>,vector<int>> dfaTransitions);

private:
  NFA* m_nfa;
  vector<vector<int>>* dfaStates;
  queue<vector<int>> newStates;
  vector<pair<vector<int>,string>> newKeys;
  vector<int> epsilonTrans;
  ofstream outFS;
};
