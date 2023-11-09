#include <fstream>
#include <iostream>
#include <cstring>

//idImpianto;descCarburante;prezzo;isSelf;dtComu
struct prezzo{
  int idImpianto;
  char *descCarburante = new char[50];
  float prezzo;
  bool isSelf;
};

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "too few arguments passed: missing input file" << endl;
    return 0;
  }
  
  ifstream fIn(argv[1], ios::in);

  char* line = new char[255];
  int lineNum = 0;
  fIn >> line;
  while(fIn >> line && lineNum < 10){
    cout << lineNum << endl;
    prezzo *p = {};
    int numChar = 0;
    int recordNum = 0;
    while(strlen(line) > numChar){
      char *record = new char[50];
      int flag = 0;
      while(line[numChar] != ';'){
        record[flag] = line[numChar];
        numChar++;
        flag++;
      }
      cout << record << endl;
      switch(recordNum){
        case 0:
          p->idImpianto = atoi(record);
          cout << p->idImpianto << endl;
          break;
        case 1:
          strcpy(p->descCarburante,record);
          break;
        case 2:
          p->prezzo = atof(record);
          break;
        case 3:
          p->isSelf = atoi(record);
          break;
        default:
          break;
      }
      numChar++;
      recordNum++;
      delete [] record;
    }
    cout << p->idImpianto << endl;
    lineNum++;
    line = {};
  }

  delete [] line;
  return 0;
}
