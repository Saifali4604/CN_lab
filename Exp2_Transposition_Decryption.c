#include <stdio.h>
#include <string.h>

int main() {
    printf("Enter the data to be decrypted: ");
    char ch, data[100], output[100], seq[] = "MEGABUCK";
    int i, j, seq_No, data_len = 0, Rows, len = strlen(seq);
    
    // Read input data and determine the number of rows
    while ((ch = getchar()) != '\n' && data_len < 100) {
        data[data_len++] = ch;
    }
    data[data_len] = '\0';
    
    Rows = (data_len + len - 1) / len; // Calculate the number of rows needed
    
    for (i = 0; i < len; i++) {
        seq_No = 0;
        for (j = 0; j < len; j++) {
            if (seq[i] > seq[j])
                seq_No++; // Calculate the sequence order based on the keyword
        }
        for (j = 0; j < Rows; j++) {
            if ((seq_No * Rows) + j < data_len) {
                output[i + (j * len)] = data[(seq_No * Rows) + j];
            }
        }
    }
    
    output[data_len] = '\0'; // Ensure the output string is null-terminated
    printf("\nDecrypted data: %s\n", output);
    
    return 0;
}
