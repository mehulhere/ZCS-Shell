#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>



int directoryhandler(char dirName[]){
    struct stat dirStat;
    if (stat(dirName, &dirStat) == 0) {
        if (S_ISDIR(dirStat.st_mode)) {
            printf("Directory \"%s\" already exists.\n", dirName);
            printf("Path Changed Successfully.");
            return 1;
        } else {
            printf("\"%s\" is not a directory.", dirName);
            return 0;
        }
    } else {
        printf("Directory \"%s\" does not exist.\n", dirName);
        return 0;
    }

    return 0;
}

int directoryhandlersilent(char dirName[]){
    struct stat dirStat;
    if (stat(dirName, &dirStat) == 0) {
        if (S_ISDIR(dirStat.st_mode)) {
            fflush(stdout);
            return 1;
        } else {
            // printf("%s is not a directory.\n", dirName);
            return 0;
        }
    } else {
        // printf("Directory %s does not exist.\n", dirName);
        return 0;
    }

    return 0;
}


int optionintplot(char arg[]){
    switch(arg[1]){
        case 'r':
            return 1;
            break;
        case 'v':
            return 2;
            break;
        default:
            return -1;
            break;

}
}

int checkfileexists(char filename[]){
        if (directoryhandlersilent(filename)==1){ //Checks if a file or directory exists with the same name. 0 -- No directory
        if (rmdir(filename) == 0) {
        // printf("Directory \"%s\" removed successfully.\n", filename);

        }
         else {
        // perror("Error removing directory");
        }
        return 1;
        }
        else{
            return 0;
        }
}


int main(int argc, char *argv[]){
    fflush(stdout);
    char *optioncommand=strdup(argv[1]); //Copies -d, -n or iff no option the file name.
    char *filename=strdup(argv[2]); //Copies filename
    fflush(stdout);
    int optionnum = optionintplot(optioncommand); //Returns a number
    switch(optionnum){
        case 1:; //-r
            if (checkfileexists(filename)==1){ // Checks if the file exist --> removes the file, does not exist --> Creates a new file
            mkdir(filename, 0777);
            printf("Directory Changed");
    }
    break;
        case 2: //-v
    if (directoryhandler(filename)==0){
            mkdir(filename, 0777);
            printf("Directory created successfully\n");
            if (chdir(filename)==0){
                printf("Path Changed Successfully");
            }
            else{
                printf("Change Directory Failed");
                fflush(stdout);
            }        
        fflush(stdout);
            }
            break;


        case -1:
        if (directoryhandlersilent(filename)==0){
            mkdir(filename, 0777);
            printf("Directory Changed");
        }
                    else{
                printf("Directory \"%s\" already exists.", filename);
                fflush(stdout);
            }

            break;
    }


}
