/*
*************************************CRC*******************************************
Reads the data to be transmitted.
Appends zeros to the data to accommodate the CRC.
Calculates the CRC and appends it to the data for transmission.
Simulates the transmission by printing the transmitted data.
Reads the received data.
Calculates the CRC for the received data.
Prints the actual data received after removing the CRC.
*/

#include <stdio.h>
#define degree 16

void xor_division(int data[], int length, int Remainder[]) {
    int ccit[] = {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    int ccit_size = degree + 1, i, j; 
    for (i = 0; i < length; i++)
        Remainder[i] = data[i]; // Copy into result Array
    for (i = 0; i <= length - ccit_size; i++)
        if (Remainder[i] == 1 ) // checking if the current bit is 1 
            for (j = 0; j < ccit_size; j++) 
                Remainder[i + j] = Remainder[i + j] ^ ccit[j]; // bit wise XOR operation
    printf("\nRemainder: ");
    for (i = 0; i < length; i++)
        printf("%d", Remainder[i]); //prints the remainder
    
}

int main() {
    int data[100],received_data[100], length, i;
    char ch;
    printf(" Enter the Data to be transmited : ");
    while ((ch = getchar())!= '\n')
        data[length++] = ch - '0';
    printf("Data is: ");
    for (i = 0; i < length + degree; i++) {
        if(i>=length)
            data[i] = 0;
        printf("%d", data[i]);
    }
    length+=degree;
    int Remainder[length];
    xor_division(data, length, Remainder); // CRC calculation
    printf("\nTransmitting Data is : ");
    for (i = 0; i < length; i++) {
        if(i >= length - degree)
            data[i] = Remainder[i]; //append CRC to the transmitting data
        printf("%d", data[i]);
    }
    printf("\nEnter the recived data : ");
    length=0;
    while ((ch = getchar())!= '\n')
        received_data[length++] = ch - '0';
    int Remainder_of_received[length];
    xor_division(received_data, length, Remainder_of_received);
    // Check if the remainder is zero (i.e., no error)
    int error = 0;
    for (i = 0; i < length; i++) {
        if (Remainder_of_received[i] != 0) {
            error = 1;
            break;
        }
    }
    if (error == 0) {
        printf("\nActual Data is: ");
        for (i = 0; i < length - degree; i++) {
            printf("%d", received_data[i]);
        } 
    } else {
        printf("\nReceived Data is Not correct");
    }
    return 0;
}
