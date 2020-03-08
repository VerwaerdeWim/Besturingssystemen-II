#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#include <string.h>

#define BUFFER_SIZE 8*1024

void in_to_out(){
	char buffer[BUFFER_SIZE];
	int n;
	while(n = read(STDIN_FILENO, buffer, BUFFER_SIZE)){
		write(STDOUT_FILENO,buffer,n);
	}
}

int main(int argc, char **argv){
    //doet hetzelfde als printf("%d",argc);
	/*
	int i;
	char tab[10];
	for(i=0;i<10;i++){
		tab[i]='0'+i;
	}
	write(1,&tab[argc],sizeof(char));
	*/

	if(argc==1) {
		in_to_out();	
	} else {
		int i;
		for(i=1; i<argc;i++){
			if(strcmp(argv[i],"-")==0){
				in_to_out();
				continue;
			}
			
			int fd;
			if((fd=open(argv[i],O_RDONLY))==-1){
				perror(argv[i]);
				continue;
			}
			
			unsigned char buffer[BUFFER_SIZE];	
			int n;
			while((n = read(fd,buffer,BUFFER_SIZE))>0){
				write(STDOUT_FILENO,buffer,n);
			}

			if(n==-1){
				perror(argv[i]);
			}

			close(fd);
			
		}
	}
	
	exit(0); 
}
