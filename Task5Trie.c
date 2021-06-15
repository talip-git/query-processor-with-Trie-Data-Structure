// C implementation of search and insert operations
// on Trie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    int count;
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};
struct ThreadParams{
    struct TrieNode *root;
    char *fileName;
};
pthread_mutex_t mutex;
// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = NULL;

    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    if (pNode)
    {
        int i;

        pNode->isEndOfWord = false;

        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }

    return pNode;
}
// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}
// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, char *key)
{
    int level;
    int length = strlen(key);
    int index;

    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
    pCrawl->count+=1;
}
// Helper function to print the word found
void printWord(char* str, int n,struct TrieNode *pCrawl,FILE *out)
{
    printf("%s ",str);
    printf("\t%d\n",pCrawl->count);
    fprintf(out,"%s \t%d\n",str,pCrawl->count);
}
void printAllToFile(struct TrieNode *root, char* wordArray, int pos, FILE *out)
{
    struct TrieNode *pCrawl = root;
    if(pCrawl == NULL)
        return;
    if(pCrawl->isEndOfWord)
    {
        printWord(wordArray, pos,pCrawl,out);
    }
    for(int i=0; i<ALPHABET_SIZE; i++)
    {
        if(pCrawl->children[i] != NULL)
        {
            wordArray[pos] = i+'a';
            printAllToFile(pCrawl->children[i], wordArray, pos + 1, out);
        }
    }
}
void* readFromFile(void* params){
    pthread_mutex_lock(&mutex);
    struct ThreadParams *param = params;
    FILE *fp = NULL;

    fp = fopen(param->fileName,"r");
    if (fp == NULL)
    {
        printf("File not found!\n");
    }
    else{
        char line[50];
        while (fgets(line,50,fp) != NULL)
        {
            char tmp[50];
            strcpy(tmp,line);
            char *token = strtok(tmp,"\n");
            insert(param->root,token);
        }
    }
    pthread_mutex_unlock(&mutex);
}
void writeToFile(struct TrieNode *root){
    FILE *out = NULL;

    out = fopen("output1.txt","w");
    char wordarray[100];

    printAllToFile(root,wordarray,0,out);
}
int main(){
    pthread_t p1,p2,p3,p4,p5,p6,p7,p8,p9,p10;
    pthread_mutex_init(&mutex,NULL);

    struct TrieNode *root = getNode();
    struct ThreadParams params;

    char fileName[50];

    strcpy(fileName,"data1.txt");

    params.root = root;
    params.fileName = fileName;

    pthread_create(&p1,NULL,&readFromFile,&params);
    pthread_join(p1,NULL);

    struct ThreadParams params2;
    strcpy(fileName,"data2.txt");
    params2.fileName = fileName;
    params2.root = getNode();

    pthread_create(&p2,NULL,&readFromFile,&params2);
    pthread_join(p2,NULL);

    struct ThreadParams params3;
    strcpy(fileName,"data3.txt");
    params3.fileName = fileName;
    params3.root = getNode();

    pthread_create(&p3,NULL,&readFromFile,&params3);
    pthread_join(p3,NULL);

    struct ThreadParams params4;
    strcpy(fileName,"data4.txt");
    params4.fileName = fileName;
    params4.root = getNode();

    pthread_create(&p4,NULL,&readFromFile,&params4);
    pthread_join(p4,NULL);

    struct ThreadParams params5;
    strcpy(fileName,"data5.txt");
    params5.fileName = fileName;
    params5.root = getNode();

    pthread_create(&p5,NULL,&readFromFile,&params5);
    pthread_join(p5,NULL);

    struct ThreadParams params6;
    strcpy(fileName,"data6.txt");
    params5.fileName = fileName;
    params5.root = getNode();

    pthread_create(&p6,NULL,&readFromFile,&params6);
    pthread_join(p6,NULL);

    struct ThreadParams params7;
    strcpy(fileName,"data7.txt");
    params5.fileName = fileName;
    params5.root = getNode();

    pthread_create(&p7,NULL,&readFromFile,&params7);
    pthread_join(p7,NULL);

    struct ThreadParams params8;
    strcpy(fileName,"data8.txt");
    params5.fileName = fileName;
    params5.root = getNode();

    pthread_create(&p8,NULL,&readFromFile,&params8);
    pthread_join(p8,NULL);

    struct ThreadParams params9;
    strcpy(fileName,"data9.txt");
    params5.fileName = fileName;
    params5.root = getNode();

    pthread_create(&p9,NULL,&readFromFile,&params9);
    pthread_join(p9,NULL);

    struct ThreadParams params10;
    strcpy(fileName,"data10.txt");
    params5.fileName = fileName;
    params5.root = getNode();

    pthread_create(&p10,NULL,&readFromFile,&params10);
    pthread_join(p10,NULL);

    return 0;
}

