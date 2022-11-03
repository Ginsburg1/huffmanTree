#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "linkedList.h"
#include "hcompress.h"

int main(int argc, char *argv[]) {
  // Check the make sure the input parameters are correct

   if (argc != 3) {
      printf("Error: The correct format is \"hcompress -e filename\" or \"hcompress -d filename.huf\"\n"); fflush(stdout);

    exit(1);

  }

  // Create the frequency table by reading the generic file

  huffmanTree* leafNodes = createFreqTable("decind.txt");

  // Create the huffman tree from the frequency table

  huffmanTree* treeRoot = createHuffmanTree(leafNodes);

  // encode

  if (strcmp(argv[1], "-e") == 0) {

    // Pass the leafNodes since it will process bottom up

    encodeFile(argv[2], leafNodes);

  } else { // decode

//    Pass the tree root since it will process top down

    decodeFile(argv[2], treeRoot);

  }

  return 0;

}
//Creates the huffman Tree with all of the values
//value stores the ASCII code
//freq stores the amount of times each ASCII shows up in the document
huffmanTree* createFreqTable(char* name){

  huffmanTree* leafNodes = (huffmanTree*) malloc(127 * sizeof(huffmanTree));
  FILE* ptr;
  char ch;
  ptr = fopen(name, "r");
  int temp = 0;
  do {
    temp ++;
    ch = fgetc(ptr);
    leafNodes[(int) ch].freq += 1;
    leafNodes[(int) ch].value = ch;
    } while (ch != EOF);
  fclose(ptr);
  return leafNodes;
}

//Takes the huffman Tree and stores it into a linked List
//All of the huffmanTree nodes are in the same location so the 
//code is able to up and down
//AddInOrder also sets the parent and child nodes
huffmanTree* createHuffmanTree(huffmanTree* leafNodes) {

LinkedList* newl = llCreate();

for (int j = 0; j < 128; j++){
llAddInOrder(&newl,&leafNodes[j]);
}
llremoveFirst(&newl);

do{
        llCombine(&newl,leafNodes);
}while(newl->next != NULL);

huffmanTree* rValue = newl->value;
return rValue;
}

//Encode file reads in the files and does up the tree indicating
//if the node is a right or left child. Every 8 elements, the code prints a 
//character until the end of the file.
void encodeFile(char* filename, huffmanTree* leafNodes){
        FILE* ptr = fopen(filename, "r");
        FILE* encodeF = fopen((strcat(filename, ".huf")), "w");
        int countFlip = 0;
        int* arrFlip = (int*)malloc(sizeof(int) *20);
        unsigned char comp = 0;
        int compCount = 0;
        char ch;

        do {
        countFlip = 0;

        ch = fgetc(ptr);
        int z = (int)(ch);
        for(int e =0; e< 20; e++){
                arrFlip[e] = 0;
        }
        if(z == -1){
                //Do nothing
        }else{
                        llFindCodes(&leafNodes[z], &arrFlip, &countFlip);
                        for(int q = countFlip-1; q >= 0 ; q--){
                        comp = (comp << 1) + arrFlip[q];
                        compCount++;
                        if (compCount == 8){
                                fprintf(encodeF,"%c", comp);
                                comp = 0;
                                compCount = 0;
                        }
                }
        }
        } while (ch != EOF);
        if (comp < 8){
                int temp  = 7 - compCount;
                comp = (comp << temp);
                fprintf(encodeF,"%d ", comp);
        }

fclose(encodeF);
fclose(ptr);
}

//Decode file takes in in the file with the chars that are incoded. It then
//takes in the file and reads it in bit by bit. It then goes down the tree
//until it reaches the bottom and that chacter is printed to the file.
void decodeFile(char* filename, huffmanTree* treeRoot) {



  FILE* file = fopen(filename, "r");
  FILE* decodeF = fopen(strcat(filename, ".dec"), "w");

  unsigned char tempChar = 0;

  huffmanTree* hNode = treeRoot;

  while (fscanf(file, "%c", &tempChar) != EOF) {
  unsigned char tempInt = tempChar;

  for (int i = 7; i >= 0; i--) {
     char TF =  (tempInt & (1 << i)) >> i;

        if (hNode->rChild == NULL && hNode->lChild == NULL){
        fprintf(decodeF, "%c", hNode->value);
        hNode = treeRoot;
        i++;
      }else {
          if (TF && hNode->rChild != NULL) {
                hNode = hNode->rChild;
          } else if (!TF && hNode->lChild != NULL) {
                hNode = hNode->lChild;
                }
        }
  }
}
fclose(decodeF);
fclose(file);
}
