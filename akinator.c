#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Tree.h"


char * getSentence(char*buffer){
    int i = 0;
    int str_len = 0;
    char* sentence = (char*) malloc(sizeof (char));
    while (buffer[i] != '-')
        i++;
    i++;
    while (buffer[i] != '\0'){
        sentence[str_len] = buffer[i];
        str_len++;
        i++;
        sentence = (char*)realloc(sentence, 1000 * sizeof (char));
    }
    sentence[str_len] = '\0';
    return sentence;
}


int getNum(char* buffer){
    int i = 0;
    int num_len = 0;
    char *num = (char*) malloc(sizeof (char));
    while (buffer[i] != '-'){
        num[num_len] = buffer[i];
        num_len++;
        i++;
        num = (char*)realloc(num ,1000 * sizeof (char));
    }
    num[num_len] = '\0';
    return atoi(num);

}


void FromFileToTree(TREE*tree, char*buffer){
    int number = getNum(buffer);
    char* str = getSentence(buffer);
    insert(tree, str, number);
}


void CreateNewData(char* savetxt, int savenum){
    char correct_answ[256];
    char new_qstn[256];
    char new_answ[4];
    int new_num;
    char* buffer = (char*) malloc(sizeof (char));
    char* save_answ;
    puts("What is the correct answer?");
    char c = getchar();
    gets( correct_answ);
    puts("With what question can your answer be distinguished from mine?");
    gets(new_qstn);
    /*FILE * file;
    file = fopen("DATAakinator.txt", "r+");
    fread(buffer, )
        fclose(file);*/
    puts("What is the answer for this question?");
    scanf("%s", new_answ);
}


int main(){
    FILE * file;
    TREE* tree;
    char buffer[256];
    file = fopen("DATAakinator.txt", "r");
    fgets(buffer, 256, file);
    tree = create(getSentence(buffer), getNum(buffer));
    while (fgets(buffer, 256, file) != NULL){
        FromFileToTree(tree, buffer);
    }
    fclose(file);
    while (tree != NULL){
        printf("%s", tree -> text);
        char answer[4];
        scanf("%s", &answer);
        if (strcmp(answer, "yes") == 0) {
            tree = tree->left;
            if (tree == NULL){
                puts("I know it!!!");
                return 0;
            }
        }
        else if (strcmp(answer, "no") == 0) {
            char* savetxt = tree -> text;
            int savenum = tree -> num;
            tree = tree->right;
            if (tree == NULL){
                CreateNewData(savetxt, savenum);
            }
        }
        else {
            puts("Syntax error");
            return 0;
        }

    }

    return 0;
}