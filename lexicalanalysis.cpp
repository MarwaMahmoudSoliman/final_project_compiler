#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<fstream>

using namespace std;

char theKewards[40][40] = {"if","int","else","switch","typedef","union",
              "unsigned","short","signed","void","long","register",
              "sizeof","static","volatile","while","auto","break","case","char","const","continue","default",
              "do","double","enum","extern","return","struct","float","for","goto"};

int matchKeyword(char mybuf[]){
  int j, M_Flag = 0;
  
  for(j = 0; j < 32; ++j){
    if(strcmp(theKewards[j], mybuf) == 0){
      M_Flag = 1;
      break;
    }
  }  
  return M_Flag;
}
 
int main(){
  char mychar, mybuf[15], operators[] = "+-*/%=";
  ifstream f("m.txt");
  int i = 0, j = 0;
  
  if(!f.is_open()){
    cout<<"There is an issue in opening this file"<<endl;
    exit(0);
  }
  
  while(!f.eof()){
    mychar = f.get();
       
    for(i = 0; i < 6; ++i){
      if(mychar == operators[i])
        cout << mychar << " : operator" << endl;
    }
       
    if(isalnum(mychar)){
      mybuf[j++] = mychar;
    }
    else if((mychar == ' ' || mychar == '\n') && (j != 0)){
      mybuf[j] = '\0';
      j = 0;
                      
      if(matchKeyword(mybuf) == 1)
        cout << mybuf << " is keyword" << endl;
      else
        cout << mybuf << " : identifier" << endl;
    }
  }
  
  f.close();
  
  return 0;
}
