#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE 256
#define WORD 24
#define MAXLINES 250
#define BUFFERSIZE LINE*WORD*MAXLINES
#define new_min(x,y) (((x) <= (y)) ? (x) : (y))
#define new_max(x,y) (((x) >= (y)) ? (x) : (y))

void LCS(char* m, char* n, int mSize, int nSize);
int getLine(char* s);
int getword(char* w);
int substring(char *str1, char *str2);
char* HeyWord(char *str);
char* HeyLine(char *str);
int checkMyWords(char *str, char* word);
void print_lines(char *str, char *word);
void print_similar_words(char * str, char *word);
void takeTeChoice(char *line, char *word, char *choice);
void tryingSomthing(char* str);
void print_similar_words2(char* str, char *word);
int lcsLenghtDynamic(char* m, char* n, int mSize, int nSize);
void print_similar_wordsLcs(char* str, char *word, char **biggest, int* max);


int main(int argc, char* argv[]){
    if (argv[2]==NULL||argv[1]==NULL){
        printf("didn't have all of the arguments\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("can't find file\n");
        return 1;
    }
    char *word = malloc(24);
    word = argv[2];
    char *line = NULL;
    size_t size;
    char *big = malloc(24);
    int max = 0;
    while (getline(&line, &size, fp) != -1) {
        print_similar_wordsLcs(line, word, &big, &max);
        char *line = NULL;
        size_t size1;
    }
    printf("\nWord - %s\n", big);
    //printf("big - %d\n", max);
    free(big);
    return 0;
}


int getLine(char* s)
{
    char *ptr = s;
    int count = 0;
    while (*ptr != '\n'&& *ptr != '\r')
    {
        count = count + 1;
        ptr = ptr + 1;
    }
    return count;
}
int getword(char* w)
{
    int count = 0;
    char *ptr = w;
    while(*ptr != ' '&& *ptr != '\n' && *ptr != '\t' &&  *ptr != '\0' && *ptr != '\r')
    {
        count = count + 1;
        ptr = ptr + 1;
    }
    return count;
}
//return 1 if str2 is in str1, else return 0
int substring(char *str1, char *str2)
{
    while (*str1 != ' ' && *str1 != '\t' && *str1 != '\n' && *str1 != '\0'&& *str1 != '\r')
    {
        if (*str2 == ' ' || *str2 == '\t' || *str2 == '\n' || *str2 == '\0' || *str2 == '\r')
        {
            return 1;
        }
        if (*str1 == *str2)
        {
            str2 = str2 + 1;
        }
        str1 = str1 + 1;
    }
    //edge case
    if (*str2 == ' ' || *str2 == '\t' || *str2 == '\n' || *str2 == '\0'||*str2 == "" || *str2 == '\r')
    {
        return 1;
    }
    return 0;
}
char* HeyWord(char *str){
    char word [WORD] = {0};
    int index = 0;
    while(*str != '\n' && *str != '\t' && *str != ' ' && *str != '\0' && *str != '\r')
    {
        word[index] = *str;
        str = str + 1;
        index = index + 1;
    }
    int a = getword(word);
    char *str2 = malloc(a);
    for (int j = 0; j < a; j++)
    {
        str2[j] = word[j];
    }
    str2[a] = '\0';
    return str2;
}
//mabye should add one more statment
char* HeyLine(char *str){
    char line [LINE]  = {0};
    int index = 0;
    while(*str != '\n' && *str != '\r'){
        line[index] = *str;
        str = str + 1;
        index = index + 1;
    }
    line[index] = '\n';
    int a = getLine(line);
    char *str2 = malloc(a+1);
    for (int i = 0; i < a; i++)
    {
        str2[i] = line[i];
    }
    str2[a] = '\n';
    return str2;
}
int checkMyWords(char *str, char *word){
    int index = 0;
    while ( *str != '\n'&&index<LINE+1 && *str != '\r')
    {
        if(*str == '\t' || *str == ' ' || *str == '\0' || *str == '\r'){
            str = str + 1;
        }else{
            char* wordInStr = HeyWord(str);
            if(substring(wordInStr, word )> 0){
                return 1;
            }
            str = str + strlen(wordInStr);
            index = index + getword(wordInStr) - 1;
        }
        index++;
    }
    return 0;
}
//option a
//void print_lines(char *str, char *word) {
//    char *s = HeyLine(str);
//    if (checkMyWords(str, word) > 0) {
//        for (int i = 0; i < strlen(s); i++) {
//            printf("%c", *str);
//            str = str + 1;
//        }
//    } else {
//        str = str + strlen(s);
//    }
//}

//void print_similar_words2(char* str, char *word){
//
//    int index = 0;
//    while ( *str != '\n'&&index<LINE+1 && *str != '\r')
//    {
//        if(*str == '\t' || *str == ' ' || *str == '\0' || *str == '\r'){
//            str = str + 1;
//        }else{
//            char* wordInStr = HeyWord(str);
//            if(substring(wordInStr, word )> 0){
//                printf("%s\n", wordInStr);
//            }
//            str = str + strlen(wordInStr);
//            index = index + getword(wordInStr) - 1;
//        }
//        index++;
//    }
//}


//void print_similar_wordsLcs2(char* str, char *word){
//
//    int index = 0;
//    int max = 0;
//    int good = 0;
//    while ( *str != '\n'&&index<LINE+1 && *str != '\r')
//    {
//        if(*str == '\t' || *str == ' ' || *str == '\0' || *str == '\r'){
//            str = str + 1;
//        }else{
//            int si = getword(str);
//            char* wordInStr = malloc(si);
//            wordInStr = HeyWord(str);
//            good = lcsLenghtDynamic(word,wordInStr,strlen(word),strlen(wordInStr));
//            printf("%d---", good);
//            if(good >= max){
//                max = good;
//                for (int i = 0; i < si; ++i) {
//                    printf("%c",wordInStr[i]);
//                }
//                printf("--");
////                printf("%d\n", good);
//            }
//            str = str + strlen(wordInStr);
//            index = index + getword(wordInStr) - 1;
//            free(wordInStr);
//        }
//        index++;
//    }
//    printf("%d\n", max);
//}


void print_similar_wordsLcs(char* str, char *word, char **biggest, int* max){

    int index = 0;
    while ( *str != '\n'&&index<LINE+1 && *str != '\r')
    {
        if(*str == '\t' || *str == ' ' || *str == '\0' || *str == '\r'){
            str = str + 1;
        }else{
            char* wordInStr = HeyWord(str);
            int good = lcsLenghtDynamic(word,wordInStr,strlen(word),strlen(wordInStr));
            if(good > *max){
                *max = good;
                *biggest = wordInStr;
            }
            str = str + strlen(wordInStr);
            index = index + getword(wordInStr) - 1;
        }
        index++;
    }
}

int lcsLenghtDynamic(char* m, char* n, int mSize, int nSize){
    //build the matrix
    int ** matrix = (int**)malloc(sizeof(int*)*(mSize+1));
    for (int i = 0; i < mSize+1; ++i) {
        matrix[i] = (int*)malloc(sizeof(int)*(nSize+1));
    }
    for (int i = 0; i < mSize+1; ++i) {
        for (int j = 0; j < nSize+1; ++j) {
            matrix[i][j]=0;
        }
    }
    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < nSize; j++)
        {
            if(m[i] == n[j]){
                matrix[i+1][j+1] = 1 + matrix[i][j];
            }else{
                matrix[i+1][j+1] = new_max(matrix[i][j+1], matrix[i+1][j]);
            }
        }
    }
    free(matrix);
    return matrix[mSize][nSize];
}

void LCS(char* m, char* n, int mSize, int nSize) {
    //build the matrix
    int matrix[mSize + 1][nSize + 1];
    for (int i = 0; i < mSize + 1; i++) {
        for (int j = 0; j < nSize + 1; j++) {
            matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < mSize; i++) {
        for (int j = 0; j < nSize; j++) {
            if (m[i] == n[j]) {
                matrix[i + 1][j + 1] = 1 + matrix[i][j];
            } else {
                matrix[i + 1][j + 1] = new_max(matrix[i][j + 1], matrix[i + 1][j]);
            }
        }
    }
}
