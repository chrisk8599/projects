#ifndef svc_h
#define svc_h

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
typedef unsigned char BYTE;
static int flag = -1;
static char number = 'a' ;



typedef struct branches {
    // NOTE: DO NOT MODIFY THIS STRUCT
 struct branch** branches;
 int n_branch;
 int current;

} branches;

typedef struct branch {
    // NOTE: DO NOT MODIFY THIS STRUCT
    struct commit * commits;
    int  n_commits;
    struct file* tracked_files;
    struct changes* changes;
    int n_tracked;
    struct commit* last_commit;
    int n_add;
    int n_rmv;
    int merged;
    char** removed;
    char* name;
    int commitCalled;
    int mergeCalled;

} branch;

typedef struct commit {
    // NOTE: DO NOT MODIFY THIS STRUCT
    char * commit_id;
    char* message;
    struct file** tracked;
    int n_tracked;
    struct commit * next;
    struct commit* resetNext;
    struct commit * prev;
    struct changes* changes;
    struct commit* resetPrev;
    struct commit* mergePrev;

} commit;


typedef struct file {
    // NOTE: DO NOT MODIFY THIS STRUCT
    int  hash;
    int oldHash;
    char* file_name;
    struct contents* content;
    struct file* next;
    int tracked;
    int delete;
} file;


typedef struct contents {
    // NOTE: DO NOT MODIFY THIS STRUCT
    char* saved;
    int hash;
    char* orig;

} contents;


typedef struct changes {
    // NOTE: DO NOT MODIFY THIS STRUCT
    char* type;
    struct changes * next;
    struct changes * prev;
    char* file_name;

} changes;


typedef struct resolution {
    // NOTE: DO NOT MODIFY THIS STRUCT
    char *file_name;
    char *resolved_file;
} resolution;

void *svc_init(void);

void cleanup(void *helper);

int hash_file(void *helper, char *file_path);

char *svc_commit(void *helper, char *message);

void *get_commit(void *helper, char *commit_id);

char **get_prev_commits(void *helper, void *commit, int *n_prev);

void print_commit(void *helper, char *commit_id);

int svc_branch(void *helper, char *branch_name);

int svc_checkout(void *helper, char *branch_name);

char **list_branches(void *helper, int *n_branches);

int svc_add(void *helper, char *file_name);

int svc_rm(void *helper, char *file_name);

int svc_reset(void *helper, char *commit_id);

char *svc_merge(void *helper, char *branch_name, resolution *resolutions, int n_resolutions);

#endif
