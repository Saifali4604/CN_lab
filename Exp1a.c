/*
The main function starts by initializing an array data with the start and end frame bits (01111110). This signifies the beginning and end of the frame.
It then reads input data from the user character by character until the newline character ('\n') is encountered.
During the reading process, if five consecutive ones are encountered (11111), a zero bit is stuffed (0) after them to avoid ambiguity.
Finally, the end frame (01111110) is appended to the transmitted data.
The stuffed bit stream is printed.
*/

#include<stdio.h> 
#include<string.h>

void destuffing(char input_data[], char output_data[]){
    int length_data = strlen(input_data), count = 0, j = 0, i;
    for(i = 8; i < length_data - 8; i++){
        output_data[j++] = input_data[i];
        if(input_data[i] == '1'){
            count++;
            if(count == 5 && input_data[i + 1] == '0'){
                i++;
                count = 0;
            }
        }
        else
            count = 0;
    }
    output_data[j] = '\0';
}

int main(){
    char data[30]= "01111110", recive_data[30], ch; // start/end frame
    int count,i = 8;// size of start/end frame
    printf(" Enter the Data to be transmited : ");
    while ((ch = getchar()) != '\n') { // Read a character from user
        data[i++] = ch;
        if (ch == '1') {// Check for five consecutive ones and stuff a bit 0
            count++;
            if (count == 5) {
                data[i++] = '0';
                count = 0;
            }
        } else {
            count = 0;
        }
    }
   strcat(data, "01111110"); // appending the end of frame
   printf("\n Transmitted bit stream After stuffing at the transmitter :%s",data);

   destuffing(data,recive_data);
   printf("\n Recived bit stream After destuffing at the reciever :%s",recive_data);
   return 0;
}
