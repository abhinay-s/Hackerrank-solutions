You are given a 2D matrix of dimension  and a positive integer . You have to rotate the matrix  times and print the resultant matrix. Rotation should be in anti-clockwise direction.

Rotation of a  matrix is represented by the following figure. Note that in one rotation, you have to shift elements by one step only.

matrix-rotation

It is guaranteed that the minimum of m and n will be even.

As an example rotate the Start matrix by 2:

Start         First           Second
 1 2 3 4        2  3  4  5      3  4  5  6
12 1 2 5  ->   1  2  3  6 ->   2  3  4  7
11 4 3 6      12  1  4  7       1  2  1  8
10 9 8 7      11 10  9  8     12 11 10  9
Function Description

Complete the matrixRotation function in the editor below. It should print the resultant 2D integer array and return nothing.

matrixRotation has the following parameter(s):

matrix: a 2D array of integers
rot: an integer that represents the rotation factor

Sample Input

Sample Input #01

4 4 2
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
Sample Output #01

3 4 8 12
2 11 10 16
1 7 6 15
5 9 13 14
Explanation #01

The matrix is rotated through two rotations.

 1  2  3  4      2  3  4  8      3  4  8 12
 5  6  7  8      1  7 11 12      2 11 10 16
 9 10 11 12  ->  5  6 10 16  ->  1  7  6 15
13 14 15 16      9 13 14 15      5  9 13 14
Sample Input #02

5 4 7
1 2 3 4
7 8 9 10
13 14 15 16
19 20 21 22
25 26 27 28
Sample Output #02

28 27 26 25
22 9 15 19
16 8 21 13
10 14 20 7
4 3 2 1
Explanation 02

The various states through 7 rotations:

1  2  3  4      2  3  4 10    3  4 10 16    4 10 16 22
7  8  9 10      1  9 15 16    2 15 21 22    3 21 20 28
13 14 15 16 ->  7  8 21 22 -> 1  9 20 28 -> 2 15 14 27 ->
19 20 21 22    13 14 20 28    7  8 14 27    1  9  8 26
25 26 27 28    19 25 26 27    13 19 25 26   7 13 19 25

10 16 22 28    16 22 28 27    22 28 27 26    28 27 26 25
 4 20 14 27    10 14  8 26    16  8  9 25    22  9 15 19
 3 21  8 26 ->  4 20  9 25 -> 10 14 15 19 -> 16  8 21 13
 2 15  9 25     3 21 15 19     4 20 21 13    10 14 20  7
 1  7 13 19     2  1  7 13     3  2  1  7     4  3  2  1
Sample Input #03

2 2 3
1 1
1 1
Sample Output #03

1 1
1 1
Explanation #03

All of the elements are the same, so any rotation will repeat the same matrix.

======================================================================================================================================================================================


#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

// Complete the matrixRotation function below.
void matrixRotation(int matrix_rows, int matrix_columns, int** matrix, int rot) {
    int result[matrix_rows][matrix_columns];

    matrix_rows--;
    matrix_columns--;
    for (int r = 0; r <= matrix_rows; r++) {
        for (int c = 0; c <= matrix_columns; c++) {
            int x = r < matrix_rows - r ? r : matrix_rows - r;
            int y = c < matrix_columns - c ? c : matrix_columns - c;
            int min = x < y ? x : y;
            int maxRow = matrix_rows - min;
            int maxCol = matrix_columns - min;
            int parameter = (maxRow + maxCol) * 2 - min * 4;

            int row = r;
            int col = c;
            for (int a = 0; a < rot%parameter; a++) {
                if (col == min && row < maxRow) {
                    row++;
                }
                else if (row == maxRow && col < maxCol) {
                    col++;
                }
                else if (row > min && col == maxCol) {
                    row--;
                }
                else if (row == min && col > min) {
                    col--;
                }
            }
            result[row][col] = matrix[r][c];
        }
    }


    for (int r = 0; r <= matrix_rows; r++) {
        for (int c = 0; c <= matrix_columns; c++) {
            printf("%d ", result[r][c]);
        }
        printf("\n");
    }


}

int main()
{
    char** mnr = split_string(rtrim(readline()));

    char* m_endptr;
    char* m_str = mnr[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mnr[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* r_endptr;
    char* r_str = mnr[2];
    int r = strtol(r_str, &r_endptr, 10);

    if (r_endptr == r_str || *r_endptr != '\0') { exit(EXIT_FAILURE); }

    int** matrix = malloc(m * sizeof(int*));

    for (int i = 0; i < m; i++) {
        *(matrix + i) = malloc(n * (sizeof(int)));

        char** matrix_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < n; j++) {
            char* matrix_item_endptr;
            char* matrix_item_str = *(matrix_item_temp + j);
            int matrix_item = strtol(matrix_item_str, &matrix_item_endptr, 10);

            if (matrix_item_endptr == matrix_item_str || *matrix_item_endptr != '\0') { exit(EXIT_FAILURE); }

            *(*(matrix + i) + j) = matrix_item;
        }
    }

    int matrix_rows = m;
    int matrix_columns = n;

    matrixRotation(matrix_rows, matrix_columns, matrix, r);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
