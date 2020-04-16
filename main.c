#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void sort_names(char **str, int num)
{
    char *k;
    for (int i = 1; i < num; i++)
        for (int j = 0; j < num - i; j++)
            if (strcmp(str[j], str[j + 1]) > 0) {
                k = str[j];
                str[j] = str[j + 1];
                str[j + 1] = k;
            }
}

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
    }
    closedir(dir);

    /* sort the fnames array lexicografically */
    sort_names(fnames, fnum);

    struct stat stats;

    printf("filenum = %d\n", fnum);
    for (int i = 0; i < fnum; i++) {
        char name[258];
        sprintf(name, "./%s", fnames[i]);
        if (!stat(name, &stats)) {
            printf("mode %x | links %d | %s\n",
                    stats.st_mode, stats.st_nlink, fnames[i]);
        }
    }

    /* free the fnames memory */
    for (int i = 0; i < fnum; i++)
        free(fnames[i]);
    free(fnames);

    return 0;
}
