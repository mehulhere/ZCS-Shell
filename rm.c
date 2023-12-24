#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <dirent.h>

// Function to handle the '-r' option
int removeDirectory(const char *path)
{
    DIR *d = opendir(path);
    size_t path_len = strlen(path);
    int r = -1;

    if (d)
    {
        struct dirent *p;
        r = 0;

        while (!r && (p = readdir(d)))
        {
            int r2 = -1;
            char *completePath;
            size_t len;

            if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
            { // Skip "." and ".."
                continue;
            }

            len = path_len + strlen(p->d_name) + 2; // +2 for "/"" and null terminator
            completePath = malloc(len);

            if (completePath)
            {
                struct stat filemode;
                snprintf(completePath, len, "%s/%s", path, p->d_name); // constructs complete path

                if (!stat(completePath, &filemode))
                { // Checks if its directory or file
                    if (S_ISDIR(filemode.st_mode))
                    {
                        r2 = removeDirectory(completePath);
                    }
                    else
                    {
                        r2 = remove(completePath);
                    }
                }
                free(completePath);
            }
            r = r2;
        }
        closedir(d);
    }

    if (!r)
    {
        r = rmdir(path);
    }
    return r;
}

// Function to handle the '-f' option
int removeFile(const char *path)
{
    return remove(path);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s [-r/-f] <filename>\n", argv[0]);
        return 1;
    }

    char *option = argv[1];
    char *filename = argv[2];

    if (strcmp(option, "-r") == 0)
    {
        if (removeDirectory(filename) == 0)
        {
            printf("Directory '%s' deleted successfully.\n", filename);
        }
        else
        {
            printf("Error deleting directory '%s'.\n", filename);
        }
    }
    else if (strcmp(option, "-f") == 0)
    {
        if (removeFile(filename) == 0)
        {
            printf("File '%s' deleted successfully.\n", filename);
        }
        else
        {
            printf("Error deleting file '%s'.\n", filename);
        }
    }
    else
    {
        printf("Invalid option: %s\n", option);
        printf("Usage: %s [-r/-f] <filename>\n", argv[0]);
        return 1;
    }

    return 0;
}
