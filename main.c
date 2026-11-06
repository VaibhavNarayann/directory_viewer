#include<stdio.h>
#include<string.h> 
#include<dirent.h>  // Required header for DIR, opendir, readdir, and closedir


void print_file(const char *name, int is_dir, int indent){ // Indentation is the way of adding spaces or tabs at the beginning of lines.
  if(indent)
  printf("%*c", indent * 2, ' '); 
      if(is_dir) 
        printf("\033[0;34m%s\033[0m\n", name);  // Folder color
      else 
        printf("%s\n", name); 	
} 

int walk(const char *path, int indent){
 DIR *dir = opendir(path);
  if(!dir){
    perror("opendir"); 
    return 1; 
  } 
	
 struct dirent *dp; 
 
 while((dp = readdir(dir)) != NULL) { 
 	const char *name = dp->d_name; 
 	
	//ignore files
 	if(strcmp(name, ".") == 0 || strcmp(name, "..") == 0 || strcmp(name, ".git") == 0) 
	continue;  
	
	if(dp->d_type == DT_DIR) {
       	 print_file(name, 1, indent);
	
        //   //walk to sub path; 
          size_t len = strlen(path) + strlen(name) + 2; 
          char sub_path[len];
          snprintf(sub_path, len, "%s/%s", path, name); 
          walk(sub_path, indent + 1); 
        } 
         else {
	          print_file(name, 0, indent); 
         } 
    }  
    
  closedir(dir);    // closes an open directory stream and frees all resources
	return 0; 
}

int main(int argc, char **argv){
 const char *path = "."; //default path is current dir; 

 if (argc > 1 ) {
   path = argv[1];  
 } 

 int err = walk(path, 0); 
  return err; 
}
