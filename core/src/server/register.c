#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>  
#include <stdlib.h>
#include <string.h> 
#include <errno.h>

int register_user(char login[1024], char password[512]){
	/** Create a user and a mailbox with the given login and password.
	Arguments:
	login		--	login of a user
	password 	--	password of a user
	Returns:
	Error code
	*/
	int result = 0;
	char tmp[256] = {0},  url[200] = "../../../mailboxes/";
		
	// Mailbox creation
	strcat(url, login);

	result = mkdir(url, 0777);

	if(result == -1){
		if(errno == EEXIST){
			perror("This user still exists ");
			return 2;
		}
		else{
			perror("Folder creation failed ");
			return(EXIT_FAILURE);
		}
	}

	else 
		puts("Folder creation succeed");
	
	// Register the new user in the users-db file
	FILE *fp = fopen("../../../users-db.txt","a");

	if (fp==NULL){
		perror ("Error opening file");
		exit(EXIT_FAILURE);
	}

	else{
		sprintf(tmp, "%s %s", login, password);
		fprintf (fp, "%s", tmp); 
		fclose(fp);
		return(EXIT_SUCCESS);
	}
}

