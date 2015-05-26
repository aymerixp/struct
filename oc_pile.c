#include <stdlib.h>

typedef struct	pile
{
	int			donnee;
	struct pile *precedent;
}				Pile;

/*
** Ajout d'un nouvel element
*/

void pile_push(Pile **p_pile, int donnee)
{
	Pile *p_nouveau = malloc(sizeof *p_nouveau);
	if (p_nouveau != NULL)
	{
		p_nouveau->donnee = donnee;
		p_nouveau->precedent = *p_pile;
		*p_pile = p_nouveau;
	}
}

/*
** Retrait d'un element
*/

int pile_pop(Pile **p_pile)
{
	int ret;

	ret = -1;
	if (p_pile != NULL)
	{
		Pile *temporaire = (*p_pile)->precedent;
		ret = (*p_pile)->donnee;
		free(*p_pile);
		*p_pile = NULL;
		*p_pile = temporaire;
	}
	return (ret);
}

/*
** Vidage de la pile
*/

void	pile_clear(Pile **p_pile)
{
	while (*p_pile != NULL)
	{
		pile_pop(p_pile);
	}
}

/*
** Retourner la valeur du dernier element
*/

int		pile_peek(Pile *p_pile)
{
	int ret;

	ret = -1;
	if (p_pile != NULL)
		ret = p_pile->donnee;
	return (ret);
}

/*
** Ceci est le main.
** C'est un nom de fonction particulier qui signifie « principal »
** main est la fonction principale de votre programme, c'est 
** toujours par la fonction main que le programme commence.
*/

int		main(void)
{
	return (0);
}
