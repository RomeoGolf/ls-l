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

    /* file names array */
    char **fnames = NULL;
    int fnum = 0;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        fnames = (char **) realloc (fnames, sizeof(char *) * (fnum + 1));
        char *fname = malloc(255 * sizeof(char));
        sprintf(fname, "%s", entry->d_name);
        fnames[fnum] = fname;
        fnum++;
        /*printf("%d - %s [%d] %d\n",*/
                /*entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen);*/
    }
    closedir(dir);

    printf("-----\n");
    printf("filenum = %d\n", fnum);
    for (int i = 0; i < fnum; i++) {
        printf("%s\n", fnames[i]);
    }


    /* free the fnames memory */
    for (int i = 0; i < fnum; i++)
        free(fnames[i]);
    free(fnames);

    return 0;
}
