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
#include <sys/stat.h>
#include <dirent.h> /* Pour l'utilisation des dossiers */
#include "../../headers/server.h" 

void read_mail(int num, char *login){
	/** Read an email given an email number and a mailbox name.
	Arguments:
	num		-- mail number
	login 	-- mailbox name
	*/
	int counter = 1;
	char phrase[4096] = {0}, chemin[200] = "../../../mailboxes/";
	struct dirent *lecture;
	struct stat infos;
	DIR *rep;
	FILE *f_in=NULL;
    
	// mailboxes/{login}
	strcat(chemin, login);       				

	if(!(rep = opendir(chemin))){
		fprintf(stderr, "cannot open directory: %s\n", chemin);
		return;
	}
	
	while((lecture = readdir(rep)) != NULL){
		lstat(lecture->d_name,&infos);
		
		if(S_ISDIR(infos.st_mode)){
			if(strcmp(".", lecture->d_name) == 0 || strcmp("..", lecture->d_name) == 0)
				continue;
		}

		if(num == counter){
			// mailboxes/{login}/   
			strcat(chemin, "/"); 
			// mailboxes/{login}/{nom_du_fichier}	
			strcat(chemin, lecture->d_name);

			f_in = fopen(chemin, "r");

			if (!f_in){
				printf("ERREUR fichier [read_mail]\n");
				break;
			}

			// Read an email char by char
			while(feof(f_in) != 1){
				fgets(phrase, 4096, f_in);
				sprintf(phrase, "%s\n", phrase);
				Emission(phrase);
			}
			
			// Send the END char
			Emission(" \n");
			fclose(f_in);
		}

		counter++;
	}
	chdir("../../core/src/server");
	call_getcwd();
	closedir(rep);
}
 
