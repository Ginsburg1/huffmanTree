typedef struct htNode{
        int value;
        int freq;
        int TF;
        struct htNode* lChild;
        struct htNode* rChild;
        struct htNode* parent;
        }huffmanTree;

typedef struct node {
        huffmanTree* value;
        struct node* next;
} LinkedList;

LinkedList* llCreate();
int llIsEmpty(LinkedList* ll);
void llDisplay(LinkedList* ll);
void llAdd(LinkedList** ll, huffmanTree* htNode);
void llAddInOrder(LinkedList** head_ref, huffmanTree* new_node);
int llCombine(LinkedList** head, huffmanTree* hTree);
void llFree(LinkedList* ll);
int llremoveFirst(LinkedList** ll);
void llFindCodes(huffmanTree* findH, int** arr, int* countFlip);

