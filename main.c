#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR *dir = opendir("./");
    if (!dir) {
        perror("Can not open dir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%d - %s [%d] %d\n",
                entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen);
    }
    closedir(dir);

    return 0;
}
