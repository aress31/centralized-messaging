#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>

void delete_mail(char* login, int number) {
	/** Delete a mail given a login and a mail number.
	Arguments:
	login		--	login of a user 
	number	--	mail number
	*/
	DIR *rep; 
	struct dirent *lecture;
	struct stat infos;
	char chemin[200]="../../../mailboxes/";
	int counter = 1;

	strcat(chemin,login);

	if((rep = opendir(chemin)) == NULL){
		fprintf(stderr,"cannot open directory: %s\n", login);
		return;
	}
	
	chdir(chemin);
	
	while((lecture = readdir(rep)) != NULL){
	
		lstat(lecture->d_name,&infos);
		
		if(S_ISDIR(infos.st_mode)){
			// Find a folder and ignoring . and ..
			if(strcmp(".",lecture->d_name) == 0 || strcmp("..",lecture->d_name) == 0)
				continue;
		}
		
		if(number == counter)
			remove(lecture->d_name);
		
		counter++;
	}    
	chdir("../../core/src/server");
	closedir(rep);
}
