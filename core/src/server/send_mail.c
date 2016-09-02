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

int send_mail(char* login_dest, char* login, char* object, char* message){
	/** Store a textfile (mail) to a mailbox name .
	Arguments:
	login_dest	--	receiver login name
	login		-- 	sender login name
	object 		-- 	object of the mail
	message		-- 	message of the mail
	Returns:
	Error code
	*/
	FILE *f_in = NULL;
	char title[4096] = {0}, chemin[200] = "../../../mailboxes/";

	strcpy(title, login);							
	strcat(title, " ");			
	strcat(title, object);											

	// Destination mailbox path
	strcat(chemin, login_dest);       	   		
	strcat(chemin, "/");  		
	strcat(chemin, title);  	   					 	

	// Creation of the email file
	f_in=fopen(chemin, "w");

	if (f_in==NULL){
		printf("ERREUR fichier [send_mail]\n");
		return 6;
	}


	fprintf(f_in,"From: %s\n", login);
	fprintf(f_in,"To: %s\n", login_dest);
	fprintf(f_in,"Object: %s\n\n", object);
	fprintf(f_in,"%s \n", message);

	fclose(f_in);

	return 0;
}
