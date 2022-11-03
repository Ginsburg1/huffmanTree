#include <stdio.h>
//#include<string.h>
#include <stdlib.h>
#include "linkedList.h"



LinkedList* llCreate() {
  return NULL;
}

int llIisEmpty(LinkedList* ll) {
  return (ll == NULL);
}//stuctures; 

void llDisplay(LinkedList* ll) {

  LinkedList* p = ll;
  printf("[");

  while (p != NULL) {
    printf("(%d, %d), ",p->value->freq,p->value->value);
    p = p->next;
  }
  printf("]\n");
}

void llAddInOrder(LinkedList** head_ref, huffmanTree* new_node){
     LinkedList* current = *head_ref;
     LinkedList* ht = (LinkedList*)malloc(1 * sizeof(LinkedList));
        ht->value = new_node;

   if (*head_ref == NULL || (*head_ref)->value->freq >= new_node->freq) {
        if (*head_ref == NULL){
                llAdd(head_ref,ht->value);
        }else{
                ht->next = *head_ref;
                (*head_ref)->value = new_node;
        }
   } else {
        while (current->next != NULL && current->next->value->freq < new_node->freq) {
        current = current->next;
      }
        LinkedList* temp  = current->next;
        ht->next = temp;
        current->next = ht;
    }
}

void llAdd(LinkedList** ll, huffmanTree* htNode){
        // Create the new node
        LinkedList* newNode = (LinkedList*) malloc(1 * sizeof (LinkedList));
        newNode->value = htNode;
        newNode->next = NULL;

        // Find the end of the list
        LinkedList* p = *ll;
        if (p == NULL) { // Add first element
        *ll = newNode;  // This is why we need 11 to be a **
        }else {
        while (p->next != NULL) {
                p = p->next;
        }
        // Attach it to the end
        p->next = newNode;
        }
}

int llCombine(LinkedList** head, huffmanTree* hTree){
        huffmanTree* ht = (huffmanTree*)malloc(1 * sizeof(huffmanTree));
        LinkedList* current = *head;
        huffmanTree* left;
        huffmanTree* right;

        left = current->value;
        right = current->next->value;

        left->TF = 0;
        right->TF = 1;


        int temp = 0;
        temp = left->freq;
        temp += right->freq;
        left->parent = ht;
        right->parent = ht;


        ht->lChild = left;
        ht->rChild = right;
        ht->freq = temp;
        ht->value = -1;

if (left ->value == -1){
        hTree[left->value] = *left;
        }
if (right->value == -1){
        hTree[right->value] = *right;
}
        llremoveFirst(head);
        llremoveFirst(head);
        llAddInOrder(head,ht);
return 0;
        }

int llremoveFirst(LinkedList** ll){
    struct node *temp;
        if(ll == NULL){
    }
    else{
        temp = *ll;
        *ll  = (*ll)->next;
    }
return 0;
}

void llFindCodes(huffmanTree* findH, int** arr, int* countFlip){
        int temp = 0;
        while(findH->parent!= NULL){
                *((*arr) + temp) = findH->TF;
                temp++;
                findH = findH->parent;
        }
        *countFlip = temp;
}


void llFree(LinkedList* ll) {
  LinkedList* p = ll;
  while (p != NULL) {
    LinkedList* oldP = p;
    p = p->next;
   free(oldP);
  }

}
