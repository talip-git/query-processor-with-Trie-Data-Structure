//
// Created by sina on 5.06.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include "Task1Trie.c"
void readFromFile(struct TrieNode *root, char *fileName,char mem[64][64]){
    FILE *fp = NULL;

    fp = fopen(fileName,"r");
    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }
    char line[100];
    while(1){
        int i = 0;
        int c = fscanf(fp,"%[^\n]%*c", line);
        if(c == EOF){
            break;
        }
        while (c != EOF && i<64)
        {
            char tmp[100];
            strcpy(tmp,line);
            char *token = strtok(tmp,"\n");
            strcpy(mem[i],token);
            i++;
            c = fscanf(fp,"%[^\n]%*c", line);
        }
        for (int j = 0; j <64 ; ++j) {
            insert(root,mem[j]);
        }
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
    char mem[64][64];

    readFromFile(trie,"data1.txt",mem);
    readFromFile(trie,"data2.txt",mem);
    readFromFile(trie,"data3.txt",mem);
    readFromFile(trie,"data4.txt",mem);
    readFromFile(trie,"data5.txt",mem);
    readFromFile(trie,"data6.txt",mem);
    readFromFile(trie,"data7.txt",mem);
    readFromFile(trie,"data8.txt",mem);
    readFromFile(trie,"data9.txt",mem);
    readFromFile(trie,"data10.txt",mem);
    writeToFile(trie);
    return 0;
}
