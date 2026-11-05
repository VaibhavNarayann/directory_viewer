#include<stdio.h>
#include<dirent.h>
#include<string.h> 


void print_file(const char *name, int is_dir){
      if(is_dir) 
        printf("\033[0;34m%s\033[0m\n", name); 
      else 
        printf("%s\n", name); 	
} 

int walk(const char *path){
 DIR *dir = opendir(path);
  if(!dir){
    perror("opendir"); 
    return 1; 
  } 
	
 struct dirent *dp; 
 
 while((dp = readdir(dir)) != NULL) { 
 	const char *name = dp->d_name; 
 	
	//ignore files
 	if(strcmp(name, ".") == 0 || strcmp(name, "..") == 0) 
	continue;  
//        printf("%s\n", name);
	
	if(dp->d_type == DT_DIR) {
       	 print_file(name, 1);
	
          //walk to sub path; 
          size_t len = strlen(path) + strlen(name) + 2; 
          char sub_path[len];
          snprintf(sub_path, len, "%s/%s", path, name); 
          walk(sub_path); 
        }
         else {
	          print_file(name, 0); 
         } 
    }  
    
  closedir(dir); 
	return 0; 
}

int main(int argc, char **argv){
 const char *path = "."; //default path is current dir; 

 if (argc > 1 ) {
   path = argv[1];  
 } 

 int err = walk(path); 
  return err; 
}
