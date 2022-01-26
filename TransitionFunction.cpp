#include "TransitionFunction.h"

TransitionFunction::TransitionFunction(){
  m_nfa = new NFA();
  dfaStates = new vector<vector<int>>();
}

TransitionFunction::TransitionFunction(NFA* nfa){
  m_nfa = nfa;
  dfaStates = new vector<vector<int>>();
}

TransitionFunction::~TransitionFunction(){
  delete m_nfa;
  delete dfaStates;
}

vector<int> TransitionFunction::epsilonClosure(){
  vector<int> newStarts;
  vector<int> epState;

  int startState = m_nfa->getStartState();
  newStarts.push_back(startState);

  map<string,vector<int>> transitions = m_nfa->getTransitions();
  vector<string> keys = m_nfa->getStateInputPairs();

  for(int i = 0; i < keys.size(); i++){
    int currKey = ((int) keys[i][0] - 48);
    if(currKey == startState){
      size_t found = keys[i].find("EPS");
      if (found!=std::string::npos){
        newStarts.push_back(transitions[keys[i]][0]);
        epsilonTrans.push_back(currKey);
      }
    }
  }

  return newStarts;
}

DFA* TransitionFunction::generateDFA(){
  DFA* m_dfa = new DFA();
  vector<char> alpha = m_nfa->getAlphabet();
  m_dfa->setAlphabet(alpha);

  vector<int> startStates = epsilonClosure();
  m_dfa->setStartStates(startStates);

  vector<int> nfaAccept = m_nfa->getAcceptStates();

  vector<string> keys = m_nfa->getStateInputPairs();
  map<string,vector<int>> transitions = m_nfa->getTransitions();
  pair<pair<vector<int>,string>,vector<int>> currPair;

  // vector<pair<vector<int>,string>> newKeys;
  map<pair<vector<int>,string>,vector<int>> dfaTransitions;
  dfaStates->push_back(startStates);
  newStates.push(startStates);

  while(!newStates.empty()){
    vector<int> currState = newStates.front();
    for(int i = 0; i < alpha.size(); i++){
      string let = "";
      let += alpha[i];
      dfaTransitions = createTransition(alpha,let,currState,dfaTransitions);
    }
    newStates.pop();
  }

  m_dfa->setQ(dfaStates);
  m_dfa->setNewKeys(newKeys);
  m_dfa->setTransitions(dfaTransitions);

  vector<vector<int>> dfaAccept;

  for(int n = 0; n < nfaAccept.size(); n++){
    for(int d = 0; d < newKeys.size(); d++){
      for(int ds = 0; ds < get<0>(newKeys[d]).size(); ds++){
        if(get<0>(newKeys[d])[ds] == (nfaAccept[n]-48)){
          dfaAccept.push_back(get<0>(newKeys[d]));
        }
      }
    }
  }

  m_dfa->setAccept(dfaAccept);


  outFS.open("newDFA.dfa");
  if(!outFS.is_open()){
    cout << "Error writing to DFA file" << endl;
    exit(1);
  }
  for(int i = 0; i < newKeys.size(); i ++){
    string currState = "{";
    for(int j = 0; j < get<0>(newKeys[i]).size(); j++){
      if(get<0>(newKeys[i])[j] != -1){
        currState += to_string(get<0>(newKeys[i])[j]);
      }else{
        currState += "EM";
      }
      if(j != get<0>(newKeys[i]).size() -1){
        currState += ", ";
      }
    }
    currState += "}\t";
    outFS << currState;
    i++;
  }

  outFS << "\n";

  for(int ab = 0; ab < alpha.size(); ab++){
    outFS << alpha[ab];
    outFS << "\t";
  }

  outFS << "\n";

  startStates = epsilonClosure();
  string currState = "{";
  for(int s = 0; s < startStates.size(); s++){
    currState += to_string(startStates[s]);
    if(s != startStates.size() - 1){
      currState += ", ";
    }
  }
  currState += "}\t";
  outFS << currState;

  outFS << "\n";

  for(int a = 0; a < dfaAccept.size(); a++){
    string currState = "{";
    for(int b = 0; b < dfaAccept[a].size(); b++){
      currState += to_string(dfaAccept[a][b]);
      if(b != dfaAccept[a].size() -1){
        currState += ", ";
      }
    }
    currState += "}\t";
    outFS << currState;
    a++;
  }

  outFS << "\n";

  for(int j = 0; j < newKeys.size(); j++){
    pair<vector<int>,string> currKey (get<0>(newKeys[j]),get<1>(newKeys[j]));
    string currState = "{";
    for(int l = 0; l < get<0>(currKey).size(); l++){
      if(get<0>(currKey)[l] != -1){
        currState += to_string(get<0>(currKey)[l]);
      }else{
        currState += "EM";
      }
      if(l != get<0>(currKey).size() -1){
        currState += ", ";
      }
    }
    currState += "},\t";
    currState += get<1>(currKey);

    currState += " = {";
    for(int i = 0; i < dfaTransitions[currKey].size(); i++){
      if(dfaTransitions[currKey][i] != -1){
        currState += to_string(dfaTransitions[currKey][i]);
      }else{
        currState += "EM";
      }
      if(i != dfaTransitions[currKey].size() -1){
        currState += ", ";
      }
    }
    currState += "}\n";
    outFS << currState;
  }

  outFS.close();
}

map<pair<vector<int>,string>,vector<int>> TransitionFunction::createTransition(vector<char> alpha, string currLet, vector<int> currStates, map<pair<vector<int>,string>,vector<int>> dfaTransitions){

  vector<string> keys = m_nfa->getStateInputPairs();
  map<string,vector<int>> transitions = m_nfa->getTransitions();

  vector<int> currTran;
  vector<int> currStats;
  string trans = "";
  bool found = false;
  for(int i = 0; i < keys.size(); i ++){
    string origKey = keys[i];
    int stat = ((int) origKey[0] - 48);
    trans = origKey.substr(1,string::npos);
    for(int j = 0; j < currStates.size(); j++){
      if(stat == currStates[j]){
        if(trans == "EPS"){
          found = true;
          continue;
        }else{
          for(int let = 0; let < alpha.size(); let++){
            if(currLet == trans){
              found = true;
              vector<int> oldT = transitions[origKey];
              for(int t = 0; t < oldT.size(); t++){
                currTran.push_back(oldT[t]);
                for(int eps = 0; eps < epsilonTrans.size(); eps++){
                  if(oldT[t] == epsilonTrans[eps]){
                    string check = "";
                    check += to_string(oldT[t]);
                    check += "EPS";
                    currTran.push_back(transitions[check][0]);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if(found == false && currTran.size() == 0){
    currTran.push_back(-1);
  }

  sort(currTran.begin(),currTran.end());

  auto last = std::unique(currTran.begin(), currTran.end());
  currTran.resize(distance(currTran.begin(),last));


  pair<vector<int>,string> currKey (currStates,currLet);
  pair<pair<vector<int>,string>,vector<int>> currPair (currKey,currTran);
  for(int m = 0; m < newKeys.size(); m++){
    if(newKeys[m] == currKey){
      dfaTransitions[currKey] = currTran;
      return dfaTransitions;
    }
  }

  dfaTransitions.insert(currPair);
  dfaStates->push_back(currTran);
  newStates.push(currTran);
  newKeys.push_back(currKey);

  return dfaTransitions;
}
