#include <stdio.h>  
#include <stdlib.h>
#include <string.h> 

int authentication(char login[1024], char password[512]) {
	/** Check if a password matches with a login and if the given login exists.
	Arguments:
	login			--	login of a user
	password	--	password of a user
	Returns:			
	Authentication code
	*/
   	char tmp[51232]={0};
	char authent[51232]="";
	int  boolean = 0;    

	FILE *fp=fopen("../../../users-db.txt","r");

	if(fp==NULL){
		perror ("Error opening file");
		return 1;
	}

	else{
		sprintf(authent, "%s %s", login, password);

		// We search the authent string in each lines of the users-db.txt
		while(fgets(tmp, sizeof(tmp), fp)!=NULL) {
			// If we find it
			if (strcmp(authent, tmp)==0) {
				boolean = 1;
				break;
			}
		}
		
		fclose(fp);

		// Error codes
		if (boolean == 1)
			return 0;

		else
			return 4;
	}
}
