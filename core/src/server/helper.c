#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int count_mails(char *login){
	/** Count the number of mail in a mailbox.
	Arguments:
	login		--	login of a user
	Returns:
	Number of mails 
	*/
	int number = 0;
	char chemin[200] = "../../../mailboxes/";
	struct dirent *fichierlu = NULL; /* Déclaration d'un pointeur vers la structure dirent */
	DIR *rep_in = NULL;
	
	strcat(chemin,login);

	rep_in = opendir(chemin);

	if(rep_in==NULL){
		perror("ERREUR repertoire [hmany]\n");
		return 1;
	}
	
	// Count all the files in the folder
	while((fichierlu = readdir(rep_in)) != NULL){
		if(strcmp(fichierlu->d_name, ".") != 0 && strcmp(fichierlu->d_name, "..") != 0) 
			number++;                        
	}
	
	closedir(rep_in);

	return number;
}

void extract_mail_info(char *request, size_t request_length, char *login_dest, char *object, char *message){
	/** Extract the information in a request (receiver, object and message of a mail).
	Arguments:
	request				--	request
	request_length	--	request size
	login_dest			--	login of the receiver 
	object				--	object of the mail
	message			--	message of the mail
	*/
	int i = 0, j = 0, k = 0, l = 0;
	int a = 0, b = 0, c = 0;
  
	while(i<request_length){
		if(request[i]=='|')
			break;
	
		i++;
	}

	for(j=i+1; j<request_length; j++){
		if(request[j]=='|')
			break;
	
		login_dest[a]=request[j];
		a++;
	}

	login_dest[a] = '\0';

	for(k=j+1; k<request_length; k++){
		if(request[k]=='|')
			break;
	
		object[b]=request[k];
		b++;
	}

	object[b]= '\0';

	for(l=k+1; l<request_length; l++){
		message[c]=request[l];
		c++;
	}

	message[c] = '\0';
}

void extract_login_password(char *request, size_t request_length, char *login, char *password){
	/** Extract the login and password in a request (receiver, object and message of a mail).
	Arguments:
	request				--	request
	request_length	--	request size
	login					--	login to extract
	password			--	password to extract
	*/
	int i = 0, j = 0, k = 0;
	int a = 0, b = 0;
  
	while(i<request_length){
		if(request[i]==' ')
			break;
		
		i++;
	}

	for(j=i+1; j<request_length; j++){
		if(request[j]==' ')
			break;
		
		login[a]=request[j];
		a++;
	}
   
	login[a] = '\0';
	
	for(k=j+1; k<request_length; k++){
		if(request[k]==' ')
			break;
		
		password[b]=request[k];
		b++;
	}
	
	password[b]= '\0';
}

int extract_mail_number(char *request, size_t request_length) {
	/** Extract the mail number in a request (receiver, object and message of a mail).
	Arguments:
	request				--	request
	request_length	--	request size
	Returns:
	Number of mail
	*/
	int i = 0, j = 0, k = 0, num = 0;
    	char string[10]={0};

	while(i<request_length){
		if(request[i]==' ')
			break;
		
		i++;
	}

	for(j=i+1; j<request_length; j++){
		if(request[j]=='\0')
			break;
		
		string[k]=request[j];
		k++;
	}
	num = atoi(string);

	return num;
}
