#include <fstream>
#include <iostream>
#include "TransitionFunction.h"

using namespace std;

class FileProcessor{
public:
  FileProcessor();
  FileProcessor(string inFile, string outFile);
  ~FileProcessor();

  NFA* readFile();
  void writeFile(DFA* dfa);

private:
  ifstream inFS;
  ofstream outFS;
  string m_inFile;
  string m_outFile;
};
