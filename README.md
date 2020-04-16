# ls-l

This is a test task before a job interview

## Task

Develop your version of the ls utility. Only the 'ls -l' finctionality is needed.

## Overview

This task was done in the Debian 10, gcc v8.3.0.

A first commandline parameter can be used as a path.

## Difference

- a locale is not used
- a commandline parameter (path) must be with a trailing slash
- alignment in columns is not exactly the same
- timestamp formatting is not exactly the same
- total blocks count is shown on the bottom
- file names with slashes are not quoted

## Example

This is an output of `ls -l`:

```bash
итого 40
-rwxr-xr-x 1 alpha alpha 16100 апр 15 21:33  main
-rw-r--r-- 1 alpha alpha  2886 апр 15 23:52  main.c
-rw-r--r-- 1 alpha alpha     7 апр 15 13:42 'name with spaces'
drwxr-xr-x 2 alpha alpha  4096 апр 15 13:19  testDir
drwxr-xr-x 2 alpha alpha  4096 апр 15 13:19  testDirYetAnother
-rw-r--r-- 1 alpha alpha     0 апр 15 13:19  testEmptyFile
-rw-r--r-- 1 alpha alpha    38 апр 15 13:58  Кириллица
-rw-r--r-- 1 alpha alpha    10 апр 15 13:57 'кириллица с пробелами'
```

This is an output of `./ls-l`:

```bash
-rwxr-xr-x 1 alpha alpha 16100	Apr 15 21:33 2020 main
-rw-r--r-- 1 alpha alpha 2886	Apr 15 23:52 2020 main.c
-rw-r--r-- 1 alpha alpha 7	Apr 15 13:42 2020 name with spaces
drwxr-xr-x 2 alpha alpha 4096	Apr 15 13:19 2020 testDir
drwxr-xr-x 2 alpha alpha 4096	Apr 15 13:19 2020 testDirYetAnother
-rw-r--r-- 1 alpha alpha 0	Apr 15 13:19 2020 testEmptyFile
-rw-r--r-- 1 alpha alpha 38	Apr 15 13:58 2020 Кириллица
-rw-r--r-- 1 alpha alpha 10	Apr 15 13:57 2020 кириллица с пробелами
total: 40
```


