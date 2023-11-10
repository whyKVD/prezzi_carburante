#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <unordered_map>

//idImpianto;descCarburante;prezzo;isSelf;dtComu
struct prezzo{
  int idImpianto;
  char descCarburante[25];
  float price;
  bool isSelf;
  char dateTime[19];
};

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "too few arguments passed: missing input file" << endl;
    return 0;
  }
  
  unordered_map<char[25],float> map;

  ifstream fIn(argv[1], ios::in);

  char line[100] = {};
  long lineNum = 0;
  int recordNum = 0;
  prezzo p = {};
  fIn >> line;
  while(fIn >> line /*&& lineNum < 3410*/){
    int numChar = 0;
    recordNum = 0;
    p = {};
    while(strlen(line) > numChar){
      char *record = new char[25];
      int flag = 0;
      while(line[numChar] != ';' && line[numChar] != '\n' && strlen(line) > numChar){
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
          if(map.find(p.descCarburante) == map.end()){
            map[p.descCarburante] = 0.0f;
          }
          record = {};
          break;
        case 2:
          p.price = atof(record);
          map[p.descCarburante] += p.price;
          break;
        case 3:
          p.isSelf = atoi(record);
          break;
        case 4:
          strcpy(p.dateTime,record);
          break;
        default:
          break;
      }
      numChar++;
      recordNum++;
      delete [] record;
    }
				/*cout << "prezzo{" << endl;
				cout << "\t"  << p.idImpianto << "," << endl;
				cout << "\t"  << p.descCarburante << "," << endl;
				cout << "\t"  << p.price << "," << endl;
				cout << "\t"  << p.isSelf << ","<< endl;
				cout << "\t"  << p.dateTime << "," << endl;
				cout << "}" << endl;*/
    cout << "reading..."  << lineNum /*<< endl*/ << "\r";
    lineNum++;
  }

  cout << map.begin()->first << endl;

  return 0;
}
