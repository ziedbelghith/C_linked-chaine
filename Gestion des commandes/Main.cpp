#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<stdlib.h>
#include<dos.h>

/* Definition d'une liste chainée */
typedef struct element Element;
struct element
{
	char *produit;
	char *client;
	char *email;
	int qte = 0;
	double prixU = 0.000;
	struct element *next;
};
typedef Element* List;

/* Definition des variables globaux */
FILE *fp, *ft;
int i, n, ch, l, found;
List list = NULL;

/* Fonction d'ajout d'un élèment a la LC */
void ajouterElement(List &list, char *prod, char *clt, char *em, int qte, double prixU)
{
	List nouvelElement = (element*)malloc(sizeof(element));

	nouvelElement->produit = _strdup(prod);
	nouvelElement->client = _strdup(clt);
	nouvelElement->email = _strdup(em);
	nouvelElement->qte = qte;
	nouvelElement->prixU = prixU;
	nouvelElement->next = list;
	list = nouvelElement;

	nouvelElement = NULL;
}

/* Fonction d'affichage d'une LC */
void afficherListe(List list)
{
	List tmp = list;
	while (tmp != NULL)
	{
		printf("\n  Produit : ");
		printf("%s", tmp->produit);
		printf("\n  Client : ");
		printf("%s", tmp->client);
		printf("\n  Email : ");
		printf("%s", tmp->email);
		printf("\n  Quantite : ");
		printf("%d", tmp->qte);
		printf("\n  Prix Unitaire : ");
		printf("%.3lf", tmp->prixU);
		tmp = tmp->next;
		printf("\n");
	}
}

/* Fonction d'affichage d'une LC */
void afficherListeFidele(List list)
{
	List tmp = list;
	int i = 0, f = 0;
	char tmpp[500] = "";
	while (tmp != NULL)
	{
		if (i==0) {
			strcpy(tmpp, tmp->client);
		}
		if (i==4 && f == 0) {
			printf("\n  Client Fidele : ");
			printf("%s", tmpp);
			f = 1;
			printf("\n");
		}
		if (strcmp(tmpp, tmp->client)==0)
		{
			i++;
		}
		tmp = tmp->next;
	}
}

void acceuil() {
	system("cls");    /* ************ Menu ***********************  */
	printf("\n\t\t==============================================\n\t\t // Gestion des commandes d'une entreprise //\n\t\t==============================================\n\n");
	printf("\n  =======================\n\t>< MENU ><\n  =======================\n\n  [1] Ajouter une commande\n  [2] Afficher toutes les commandes\n  [3] Clients fideles\n  [0] Quitter\n\n  =======================\n\n");
}

/* Main */
int main()
{
	/* Definition des variables */
	char buf[2000];
	char *buf2 = "";
	char produit[500] = "";
	char client[500] = "";
	char email[500] = "";
	int qte = 0;
	double prixU = 9.999;
	char buffer[50] = "C:\\Users\\zied\\Desktop\\commandes.txt";
	int i = 0;
	int r = 0;
	int iter = 0;
main:
	acceuil();
	printf("[+] Choisir une option > ");
	scanf("%d", &ch);
	
	switch (ch)
	{
	case 0:
		printf("\n[?] Voulez vous quitter ?");
		break;
	/* ********************* Ajouter une commande ************  */
	case 1:
		system("cls");
		fp = fopen(buffer, "a");
		for (;;)
		{
			fflush(stdin);
			printf("\n[!] Pour quitter saisir un Espace puis Entrer\n");
			printf("\n  =====================================================\n\t\t>< Ajout de commandes ><\n  =====================================================\n\n  Produit : ");
			
			scanf("%[^\n]", produit);
			if (_stricmp(produit, "") == 0 || _stricmp(produit, " ") == 0)
				break;
			fflush(stdin);
			printf("  Client : ");
			scanf("%[^\n]", client);
			fflush(stdin);
			printf("  Email Client : ");
			scanf("%[^\n]", email);
			fflush(stdin);
			printf("  Quantite : ");
			scanf("%d", &qte);
			fflush(stdin);
			printf("  Prix Unitaire : ");
			scanf("%lf", &prixU);
			fflush(stdin);
			printf("\n");
			ajouterElement(list, produit, client, email, qte, prixU);
			fprintf(fp, "\nProduit\t: %s\nClient\t: %s\nEmail\t: %s\nQuantite\t: %d\nPrix Unitaire\t: %.3lf\n", list->produit, list->client, list->email, list->qte, list->prixU);
			system("cls");
		}
		fclose(fp);
		break;
		/* ********************* List des commandes *************************  */
	case 2:
		system("cls");
		printf("\n\t\t\t===========================\n\t\t\t // Liste des commandes //\n\t\t\t===========================\n\n");
		if ((fp = fopen(buffer, "r")) == NULL)
		{
			printf("Liste de commandes vide !");
			_getch();
			goto main;
		}
		fflush(stdin);
		found = 0;
		while (fgets(buf, 1000, fp) != NULL)
		{
			printf("  ");
			printf("%s", buf);
		}
		fclose(fp);
		break;
		/* ******************* Liste des clients fidele **********************  */
	case 3:
		system("cls");
		printf("\n\t\t\t================================\n\t\t\t // Liste des clients fideles //\n\t\t\t================================\n\n");
		if ((fp = fopen(buffer, "r")) == NULL)
		{
			printf("Liste des clients fideles est vide !");
			_getch();
			goto main;
		}
		fclose(fp);
		afficherListeFidele(list);
		break;
		/* ******************* Liste des clients fidele **********************  */
	case 4:
		system("cls");
		printf("\n\t\t\t================================\n\t\t\t // Liste des clients fideles //\n\t\t\t================================\n\n");
		
		list = NULL;
		if ((fp = fopen(buffer, "r")) == NULL)
		{
			printf("Liste des clients fideles est vide !");
			_getch();
			goto main;
		}
		strcpy(buf, "");
		while (fgets(buf, sizeof(buf), fp) != NULL){
			List node = (element*)malloc(sizeof(element));
			fscanf(fp, "\nProduit\t: %s\nClient\t: %s\nEmail\t: %s\nQuantite\t: %d\nPrix Unitaire\t: %.3lf\n", &produit, &client, &email, &qte, &prixU);
			node->produit = _strdup(produit);
			node->client = _strdup(client);
			node->email = _strdup(email);
			node->qte = qte;
			node->prixU = prixU;
			node->next = list;
			list = node;
			node = NULL;
		}
		fclose(fp);
		afficherListe(list);
		break;
	default:
		printf("Choix invalid !");
		break;
	}
	printf("\n\n[+] Saisir votre choix:\t\t[1] Menu\t[0] Quitter\n");
	printf(">_ ");
	scanf("%d", &ch);
	switch (ch)
	{
	case 1:
		goto main;
	case 0:
		break;
	default:
		printf("Choix invalid !");
		break;
	}
	return 0;
}
