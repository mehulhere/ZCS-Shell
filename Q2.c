#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>

char* extractBeforeQ2M(const char* input) {
    char *search = "Q2";
    char *found = strstr(input, search);

    if (found != NULL) {
        int length = found - input;

        if (length > 0) {
            char *result = (char *)malloc(length + 1);
            strncpy(result, input, length);
            result[length] = '\0';
            return result;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}

void tokenisation(char msg[], char arr[5][100]) {
    int index = 0;
    int indexword = 0;

    for (int i = 0; i < strlen(msg)-1; i++) {
        if (msg[i] != ' ') {
            arr[index][indexword] = msg[i];
            indexword++;
        } else if (indexword > 0) {
            arr[index][indexword] = '\0';
            index++;
            indexword = 0;
        }
    }
}


FILE* fileOpen(char args[]){ //Takes in the filename and returns the address of the file in FILE datatype after opening.
    return fopen(args, "r");
    fflush(stdout);
}


int checkhyphen(char arg[]){
    if (arg==NULL || strlen(arg)<2){
        return 0;
    }
            if (arg[0] == '-'){
                    return 1;
                }
            return -1;
}

int txtfileextensioncheck(char arg[]){
if (strlen(arg)<5){
    return -1;
}
if (arg[strlen(arg)-1] == 't' && arg[strlen(arg)-2] == 'x' && arg[strlen(arg)-3] == 't' && arg[strlen(arg)-4] == '.'){
    return 1;
}
return -1;
}

int argumenthandler(char args[]){
    if (args==NULL){
        printf("\033[1;31mZombie Child is ANGRY: \033[0mIncorrect Argument: %s", args);
            return -1; 
    }
        if (txtfileextensioncheck(args)==-1){
        if (strlen(args)<4 && checkhyphen(args)==1){
        printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Options are not allowed, remove the second option: %s", args);
        return -1;
        }
        else{
            printf("\033[1;31mZombie Child is ANGRY: \033[0mIncorrect Argument: %s", args);
            return -1;
        }
    }
}



int dirargumenthandler(char args[]){

    if (args==NULL){
        printf("\033[1;31mZombie Child is ANGRY: \033[0mIncorrect Argument: %s", args);
            return -1;
    }
        if (checkhyphen(args)==1){
        printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Options are not allowed, remove the second option: %s", args);
        return -1;
        }
        return 1;
    }

int worderrorhandler(char* args[]){
    if (checkhyphen(args[1])==1){ //If contains hyphen, check if option is valid
        if (strlen(args[1]) !=2 || (args[1][1]!='n' && args[1][1]!='d')){
            printf("\033[1;31mZombie Child is ANGRY: \033[0mIncorrect option: %s", args[1]);
            fflush(stdout);
            return -1;
        }
        else{
            if (argumenthandler(args[2])==-1){
                return -1;
            } //Option checked already, argument getting checked
            if (args[1][1]=='d'){ //Handle case 'd'
                if (argumenthandler(args[3])==-1){
                    return -1;
                } 
                if (args[4] != NULL){
                    printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments Error");
                    fflush(stdout);
                    return -1;
                    }
            }
            else{
                if (args[3] != NULL){
                    printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments Error");
                    return -1;
            }
        }
        }
    }


    else if(checkhyphen(args[1])==0){
        printf("\033[1;31mZombie Child is ANGRY: \033[0mInsufficient Arguments");
        return -1;
    }
    else{
        if (argumenthandler(args[1])==-1){
            return -1;
        } //No hyphen, check if it is correct argument.'
        if (args[2]!=NULL){
            printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments;");
        return -1;
    }
        }
}



int direrrorhandler(char* args[]){
    if (checkhyphen(args[1])==1){ //If contains hyphen, check if option is valid
        if (strlen(args[1]) !=2 || (args[1][1]!='r' && args[1][1]!='v')){
            printf("\033[1;31mZombie Child is ANGRY: \033[0mIncorrect option: %s", args[1]);
            fflush(stdout);
            return -1;
        }
        else{
            if (dirargumenthandler(args[2])==-1){
                return -1;
            } //Option checked already, argument getting checked
            else{
                if (args[3] != NULL){
                    printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments Error");
                    return -1;
            }
        }
        }
    }
    else if(checkhyphen(args[1])==0){
        printf("\033[1;31mZombie Child is ANGRY: \033[0mInsufficient Atguments");
        return -1;
    }
    else{
        if (dirargumenthandler(args[1])==-1){
            return -1;
        } //No hyphen, check if it is correct argument.'
        if (args[2]!=NULL){
            printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments;");
        return -1;
    }
        }
        return 0;
}

int dateerrorhandler(char* args[]){
    if (checkhyphen(args[1])==1){ //If contains hyphen, check if option is valid
        if (strlen(args[1]) !=2 || (args[1][1]!='d' && args[1][1]!='R')){
            printf("\033[1;31mZombie Child is ANGRY: \033[0mIncorrect option: %s", args[1]);
            fflush(stdout);
            return -1;
        }
        else{
            if (dirargumenthandler(args[2])==-1){ 
                return -1;
            } //Option checked already, argument getting checked
                        if (args[1][1]=='d'){ //Handle case 'd'
                if (argumenthandler(args[3])==-1){
                    return -1;
                } 
            }
            else{
                if (args[3] != NULL){
                    printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments Error");
                    return -1;
            }
            }
        }
    }
    else if(checkhyphen(args[1])==0){
        printf("\033[1;31mZombie Child is ANGRY: \033[0mInsufficient Arguments");
        return -1;
    }
    else{
        if (dirargumenthandler(args[1])==-1){
            return -1;
        } //No hyphen, check if it is correct argument.'
        if (args[2]!=NULL){
            printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments;");
        return -1;
    }
        }
        return 0;
}

int lserrorhandler(char* args[]) {
    // Count arguments
    int argc = 0;
    while (args[argc] != NULL) {
        argc++;
    }

    // Check for valid number of arguments
    if (argc > 3) {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mToo many arguments.\n");
        return -1;
    }

    if (argc == 1) {
        // Only "ls" is given, which is valid.
        return 0;
    }

    if (checkhyphen(args[1])) {
        // Check for valid options "-a" or "-l"
        if (strcmp(args[1], "-a") == 0 || strcmp(args[1], "-l") == 0) {
            if (argc == 3) {
                printf("\033[1;31mZombie Child is ANGRY: \033[0mUnexpected argument: %s", args[2]);
                return -1;
            }
            return 0; // Valid case
        } else {
            printf("\033[1;31mZombie Child is ANGRY: \033[0mInvalid option: %s", args[1]);
            return -1;
        }
    } else {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mExpected option, but got: %s", args[1]);
        return -1;
    }
}

int pwderrorhandler(char* args[]) {
    // Count arguments
    int argc = 0;
    while (args[argc] != NULL) {
        argc++;
    }

    // Check for valid number of arguments
    if (argc > 1) {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mToo many arguments.\n");
        return -1;
    }

    if (argc == 1) {
        // Only "ls" is given, which is valid.
        return 0;
    }

}


int wordoptionintplot(char arg[]){
    switch(arg[1]){
        case 'n':
            return 1;
            break;
        case 'd':
            return 2;
            break;
        default:
            return -1;
            break;

}
}


int wordcounter(char arg[]){//Takes in file and returns the number of words
    FILE *file=fileOpen(arg);  
        if (file == NULL){
        printf("\033[1;32mZombie Child is ANGRY: \033[0mError opening file: %s", arg);
        return -1;
    }
    int count = 0;
    fflush(stdout);
    int inWord = 0;
    char line[100];

while (fgets(line, sizeof(line), file) != NULL) {
for (int i = 0; line[i] != '\0'; i++) {
if (line[i]==' ') { 
    inWord = 0; 
}

else {
    if (!inWord) {
        inWord = 1;
        count ++; 

    }
}
}
}
    fclose(file);
    return count;
}


int nonewlinewordcounter(char arg[]){//Takes in file and returns the number of words without counting "\n"
    FILE *file=fileOpen(arg); 
    if (file == NULL){
        printf("\033[1;32mZombie Child is ANGRY: \033[0mError Opening file");
        return -1;
    }
    int count = 0;
    int inWord = 0;
    char line[1000];

    while (fgets(line, sizeof(line), file) != NULL) {
for (int i = 0; line[i] != '\0'; i++) {
if (line[i]==' ') { 
    inWord = 0; 
}

else {
    if (!inWord) {
        if(line[i] != 13 && line[i] != 10 ){
        inWord = 1;
        count ++; 
        fflush(stdout);
        }
    }
}
}
}
    fclose(file);
    return count;
}

int cdHandler(char* args[]){
    if (args[1] == NULL) {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mInsufficient Arguments\n");
        return -1;
    } else if (args[2] != NULL) {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments\n");
        return -1;
    } else {
        // Directory argument exists, no extra arguments
        if (chdir(args[1]) != 0) {
            printf("\033[1;31mZombie Child is ANGRY: \033[0mNo such file or directory");
            printf("\n");
            return -1;
        }
    }
    return 0;
}

int rmErrorHandler(char* args[]) {
    if (checkhyphen(args[1]) == 1) { //Checks if options are used
        if (strlen(args[1]) != 2 || (args[1][1] != 'f' && args[1][1] != 'r')) { //Verifies that options are used correctly. 
            printf("\033[1;31mZombie Child is ANGRY: \033[0mIncorrect option: %s\n", args[1]);
            fflush(stdout);
            return -1;
        } else { //Correct options checking arguments
            if (dirargumenthandler(args[2]) == -1) { //checks if its a valid directory
            printf("dad");
                return -1;
            }
                else { //Verification successful, check for multiple arguments
                if (args[3] != NULL) { //Prints if more than 3 arguments rm -r hello hello
                    printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments Error\n");
                    return -1;
                }
            }
        }
    }
     else {
        // No hyphen, check if it is correct argument
        if (dirargumenthandler(args[1]) == -1) {
            return -1;
        }
        if (args[2] != NULL) {
            printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments\n");
            return -1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    pid_t parentpid = (int) getpid();
    int dircreate = 0; 
    char* dirname = NULL;
    const char* bgRed = "\x1b[41m";
    system("python3 Video-to-Text/videoToTextColor.py Video-to-Text/1213.mp4");
    printf("\033[1;32mZombie Child Shell\n\033[0m");  
    
        printf("  _____\n");
    printf(" /     \\\n");
    printf("|  T T  |\n");
    printf("|   -   |\n");
    printf(" \\_____/\n");
    printf("    |\n");
    printf("  /   \\\n");
    printf(" |     |\n");
    printf("\n");
    printf("\033[1;31mCopyright (C) J4ZC. All rights reserved. \n \n\033[0m");
    printf("\033[1;31mIf you get stuck, then rtfm! \033[0m");

    while(1){
        // char dirname[50]={'\0'};
        char mypath[200]={'\0'};
        char userinput[100]={'\0'};
        char *args[100] = {NULL}; // Initialize an array of pointers with NULL
        int commandid=-1;
        fflush(stdout);
        if (dircreate == 1){
            fflush(stdout);
            if(chdir(dirname)==1){
                printf("\033[1;31mZombie Child is ANGRY: \033[0mDirectory change failed: %s",dirname);
                fflush(stdout);
            }
            dircreate = 0;
        }

        getcwd(mypath, sizeof(mypath));
        printf("\033[1;32m\nZCS \x1b[34m%s> \033[0m", mypath);
        fflush(stdout);
        if (fgets(userinput, sizeof(userinput), stdin)==NULL){
            printf("\033[1;31mZombie Child is ANGRY: \033[0mLoop Did not work");
            fflush(stdout);
            exit(1);
        }
    
        char tokenizedarr[5][100]={"\0"};
        fflush(stdout);
    tokenisation(userinput, tokenizedarr);


    
    for (int i = 0; i < 100; i++) {
        if (tokenizedarr[i][0] != '\0') {
            args[i] = tokenizedarr[i];
        }
    }

    if (strcmp("word", tokenizedarr[0]) == 0){
        commandid=0;
        fflush(stdout);
        if(worderrorhandler(args)==-1){
            continue;
        }
        int optionnum = wordoptionintplot(args[1]); //Returns a number

    switch(optionnum){
        case 1:;
        int countn=nonewlinewordcounter(args[2]);
        if (countn!=-1){
            printf("Word Count: %d", countn);
            fflush(stdout);
    }
        break;
        case 2:;
            int p = wordcounter(args[2]);
            int q = wordcounter(args[3]);
            if (p!=-1 && q!=-1){
            printf("Word Count Difference: %d", p-q);
            }
            break;

        case -1:;
            int countk=wordcounter(args[1]);
            if (countk!=-1){
                printf("Word Count: %d",countk);
            }
            break;
}
    fflush(stdout);
}
    else if(strcmp("dir", tokenizedarr[0]) == 0){
        commandid=1;
        if(direrrorhandler(args)==-1){
            fflush(stdout);
            continue;
        }
    if (args[2]==NULL){ //Changes file name to arg[2] if no option
    args[2]=strdup(args[1]);

    }
        dircreate=1;
        dirname=strdup(args[2]);
        fflush(stdout);

    }


    else if(strcmp("date", tokenizedarr[0]) == 0){
        commandid=2;
        // if(dateerrorhandler(args)==-1){
        //     fflush(stdout);
        //     continue;
        // }
    }

     else if(strcmp("ls", tokenizedarr[0]) == 0){
        commandid=3;
        if(lserrorhandler(args)==-1){
            fflush(stdout);
            continue;
        }
    }

     else if(strcmp("pwd", tokenizedarr[0]) == 0){
        commandid = 4;
        if(pwderrorhandler(args)==-1){
            fflush(stdout);
            continue;
        }
    }

        else if(strcmp("cd", tokenizedarr[0]) == 0){
        commandid=5;
        if(cdHandler(args)==-1){ //Checks error in dir commands
            fflush(stdout);
            continue;
        }
    }
        else if(strcmp("rm", tokenizedarr[0]) == 0){
        commandid=6;
        if(rmErrorHandler(args)==-1){ //Checks error in dir commands
            fflush(stdout);
            continue;
        }
    }

    else if(strcmp("exit", tokenizedarr[0]) == 0){
        break;
    }
    else{
        printf("\033[1;31mZombie Child is ANGRY: \033[0m%s : The term '%s' is not recognized as the name of a command supported by ZCS. Check the\nspelling of the name, or if a path was included, verify that the path is correct and try again.\nAt line:1 char:1\n+ %s\n+ ~~~\n    + CategoryInfo          : ObjectNotFound: (dad:String) [], CommandNotFoundException\n    + FullyQualifiedErrorId : CommandNotFoundException \n", tokenizedarr[0], tokenizedarr[0], tokenizedarr[0]);
    }
    int rc = fork();

    if (rc < 0) { //fork has failed
        printf("\033[1;31mZombie Child is ANGRY: \033[0m ZCS Internal Error - Fork Failed");
        exit(1);
    }

    else if (rc == 0) {//fork is successful, the rc of child=0, rc of parent=PID of child
    // printf("fork successful\n");
    char* mainpath=extractBeforeQ2M(mypath);
    if (commandid == 0) {
        exit(1); //Internal Command
    }
    else if (commandid == 1){
        char anotherString[] = "Q2/dir";
        strcat(mainpath,anotherString);
        if (execv(mainpath, args)==-1){ //Please change the address accodindly in the command
            printf("\033[1;31mZombie Child is ANGRY: \033[0mExecutable file not found at the specified address");
        }
    }
    else if (commandid == 2){
        char anotherString[]= "Q2/date";
           strcat(mainpath,anotherString);
        if (execv(mainpath, args)==-1){ //Please change the address accodindly in the command
            printf("\033[1;31mZombie Child is ANGRY: \033[0mExecutable file not found at the specified address");
        }
    }

    else if (commandid == 3){
        char anotherString[]= "Q2/ls";
           strcat(mainpath,anotherString);
        if (execv(mainpath, args)==-1){ //Please change the address accodindly in the command
            printf("\033[1;31mZombie Child is ANGRY: \033[0mExecutable file not found at the specified address: ");
        }
    } 

    else if (commandid == 4){
        char mypwdpath[200]={'\0'};
        getcwd(mypwdpath, sizeof(mypwdpath));
        printf("%s", mypwdpath);
        fflush(stdout);
        }

    else if(commandid == 5){ //cd
        exit(1);
    }
    else if(commandid == 6){ //rm
        char anotherString[]= "Q2/rm";
           strcat(mainpath,anotherString);
        if (execv(mainpath, args)==-1){ //Please change the address accodingly in the command
            printf("\033[1;31mZombie Child is ANGRY: \033[0mExecutable file not found at the specified address"); //This shouldn't happen
            printf("%s", mainpath);
        }
    }
    }
    else {

        wait(NULL);
        // printf("Parent process is running\n");

    }

    }
return 0;
}

