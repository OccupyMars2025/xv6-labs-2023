/**
 * https://pdos.csail.mit.edu/6.1810/2023/labs/util.html
 * 
 * Write a simple version of the UNIX find program for xv6: 
 * find all the files in a directory tree with a specific name.
 *  Your solution should be in the file user/find.c.
 * 
 * modified from user/ls.c
 * 
 * test method:
 * $ ./grade-lab-util find
 * $ make GRADEFLAGS=find grade
*/

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

/**
 * recursively print all files and devices that have the name "filename"
 * under the path "path"
*/
void
find(char *path, char *filename)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)){
        fprintf(2, "find: path too long\n");
        return;
    }

    if((fd = open(path, O_RDONLY)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    if(T_DIR != st.type) {
        fprintf(2, "find: 'path' has to be a directory\n");
        close(fd);
        return;
    }

    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        if(de.inum == 0)
            continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = '\0';
        // printf("%s  length:%d\n", buf, strlen(buf));

        if(stat(buf, &st) < 0){
            printf("find: cannot stat %s\n", buf);
            continue;
        }
        if(T_DIR == st.type) {
            if(0 != strcmp(de.name, ".") && 0 != strcmp(de.name, "..")) {
                find(buf, filename);
            }
        } else {
            if(strcmp(de.name, filename) == 0) {
                //TODO: It seems that "%ul" is NOT supported
                // printf("%s %d %d %l\n", buf, st.type, st.ino, st.size);
                printf("%s\n", buf);
            }
        }
    }

    close(fd);
}

int
main(int argc, char *argv[])
{
    if(3 != argc){
        fprintf(2, "Error: there need be 2 arguments. Usage example: $ find . text.txt\n");
        exit(1);
    }

    find(argv[1], argv[2]);
    exit(0);
}
