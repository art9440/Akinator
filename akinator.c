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
    char *result = (char*) malloc(sizeof(char));
    int res_len = 0;

    while (num != 0) {
        result[res_len] = '0' + num % 10;
        num /= 10;
        res_len++;
        result = (char*)realloc(result, sizeof(char) * (res_len + 1));
    }
    result[res_len] = '\0';

    for (int i = 0; i < res_len / 2; i++) {
        char tmp = result[i];
        result[i] = result[res_len - 1 - i];
        result[res_len - 1 - i] = tmp;
    }

    return result;
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
    char *filename = "DATAakinator.txt";
    char *tmp_filename = "temp.txt";
    file = fopen("DATAakinator.txt", "r+");
    FILE * tmp_file = fopen(tmp_filename, "w+");
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        if (getNum(buffer) == savenum){
            char* str_num;
            str_num = FromIntToStr(savenum);
            strcat(str_num, "-");
            strcat(str_num, new_qstn);
            strcat(str_num, "\n");
            printf("%s", str_num);
            fputs(str_num, tmp_file);

        }
        else
            fputs(buffer, tmp_file);
    }

    if (strcmp(new_answ, "yes") == 0) {
        char *cur_left = FromIntToStr(savenum * 2);
        char *cur_right = FromIntToStr(savenum * 2 + 1);

        strcat(cur_left, "-");
        strcat(cur_left, correct_answ);
        strcat(cur_left, "\n");
        fputs(cur_left, tmp_file);

        strcat(cur_right, "-");
        strcat(cur_right, savetxt);
        strcat(cur_right, "\n");
        fputs(cur_right, tmp_file);
    }
    else if (strcmp(new_answ, "no") == 0){
        char *cur_left = FromIntToStr(savenum * 2 + 1);
        char *cur_right = FromIntToStr(savenum * 2);

        strcat(cur_left, "-");
        strcat(cur_left, correct_answ);
        strcat(cur_left, "\n");
        fputs(cur_left, tmp_file);

        strcat(cur_right, "-");
        strcat(cur_right, savetxt);
        strcat(cur_right, "\n");
        fputs(cur_right, tmp_file);
    }
    fclose(file);
    fclose(tmp_file);
    remove(filename);
    rename(tmp_filename, filename);

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