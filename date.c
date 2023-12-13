#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

//---GENERAL AND HELPER FUNCTIONS---
int istxtfile(const char *filename) {//Checks if a given file is a text file. 
    size_t len = strlen(filename);

    if (len >= 4) {
        if (strcmp(filename + len - 4, ".txt") == 0) {
            return 1;
        }
    }

    return 0;  
}
void printerror(){ //Prints and error message for invalid syntax
     printf("\033[1;31mZombie Child is ANGRY: \033[0mInvalid command entered");
}
int isnumber(const char *string){//Check if string is a  number
    while (*string){
        if (!isdigit(*string)) return 0;
        string++;
    }
    return 1;  
}
int checkdir(char dirname[100]){//Check for existence of file/directory
    FILE *myfile;
    if ((myfile = fopen(dirname, "r"))){
        fclose(myfile);
        return 1;
    }
    return 0;
}


void removequotes(char *input) {//Remove ""
    char *src = input;
    char *dst = input;

    while (*src) {
        if (*src != '"') {
            *dst = *src;
            dst++;
        }
        src++;
    }

    *dst = '\0';
}

int isvalidstringcheck(char mystring[100]){//Check if string is enclosed within ""
    int length = strlen(mystring);
    if (length < 2 || mystring[0] != '"' || mystring[length - 1] != '"'){
        return 0;
    }
    return 1;
}

struct tm* rdatehandler(char filename[100], int toprint) {//Prints last modified date in RFC 5322 format
    struct tm *timeparsedinfo = NULL;
    char lastmodifieddate[1000];

    if (checkdir(filename) == 1) {
        struct stat myfile;
        stat(filename, &myfile);
        time_t lastmodified = myfile.st_mtime;
        timeparsedinfo = localtime(&lastmodified);
        strftime(lastmodifieddate, sizeof(lastmodifieddate), "%a, %d %b %Y %H:%M:%S %z", timeparsedinfo);
        if (toprint == 1) printf("%s", lastmodifieddate);
        }

    else {
     printf("\033[1;31mZombie Child is ANGRY: \033[0mEFile could not be found");
    }

    return timeparsedinfo;
}

void ddatehandler1(char filename[100], char mystring[100]){//Handles date -d "today"/"tomorrow"/"yesterday"

    if (isvalidstringcheck(mystring) == 1){
        removequotes(mystring);
        struct tm* lastmodified = rdatehandler(filename, 0);
        char today[]="today";
        char tomorrow[]="tomorrow";
        char yesterday[]="yesterday";
        char lastmodifieddate[1000];

        if (strcmp ( today, mystring ) == 0){
            rdatehandler(filename , 1);
        } 

        else if (strcmp( tomorrow , mystring ) == 0 ){
            lastmodified->tm_mday += 1;
            mktime(lastmodified);
            strftime(lastmodifieddate, sizeof(lastmodifieddate), "%a %b %d %H:%M:%S %Z %Y", lastmodified);
            printf("%s", lastmodifieddate);
        } 

        else if (strcmp( yesterday , mystring ) == 0 ){
            lastmodified->tm_mday -= 1;
            mktime(lastmodified);
            strftime(lastmodifieddate, sizeof(lastmodifieddate), "%a %b %d %H:%M:%S %Z %Y", lastmodified);
            printf("%s", lastmodifieddate);
        } 

        else{
            printerror();
        }

    }
    
    else{
            printerror();
        }
}
void ddatehandler2(char filename[100], char mystring[100]){//Handles date -d "next second/minute/hour/week/day/month/year" type commands

    {
        struct tm* lastmodified = rdatehandler(filename, 0);
        char second[]="second";
        char minute[]="minute";
        char hour[]="hour";
        char day[]="day";
        char week[]="week";
        char month[]="month";
        char year[]="year";

        char lastmodifieddate[1000];
       
        if (strcmp ( second, mystring ) == 0) lastmodified->tm_sec += 1;
        else if (strcmp( minute , mystring ) == 0 ) lastmodified->tm_min += 1;
        else if (strcmp( hour , mystring ) == 0 ) lastmodified->tm_hour += 1;
        else if (strcmp( day , mystring ) == 0 ) lastmodified->tm_mday += 1;
        else if (strcmp( week , mystring ) == 0 ) lastmodified->tm_mday += 7;
        else if (strcmp( month , mystring ) == 0 ) lastmodified->tm_mon += 1;
        else if (strcmp( year , mystring ) == 0 ) lastmodified->tm_year += 1;

        mktime(lastmodified);
        strftime(lastmodifieddate, sizeof(lastmodifieddate), "%a %b %d %H:%M:%S %Z %Y", lastmodified);
        printf("%s", lastmodifieddate);
    }

}
void ddatehandler3(char filename[100], char values[100], char times[100]){//Handles date -d "+ x second/minute/hour/week/day/month/year" type commands

    {
        struct tm* lastmodified = rdatehandler(filename, 0);
        char second[]="seconds";
        char minute[]="minutes";
        char hour[]="hours";
        char day[]="days";
        char week[]="weeks";
        char month[]="months";
        char year[]="years";

        char lastmodifieddate[1000];
        int value = atoi(values);
        if (strcmp ( second, times ) == 0) lastmodified->tm_sec += value;
        else if (strcmp( minute , times ) == 0 ) lastmodified->tm_min += value;
        else if (strcmp( hour , times ) == 0 ) lastmodified->tm_hour += value;
        else if (strcmp( day , times ) == 0 ) lastmodified->tm_mday += value;
        else if (strcmp( week , times ) == 0 ) lastmodified->tm_mday += value;
        else if (strcmp( month , times ) == 0 ) lastmodified->tm_mon += value;
        else if (strcmp( year , times ) == 0 ) lastmodified->tm_year += value;
        else printerror();

        mktime(lastmodified);
        strftime(lastmodifieddate, sizeof(lastmodifieddate), "%a %b %d %H:%M:%S %Z %Y", lastmodified);
        printf("%s", lastmodifieddate);
    }

}
void ddatehandler4(char filename[100], char values[100], char times[100]){//Handles date -d "x second/minute/hour/week/day/month/year ago" type commands

    {
        struct tm* lastmodified = rdatehandler(filename, 0);
        char second[]="seconds";
        char minute[]="minutes";
        char hour[]="hours";
        char day[]="days";
        char week[]="weeks";
        char month[]="months";
        char year[]="years";

        char lastmodifieddate[1000];
        int value = atoi(values);
        if (strcmp ( second, times ) == 0) lastmodified->tm_sec -= value;
        else if (strcmp( minute , times ) == 0 ) lastmodified->tm_min -= value;
        else if (strcmp( hour , times ) == 0 ) lastmodified->tm_hour -= value;
        else if (strcmp( day , times ) == 0 ) lastmodified->tm_mday -= value;
        else if (strcmp( week , times ) == 0 ) lastmodified->tm_mday -= value;
        else if (strcmp( month , times ) == 0 ) lastmodified->tm_mon -= value;
        else if (strcmp( year , times ) == 0 ) lastmodified->tm_year -= value;

        mktime(lastmodified);
        strftime(lastmodifieddate, sizeof(lastmodifieddate), "%a %b %d %H:%M:%S %Z %Y", lastmodified);
        printf("%s", lastmodifieddate);
    }

}
void datenoparamhandler(char filename[100]) {//Handles date [filename] type commands
    if (checkdir(filename)==1){
    struct stat myfile;
    stat(filename, &myfile);
    time_t lastmodified = myfile.st_mtime;
    struct tm *timeparsedinfo;
    timeparsedinfo = localtime(&lastmodified);
    
    char date[1000];
    strftime(date, sizeof(date), "%a %b %d %H:%M:%S %Z %Y", timeparsedinfo);
    printf("%s", date);
    }

    else{
        printf("\033[1;31mZombie Child is ANGRY: \033[0mEFile could not be found");
    }
    
}

void datecheck(int rows, char inputtokens[rows][100]) {
    if (rows < 2) {
       printf("\033[1;31mZombie Child is ANGRY: \033[0mEInsufficient arguments passed");
        return;
    }

    char *command = inputtokens[1];
    char *filename = (rows > 2) ? inputtokens[2] : NULL;
    char *timestring = (rows > 3) ? inputtokens[3] : NULL;

    // Check if command is -d or -R
    int isDCommand = strcmp(command, "-d") == 0;
    int isRCommand = strcmp(command, "-R") == 0;

    // If command is -d or -R, filename is required
    if ((isDCommand || isRCommand) && !filename) {
       printf("\033[1;31mZombie Child is ANGRY: \033[0mNo file passed");
        return;
    }

    // Check if filename is a valid text file and exists
    if (filename && !istxtfile(filename)) {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mInvalid option: %s", filename);
        return;
    } else if (filename && !checkdir(filename)) {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mEFile could not be found");
        return;
    }

    // Handle different cases
    if (isDCommand) {
        if (rows == 4) {
            ddatehandler1(filename, timestring);
        } else if (rows == 5) {
            removequotes(inputtokens[3]);
            removequotes(inputtokens[4]);
            ddatehandler2(filename, inputtokens[4]);
        } else if (rows == 6) {
            removequotes(inputtokens[3]);
            removequotes(inputtokens[5]);
            if (isnumber(inputtokens[4])) {
                ddatehandler3(filename, inputtokens[4], inputtokens[5]);
            } else {
                 printf("\033[1;31mZombie Child is ANGRY: \033[0mUnexpected argument: %s", inputtokens[4]);
            }
        } else {
            printf("\033[1;31mZombie Child is ANGRY: \033[0mTime string not passed");
        }
    } else if (isRCommand) {
        if (rows == 3) {
            rdatehandler(filename, 1);
        } else {
              printf("\033[1;31mZombie Child is ANGRY: \033[Incorrect usage of -R");
        }
    } else if (istxtfile(command) && rows == 2) {
        datenoparamhandler(command);
    } else {
         printf("\033[1;31mZombie Child is ANGRY: \033[0mInvalid option: %s", command);
    }
}

int main(int argc, char *argv[]){


    char arr[5][100]; 
    for (int i = 0; i < 5; i++) { 
        if (i < argc && argv[i][0] != '\0') { 
            // check the length of argv 
            strncpy(arr[i], argv[i], 99); // copy at most 99 characters 
            arr[i][99] = '\0'; // add a null character at the end 
            } }


        datecheck(argc, arr);

    }

