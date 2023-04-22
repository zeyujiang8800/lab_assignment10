#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie {
    struct Trie *children[30];
    int count;
    //declare the children array for trie
} Trie;

void insert(Trie **ppTrie, char *word) {
    Trie *pTrie = *ppTrie;
    //create a pointer trie to be used for setting the children index
    if (pTrie == NULL) {
        //create a new root if the trie's empty
        pTrie = (Trie*) malloc(sizeof(Trie));
        pTrie->count = 0;
        for (int i = 0; i < 30; i++) {
            pTrie->children[i] = NULL;
            //set the children as an empty value for each element
        }
        *ppTrie = pTrie;
    }
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        //subtract the int by the ascii of a to get the index
        if (pTrie->children[index] == NULL) {
            //create a new child if it doesn't exist, which was declared bakc in the previous loop
            Trie *newTrie = (Trie*) malloc(sizeof(Trie));
            newTrie->count = 1;
            for (int i = 0; i < 30; i++) {
                newTrie->children[i] = NULL;
            }
            pTrie->children[index] = newTrie;
            //set the index of the pointer trie to the new trie.
        }
        pTrie = pTrie->children[index];
    }
    pTrie->count++;
    //increment the count after the pointer trie has set
}

int numberOfOccurances(Trie *pTrie, char *word) {
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        pTrie = pTrie->children[index];
    }
    return pTrie->count;
    //returns the count for the word
}

Trie *deallocateTrie(Trie *pTrie) {
    if (pTrie != NULL) {
        //keep on recursing if it's not freed
        for (int i = 0; i < 30; i++) {
            if (pTrie->children[i] != NULL) {
                deallocateTrie(pTrie->children[i]);
                //using recurssion, we free each of the children's allocations
            }
        }
        free(pTrie);
        return NULL;
    }
    else
        return NULL;
        //check if it's already freed
}

int main(void) {
    //read the number of the words in the dictionary
    //parse line by line, and insert each word to the trie data structure
    Trie *trie = NULL;
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
        insert(&trie, pWords[i]);
        //insert the words in the trie

    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);

    if (trie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
