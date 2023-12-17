//22118080062 - Ali Burak Pekışık

//Initiating necessary libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declaration of function getIndex.
getIndex(int row, int col, int n);

int main() {
    char allStrings[1000]; //Declaring main char array for containing all content of input.txt.
    int row_count = 0, index = 0 , dimension;
    int i = 0, j = 0, k = 0; //Declaring for loop indexs.
    char * token; //Declaring pointer token for dividing char arrays.
    char matrixA_str[100], matrixB_str[100]; //Declaring char arrays of matrixA and matrixB.
    int matrixA_int[100], matrixB_int[100]; //Declaring integer arrays of matrixA and matrixB.

    //Research made from Geeks For Geeks for file reading.
    //https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/
    FILE * file; //Declaring of file pointer.
    file = fopen("input.txt", "r"); //Opening input.txt using fopen for accessing content of It.

    //Validation of input.txt file.
    if (file == NULL) {
        printf("File could not found.\n");
        return 1;
    }

    //Fgets used for getting each row of input.txt with while loop.
    while(fgets(allStrings, sizeof(allStrings), file)) {
        //Dividing each row by using a variable called row_count.
        if (row_count == 0) {
            dimension = atoi(allStrings); //atoi is used for converting content of allString char array to integer variable type.
        }
        else if (row_count == 1) {
            strcpy(matrixA_str, allStrings); //Because 2nd row has a long content we can not convert directly to integer so first we copy them to another char array.
        }
        else if (row_count == 2) {
            strcpy(matrixB_str, allStrings);
        }
        row_count++;
    }

    //Closing access of input.txt file because we do not need It anymore.
    fclose(file);

    //Converting matrixA char array into matrixA integer array.
    //Research made from Tutorials Point.
    //https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
    token = strtok(matrixA_str, " "); //strtok is used for dividing char arrays using special characters.
    while( token != NULL ) { //When char array can be divided with blanks we convert them into integer values and add into matrix.
        matrixA_int[i] = atoi(token); //Appending integer value of token into matrixA.
        i++;
        token = strtok(NULL, " "); //Helps function to continue dividing.
    }

    i = 0;

    //Converting matrixB char array into matrixB integer array.
    token = strtok(matrixB_str, " "); //strtok is used for dividing char arrays using special characters.
    while( token != NULL ) { //When char array can be divided with blanks we convert them into integer values and add into matrix.
        matrixB_int[i] = atoi(token); //Appending integer value of token into matrixB.
        i++;
        token = strtok(NULL, " "); //Helps function to continue dividing.
    }

    //Inspired from a Stack Overflow help request.
    //https://stackoverflow.com/questions/47023651/multiplying-matrices-in-one-dimensional-arrays
    int result[dimension * (dimension + 1) / 2]; //Declared a variable for containing result of matrix' multiplication with help of formula for non-zero value count.
    for (i = 0; i < dimension; i++) { //i is used for current row number.
        for (j = i; j < dimension; j++) { //j is used for current column number.
            index = getIndex(i, j, dimension);
            result[index] = 0; //First we initiate required index as 0 then make calculations for It. Otherwise there will be miscalculation.
            for (k = i; k <= j; k++) {
                //Because we use upper triangular matrixs we need to consider we can not access 0 values of these matrixs.
                result[index] += matrixA_int[getIndex(i, k, dimension)] * matrixB_int[getIndex(k, j, dimension)];
            }
        }
    }

    //Printing 1D result matrix using for loop.
    for (j = 0; j < dimension * (dimension + 1) / 2; j++) { //dimension * (dimension + 1) / 2 used for calculating count of non-zero values.
        printf("%d ", result[j]);
    }

    printf("\n\n");

    //Printing 1D result array with for loops for trying to look like a traditional matrix.
    for (i = 0; i < dimension; i++) { //
        for (j = 0; j < dimension; j++) {
            if (i <= j) { //If the selected index is above or equal to diagonal indexs we use result array values.
                index = getIndex(i, j, dimension);
                printf("%d\t", result[index]);
            } else { //If the values are under the diagonal indexs we simply print 0.
                printf("0\t");
            }
        }
        printf("\n");
    }

    return 0;
}

//Because we use upper triangular matrixes we can not directly use traditional matrix multiplication formula so we need to create our own.
int getIndex(int current_row, int current_col, int dimension) {
    return current_row * dimension - (current_row * (current_row + 1) / 2) + current_col; //This is the formula that teacher wanted us to find index number of upper triangle matrix's values.
}
