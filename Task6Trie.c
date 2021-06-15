//
// Created by sina on 5.06.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include "Task1Trie.c"
void readFromFile(char *fileName,char mem[7000][7000]){
    FILE *fp = NULL;

    fp = fopen(fileName,"r");
    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }
    char line[100];
    int i = 0;
    int c = fscanf(fp,"%[^\n]%*c", line);
    while (c != EOF)
    {
        char tmp[100];
        strcpy(tmp,line);
        char *token = strtok(tmp,"\n");
        strcpy(mem[i],token);
        i++;
        c = fscanf(fp,"%[^\n]%*c", line);
    }
}
void addFromMemory(struct TrieNode *root,char mem[7000][7000]){
    for (int i = 0; i <30; ++i) {
        insert(root,mem[i]);
    }
}
void printWord2(char* str, int n,struct TrieNode *pCrawl,FILE *out)
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
        printWord2(wordArray, pos,pCrawl,out);
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
void writeToFile(struct TrieNode *root){
    FILE *out = NULL;

    out = fopen("output1.txt","w");

    char wordArray[100];

    printAllToFile(root, wordArray, 0, out);
}
int main(){
    struct TrieNode *trie = getNode();
    char mem[7000][7000];

    readFromFile("data1.txt",mem);
    addFromMemory(trie,mem);
    readFromFile("data2.txt",mem);
    addFromMemory(trie,mem);
    readFromFile("data3.txt",mem);
    addFromMemory(trie,mem);
    readFromFile("data4.txt",mem);
    addFromMemory(trie,mem);
    readFromFile("data5.txt",mem);
    addFromMemory(trie,mem);
    readFromFile("data6.txt",mem);
    addFromMemory(trie,mem);
    readFromFile("data7.txt",mem);
    addFromMemory(trie,mem);
    readFromFile("data8.txt",mem);
    addFromMemory(trie,mem);
    readFromFile("data9.txt",mem);
    addFromMemory(trie,mem);
    readFromFile("data10.txt",mem);
    writeToFile(trie);
    return 0;
}

