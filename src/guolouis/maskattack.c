#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main( int argc, char *argv[])
{
	char *s = argv[1];
	argc=argc;
	unsigned long nombremdp=0;  // nombremdp = au nombre de combinaison crées
	int i = 0;
	int number = 0; // number = nombre de '%' donc au nombre de caractere qu'il va falloir tourner
	int len = strlen(s); // len de l'argument d'entrée
	for ( ; s[i] != '\0' ; i++ ) // on fait la boucle de number 
	{	

		if ( s[i] == '%' )
		{	
			number++;
		}
	}
	char *mdp = calloc(1, len+1); // on initialise la chaine de char à 0   
	int interm=0;
	int tab[number]; // tab = contenant l'indice de mdp ' a probleme '
	int tam = 0; // variable intermediaire
	int tab1[number]; // tab1 contient le type : majuscule/minuscule/char spé/chiffre
	// 0 = chiffre || 1 = minuscule || 2 = majuscule || 3 = char spé
	int air = 0; // variable intermediaire 
	int tabmin[number]; // tabmin contient la 1ere valeur ascii pour le type indice i
	int tabmax[number];// same pour la derniere valeur ascii 
	for (i =0 ; s[i]; )   // boucle for pour mettre l'argument dans mdp sans les %
	{						
		if ( s[i] != '%' )
		{
			mdp[interm]=s[i];
			interm++;
			i++;
		}
		else 
		{	

			i++;
			tab[tam]=interm;
			if ( s[i]=='1') 		// 1 = alphabet minuscule
			{
				tab1[tam]=1;
				tabmin[air]=97;      
				tabmax[air]=122;
				
				air++;
				
			}
			if (s[i]=='0')			// 0 = chiffre
			{
				tab1[tam]=0;		
				tabmin[air]=48;
				tabmax[air]=57;
			
				air++;
	
			}
			if ( s[i]=='2')			// 2 = alphabet majuscule
			{
				tab1[tam]=2;
				tabmin[air]=65;	
				tabmax[air]=90; 
				air++;
			}
			if ( s[i]=='3')			// 3 = caractere spéciaux
			{
				tab1[tam]=3;
				tabmin[air]=32;
				tabmax[air]=126;
				air++;
			}
			tam++;	
		}
	}

	
	for ( i = 0; i < number ; i++ ) // boucle for pour initialiser les caracteres des 
	{								// positions voulues à leur tabmin respectifs 
		mdp[tab[i]]=tabmin[i];
	}
	int j = 0;
	int a = 0;
	while ( a == 0)
	{

		for ( j = tabmin[0] ; j <= tabmax[0] ; j++ ) // loop for in order to vary the first
		{											// caracter 
			if ( tab1[0] == 3 )	// this is because the ASCII of the special characters 
			{					// are not one after an other they are seperated
				if ( j == 48 )
				{ 
					j = 58 ;
				}
				if ( j == 65)
				{
					j = 91;
				}
				if ( j == 97)
				{ 
					j = 123;
				}
			}
			mdp[tab[0]] = j;  // this is where we CHECK the password, here we just printf
			nombremdp++;		// count number of passwords created
	//		printf("nombremdp = %lu\n", nombremdp);   */ here we print the number of passwords created /* 
			printf("%s\n" , mdp);
		}
			
		int b = 0;
		for ( i = 0; i < number ; i++ )
		{
			if ( mdp[tab[i]] == tabmax[i])
			{
				b++;
			}
		}
		if ( b == number )
		{
			a=1;
		}
		if ( number > 1 )
		{
			mdp[tab[1]]++;
		}
		for ( int y = 1; y < number && a==0 ; y++ )
		{	
			if ( tab1[y] == 3 && mdp[tab[y]] == 48 )
			{
				mdp[tab[y]] = 58;
			}
			if ( tab1[y] == 3 && mdp[tab[y]] == 65 )
			{
				mdp[tab[y]] = 91;
			}
			if ( tab1[y] == 3 && mdp[tab[y]] == 97 )
			{
				mdp[tab[y]] = 123;
			}


			if ( mdp[tab[y]] == tabmax[y]+1 )
			{
				mdp[tab[y]] = tabmin[y];
				if (tab[y+1])
				{
					mdp[tab[y+1]]++;
				}
			}
		}	
	}
	free(mdp);
}

