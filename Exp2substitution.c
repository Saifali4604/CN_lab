#include <stdio.h>
#include <string.h>
#include <ctype.h>

char ch, output[100], seq[36] = "qwertyuiopasdfghjklzxcvbnm1234567890";
int i, j, len;

void getdata() {
    len = 0;
    while ((ch = getchar()) != '\n' && len < 99) {
        data[len++] = ch;
    }
    data[len] = '\0';
}

void encryption() {
    for (i = 0; i < len; i++) {
        if (isupper(data[i])) {
            output[i] = toupper(seq[data[i] - 'A']);  // Convert encoded character to uppercase
        } else if (islower(data[i])) {
            output[i] = seq[data[i] - 'a'];  // Use lowercase sequence for lowercase input
        } else if (isdigit(data[i])) {
            output[i] = seq[data[i] - '0' + 26];  // Offset for digits in the sequence
        } else {
            output[i] = data[i];  // Non-alphanumeric characters remain unchanged
        }
    }
    output[len] = '\0';  // Null-terminate the encrypted string
}

void decryption() {
    for (i = 0; i < len; i++) {
        int found = 0;  // Flag to indicate when the character is found
        for (j = 0; j < 36 && !found; j++) {
            if (seq[j] == tolower(data[i])) {  // Check both lowercase and uppercase in sequence
                if (isdigit(data[i]))
                    output[i] = '0' + j - 26;
                else if (islower(data[i]))
                    output[i] = 'a' + j;
                else 
                    output[i] = 'A' + j;
                found = 1;  // Set flag to indicate character is found
            }
        }
        if (!found) {
            output[i] = data[i];  // Non-alphanumeric characters remain unchanged
        }
    }
    output[len] = '\0';  // Null-terminate the decrypted string
}

int main() {
    printf("Enter the data to be encrypted: ");
    getdata();
    encryption();
    printf("\nEncrypted data is: %s", output);
    printf("\nEnter the data to be decrypted: ");
    getdata();
    decryption();
    printf("\nDecrypted data is: %s\n", output);
    return 0;
}
