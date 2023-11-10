#include <fstream>
#include <iostream>
#include <cstring>

//idImpianto;descCarburante;prezzo;isSelf;dtComu
struct prezzo{
  int idImpianto;
  char descCarburante[20];
  float price;
  bool isSelf;
  char date[10];
  char time[8];
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
  bool timeIns = 0;
  int recordNum = 0;
  prezzo p = {};
  fIn >> line;
  while(fIn >> line && lineNum < 40){
    cout << lineNum << endl;
    int numChar = 0;
    if(timeIns){
      recordNum = 0;
      timeIns = 0;
      p = {};
    }
    while(strlen(line) > numChar){
      char *record = new char[50];
      int flag = 0;
      while(line[numChar] != ';' && line[numChar] != '\n'){
        record[flag] = line[numChar];
        numChar++;
        flag++;
      }
      switch(recordNum){
        case 0:
          p.idImpianto = atoi(record);
          break;
        case 1:
          strcpy(p.descCarburante,record);
          break;
        case 2:
          p.price = atof(record);
          break;
        case 3:
          p.isSelf = atoi(record);
          break;
        case 4:
          strcpy(p.date,record);
          break;
        case 5:
          strcpy(p.time,record);
          timeIns = 1;
          break;
        default:
          break;
      }
      numChar++;
      recordNum++;
      delete [] record;
    }
    if(timeIns){
				  cout << "prezzo{" << endl;
						cout << "\t"  << p.idImpianto << "," << endl;
						cout << "\t"  << p.descCarburante << "," << endl;
						cout << "\t"  << p.price << "," << endl;
						cout << "\t"  << p.isSelf << ","<< endl;
						cout << "\t"  << p.date << "," << endl;
						cout << "\t"  << p.time << endl;
						cout << "}" << endl;
    }
    lineNum++;
  }

  delete [] line;
  return 0;
}
