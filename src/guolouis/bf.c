#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*char is_mdp( char mdp, char hashedmdp )
{
	if ( hash(mdp) == hashedmdp )
	{
		return mdp;
	}
	return 0;
}
*/
int main( )
{	

	char *caractere = "abc"; 
	char *mdp = malloc(sizeof(char));
	mdp[0]=caractere[0];
	int len = 1;
	int choose_len = 10;
	int len_caract = strlen(caractere);

	while ( len < choose_len )
	{   

		mdp = realloc(mdp, len * sizeof(char));
		for ( int i = 0 ; i < len ; i++ )
		{
			mdp[i]=caractere[0];
		}
		int len2 = len;
		while ( len2 > 0 )
		{
			for ( int j = 0 ; j < len_caract ; j++)
			{
				mdp[len-1] = caractere[j];
				printf("%s\n", caractere);
				printf("%s\n", mdp);
				/*if ( is_mdp != 0 )
				{
					return is_mdp;
	
				}
				*/
			}
			for ( int k = 0; k < len-1 ; k++ )
			{
		 		if(	mdp[len-k] == caractere[len_caract]) 
				{
					mdp[len-k] = caractere[0];
					mdp[len-k-1] = mdp[len-k-1] + caractere[sizeof(char)];
					printf("ligne54");
				}
				continue;
			}
			len2--;
		}
		len++;
	}
	free(mdp);
}











/*
	while ( len < n )
	{	
		for ( ; i != '\0' ; i++ )
		{
			if ( mdp = argv[1])
			{
				return mdp;
			}
		}
		
		len++;
	}
	while ( len < n )
	{
		if ( mdp[len] != x )
		{
			i++;
		}
		if ( i > 256 )
		{
			len++;
			mdp[len]=mdp[i+1]++;
			i=0;
		}
		if ( mdp[i+1]==256 )
		{
			i=i+1;
		}
	for ( size_t j = 0; j < len ; j++ )
	{
		for ( i = 0; i < 256 ; i++ )
		{
			if ( mdp[j] == x )
			{ 
				return 0;
			}
		}
	} 
	len++;


	
	









	for ( size_t j = 0; j != '\0' ; j++ )
	{
		for ( i ; i < 100 ; i++ )
		{
			if ( hash(strcat(mot[i], caractere[j])) != argv[1])
			{		
	
	size_t i=0;
	size_t j=0;
	for ( hash(strcat(mot[i], caractere[j])) != argv[1] )
	{
		if ( j != '\0' )
		{	
			j++;
		}
		i++;
	}
		







void bruteforce(n, chara)
{
	char *abc = "abc"
	while (  *abc != n ) 
	{

*/	



