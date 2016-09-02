#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/client.h"

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * \brief Client de Messagerie.						     							   		*
 * 										      										   		*
 * Ce programme est un client de messagerie permettant de :									*
 *									      	     								       		*
 * 			1-Création de comptes/Connexion à des comptes pré-existants 					*
 * 			2-Envoie de Mails						     					           		*
 * 			3-Consultation de sa boite mail	      									   		*
 * 				1-Lecture des Mails													   		*
 *				2-Suppression des Mails												   		*
 *																					   		*
 * L'affichage est réalisé en mode console. Ce logiciel libre de droit   					*
 * a été développé par A.Teyar, S.Delay et Y.Lachkar.										*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
**/

int main() {

	int choice = 0, num_mail = 0, error_code = 1, number = 0;
	char* response = NULL;
	char request[51232]={0};
	
		if(Initialisation("localhost") != 1) {
			printf("Erreur d'Initialisation\n");
			return 1;
		}

		else {			
			// Print the authentication menu 
			do { 
				label:
				choice = authentication_menu();

				// If "1. Log In" 
				if(choice == 1){
					identification_menu(request);
					printf("\n\n");
					
					Emission(request);

					response = Reception();

					if (response != NULL) 
						error_code=atoi(response);
			
					if(error_code==4)
						printf("\nWrong identifiants, try again ;)\n\n");
				}

				// If "2. Register" 
				if(choice == 2){
					registration_menu(request);
					printf("\n");
					
					Emission(request);
					
					response = Reception();
					error_code=atoi(response);
					
					if(error_code == 2)
						printf("This login is already used, choose a new one");
					
					else if(error_code == EXIT_FAILURE)
						printf("A problem occured, creation failed");
					 
					else
						printf("User created");

					printf("\n\n");
				}

				// Quit the messaging client 
				if(choice == 3){
					exit(0);
				}
			} while(error_code!=0);

			// Print the messaging menu
			while(1) {
				choice=main_menu();
				
				// If "1. Send" 
				if(choice == 1){
					sending_menu(request);
					
					Emission(request);
					printf("\n");
					
					response = Reception();
					error_code=atoi(response);
					
					if(error_code == 6)
						printf("This destinator doesn't exist !\n\n");
				}

				// If "2. Consult" 
				if(choice == 2){
					Emission("LIST \n");
					
					system("clear");
					
					// Print the mail list in the mailbox
					do {
						response = Reception();
						printf("%s", response);
					} while(strncmp(response, " ", 1) != 0);

					choice=consultation_menu();	

					// Read an email
					if(choice == 1) {
						printf("Which mail do you want to read: ");
						scanf("%d", &num_mail);
						
						// Clear the buffer
						while(getchar()!='\n');

						sprintf(request, "GET %d\n", num_mail);
						
						Emission(request);
					
						response = Reception();
						error_code=atoi(response);
						
						if(error_code == 7){
						      printf("This e-mail doesn't exist !\n\n");
						}

						else{

						    system("clear");
				    
						    // Print the email in the terminal
						    do {
							    response = Reception();
							    printf("%s", response);
						    } while(strncmp(response, " ", 1) != 0);
						}
					}
				
					// Delete an email 
					if(choice == 2) {
							printf("Which mail do you want to delete: ");
							scanf("%d", &num_mail);
							
							// Clear the buffer
							while(getchar()!='\n');

							sprintf(request, "DEL %d\n", num_mail);
							
							Emission(request);
							
							printf("\n");
					
							response = Reception();
							error_code= atoi(response);

							if(error_code == 8){
							      printf("This e-mail doesn't exist !\n\n");
							}
							else{
							      system("clear");
							}
					}

					// Back to the previous menu
					if(choice == 3){
						system("clear");
						continue;
					}

					// Back to the authenticate menu
					if(choice == 4){
						system("clear");
						goto label;
					}
				}

				// If "3. How Many" 
				if(choice == 3){
					system("clear");
					
					Emission("HMANY\n");

					response = Reception();

					if (response != NULL) {
						number=atoi(response);
						printf("Vous avez %d mail(s)\n\n\n", number);
					}
				}
			
				// Back to the authenticate menu
				if(choice == 4){
					system("clear");
					goto label;
				}
			}
			Terminaison();
		}
	return 0;
}

