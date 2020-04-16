#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

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

char *mode2str(int mode)
{
    char *result = malloc(11 * sizeof(char));
    result[10] = '\0';
    result[0] = (S_ISDIR(mode) ? 'd' : '-');
    result[1] = (mode & S_IRUSR) ? 'r' : '-';
    result[2] = (mode & S_IWUSR) ? 'w' : '-';
    result[3] = (mode & S_IXUSR) ? 'x' : '-';
    result[4] = (mode & S_IRGRP) ? 'r' : '-';
    result[5] = (mode & S_IWGRP) ? 'w' : '-';
    result[6] = (mode & S_IXGRP) ? 'x' : '-';
    result[7] = (mode & S_IROTH) ? 'r' : '-';
    result[8] = (mode & S_IWOTH) ? 'w' : '-';
    result[9] = (mode & S_IXOTH) ? 'x' : '-';
    if (S_ISLNK(mode)) result[0] = 'l';
    return result;
}

int main(int argc, char *argv[])
{
    char *path;
    if (argc > 1) {
        path = argv[1];
    }
    else path = "./";

    DIR *dir = opendir(path);
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
    struct tm dt;

    for (int i = 0; i < fnum; i++) {
        if (fnames[i][0] == '.')
            continue;
        char name[258];
        sprintf(name, "%s%s", path, fnames[i]);
        if (!lstat(name, &stats)) {
            char *mode_str = mode2str(stats.st_mode);
            struct passwd *pw = getpwuid(stats.st_uid);
            struct group *gr = getgrgid(stats.st_gid);
            dt = *(localtime(&stats.st_ctime));
            char ftime[30];
            strftime(ftime, 30, "%b %d %H:%M %Y", &dt);
            printf("%s %d %s %s %d\t%s %s\n",
                    mode_str, stats.st_nlink, pw->pw_name, gr->gr_name,
                    stats.st_size, ftime, fnames[i]);
            free(mode_str);
        }
    }

    /* free the fnames memory */
    for (int i = 0; i < fnum; i++)
        free(fnames[i]);
    free(fnames);

    return 0;
}
