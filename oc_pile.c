/*
 * file = queue
 */
#include <stdlib.h>

typedef struct	pile
{
	int			donnee;
	struct pile *precedent;
}				Pile;

// Ajout d'un nouvel element
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

// Retrait d'un element
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

// Vidage de la pile
void	pile_clear(Pile **p_pile)
{
	while (*p_pile != NULL)
	{
		pile_pop(p_pile);
	}
}

// Retourner la valeur du dernier element
int pile_peek(Pile *p_pile)
{
	int ret;
	ret = -1;
	if (p_pile != NULL)
	{
		ret = p_pile->donnee;
	}
	return (ret);
}

void	print_pile(Pile *pile)
{
	Pile *tmp;
	int i;

	i = 0;
	tmp = pile;
	while (tmp != NULL)
	{
		ft_putnbr(i++);
		ft_putstr(" : ");
		ft_putnbr(tmp->donnee);
		ft_putchar('\n');
		tmp = tmp->precedent;
	}
}

int		main(void)
{
	Pile *pointeur_pile;
	pointeur_pile = NULL;

	pile_push(&pointeur_pile, 40);
	pile_push(&pointeur_pile, 50);
	pile_push(&pointeur_pile, 60);
	pile_push(&pointeur_pile, 70);
	print_pile(pointeur_pile);

	return (0);
}
