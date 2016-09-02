#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/server.h"

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \brief Serveur de Messagerie.						       							*
 * 										      							 				*
 * Ce programme  est un serveur de messagerie traitant des								* 
 * requêtes de clients 																	*
 * et gérant/stockant les boites mails et les comptes utilisateurs 						*
 * (adresse mail) de chaque client.													    *
 *										       											*
 * L'affichage est réalisé en mode console. Ce logiciel libre de droit  			    *
 * a été développé par A.Teyar, S.Delay et Y.Lachkar.				       				*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
**/

int main(){
	int num = 0, num1 = 0, error_code=0, request_length=0;
	char login[1024]= {0}, login_dest[1024]= {0}, password[512]= {0}; 
	char object[4096]= {0}, message[51200]= {0};
	char *request=NULL, response[51232]={0};

	Initialisation();
	AttenteClient();

	while(1){
		// Receive a message sent by the client and store it 
		request = Reception();

		if(request != NULL){
			printf("I got: %s\n", request);
			request_length=strlen(request);


			// If it is a "CREATE " request
			if(strncmp(request, "CREATE ", 7)==0){
				// Extraction of the login, password in the CREATE request
				extract_login_password(request, request_length, login, password);
				// Creation of a new account 
				error_code = register_user(login, password);
				sprintf(response,"%d\n", error_code);
				Emission(response);
			}

			// If it is a "AUTHENTIFICATION "  request 
			if(strncmp(request, "AUTHENTIFICATION ", 17)==0){
				// extraction du login & du password de la requête AUTHENTIFICATION 
				extract_login_password(request, request_length, login, password);
				// vérification que les paramètres [login] & [password] sont corrects et renvoie d'un code de validité (0 ou 1) dans la variable error_code 
				error_code = authentication(login, password);
				// conversion d'une variable de type int vers un type char stocké dans la variable [response] 
				sprintf(response, "%d\n", error_code);
				// emission du code de validité 
				Emission(response);
			}

			// If it is a "HMANY " request
			if(strcmp(request, "HMANY\n")==0){
				num = count_mails(login);
				sprintf(response, "%d\n", num);
				Emission(response);
			}

			// If it is a "SEND " request
			if(strncmp(request, "SEND|", 5)==0){
				extract_mail_info(request, request_length, login_dest, object, message);
				fprintf(stderr,"%s\n", message);
				error_code = send_mail(login_dest, login, object, message);
				printf("%d", error_code);
				sprintf(response, "%d\n", error_code);
				Emission(response);
			}

			// If it is a "LIST " request
			if(strncmp(request, "LIST ", 5)==0) 
				send_mails_list(login);
			
			// If it is a "DEL " request
			if(strncmp(request, "DEL ", 4)==0){
				num = extract_mail_number(request, request_length);
				num1 = count_mails(login);
				if((num <= num1) && (num1 != 0))
				    	delete_mail(login, num);
				else
			    		error_code = 8;
				    
				sprintf(response, "%d\n", error_code);
				Emission(response);
			}

			// If it is a "GET " request
			if(strncmp(request, "GET ", 4)==0){
				num = extract_mail_number(request, request_length);
				num1 = count_mails(login);

				if((num <= num1) && (num1 != 0))
				    	read_mail(num, login);
				
				else
			    		error_code = 7;
				    
				sprintf(response, "%d\n", error_code);
				Emission(response);
			}	

			free(request);
		}
	}
	TerminaisonClient();

	return(EXIT_SUCCESS);;
}
