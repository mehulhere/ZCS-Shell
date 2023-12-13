#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>

void printFileMode(mode_t mode) {
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

void printFileInfo(struct dirent *d, int l, const char *dir) {
    int isHiddenFile = (d->d_name[0] == '.');
    if (l) {
        struct stat fileInfo;
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir, d->d_name);

        if (stat(path, &fileInfo) < 0) {
            perror("stat");
            return;
        }

        printFileMode(fileInfo.st_mode);
        printf(" %lu", fileInfo.st_nlink);

        struct passwd *pwd = getpwuid(fileInfo.st_uid);
        struct group *grp = getgrgid(fileInfo.st_gid);

        printf(" %s %s", pwd ? pwd->pw_name : " ", grp ? grp->gr_name : " ");
        printf(" %5ld", fileInfo.st_size);

        char timeStr[16];
        strftime(timeStr, sizeof(timeStr), "%b %d %H:%M", localtime(&fileInfo.st_mtime));
        printf(" %s %s\n", timeStr, d->d_name);
    } else {
        if (isHiddenFile) {
            printf("\033[42m\033[34m%s\033[0m ", d->d_name); // Yellow color for hidden files
        } else {
            printf("\033[1;32m%s \x1b[34m \033[0m", d->d_name);// Green color for regular files
        }
       
      
    }
}

void ls(const char *dir, int l, int a) {
    DIR *dp = opendir(dir);
    if (!dp) {
        perror("Unable to open directory");
        return;
    }

    struct dirent *d;
    while ((d = readdir(dp)) != NULL) {
        if (!a && d->d_name[0] == '.') {
            continue; // Skip hidden files unless -a option is specified
        }
        printFileInfo(d, l, dir);
    }
    closedir(dp);
}

int main(int argc, char *argv[]) {
    int l_flag = 0;
    int a_flag = 0;

    // Parsing command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            l_flag = 1;
        } else if (strcmp(argv[i], "-a") == 0) {
            a_flag = 1;
        }
    }

    ls(".", l_flag, a_flag);
    return 0;
}
