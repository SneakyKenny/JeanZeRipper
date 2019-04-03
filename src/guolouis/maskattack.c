#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	unsigned long nombremdp=0;
	char *s="%1%1";      // OK, ici c'était principalement des test 
//	int b = s[0];
//	printf("%s\n position ascii de s[0] =%d\n", s, b);
	int i = 0;
	int number = 0;
	int len = strlen(s);
//	printf("%d = len\n", len);
	for ( ; s[i] != '\0' ; i++ )	// OK, ici on compte le nombre de pourcentage ( donc de futur boucle)
	{	

		if ( s[i] == '%' )
		{	
			number++;
		}
	}
//	printf("%d = len-number", len-number);	
//	printf("%d = number\n", number);
	char *mdp = calloc(1, len+1);   
	int interm=0;
/*	printf("%s = au débuti\n", mdp);
	mdp[0]='0';
	printf("%s = 0 \n", mdp);
	mdp[1]='p';
	printf("%s = p\n", mdp);
	mdp[2]='2';
	mdp[3]='3';

	mdp[4]='n';
	printf("%s = n\n", mdp);
*/	
	int tab[number];
	int tam = 0;
//	int tab1[number];
	int air = 0;
	int tabmin[number];
	int tabmax[number];
	for (i =0 ; s[i]; )   // OK, ici tabmin c'est la valeur ASCII de 0 ou a soit 47 ou 97
	{							// pareil pour 
		if ( s[i] != '%' )
		{
			mdp[interm]=s[i];
			interm++;
//			printf("%s\n", mdp);
			i++;
		}
		else 
		{	

			i++;
			tab[tam]=interm;
//			printf("tam = %d\n", tam);
//			printf("tab[%d] = %d\n", tam , tab[tam]);
			if ( s[i]=='1')
			{
//				tab1[tam]=1;
				tabmin[air]=97;        // 1 = ALPHABET
				tabmax[air]=122;
				
//				printf("tabmin[%d]=%d\n", air, tabmin[air]);
				air++;
				
			}
			if (s[i]=='0')
			{
//				tab1[tam]=0;			// 0 = CHIFFRE
				tabmin[air]=48;
				tabmax[air]=57;
			
				air++;
	
			}
//			printf("tab1[%d]=%d\n", tam, tab1[tam]);
			tam++;	
		}
	}
//	printf("\n%s\n", mdp);
//	printf("tabmax[1]=%d\n", tabmax[1]);
/*	int max;
	if ( tab1[number-1] == 0)
	{
		max = 122;
		printf("max = %s \n", max);
	}
	if ( tab1[number-1] == 1)
	{
		max = 57;
	}
	printf("max = %s\n", max);
	

	for ( i = 0; mdp[i]; i++ )
	{ 
		printf("mdp[%d] = %d\n", i, mdp[i]);
	}
*/
	
	for ( i = 0; i < number ; i++ )
	{
		mdp[tab[i]]=tabmin[i];
	}
//	printf("save1\n");
	int j = 0;
//	printf("%s %d", s, i);
//	while ( mdp[tab[number-1]] != tabmax[number-1] )
	int a = 0;
/*	for ( i = 0; i < number; i++ )
	{
		printf("mdp[tab[%d]] = %d\n", i, mdp[tab[i]]);
		printf("tabmin[%d]=%d\n", i, tabmin[i]);
		printf("tabmax[%d]=%d\n", i, tabmax[i]);
	}
*/

	while ( a == 0)
	{

//		printf("bonjour");
		for ( j = tabmin[0] ; j <= tabmax[0]; j++ )
		{
			mdp[tab[0]] = j;
			nombremdp++;
			printf("nombremdp = %lu\n", nombremdp);
		//	printf("mdp[tab[0]] = %d = %d\n", mdp[tab[0]], j);
			printf("mdp = %s\n" , mdp);
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
		mdp[tab[1]]++;
		for ( int y = 1; y < number && a==0 ; y++ )
		{	
//			printf("jsuisla");
	//		if ( mdp[tab[y]] == tabmax[y] && mdp[tab[number-1]]!=tabmax[number-1] )
			if ( mdp[tab[y]] == tabmax[y]+1 )
			{
				mdp[tab[y]] = tabmin[y];
//				printf("le mdp = %s\n", mdp);
				if (tab[y+1])
				{
					mdp[tab[y+1]]++;
//					printf("LE mdp = %s\n", mdp);
				}
			}
		}
	}

	

/*	d[0] = c;
	d[1]=c;
	printf("%s\n %d\n ", d, c);
	d[0] = c+1;
	printf("save2");
	printf("%s\n", d);
	for ( int i = 0; i < 6 ; i++ )
	{
		printf("save3\n");
		d[0]=  i;
		printf("save4\n");
		printf("%s  %d \n ", d, i);
	}
*/
	free(mdp);
}

