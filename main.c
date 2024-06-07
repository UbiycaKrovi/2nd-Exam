#include <stdio.h>
#include <string.h>
#include <wchar.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

typedef struct {
    WordCount words[MAX_WORDS];
    int size;
} BagOfWords;

void initBagOfWords(BagOfWords *bag) {
    bag->size = 0;
}

void addWord(BagOfWords *bag, const char *word) {
    for (int i = 0; i < bag->size; i++) {
        if (strcmp(bag->words[i].word, word) == 0) {
            bag->words[i].count++;
            return;
        }
    }
    if (bag->size < MAX_WORDS) {
        strcpy(bag->words[bag->size].word, word);
        bag->words[bag->size].count = 1;
        bag->size++;
    }
}

void printBagOfWords(const BagOfWords *bag) {
    printf("\nHow many similar words in text:\n");
    for (int i = 0; i < bag->size; i++) {
        printf("%s: %d\n", bag->words[i].word, bag->words[i].count);
    }
}

void toLowerCase(wchar_t *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = towlower(str[i]);
    }
}

int main() {
    BagOfWords bag;
    initBagOfWords(&bag);
    
    char text[1000];
    wchar_t wtext[1000];
    wchar_t *token;

    printf("Input text:\n");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;

    mbstowcs(wtext, text, sizeof(wtext) / sizeof(wchar_t));

    token = wcstok(wtext, L" ,.!?;:()\t\n");
    while (token != NULL) {
        toLowerCase(token);

        char narrowToken[MAX_WORD_LENGTH];
        wcstombs(narrowToken, token, sizeof(narrowToken));

        addWord(&bag, narrowToken);

        token = wcstok(NULL, L" ,.!?;:()\t\n");
    }

    printBagOfWords(&bag);

    return 0;
}