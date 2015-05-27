#include <stdio.h>

int		main()
{
	/*
	 * Bonjour Mosieur Wells, apres une premiere tentative de compilation a 
	 * l'ecole le compilateur m'a indique une erreur dans le printf car
	 * l'argument %i ne peut afficher les unsigned long
	 * et m'a dirige vers l'argument %lu ce qui donne le resultat suivant :
	 * int : 4
	 * long int : 8
	 * long long int : 8
	 *
	 * En esperant avoir repondu a votre requete
	 * */
	printf("int : %lu\n", sizeof(int));
	printf("long int : %lu\n", sizeof(long int));
	printf("long long int : %lu\n", sizeof(long long int));
	return (0);
}
