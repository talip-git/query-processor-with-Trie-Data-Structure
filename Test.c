//
// Created by sina on 5.06.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "Task1Trie.c"
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
void writeToFile(struct TrieNode *root,char *fileName){
    FILE *out = NULL;

    out = fopen(fileName,"w");

    char wordArray[50];

    printAllToFile(root, wordArray, 0, out);
}
int main(){

    struct TrieNode *root = getNode();

    FILE *fp=NULL;

    fp = fopen("A.txt","r");

    if(fp == NULL){
        printf("File not found!");
        return 0;
    }

    char line[100];

    while (fgets(line,100,fp)!=NULL){
        char *token = strtok(line,"\n");
        insert(root,token);
        //printf("%s\n",token);
    }
    writeToFile(root,"b.txt");
    return 0;
}