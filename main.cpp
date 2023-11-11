#include <fstream>
#include <iostream>
#include <cstring>
#include <string>

//idImpianto;descCarburante;prezzo;isSelf;dtComu
struct prezzo{
  int idImpianto;
  char descCarburante[25];
  float price;
  bool isSelf;
  char dateTime[19];
};

struct Node{
  char descCarburante[25];
  int numPrezzi;
  float totPrezzi;
  Node *next;
};

struct List{
  Node *head;
};

void addNode(Node *node, List *list){
  if(list->head == NULL){
    list->head = node;
    return;
  }
  
  Node *root = list->head;
  while(root->next == NULL){
    root = root->next;
  }
  
  root->next = node;
}

void updateNode(List *list, char descCarburante[25], float price){
  if(list->head == NULL){
    return;
  }

  Node *root = list->head;
  while(root != NULL && strcmp(root->descCarburante, descCarburante) == 0){
    root = root->next;
  }

  if(root == NULL){
    return;
  }

  root->totPrezzi += price;
  root->numPrezzi += 1;
}

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "too few arguments passed: missing input file" << endl;
    return 0;
  }
  
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
          record = {};
          break;
        case 2:
          p.price = atof(record);
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

  return 0;
}
