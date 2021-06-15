// C implementation of search and insert operations
// on Trie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
void insert(struct TrieNode* root, char* word)
{
    struct TrieNode *pCrawl = root;
    for(int i=0; word[i] != '\0'; i++)
    {
        if(pCrawl->children[word[i]-'a'] == NULL)
        {
            pCrawl->children[word[i]-'a'] = getNode();
        }
        pCrawl = pCrawl->children[word[i]-'a'];
    }
    pCrawl->isEndOfWord = true;
    pCrawl->count+=1;
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
void readFromFile(struct TrieNode *root, char *fileName){
    FILE *fp = NULL;

    fp = fopen(fileName,"r");
    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }
    char line[100];
    while (fgets(line,100,fp) != NULL)
    {
        char tmp[100];
        strcpy(tmp,line);
        char *token = strtok(tmp,"\n");
        insert(root,token);
    }
}
void writeToFile(struct TrieNode *root,char *fileName){
    FILE *out = NULL;

    out = fopen(fileName,"w");

    char wordArray[100];

    printAllToFile(root, wordArray, 0, out);
}
// Driver
int main()
{
	struct TrieNode *root = getNode();
    readFromFile(root,"data1.txt");
    readFromFile(root,"data2.txt");
    readFromFile(root,"data3.txt");
    readFromFile(root,"data4.txt");
    readFromFile(root,"data5.txt");
    readFromFile(root,"data6.txt");
    readFromFile(root,"data7.txt");
    readFromFile(root,"data8.txt");
    readFromFile(root,"data9.txt");
    readFromFile(root,"data10.txt");
    writeToFile(root,"out1.txt");

	return 0;
}
