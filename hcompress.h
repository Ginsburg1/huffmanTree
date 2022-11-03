huffmanTree* createFreqTable(char* name);
huffmanTree* createHuffmanTree(huffmanTree* leafNodes);
void encodeFile(char* filename, huffmanTree* leafNodes);
void decodeFile(char* filename, huffmanTree* treeRoot);

