#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/* Prototype of the recursive function */
void print_tree(char *path, int level);

int main(int argc, char *argv[]) {

    char *initial_path;

    /* Argument handling: if no path is provided, use the current directory (.) */
    if (argc == 1) {
        initial_path = ".";
    } 
    else if(argc == 2){
        initial_path = argv[1];
    }
    else{
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    /* Print the root directory name */
    printf("%s\n", initial_path);
    print_tree(initial_path, 0);

    return 0;

}

void print_tree(char *path, int level) {
    
    DIR *dir;
    struct dirent *entry;
    struct stat info;
    char new_path[1024];

    /*Open the directory. If it fails, show the error (permissions,doesn't exist, etc)*/
    if(!(dir = opendir(path))){
        perror("tree");
        return;
    }
    
    /*Read every entry inside the directory*/
    while((entry = readdir(dir)) != NULL){
        
       /* Skip the special system directories '.' and '..' to avoid infinite loops */
        if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0){
            continue;
        }
        
        /* Build the full path to analyze the file with lstat */
        snprintf(new_path,sizeof(new_path),"%s/%s",path,entry->d_name);
        
        /* Get the file's technical metadata (lstat is key for symbolic links) */
        if(lstat(new_path, &info) == -1){
            continue;
        }

        /* Print indentation based on the depth level */
        for(int i = 0; i < level; i++){
            printf("│   ");
        }
        printf("├── %s\n", entry->d_name);
        
        /* RECURSION: Only descend if it's a directory AND NOT a symbolic link */
        if (S_ISDIR(info.st_mode) && !S_ISLNK(info.st_mode)) {
            print_tree(new_path, level + 1);
        }
    }
    closedir(dir);  /* Close the directory stream to free system resources */
}