#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class NFA{
public:
  NFA();
  NFA(vector<int> q, vector<char> alphabet, int startState, map<string,vector<int>> transition, vector<int> acceptStates, vector<string> stateInputPairs);
  ~NFA();

  int getStartState();
  map<string,vector<int>> getTransitions();
  vector<string> getStateInputPairs();
  vector<char> getAlphabet();
  vector<int> getAcceptStates();

private:
  vector<int> m_q;
  vector<char> m_alphabet;
  int m_startState;
  map<string,vector<int>> m_transition;
  vector<int> m_acceptStates;
  vector<string> m_stateInputPairs;
};
