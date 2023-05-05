#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "UnixLs.h"


// struct stat -- to get the inode

// use stat()

//commands that we have to complete it with 

// ls -i: list the files along with their index number
// ls -R: list all files recursively, descending down the directory tree from the given path.
// ls -l: list the files in long format i.e. with an index number, owner name, group name, size, and permissions.

void getAndPrintGroup(gid_t grpNum) {
    //prints their index number I think - got this from the infoDemo.c 
  struct group *grp;

  grp = getgrgid(grpNum); 
  
  if (grp) {
    printf("The group ID %u -> %s\n", grpNum, grp->gr_name);
  } else {
    printf("No group name for %u found\n", grpNum);
  }
}


void listingDirectory (const char *dir, int opa, int opl){
    struct dirent *d;
    DIR *directory = opendir(".");
    if (!directory){
        if (errno == ENOENT){
            perror("directory does not exist");
        }
        else{
        perror("unable to read directory");
        exit(EXIT_FAILURE);
        }
    }
    while ((d = readdir(directory)) != NULL){
        if(!opa && d->d_name[0] == '.'){ //having '..' shows all the hidden files - just having '.' only shows files that are there 
            continue;   
// i think this is letting me see hidden file now too - this was something I tried on my own based on what he said in class 
        }
        printf("%s\n", d->d_name);
        if (opl){
            printf("\n");
        }
    }
    if (!opl){
        printf("\n");
    }
}

void mainls (int argc, const char *argv[]){
     // if (argc == 1){
    //     listingDirectory(".");
    // }
    if (argc == 1){
        listingDirectory(".", 0, 0);
    }
    else if (argc == 2){
        if (argv[1][0] == "-"){
            //checking if option is passed 
            int opa = 0;
            int opl = 0;
            char *p = (char *)(argv[1] + 1);
            while (*p){
                if (*p == "a"){
                    opl = 1;
                }
                else if (*p == "l"){
                    opl = 1;
                }
                else {
                    perror("unknown option error");
                    exit (EXIT_FAILURE);
                }
                p++;
            }
            listingDirectory(".", opa, opl);
        }
        else{
            //check if directory exists
            listingDirectory(argv[1], 0, 0);
        }
    }
    else if(argc == 3){
        if(argv[1][0] != '-'){
            perror("inccorect usage error");
            exit(EXIT_FAILURE);
        }
        int opa = 0;
        int opl = 0;
        char *p = (char *)(argv[1] + 1);
        while (*p){
            if (*p == "a"){
                opl = 1;
                }
            else if (*p == "l"){
                opl = 1;
            }
            else {
                perror("unknown option error");
                exit (EXIT_FAILURE);
            }
            p++;
        }
        listingDirectory(argv[2], opa, opl);
    }
}


//idk if making a separate function for each of these is efficient 
// how is this being tested? only in the terminal - or like are we being asked to scan the ls command being sent in 
// or are we just printing each of the commands and showing that they work?
// void ls_i (int argc, const char *argv[]){

// }

// void ls_l (int argc, const char *argv[]){

// }

// void ls_R (int argc, const char *argv[]){

// }


int main(int argc, const char *argv[]){
    // printf("enter your ls command: \n");
    // char x;
    // // scanf(" %s", x);
    if (argc == 2){
        if (argv[1] == NULL){
        mainls(argc, argv);
    }

    else if (argv[1][0] == '-'){
        // printf ("there is a flag: %s\n", argv[1]); 
        // if (argv[1][1] == 'R'){
        //     printf("it is the R command\n");
        // }
        // else if (argv[1][1] == 'l'){
        //     printf("it is the gl command\n");
        // }
        // else if (argv[1][1] == 'i'){
        //     printf("it is the i command\n");
        // }
    }
    }
    else{
        mainls(argc, argv);
    }
    // else {
    //    printf ("there is a different flag: %s\n", argv[1]); 
    // }
    // x = "ls";
    // if (x == "ls"){
        // mainls(argc, argv);


        // make sure it accounts for the argument string and the flags 
    // }
    // else{
    //     printf("what have you done\n");
    // }
    return 0;
}


// all code below this is stuff we might not need
///////////////////////////////////////////////////////////////

// void mainls (int argc, const char *argv[]){
//      // if (argc == 1){
//     //     listingDirectory(".");
//     // }
//     if (argc == 1){
//         listingDirectory(".", 0, 0);
//     }
//     else if (argc == 2){
//         if (argv[1][0] == "-"){
//             //checking if option is passed
//             int opa = 0;
//             int opl = 0;
//             char *p = (char *)(argv[1] + 1);
//             while (*p){
//                 if (*p == "a"){
//                     opl = 1;
//                 }
//                 else if (*p == "l"){
//                     opl = 1;
//                 }
//                 else {
//                     perror("unknown option error");
//                     exit (EXIT_FAILURE);
//                 }
//                 p++;
//             }
//             listingDirectory(".", opa, opl);
//         }
//         else{
//             //check if directory exists
//             listingDirectory(argv[1], 0, 0);
//         }
//     }
//     else if(argc == 3){
//         if(argv[1][0] != '-'){
//             perror("inccorect usage error");
//             exit(EXIT_FAILURE);
//         }
//         int opa = 0;
//         int opl = 0;
//         char *p = (char *)(argv[1] + 1);
//         while (*p){
//             if (*p == "a"){
//                 opl = 1;
//                 }
//             else if (*p == "l"){
//                 opl = 1;
//             }
//             else {
//                 perror("unknown option error");
//                 exit (EXIT_FAILURE);
//             }
//             p++;
//         }
//         listingDirectory(argv[2], opa, opl);
//     }
// }

/////////////////////////////////////////////////////////////////////

// void listingDirectory (const char *dir, int opa, int opl){
//     struct dirent *d;
//     DIR *directory = opendir(".");
//     if (!directory){
//         if (errno == ENOENT){
//             perror("directory does not exist");
//         }
//         else{
//         perror("unable to read directory");
//         exit(EXIT_FAILURE);
//         }
//     }
//     while ((d = readdir(directory)) != NULL){
//         if(!opa && d->d_name[0] == '.'){ //having '..' shows all the hidden files - just having '.' only shows files that are there
//             continue;
// // i think this is letting me see hidden file now too - this was something I tried on my own based on what he said in class
//         }
//         printf("%s\n", d->d_name);
//         if (opl){
//             printf("\n");
//         }
//     }
//     if (!opl){
//         printf("\n");
//     }
// }
// void mainls(int argc, const char *argv[]){

//     printf("%d\n", strcmp(argv[1], "-l"));
//     if (argc == 1){
//         listingDirectory('.', 0, 0);
//     }
//     else if (argc == 2){
//         if (argv[1][0] == "-"){
//             //checking if option is passed
//             int opa = 0;
//             int opl = 0;
//             char *p = (char *)(argv[1] + 1);
//             while (*p){
//                 if (*p == "a"){
//                     opl = 1;
//                 }
//                 else if (*p == "l"){
//                     opl = 1;
//                 }
//                 else {
//                     perror("unknown option error");
//                     exit (EXIT_FAILURE);
//                 }
//                 p++;
//             }
//             listingDirectory(".", opa, opl);
//         }
//         else{
//             //check if directory exists
//             listingDirectory(argv[1], 0, 0);
//         }
//     }
//     else if(argc == 3){
//         if(argv[1][0] != '-'){
//             perror("inccorect usage error");
//             exit(EXIT_FAILURE);
//         }
//         int opa = 0;
//         int opl = 0;
//         char *p = (char *)(argv[1] + 1);
//         while (*p){
//             if (*p == "a"){
//                 opl = 1;
//                 }
//             else if (*p == "l"){
//                 opl = 1;
//             }
//             else {
//                 perror("unknown option error");
//                 exit (EXIT_FAILURE);
//             }
//             p++;
//         }
//         listingDirectory(argv[2], opa, opl);
//     }
//     else {
//         perror("inccorect usage error");
//         exit(EXIT_FAILURE);
//     }
// }

// int main(int argc, const char *argv[]){
//     printf("%d\n", strcmp(argv[1], "-l"));

//     if (argc == 2){
//         if (argv[1] == NULL){
//         listingDirectory('.', 0, 0);
//         }

//         else if (argv[1][0] == '-'){
//             printf ("there is a flag: %s\n", argv[1]);
//             if (strcmp(argv[1], "-l") == 0){
//                 printf("it is the l command\n");
//             }
//             else if (strcmp(argv[1], "-i") == 0){
//                 printf("it is the i command\n");
//             }
//             else if (strcmp(argv[1], "-R") == 0){
//                 printf("it is the R command\n");
//             }
//         }
//     }
//     else{
//         mainls(argc, argv);
//     }

//     return 0;
// }








//////////////////////////////////////////////////////////////////////////////////////////////////////////////


//code that we had commented out in our main UnixLs.c file - pushed to here incase we needed it 


//---------//---------//---------//---------//---------//---------//---------//---------//---------//---------
// THREE POSSIBILITES OF ARGV
// if (argc == 1)
//     {
//         listingDirectory(".", 0, i, R, l);
//     }
//     else if (argc == 2)
//     {
//         if (argv[1][0] == '-')
//         {
//             printf("there is a flag: %s\n", argv[1]);
//             // if (strcmp(argv[1], "-l") == 0)
//             if (strchr(argv[1], 'l'))
//             {
//                 printf("it is the l command\n");
//                 l++;
//                 printf("i = %d, R = %d, l = %d\n", i, R, l);
//                 // listingDirectory(".", 0, i, R, l);
//             }
//             if (strchr(argv[1], 'i'))
//             {
//                 printf("it is the i command\n");
//                 i++;
//                 printf("i = %d, R = %d, l = %d\n", i, R, l);
//                 // listingDirectory(".", 0, i, R, l);
//             }
//             if (strchr(argv[1], 'R'))
//             {
//                 printf("it is the R command\n");
//                 R++;
//                 printf("i = %d, R = %d, l = %d\n", i, R, l);
//                 // listingDirectory(".", 0, i, R, l);
//             }
//         }
//         listingDirectory(".", 0, i, R, l);
//     }
//     else if (argc == 3)
//     {
//         if (argv[1][0] == '-')
//         {
//             printf("there is a flag: %s\n", argv[1]);
//             // if (strcmp(argv[1], "-l") == 0)
//             if (strchr(argv[1], 'l'))
//             {
//                 printf("it is the l command\n");
//                 l++;
//                 printf("i = %d, R = %d, l = %d\n", i, R, l);
//                 // listingDirectory(".", 0, i, R, l);
//             }
//             if (strchr(argv[1], 'i'))
//             {
//                 printf("it is the i command\n");
//                 i++;
//                 printf("i = %d, R = %d, l = %d\n", i, R, l);
//                 // listingDirectory(".", 0, i, R, l);
//             }
//             if (strchr(argv[1], 'R'))
//             {
//                 printf("it is the R command\n");
//                 R++;
//                 printf("i = %d, R = %d, l = %d\n", i, R, l);
//                 // listingDirectory(".", 0, i, R, l);
//             }
//         }
//         listingDirectory(argv[2], 0, i, R, l);
//     }
//---------//---------//---------//---------//---------//---------//---------//---------//---------//---------


/// originally what was in the listing directory function before I made the other functions 


////////////////////////////////////////////////////
    // for -i
    // while ((d = readdir(directory)) != NULL)
    // {
    //     if (!opa && d->d_name[0] == '.')
    //     {             // having '..' shows all the hidden files - just having '.' only shows files that are there
    //         continue; // may need to change this?
    //         // i think this is letting me see hidden file now too - this was something I tried on my own based on what he said in class
    //     }
    //     if (i >= 1)
    //     {                                               // when the flag is -i
    //         printf("%llu %s    ", d->d_ino, d->d_name); // d_ino is the index number
    //     }
    // }
    // printf("\n");
    // directory = opendir(dir);

    ///////////////////////////////////////////////////
    // for -l
    // while ((d = readdir(directory)) != NULL)
    // {
    //     if (!opa && d->d_name[0] == '.')
    //     {             // having '..' shows all the hidden files - just having '.' only shows files that are there
    //         continue; // may need to change this?
    //         // i think this is letting me see hidden file now too - this was something I tried on my own based on what he said in class
    //     }

    //     sprintf(filename, "%s/%s", ".", d->d_name); // construct full path of file
    //     if (stat(filename, &fileStat) == -1)
    //     {
    //         perror("Error getting file status");
    //         exit(EXIT_FAILURE);
    //     }
    //     if (l >= 1)
    //     {
    //         // adding what is to be printing when the flag is -l
    //         // Print file permissions

    //         printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    //         printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    //         printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    //         printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    //         printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    //         printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    //         printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    //         printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    //         printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    //         printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

    //         // Print number of hard links
    //         printf(" %ld", (long)fileStat.st_nlink);

    //         // Print owner name and group name
    //         owner = getpwuid(fileStat.st_uid);
    //         printf(" %s", owner->pw_name);

    //         group = getgrgid(fileStat.st_gid);
    //         printf(" %s", group->gr_name);

    //         // Print file size
    //         printf(" %lld", (long long)fileStat.st_size);

    //         // Print last modification time
    //         now = localtime(&fileStat.st_mtime);
    //         strftime(timeBuf, sizeof(timeBuf), "%b %d %H:%M", now);
    //         printf(" %s", timeBuf);

    //         // Print filename
    //         printf(" %s\n", d->d_name);
    //     }
    // }

    
    // directory = opendir(dir);
    // while ((d = readdir(directory)) != NULL)
    // {
    //     if (!opa && d->d_name[0] == '.')
    //     {             // having '..' shows all the hidden files - just having '.' only shows files that are there
    //         continue; // may need to change this?
    //         // i think this is letting me see hidden file now too - this was something I tried on my own based on what he said in class
    //     }
    //     if (l == 0 & R == 0 && i == 0)
    //     {
    //         printf(" %s    ", d->d_name);
    //     }
    // }
    // directory = opendir(dir);

    // comment below allows us to print the specific tag and directory
    //  while ((d = readdir(directory)) != NULL)
    //  {
    //      if (!opa && d->d_name[0] == '.')
    //      {             // having '..' shows all the hidden files - just having '.' only shows files that are there
    //          continue; // may need to change this?
    //          // i think this is letting me see hidden file now too - this was something I tried on my own based on what he said in class
    //      }
    //      if (i >= 1)
    //      {                                               // when the flag is -i
    //          printf("%llu %s    ", d->d_ino, d->d_name); // d_ino is the index number
    //          printf("DONE THE i's");
    //      }

    //     else if (l >= 1)
    //     {
    //         // adding what is to be printing when the flag is -l
    //         printf("hello from llllllllllllllllllllllll\n");
    //     }
    //     else if (R >= 1)
    //     {
    //         break;
    //     }
    //     else
    //     {
    //         printf(" %s    ", d->d_name);
    //     }
    // }