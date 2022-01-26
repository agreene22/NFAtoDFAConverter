#include "FileProcessor.h"

using namespace std;

int main(int argc, char const *argv[]) {

  string fileName;
  FileProcessor* fp;

  cout << "Please enter an nfa file with extension '.nfa' " << endl;
  cin >> fileName;

  fp = new FileProcessor(fileName,"newDFA.dfa");

  NFA* nfa = fp->readFile();
  // DFA* dfa;
  TransitionFunction* tf = new TransitionFunction(nfa);
  tf->epsilonClosure();
  DFA* dfa = tf->generateDFA();
  fp->writeFile(dfa);

  delete fp;
  delete nfa;
  // delete dfa;

  return 0;
}
