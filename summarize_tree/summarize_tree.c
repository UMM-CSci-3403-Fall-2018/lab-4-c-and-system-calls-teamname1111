#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
  /*
   * Use the stat() function (try "man 2 stat") to determine if the file
   * referenced by path is a directory or not.  Call stat, and then use
   * S_ISDIR to see if the file is a directory. Make sure you check the
   * return value from stat in case there is a problem, e.g., maybe the
   * the file doesn't actually exist.
   */
   struct stat sb;
   int i = stat(path, &sb);
   //checks that there was not an error running stat, if there was an error
   //it will print out the error and exit
   if(i != 0){
     fprintf(stderr, "There was an error calling stat.\n");
     exit(1);
   }
   //checks if the path is a directory
   if(S_ISDIR(sb.st_mode)){
   return true;
   } else {
   return false;
   }
}

/* 
 * I needed this because the multiple recursion means there's no way to
 * order them so that the definitions all precede the cause.
 */
void process_path(const char*);

void process_directory(const char* path) {
  /*
   * Update the number of directories seen, use opendir() to open the
   * directory, and then use readdir() to loop through the entries
   * and process them. You have to be careful not to process the
   * "." and ".." directory entries, or you'll end up spinning in
   * (infinite) loops. Also make sure you closedir() when you're done.
   *
   * You'll also want to use chdir() to move into this new directory,
   * with a matching call to chdir() to move back out of it when you're
   * done.
   */
   DIR *direct;
   struct dirent *currentdir;
   num_dirs++;
   //opens path
   direct = opendir(path);
   //Makes sure there is no issue with opendir
   if(direct == NULL){
     fprintf(stderr, "There was an error opening the directory in process_directory.\n");
     exit(1);
   }
   //sets path as the working directory
   chdir(path);
   currentdir = readdir(direct);
   //while current directory exists and the directory/file is not . or .. 
   //after the if statement it runs readdir on direct
   while(currentdir != NULL){
     if(strcmp(currentdir->d_name, ".") != 0 && strcmp(currentdir->d_name, "..") != 0){
	process_path(currentdir->d_name);  	  
     }
     currentdir = readdir(direct);
   }
   //move back to parent directory
   chdir("..");
   //closes the directory
   closedir(direct);

}

void process_file(const char* path) {
  /*
   * Update the number of regular files.
   */
	num_regular++;
}

void process_path(const char* path) {
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
