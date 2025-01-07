#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct transitionTable{
     int crrState;
     char inputSymbol;
     int outState;
};

int validateString(struct transitionTable* Entries, int initalState, char acceptingState[], char inputSymbol[], char inputStr[]){
     int currState = initalState;
     int inputSymbolLen = *(&inputSymbol + 1) - inputSymbol;
     for(int i = 0; i < strlen(inputStr); i++){
          int pos = 0;
          for(int j = 0; j < inputSymbolLen; j++){
               if(inputSymbol[j] == inputStr[i]){
                    pos = j;
                    break;         
               }
          }
          currState = Entries[((currState-1)*2)+pos].outState;
          printf("Current State : %d", currState);
     }

     int acceptingStateLen = *(&acceptingState + 1) - acceptingState;
     for(int i = 0; i < acceptingStateLen; i++){
          if(currState == acceptingState[i]) return 1;
     }
     return 0;
}

int main(){
     char *inputStr, *inputSymbol, *acceptingState;
     struct transitionTable* Entries;
     int noOfInputSymbol, noOfState, initialState, noOfAcceptingState;

     printf("Enter number of input symbol: ");
     scanf("%d", &noOfInputSymbol);
     inputSymbol = malloc(noOfInputSymbol*sizeof(char));     

     for(int i = 0; i < noOfInputSymbol; i++){
          printf("Enter the %d inputSymbol : ", i+1);
          scanf("%s", &inputSymbol[i]);
     }

     printf("Enter number of state: ");
     scanf("%d", &noOfState);
     printf("Enter initial state: ");
     scanf("%d", &initialState);

     printf("Enter number of accepting state: ");
     scanf("%d", &noOfAcceptingState);
     acceptingState = malloc(noOfAcceptingState*sizeof(char));

     for(int i = 0; i < noOfAcceptingState; i++){
          printf("Enter the %d acceptingState : ", i+1);
          scanf("%s", &acceptingState[i]);
     }
     
     int totalTableEntry = noOfInputSymbol*noOfState;
     Entries = (struct transitionTable*)malloc(totalTableEntry*sizeof(Entries));
     
     printf("Transition table : \n");
     int tableCounter = 0;
     for(int i = 0; i < noOfState; i++){
          for(int j = 0; j < noOfInputSymbol; j++){
               Entries[tableCounter].crrState = i+1;
               Entries[tableCounter].inputSymbol = inputSymbol[j];
               printf("%d to %c -> ", i+1, inputSymbol[j]);
               scanf("%d", &Entries[tableCounter].outState);
               tableCounter++;
          }
     }


     printf("Input string : ");
     scanf("%s", inputStr);

     if(validateString(Entries, initialState, acceptingState, inputSymbol, inputStr)) printf("Valid string. \n");
     else printf("Invalid string. \n");

     //https://www.geeksforgeeks.org/how-to-create-dynamic-array-of-structs-in-c/
     return 0;
}