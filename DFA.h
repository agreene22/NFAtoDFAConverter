#include <iostream>
#include <vector>
#include <map>

using namespace std;

class DFA {
public:
  DFA();
  ~DFA();

  void setAlphabet(vector<char> alphabet);
  void setStartStates(vector<int> startStates);
  void setQ(vector<vector<int>>* states);
  void setTransitions(map<pair<vector<int>,string>,vector<int>> transitions);
  void setAccept(vector<vector<int>> acceptStates);
  void setNewKeys(vector<pair<vector<int>,string>> newKeys);

  vector<vector<int>>* getStates();
  vector<pair<vector<int>,string>>* getNewKeys();

private:
  vector<vector<int>>* m_q;
  vector<char> m_alphabet;
  vector<int> m_startStates;
  map<pair<vector<int>,string>,vector<int>> m_transition;
  vector<vector<int>> m_acceptStates;
  vector<pair<vector<int>,string>>* m_newKeys;
};
