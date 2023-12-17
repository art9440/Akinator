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


void CreateNewData(char* savetxt, int savenum, FILE * file){
    printf("%d", savenum);
    char correct_answ[256];
    char new_qstn[256];
    char new_answ[4];
    int new_num1, new_num2;
    new_num1 = savenum * 2;
    new_num2 = savenum * 2 + 1;

    puts("What is the correct answer?");
    char c = getchar();
    gets( correct_answ);
    puts("With what question can your answer be distinguished from mine?");
    gets(new_qstn);
    puts("What is the answer for this question?");
    scanf("%s", new_answ);
    file = fopen("DATAakinator.txt", "r+");
    char string[256];
    char **arr = NULL;
    int arr_len = 0;

    while (fgets(string, sizeof(string), file) != NULL){
        arr = realloc(arr, (arr_len + 1) * sizeof(char*));
        arr[arr_len] = strdup(string);
        if (savenum == getNum(arr[arr_len])) {
            char num = (char) savenum;
            printf("%c*", num);
        }
        arr_len++;
    }
    fclose(file);

    for (int i = 0;i<arr_len;i++){
        printf("%s", arr[i]);
    }
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
                CreateNewData(savetxt, savenum, file);
            }
        }
        else {
            puts("Syntax error");
            return 0;
        }

    }

    return 0;
}