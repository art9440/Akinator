#include <stdio.h>
#include <stdlib.h>


int main(){
    FILE * file;
    file = fopen("DATAakinator.txt", "r+");

    fclose(file);
}
