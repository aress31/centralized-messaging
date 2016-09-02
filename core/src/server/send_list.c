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

#include "../../headers/server.h" 

void send_mails_list(char* login){
	/** Print out the mails in an user mail box.
	Arguments:
	login	--	login of a user
	*/
	int counter = 1;
	char bloc[200] = {0}, chemin[200]="../../../mailboxes/";
	struct dirent *lecture;
	struct stat infos;
	DIR *rep;

	strcat(chemin,login);

	if((rep = opendir(chemin)) == NULL){
		fprintf(stderr,"cannot open directory: %s\n", chemin);
		return;
	}

	chdir(chemin);

	// Send the email list present in the mailbox 
	while((lecture = readdir(rep)) != NULL){
		lstat(lecture->d_name,&infos);
		if(!S_ISDIR(infos.st_mode)){
			sprintf(bloc,"%d: %s\n",counter,lecture->d_name);
			Emission(bloc);
			counter++;
		}      
	}
	chdir("../../core/src/server");
	closedir(rep);
	
	// Send the END char
	Emission(" \n");
}


