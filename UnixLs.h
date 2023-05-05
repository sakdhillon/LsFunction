#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

void getAndPrintGroup(gid_t grpNum);

void listFilesRec(const char *dir, int opa, int i, int l);

void listFilesinode (const char *dir, int opa, int R, int l);

void listFilesL (const char *dir, int opa, int i, int R);

void listingDirectory(const char *dir, int opa, int i, int R, int l);

int main(int argc, const char *argv[]);