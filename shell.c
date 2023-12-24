#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>

// Helper functions

void printScene(const char *bullet)
{
    printf("\033[1;32mZombie Child Shell\n\033[0m");
    printf("  _____    \n");
    printf(" /     \\ %s\n", bullet);
    printf("|  T T  |\n");
    printf("|   -   |\n");
    printf(" \\_____/\n");
    printf("    |\n");
    printf("  /   \\\n");
    printf(" |     |\n");

    printf("\033[1;31mCopyright (C) J4ZC. All rights reserved. \n \n\033[0m");
    printf("\033[1;31mIf you get stuck, then rtfm!\n\033[0m");
}

char *extractBeforeQ2M(const char *input)
{ // Extracts the path before main folder name
    char *search = "ZCS-Shell-main";
    char *found = strstr(input, search);

    if (found != NULL)
    {
        int length = found - input;

        if (length > 0)
        {
            char *result = (char *)malloc(length + 1);
            strncpy(result, input, length);
            result[length] = '\0';
            return result;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

void tokenisation(char msg[], char arr[5][100])
{ // tokenise user input
    int index = 0;
    int indexword = 0;

    for (int i = 0; i < strlen(msg) - 1; i++)
    {
        if (msg[i] != ' ')
        {
            arr[index][indexword] = msg[i];
            indexword++;
        }
        else if (indexword > 0)
        {
            arr[index][indexword] = '\0';
            index++;
            indexword = 0;
        }
    }
}

FILE *fileOpen(char args[])
{ // Takes in the filename and returns the address of the file in FILE datatype after opening.
    return fopen(args, "r");
    fflush(stdout);
}

int checkhyphen(char arg[])
{ // checks for hyphen in argument
    if (arg == NULL || strlen(arg) < 2)
    {
        return 0;
    }
    if (arg[0] == '-')
    {
        return 1;
    }
    return -1;
}

int txtfileextensioncheck(char arg[])
{ // checks for .txt extension
    if (strlen(arg) < 5)
    {
        return -1;
    }
    if (arg[strlen(arg) - 1] == 't' && arg[strlen(arg) - 2] == 'x' && arg[strlen(arg) - 3] == 't' && arg[strlen(arg) - 4] == '.')
    {
        return 1;
    }
    return -1;
}

int argumenthandler(char args[])
{ // checks for valid arguments
    if (args == NULL)
    {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mIncorrect Argument: %s", args);
        return -1;
    }
    if (txtfileextensioncheck(args) == -1)
    {
        if (strlen(args) < 4 && checkhyphen(args) == 1)
        {
            printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Options are not allowed, remove the second option: %s", args);
            return -1;
        }
        else
        {
            printf("\033[1;31mZombie Child is ANGRY: \033[0mIncorrect Argument: %s", args);
            return -1;
        }
    }
}

int wordoptionintplot(char arg[])
{ // checks which word command to call
    switch (arg[1])
    {
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

// Error handling functions for internal commands

int direrrorhandler(char *args[])
{ // handles errors for dir
    if (checkhyphen(args[1]) == 1)
    { // If contains hyphen, check if option is valid
        if (strlen(args[1]) != 2 || (args[1][1] != 'r' && args[1][1] != 'v'))
        {
            printf("\033[1;31mZombie Child is ANGRY: \033[0mIncorrect option: %s", args[1]);
            fflush(stdout);
            return -1;
        }
        else
        {
            if (dirargumenthandler(args[2]) == -1)
            {
                return -1;
            } // Option checked already, argument getting checked
            else
            {
                if (args[3] != NULL)
                {
                    printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments Error");
                    return -1;
                }
            }
        }
    }
    else if (checkhyphen(args[1]) == 0)
    {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mInsufficient Atguments");
        return -1;
    }
    else
    {
        if (dirargumenthandler(args[1]) == -1)
        {
            return -1;
        } // No hyphen, check if it is correct argument.'
        if (args[2] != NULL)
        {
            printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments;");
            return -1;
        }
    }
    return 0;
}

int dateerrorhandler(char *args[])
{ // handles error for date
    if (checkhyphen(args[1]) == 1)
    { // If contains hyphen, check if option is valid
        if (strlen(args[1]) != 2 || (args[1][1] != 'd' && args[1][1] != 'R'))
        {
            printf("\033[1;31mZombie Child is ANGRY: \033[0mIncorrect option: %s", args[1]);
            fflush(stdout);
            return -1;
        }
        else
        {
            if (dirargumenthandler(args[2]) == -1)
            {
                return -1;
            } // Option checked already, argument getting checked
            if (args[1][1] == 'd')
            { // Handle case 'd'
                if (argumenthandler(args[3]) == -1)
                {
                    return -1;
                }
            }
            else
            {
                if (args[3] != NULL)
                {
                    printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments Error");
                    return -1;
                }
            }
        }
    }
    else if (checkhyphen(args[1]) == 0)
    {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mInsufficient Arguments");
        return -1;
    }
    else
    {
        if (dirargumenthandler(args[1]) == -1)
        {
            return -1;
        } // No hyphen, check if it is correct argument.'
        if (args[2] != NULL)
        {
            printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments;");
            return -1;
        }
    }
    return 0;
}

int lserrorhandler(char *args[])
{ // handles errors for ls
    // Count arguments
    int argc = 0;
    while (args[argc] != NULL)
    {
        argc++;
    }

    // Check for valid number of arguments
    if (argc > 3)
    {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mToo many arguments.\n");
        return -1;
    }

    if (argc == 1)
    {
        // Only "ls" is given, which is valid.
        return 0;
    }

    if (checkhyphen(args[1]))
    {
        // Check for valid options "-a" or "-l"
        if (strcmp(args[1], "-a") == 0 || strcmp(args[1], "-l") == 0)
        {
            if (argc == 3)
            {
                printf("\033[1;31mZombie Child is ANGRY: \033[0mUnexpected argument: %s", args[2]);
                return -1;
            }
            return 0; // Valid case
        }
        else
        {
            printf("\033[1;31mZombie Child is ANGRY: \033[0mInvalid option: %s", args[1]);
            return -1;
        }
    }
    else
    {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mExpected option, but got: %s", args[1]);
        return -1;
    }
}

int pwderrorhandler(char *args[])
{ // handles errors for pwd
    // Count arguments
    int argc = 0;
    while (args[argc] != NULL)
    {
        argc++;
    }

    // Check for valid number of arguments
    if (argc > 1)
    {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mToo many arguments.\n");
        return -1;
    }

    if (argc == 1)
    {
        // Only "ls" is given, which is valid.
        return 0;
    }
}

int worderrorhandler(char *args[])
{ // handles wrror for word
    if (checkhyphen(args[1]) == 1)
    { // If contains hyphen, check if option is valid
        if (strlen(args[1]) != 2 || (args[1][1] != 'n' && args[1][1] != 'd'))
        {
            printf("\033[1;31mZombie Child is ANGRY: \033[0mIncorrect option: %s", args[1]);
            fflush(stdout);
            return -1;
        }
        else
        {
            if (argumenthandler(args[2]) == -1)
            {
                return -1;
            } // Option checked already, argument getting checked
            if (args[1][1] == 'd')
            { // Handle case 'd'
                if (argumenthandler(args[3]) == -1)
                {
                    return -1;
                }
                if (args[4] != NULL)
                {
                    printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments Error");
                    fflush(stdout);
                    return -1;
                }
            }
            else
            {
                if (args[3] != NULL)
                {
                    printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments Error");
                    return -1;
                }
            }
        }
    }

    else if (checkhyphen(args[1]) == 0)
    {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mInsufficient Arguments");
        return -1;
    }
    else
    {
        if (argumenthandler(args[1]) == -1)
        {
            return -1;
        } // No hyphen, check if it is correct argument.'
        if (args[2] != NULL)
        {
            printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments;");
            return -1;
        }
    }
}

int cdHandler(char *args[])
{ // handles error for cd
    if (args[1] == NULL)
    {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mInsufficient Arguments\n");
        return -1;
    }
    else if (args[2] != NULL)
    {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments\n");
        return -1;
    }
    else
    {
        // Directory argument exists, no extra arguments
        if (chdir(args[1]) != 0)
        {
            printf("\033[1;31mZombie Child is ANGRY: \033[0mNo such file or directory");
            return -1;
        }
    }
    return 0;
}

int rmErrorHandler(char *args[])
{ // handles error for rm
    if (checkhyphen(args[1]) == 1)
    { // Checks if options are used
        if (strlen(args[1]) != 2 || (args[1][1] != 'f' && args[1][1] != 'r'))
        { // Verifies that options are used correctly.
            printf("\033[1;31mZombie Child is ANGRY: \033[0mIncorrect option: %s\n", args[1]);
            fflush(stdout);
            return -1;
        }
        else
        { // Correct options checking arguments
            if (dirargumenthandler(args[2]) == -1)
            { // checks if its a valid directory
                printf("dad");
                return -1;
            }
            else
            { // Verification successful, check for multiple arguments
                if (args[3] != NULL)
                { // Prints if more than 3 arguments rm -r hello hello
                    printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments Error");
                    return -1;
                }
            }
        }
    }
    else
    {
        // No hyphen, check if it is correct argument
        if (dirargumenthandler(args[1]) == -1)
        {
            return -1;
        }
        if (args[2] != NULL)
        {
            printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Arguments");
            return -1;
        }
    }
    return 0;
}

int helperrorhandler(char *args[])
{ // handle error for help
    // Count arguments
    int argc = 0;
    while (args[argc] != NULL)
    {
        argc++;
    }

    // Check for valid number of arguments
    if (argc > 2)
    {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mToo many arguments for 'help' command.");
        return -1;
    }

    // The 'help' command is valid with no arguments or one argument.
    return 0;
}

// Main functions for internal commands

int dirargumenthandler(char args[])
{ // handles dir command

    if (args == NULL)
    {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mIncorrect Argument: %s", args);
        return -1;
    }
    if (checkhyphen(args) == 1)
    {
        printf("\033[1;31mZombie Child is ANGRY: \033[0mMultiple Options are not allowed, remove the second option: %s", args);
        return -1;
    }
    return 1;
}

int wordcounter(char arg[])
{ // Takes in file and returns the number of words
    FILE *file = fileOpen(arg);
    if (file == NULL)
    {
        printf("\033[1;32mZombie Child is ANGRY: \033[0mError opening file: %s", arg);
        return -1;
    }
    int count = 0;
    fflush(stdout);
    int inWord = 0;
    char line[100];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        for (int i = 0; line[i] != '\0'; i++)
        {
            if (line[i] == ' ')
            {
                inWord = 0;
            }

            else
            {
                if (!inWord)
                {
                    inWord = 1;
                    count++;
                }
            }
        }
    }
    fclose(file);
    return count;
}

int nonewlinewordcounter(char arg[])
{ // Takes in file and returns the number of words without counting "\n"
    FILE *file = fileOpen(arg);
    if (file == NULL)
    {
        printf("\033[1;32mZombie Child is ANGRY: \033[0mError Opening file");
        return -1;
    }
    int count = 0;
    int inWord = 0;
    char line[1000];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        for (int i = 0; line[i] != '\0'; i++)
        {
            if (line[i] == ' ')
            {
                inWord = 0;
            }

            else
            {
                if (!inWord)
                {
                    if (line[i] != 13 && line[i] != 10)
                    {
                        inWord = 1;
                        count++;
                        fflush(stdout);
                    }
                }
            }
        }
    }
    fclose(file);
    return count;
}

void displayCommandManual(const char *command)
{ // displays user manual
    if (strcmp(command, "word") == 0)
    {
        printf("word - Count the number of words in a file\n");
        printf("word -d - Gives difference between the word sizes of two text files\n");
        printf("word -n - Count the number of words in a file ignoring newline character");
    }
    else if (strcmp(command, "dir") == 0)
    {
        printf("dir - List the contents of a directory\n");
        printf("dir -r - Removes if the directory already exists and create a new directory instead of throwing an error\n");
        printf("dir -v : Prints a message for each step in the running of dir");
    }
    else if (strcmp(command, "date") == 0)
    {
        printf("date - Display or set the system date and time\n");
        printf("date -d - Display time described by STRING\n");
        printf("date -R - Output date and time in RFC 5322 format");
    }
    else if (strcmp(command, "ls") == 0)
    {
        printf("ls -List directory contents\n");
        printf("ls -a - List all directory contents, including hidden files\n");
        printf("ls -l - List all directory contents, with file information");
    }
    else if (strcmp(command, "pwd") == 0)
    {
        printf("pwd - Print the name of the current working directory");
    }
    else if (strcmp(command, "cd") == 0)
    {
        printf("cd - Change the current directory");
    }
    else if (strcmp(command, "rm") == 0)
    {
        printf("rm - Remove files or directories");
    }
    else if (strcmp(command, "help") == 0)
    {
        printf("help - Display information about builtin commands");
    }
    else if (strcmp(command, "exit") == 0)
    {
        printf("exit - Exit the shell");
    }
    else
    {
        printf("No manual entry for %s", command);
    }
}

void help(char *args[])
{ // displays help menu
    int argc = 0;
    while (args[argc] != NULL)
    {
        argc++;
    }

    if (argc == 1)
    {
        // Display list of all commands if no specific command is provided
        printf("These shell commands are defined internally and externally. Type `help` to see this list.\n");
        printf("Type `help name` to find out more about the function `name`.\n");
        printf("Use `info bash` to find out more about the shell in general.\n");
        printf("word [-dD]\n");
        printf("dir []\n");
        printf("date [-Rd] [name...]\n");
        printf("ls [-la]\n");
        printf("pwd\n");
        printf("cd\n");
        printf("rm\n");
        printf("help [name...]\n");
        printf("exit\n");
        printf("Type 'help [command]' to get more information on a specific command.");
    }
    else if (argc == 2)
    {
        // Display manual for the specific command
        displayCommandManual(args[1]);
    }
    else
    {
        printf("Usage: help [command]\n");
    }
}

int main(int argc, char *argv[])
{

    // Setting up the terminal and loading
    pid_t parentpid = (int)getpid();
    int dircreate = 0;
    char *dirname = NULL;
    const char *bgRed = "\x1b[41m";

    const char *frames[] = {"     ", "    *", "   * ", "  *  ", " *   ", "*    "};
    int numFrames = sizeof(frames) / sizeof(frames[0]);

    for (int i = 0; i < numFrames; ++i)
    {
        printScene(frames[i]);
        usleep(400000); // 200 milliseconds delay
        system("clear");
    }

    // Final frame with bullet "hitting" the target
    printf("\033[1;32mZombie Child Shell\n\033[0m");
    printf("  _____ \n");
    printf(" /     \\ \n");
    printf("|  X X  |\n"); // Eyes changed to 'X' to indicate a hit
    printf("|   O   |\n");
    printf(" \\_____/\n");
    printf("    |\n");
    printf("  /   \\\n");
    printf(" |     |\n");

    printf("\033[1;31mCopyright (C) J4ZC. All rights reserved. \n \n\033[0m");
    printf("\033[1;31mIf you get stuck, then rtfm! \033[0m");

    while (1)
    {
        // char dirname[50]={'\0'};
        char mypath[200] = {'\0'};
        char userinput[100] = {'\0'};
        char *args[100] = {NULL}; // Initialize an array of pointers with NULL
        int commandid = -1;
        fflush(stdout);
        if (dircreate == 1)
        {
            fflush(stdout);
            if (chdir(dirname) == 1)
            {
                printf("\033[1;31mZombie Child is ANGRY: \033[0mDirectory change failed: %s", dirname);
                fflush(stdout);
            }
            dircreate = 0;
        }

        getcwd(mypath, sizeof(mypath));
        printf("\033[1;32m\nZCS \x1b[34m%s> \033[0m", mypath);
        fflush(stdout);
        if (fgets(userinput, sizeof(userinput), stdin) == NULL)
        {
            printf("\033[1;31mZombie Child is ANGRY: \033[0mLoop Did not work");
            fflush(stdout);
            exit(1);
        }

        char tokenizedarr[100][100] = {"\0"};
        fflush(stdout);
        tokenisation(userinput, tokenizedarr);

        for (int i = 0; i < 100; i++)
        {
            if (tokenizedarr[i][0] != '\0')
            {
                args[i] = tokenizedarr[i];
            }
        }

        // compares user input and calls function
        if (strcmp("word", tokenizedarr[0]) == 0)
        {
            commandid = 0;
            fflush(stdout);
            if (worderrorhandler(args) == -1)
            {
                continue;
            }
            int optionnum = wordoptionintplot(args[1]); // Returns a number

            switch (optionnum)
            {
            case 1:;
                int countn = nonewlinewordcounter(args[2]);
                if (countn != -1)
                {
                    printf("Word Count: %d", countn);
                    fflush(stdout);
                }
                break;
            case 2:;
                int p = wordcounter(args[2]);
                int q = wordcounter(args[3]);
                if (p != -1 && q != -1)
                {
                    printf("Word Count Difference: %d", p - q);
                }
                break;

            case -1:;
                int countk = wordcounter(args[1]);
                if (countk != -1)
                {
                    printf("Word Count: %d", countk);
                }
                break;
            }
            fflush(stdout);
        }
        else if (strcmp("dir", tokenizedarr[0]) == 0)
        {
            commandid = 1;
            if (direrrorhandler(args) == -1)
            {
                fflush(stdout);
                continue;
            }
            if (args[2] == NULL)
            { // Changes file name to arg[2] if no option
                args[2] = strdup(args[1]);
            }
            dircreate = 1;
            dirname = strdup(args[2]);
            fflush(stdout);
        }

        else if (strcmp("date", tokenizedarr[0]) == 0)
        {
            commandid = 2;
        }

        else if (strcmp("ls", tokenizedarr[0]) == 0)
        {
            commandid = 3;
            if (lserrorhandler(args) == -1)
            {
                fflush(stdout);
                continue;
            }
        }

        else if (strcmp("pwd", tokenizedarr[0]) == 0)
        {
            commandid = 4;
            if (pwderrorhandler(args) == -1)
            {
                fflush(stdout);
                continue;
            }
        }

        else if (strcmp("cd", tokenizedarr[0]) == 0)
        {
            commandid = 5;
            if (cdHandler(args) == -1)
            { // Checks error in dir commands
                fflush(stdout);
                continue;
            }
        }
        else if (strcmp("rm", tokenizedarr[0]) == 0)
        {
            commandid = 6;
            if (rmErrorHandler(args) == -1)
            { // Checks error in dir commands
                fflush(stdout);
                continue;
            }
        }

        else if (strcmp("help", tokenizedarr[0]) == 0)
        {
            commandid = 7;
            if (helperrorhandler(args) == -1)
            { // Checks error in dir commands
                fflush(stdout);
                continue;
            }
        }

        else if (strcmp("exit", tokenizedarr[0]) == 0)
        {
            exit(0);
        }
        else
        {
            printf("\033[1;31mZombie Child is ANGRY: \033[0m%s : The term '%s' is not recognized as the name of a command supported by ZCS. Check the\nspelling of the name, or if a path was included, verify that the path is correct and try again.\nAt line:1 char:1\n+ %s\n+ ~~~\n    + CategoryInfo          : ObjectNotFound: (dad:String) [], CommandNotFoundException\n    + FullyQualifiedErrorId : CommandNotFoundException ", tokenizedarr[0], tokenizedarr[0], tokenizedarr[0]);
        }
        int rc = fork();

        if (rc < 0)
        { // fork has failed
            printf("\033[1;31mZombie Child is ANGRY: \033[0m ZCS Internal Error - Fork Failed");
            exit(1);
        }

        else if (rc == 0)
        { // fork is successful, the rc of child=0, rc of parent=PID of child
            // printf("fork successful\n");
            char *mainpath = extractBeforeQ2M(mypath);
            if (commandid == 0)
            {
                exit(1); // Internal Command
            }
            else if (commandid == 1)
            {
                char anotherString[] = "ZCS-Shell-main/dir";
                strcat(mainpath, anotherString);
                if (execv(mainpath, args) == -1)
                { // Please change the address accodindly in the command
                    printf("\033[1;31mZombie Child is ANGRY: \033[0mExecutable file not found at the specified address");
                }
            }
            else if (commandid == 2)
            {
                char anotherString[] = "ZCS-Shell-main/date";
                strcat(mainpath, anotherString);
                if (execv(mainpath, args) == -1)
                { // Please change the address accodindly in the command
                    printf("\033[1;31mZombie Child is ANGRY: \033[0mExecutable file not found at the specified address");
                }
            }

            else if (commandid == 3)
            {
                char anotherString[] = "ZCS-Shell-main/ls";
                strcat(mainpath, anotherString);
                if (execv(mainpath, args) == -1)
                { // Please change the address accodindly in the command
                    printf("\033[1;31mZombie Child is ANGRY: \033[0mExecutable file not found at the specified address");
                }
            }

            else if (commandid == 4)
            {
                char mypwdpath[200] = {'\0'};
                getcwd(mypwdpath, sizeof(mypwdpath));
                printf("%s", mypwdpath);
                fflush(stdout);
            }

            else if (commandid == 5)
            { // cd
                exit(1);
            }
            else if (commandid == 6)
            { // rm
                char anotherString[] = "ZCS-Shell-main/rm";
                strcat(mainpath, anotherString);
                if (execv(mainpath, args) == -1)
                { // Please change the address accodindly in the command
                    printf("\033[1;31mZombie Child is ANGRY: \033[0mExecutable file not found at the specified address");
                }
            }

            else if (commandid == 7)
            { // rm
                help(args);
            }
        }
        else
        {

            wait(NULL);
            // printf("Parent process is running\n");
        }
    }
    return 0;
}
