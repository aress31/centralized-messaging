#ifndef __SERVEUR_H__
#define __SERVEUR_H__

/* Initialisation.
 * Creation du serveur.
 * renvoie 1 si ça c'est bien passé 0 sinon
 */
int Initialisation();

/* Initialisation.
 * Creation du serveur en précisant le service ou numéro de port.
 * renvoie 1 si ça c'est bien passé 0 sinon
 */
int InitialisationAvecService(char *service);


/* Attends qu'un client se connecte.
 * renvoie 1 si ça c'est bien passé 0 sinon
 */
int AttenteClient();

/* Recoit un message envoye par le client.
 * retourne le message ou NULL en cas d'erreur.
 * Note : il faut liberer la memoire apres traitement.
 */
char *Reception();

/* Envoie un message au client.
 * Attention, le message doit etre termine par \n
 * renvoie 1 si ça c'est bien passé 0 sinon
 */
int Emission(char *message);

/* Recoit des donnees envoyees par le client.
 * renvoie le nombre d'octets reçus, 0 si la connexion est fermée,
 * un nombre négatif en cas d'erreur
 */
int ReceptionBinaire(char *donnees, size_t tailleMax);

/* Envoie des données au client en précisant leur taille.
 * renvoie le nombre d'octets envoyés, 0 si la connexion est fermée,
 * un nombre négatif en cas d'erreur
 */
int EmissionBinaire(char *donnees, size_t taille);


/* Ferme la connexion avec le client.
 */
void TerminaisonClient();

/* Arrete le serveur.
 */
void Terminaison();

/* Fonction permettant au serveur d'afficher la liste des mails prÈsents dans la boÓte aux lettres
 * du client de nom d'utilisateur login.
 */
void send_mails_list(char *login);

/* Fonction permettant au serveur de supprimer le mail de numero number, saisit par le client.
 */
void delete_mail(char *login, int number);

/* Pour l'utilisation des dossiers 
 * Envoyer au client le nombre de mails prÈsents dans sa boite mail.
 */
int count_mails(char *login);

/*CrÈer une Mailbox au login passÈ en paramËtre
 */
int register_user(char login[1024], char password[512]);

/* Verifie si le login/password saisit est correct*/
int authentication(char login[1024], char password[512]);

/* Envoyer au client le mail de numÈro [number_mail] au destinataire de login placÈ en paramËtre, consultation
 */
void read_mail(int number_mail, char* login);

/* Fonction qui stocke un mail dans le dossier Mailbox/login_dest.
 */ 
int send_mail(char* login_dest, char* login, char* object, char* message);

void extract_mail_info(char* request, size_t request_length, char* login_dest, char* object, char* message);

void extract_login_password(char* request, size_t request_length, char* login, char* password);

int extract_mail_number(char* request, size_t request_length);

#endif
