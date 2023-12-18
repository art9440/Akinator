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
        sentence = (char*)realloc(sentence, i * sizeof (char));
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

char * FromIntToStr(int num){
    char *res = (char*) malloc(sizeof(char) * 12);
}


void CreateNewData(char* savetxt, int savenum, FILE * file, TREE* tree){
    char correct_answ[256], buffer[256];
    char new_qstn[256];
    char new_answ[4];

    puts("What is the correct answer?");
    char c = getchar();
    gets( correct_answ);
    puts("With what question can your answer be distinguished from mine?");
    gets(new_qstn);
    puts("What is the answer for this question?");
    scanf("%s", new_answ);
    char *tmp_filename = "temp.txt";
    file = fopen("DATAakinator.txt", "r+");
    FILE * tmp_file = fopen(tmp_filename, "w");
    long position = 0;
    while(fgets(buffer, 256, file) != NULL) {
        if (getNum(buffer) == savenum){
            position = ftell(file) - strlen(getSentence(buffer)) - 1;
        }
    }
    fseek(file, position, SEEK_SET);
    fprintf(file, "%s", new_qstn);
    fclose(file);

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
                CreateNewData(savetxt, savenum, file, tree);
            }
        }
        else {
            puts("Syntax error");
            return 0;
        }

    }

    return 0;
}