/*
Initializes the data array with the start frame "DLESTX".
Reads character data from the user until a newline character ('\n') is encountered.
Checks if the current character and the previous two characters form the escape sequence "DLE". If so, it inserts another "DLE" in the data stream.
Appends the end frame "DLEETX" to the data array.
Prints the transmitted bit stream after stuffing.
*/

#include<stdio.h> 
#include<string.h>

void destuffing(char input_data[], char output_data[]){
    int length_data = strlen(input_data), j = 0, i;
    for(i = 6; i < length_data - 6; i++){
        output_data[j++] = input_data[i];
        if(i >= 3 && input_data[i]=='E' && input_data[i-1]=='L' && input_data[i-2]=='D'){
            i=i+3;
        }
    }
    output_data[j] = '\0';
}

int main(){
    char data[256]= "DLESTX", recive_data[256],ch; // start/end frame
    int count,i = 6;// size of start/end frame 'DLESTX' or 'DLEETX'
    printf(" Enter the Char Data to be transmited : ");
    while ((ch= getchar()) != '\n') {// Read a character from user
        // Check for the sequence "DLE" and stuff another "DLE"
        data[i++] = ch;
        if (i >= 3 && data[i-1] == 'E' && data[i-2] == 'L' && data[i-3] == 'D') {
            // Insert "DLE" at the current position
            data[i++] = 'D';
            data[i++] = 'L';
            data[i++] = 'E';
        }
   }
   strcat(data, "DLEETX"); // appending the end of frame
    printf("\n Transmitted bit stream After stuffing at the transmitter :%s",data);

    destuffing(data,recive_data);
    printf("\n Recived bit stream After destuffing at the reciever :%s",recive_data);
   return 0;
}
