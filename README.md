![centralized-messaging](images/centralized-messaging_logo.png)
# centralized-messaging
Centralized messaging system. 

## Installation
1. Set-up the network:  the *IP address* parameter (line 29 of the *Initialisation* method - *core/src/client/main.c*) has to manually be changed with the IP address of the machine running the server. 

2. Compile the client and server programs - run the following command within the programs folder:	
	
		$ make
		
3. Clean the the programs folder (remove the .o and intermediate files) - run the following command within the programs folder:

		$ make clean
		
## Usage
To run the server:
	
		$ ./server

To run the client:

		$ ./client

## Project information
This software was developed in the context of a group university project in January 2013.	
