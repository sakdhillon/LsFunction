#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#include "UnixLs.h"

// commands that we have to complete it with

// ls -i: list the files along with their index number
// ls -R: list all files recursively, descending down the directory tree from the given path.
// ls -l: list the files in long format i.e. with an index number, owner name, group name, size, and permissions.

/*
To complete this assignment, we used a couple of online resources has reference, these are all listed here specifically
There are a couple that we referenced within the code when we were writing it, but those are also found here:
    https://stackoverflow.com/questions/50091777/printing-information-from-stat2
    https://stackoverflow.com/questions/8236/how-do-you-determine-the-size-of-a-file-in-c
    https://stackoverflow.com/questions/10323060/printing-file-permissions-like-ls-l-using-stat2-in-c
    https://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html
    https://pubs.opengroup.org/onlinepubs/009604499/basedefs/sys/stat.h.html
*/

void listFilesRec(const char *dir, int opa, int i, int l)
{
    char newPath[1000];
    struct dirent *d;

    struct stat fileStat;
    struct passwd *owner;
    struct group *group;
    char timeBuf[20];
    char filename[1000];
    struct tm *now;

    DIR *directory = opendir(dir);

    if (!directory)
    {
        return;
    }
    while ((d = readdir(directory)) != NULL)
    {
        // makes sure it's not a hidden file
        if (d->d_name[0] != '.')
        {
            //////////////////// this one still doesn't work properly ////////////////
            if (l >= 1)
            {
                if (!opa && d->d_name[0] == '.')
                {             // having '..' shows all the hidden files - just having '.' only shows files that are there
                    continue; // may need to change this?
                    // i think this is letting me see hidden file now too - this was something I tried on my own based on what he said in class
                }

                sprintf(filename, "%s/%s", dir, d->d_name); // construct full path of file
                if (stat(filename, &fileStat) == -1)
                {
                    printf("ERORRRR : %s", filename);
                    perror("Error getting file status NOWWWW ");
                    exit(EXIT_FAILURE);
                }

                // printf("this will print stuff for -Rl and -Ril");
                if (i >= 1)
                {
                    printf("%llu ", d->d_ino);
                }

                printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
                printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
                printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
                printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
                printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
                printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
                printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
                printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
                printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
                printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

                // TODO: add where we got this from.....

                // Print number of hard links
                printf(" %ld", (long)fileStat.st_nlink);

                // Print owner name and group name
                owner = getpwuid(fileStat.st_uid);
                printf(" %s", owner->pw_name);

                group = getgrgid(fileStat.st_gid);
                printf(" %s", group->gr_name);

                // Print file size
                printf(" %lld", (long long)fileStat.st_size);

                // Print last modification time
                now = localtime(&fileStat.st_mtime);
                strftime(timeBuf, sizeof(timeBuf), "%b %d %Y %H:%M", now);
                printf(" %s", timeBuf);

                // Print filename
                printf(" %s\n", d->d_name);
            }
            else if (i >= 1 && l == 0)
            {
                printf("%llu %s    \n", d->d_ino, d->d_name);
            }
            else
            {
                printf("%s\n", d->d_name);
            }

            // Construct new path from our base path
            strcpy(newPath, dir);
            strcat(newPath, "/");
            // getting the location to attempt to access the next directory
            strcat(newPath, d->d_name);

            // using the new path obtained, it recusively checks for the new paths to see if it is a subdirectory
            // printf("changed new path name ---------> %s", newPath);
            listFilesRec(newPath, opa, i, l);
        }
    }
    closedir(directory);
}

void listFilesL(const char *dir, int opa, int i, int R)
{
    struct dirent *d;
    struct stat fileStat;
    struct passwd *owner;
    struct group *group;
    char timeBuf[20];
    char filename[1000];
    struct tm *now;

    DIR *directory = opendir(dir);
    while ((d = readdir(directory)) != NULL)
    {
        if (!opa && d->d_name[0] == '.')
        {             // having '..' shows all the hidden files - just having '.' only shows files that are there
            continue; // may need to change this?
            // i think this is letting me see hidden file now too - this was something I tried on my own based on what he said in class
        }

        sprintf(filename, "%s/%s", ".", d->d_name); // construct full path of file
        if (stat(filename, &fileStat) == -1)
        {
            perror("Error getting file status HERE");
            exit(EXIT_FAILURE);
        }
        if (i >= 1 && R >= 1)
        {
            // printf("this flag was -iRl or -ilR\n");
            // send to listFilesRec
            listFilesRec(dir, opa, i, 1);
            // printf("this flag was -iRl or -ilR\n");
            // send to listFilesRec
            return;
        }

        else if (i == 0 && R >= 1)
        {
            // printf("this flag had -iR or -Ri\n");
            // send to listFilesrec
            listFilesRec(dir, opa, i, 1);
            return;
        }
        else
        {
            // adding what is to be printing when the flag is -l
            // Print file permissions
            if (i >= 1)
            {
                printf("%llu ", d->d_ino);
            }

            printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
            printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

            // https://stackoverflow.com/questions/10323060/printing-file-permissions-like-ls-l-using-stat2-in-c

            // Print number of hard links
            printf(" %ld", (long)fileStat.st_nlink);

            // Print owner name and group name
            owner = getpwuid(fileStat.st_uid);
            printf(" %s", owner->pw_name);

            group = getgrgid(fileStat.st_gid);
            printf(" %s", group->gr_name);

            // Print file size
            printf(" %lld", (long long)fileStat.st_size);

            // Print last modification time
            now = localtime(&fileStat.st_mtime);
            strftime(timeBuf, sizeof(timeBuf), "%b %d %Y %H:%M", now);
            printf(" %s", timeBuf);

            // Print filename
            printf(" %s\n", d->d_name);
        }
    }
}

void listFilesinode(const char *dir, int opa, int R, int l)
{

    // printf("in the inode file thing..................\n");
    struct dirent *d;
    DIR *directory = opendir(dir);

    if (!directory)
    {
        return;
    }
    // to check with other conditions (l or R)
    if (l >= 1 && R >= 1)
    {
        // printf("this flag was -iRl or -ilR\n");
        listFilesRec(dir, opa, 1, l);
        return;
    }

    else if (l == 0 && R >= 1)
    {
        // printf("this flag had -iR or -Ri\n");
        listFilesRec(dir, opa, 1, l);
        return;
    }
    else if (l >= 1 && R == 0)
    {
        // printf("this flag had -il\n");
        listFilesL(dir, opa, 1, R);
        return;
    }
    // this is only when i == 0 and nothing else happens loll
    else
    {
        while ((d = readdir(directory)) != NULL)
        {
            if (!opa && d->d_name[0] == '.')
            {
                continue;
            }
            else
            {
                printf("%llu %s    ", d->d_ino, d->d_name);
                // https://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html
                // that was what I used to find the inode number
            }
        }
    }
    closedir(directory);
}

void listingDirectory(const char *dir, int opa, int i, int R, int l)
{
    // printf("%d\n", i);
    struct dirent *d;
    // struct stat fileStat;
    // struct passwd *owner;
    // struct group *group;
    // char timeBuf[20];
    // char filename[1000];
    // struct tm *now;

    DIR *directory = opendir(dir);
    if (!directory)
    {
        if (errno == ENOENT)
        {
            perror("directory does not exist");
        }
        else
        {
            perror("unable to read directory");
            exit(EXIT_FAILURE);
        }
    }

    if (i >= 1)
    {
        // printf("\n we are in the i that will lead to the r if needed ...........................\n");
        listFilesinode(dir, opa, R, l);
    }

    else if (l >= 1)
    {
        // printf("\n we are in the l and that it will lead to r if needed  ...........................\n");
        listFilesL(dir, opa, i, R);
    }

    else if (R >= 1)
    {
        // printf("\n");
        // call recursive function that will print out current directory and the subdirectories within
        listFilesRec(dir, opa, i, l);
    }

    // this is just listing if there are no flag commands
    else
    {
        while ((d = readdir(directory)) != NULL)
        {
            if (!opa && d->d_name[0] == '.')
            {             // having '..' shows all the hidden files - just having '.' only shows files that are there
                continue; // may need to change this?
                // i think this is letting me see hidden file now too - this was something I tried on my own based on what he said in class
            }
            if (l == 0 & R == 0 && i == 0)
            {
                printf("%s    ", d->d_name);
            }
        }
    }
    if (!l)
    {
        printf("\n");
    }

    closedir(directory);
}

int main(int argc, const char *argv[])
{
    int k;
    int R = 0;
    int l = 0;
    int i = 0;
    if (argc == 1)
    {
        // printf("HELLOOOOOOOIN HEREREREERERER\n");
        listingDirectory(".", 0, i, R, l);
    }
    else
    {
        for (k = 1; k < argc; k++)
        {
            if (argv[k][0] == '-')
            {
                // printf("there is a flag: %s\n", argv[k]);
                if (strchr(argv[k], 'l'))
                {
                    // printf("it is the l command\n");
                    l++;
                    // printf("i = %d, R = %d, l = %d\n", i, R, l);
                }
                if (strchr(argv[k], 'i'))
                {
                    // printf("it is the i command\n");
                    i++;
                    // printf("i = %d, R = %d, l = %d\n", i, R, l);
                }
                if (strchr(argv[k], 'R'))
                {
                    // printf("it is the R command\n");
                    R++;
                    // printf("i = %d, R = %d, l = %d\n", i, R, l);
                }
                if (k == argc - 1)
                {
                    // printf("\n NO SPECIFIC DIRECTORY INDICATED\n");
                    listingDirectory(".", 0, i, R, l);
                }
            }
            else
            {
                // printf("i = %d, R = %d, l = %d\n", i, R, l);

                listingDirectory(argv[k], 0, i, R, l);
            }
        }
    }

    return 0;
}
