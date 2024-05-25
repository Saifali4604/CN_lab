/*
fills a matrix row-wise based on the keyword length "MEGABUCK".
ensuring equal row length by padding with '.' if needed.
For each character in the keyword "MEGABUCK", the code calculates its sequence order 
The nested loop compares the current character with every other character in the keyword.
If the current character is greater than another character, it increments seq_No.
seq_No holds the sequence order of the current character based on the keyword.
It iterates over each character in the input data and places it in the output array according to the sequence order determined earlier.
The position in the output array is calculated as (seq_No * Rows) + j
*/

#include <stdio.h>
#include <string.h>

int main() {
    printf("Enter the data to be encrypted: ");
    char ch, data[30][30], output[100], seq[] = "MEGABUCK";
    int i, j, k, count, Rows = 0, seq_N0 = 0, len = strlen(seq);
    
    while ((ch = getchar()) != '\n') { // Read input data into the matrix
        data[Rows][Columns++] = ch;
        if(Columns == len){
            Rows++;
            Columns=0;
        }
    }
    if (Columns != 0) { // Pad the remaining cells with dots
        for (i = Columns; i < len; i++) {
            data[Rows][i] = '.';
        }
        Rows++;
    }
    for (i = 0; i < len; i++) {
        seq_No = 0;
        for (j = 0; j < len; j++) { 
            if (seq[i] > seq[j])
                seq_No++; // Count gives the sequence order based on the keyword
        }
        for (j = 0; j < Rows; j++) { // Create the output based on the sequence order
            if ((seq_No * Rows) + j >= Rows * len)
                break;
            output[(seq_No * Rows) + j] = data[j][i];
        }
    }
    output[Rows * len] = '\n';
    printf("\nEncrypted data: ");
    for (i = 0; i < Rows * len; i++) {
        printf("%c", output[i]);
    }
    printf("\n");
}
