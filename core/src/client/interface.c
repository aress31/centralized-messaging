#include <stdio.h>  
#include <stdlib.h>
#include <string.h>

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \brief Menus.						     							  			 	*									      										
 * 																					  	*
 * Fonctions relatives à l'affichage des menus en mode console							*
 * et/ou à la création 	   																*
 * de certaines requetes clients.											 		   	*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
**/

int authentication_menu() {
	/** Display the authentification menu.
	Arguments:
	Returns:
	User choice
	*/
	int choice = 0;
      
		puts("Authentication:");
		puts("\t1. Log In");
		puts("\t2. Register");
		puts("\t3. Quit\n");
		
		printf("Enter your choice: ");
		scanf(" %d", &choice);
		
		// Clear the buffer
		while(getchar()!='\n');
	
	return(choice);
}

int main_menu() {
	/** Display the main menu.
	Arguments:
	Returns:
	User choice
	*/
	int choice = 0;	

		puts("Please choose one of the options below:");
		puts("\t1. Send an E-Mail");
		puts("\t2. Consult my MailBox");
		puts("\t3. How many E-Mails?");
		puts("\t4. Log Out\n");

		printf("Enter your choice: ");
		scanf(" %d", &choice);
	
		// Clear the buffer
		while(getchar()!='\n');
	
	return(choice);
}

int consultation_menu() {
	/** Display the consultation menu.
	Arguments:
	Returns:
	User choice
	*/
	int choice = 0;
	  
		puts("Consultation:");
		puts("\t1. Read");
		puts("\t2. Delete");
		puts("\t3. Back to previous menu");
		puts("\t4. Log Out\n");
		
		printf("Enter your choice: ");
		scanf(" %d", &choice);
		
		// Clear the buffer
		while(getchar()!='\n');
		
	return(choice);
}

void registration_menu(char* request) {
	/** Display the registration menu.
	*/
	char login[1024] = {0};
	char password[512] = {0};
      
		system("clear");
		
		printf("your @: ");
		scanf("%s", login);
		
		printf("your password: ");
		scanf("%s", password);
		
		sprintf(request, "CREATE %s %s\n", login, password);
		
		// Clear the buffer
		while(getchar()!='\n');
}

void identification_menu(char *request) {
	/** Display the identification menu.
	*/
	char login[1024] = {0};
	char password[512] = {0};
      
		system("clear");
		
		printf("your @: ");
		scanf("%s", login);
		
		printf("your password: ");
		scanf("%s", password);
		
		sprintf(request, "AUTHENTIFICATION %s %s\n", login, password);
		
		// Clear the buffer
		while(getchar()!='\n');
}

void sending_menu(char* request) {
  	/** Display the menu to create and send a mail.
	Arguments:
	request	--	the request to send an mail
	*/
	int length = 0;
	char login_dest[1024] = {0}, object[4096] = {0}, message[51200] = {0};
	
		system("clear");
		  
		printf("dest @: ");
		fgets(login_dest, 1024, stdin);
		length=strlen(login_dest);
		// Replace the '\n' end char by the '\0' char 
		login_dest[length-1] = '\0';
		
		printf("object: ");
		fgets(object, 4096, stdin);
		length=strlen(object);
		object[length-1] = '\0';
		
		printf("message: ");
		fgets(message, 51200, stdin);
		length=strlen(message);
		message[length-1] = '\0';

		sprintf(request, "SEND|%s|%s|%s\n", login_dest, object, message);
}



