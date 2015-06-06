#include <stdio.h>
#include "../libraire/libft.h"
/*
 * http://openclassrooms.com/courses/les-listes-doublement-chainees-en-langage-c
 */
struct node
{
	int data;
	struct node *p_next;
	struct node *p_prev;
};

typedef struct dlist
{
	size_t length;
	struct node *p_tail;
	struct node *p_head;
} Dlist;

/* Allouer une nouvelle liste  */
Dlist		*dlist_new(void)
{
	Dlist *p_new = malloc(sizeof *p_new);
	if (p_new != NULL)
	{
		p_new->length = 0;
		p_new->p_head = NULL;
		p_new->p_tail = NULL;
	}
	return (p_new);
}

/* Ajout en fin de liste */
Dlist		*dlist_append(Dlist *p_list, int data)
{
	if (p_list != NULL) /* On verifie si notre liste a ete allouee */
	{
		struct node *p_new = malloc(sizeof *p_new); /* Creation d'un nouveau node */
		if (p_new != NULL)
		{
			p_new->data = data;
			p_new->p_next = NULL; /* On fait pointer p_next vers NULL  */
			if (p_list->p_tail == NULL) /* Cas ou notre liste est vide (pointeur vers la fin de liste a NULL) */
			{
				p_new->p_prev = NULL; /* On fait pointer p_prev vers NULL  */
				p_list->p_head = p_new; /* On fait pointer la tete de la liste vers le nouvel element */
				p_list->p_tail = p_new; /* On fait pointer la fin de la liste vers le nouvel element  */
			}
			else /* Cas ou des elements sont deja presents dans notre liste  */
			{
				p_list->p_tail->p_next = p_new; /* On relie le dernier element de la liste vers notre nouvel element (debut du chainage)  */
				p_new->p_prev = p_list->p_tail; /* On fait pointer p_prev vers le dernier element de la liste  */
				p_list->p_tail = p_new; /* On fait pointer la fin de liste vers notre nouvel element (fin du chainage : 3 etapes)  */
			}
			p_list->length++; /* Incrementation de la taille de la liste  */
		}
	}
	return (p_list); /* On retourne notre nouvelle liste  */
}

/* Ajout en debut de liste  */
Dlist		*dlist_prepend(Dlist *p_list, int data)
{
	if (p_list != NULL)
	{
		struct node *p_new = malloc(sizeof *p_new);
		if (p_new != NULL)
		{
			p_new->data = data;
			p_new->p_prev = NULL;
			if (p_list->p_tail == NULL)
			{
				p_new->p_next = NULL;
				p_list->p_head = p_new;
				p_list->p_tail = p_new;
			}
			else
			{
				/* Ce qui change : */
				p_list->p_head->p_prev = p_new;
				p_new->p_next = p_list->p_head;
				p_list->p_head = p_new;
			}
			p_list->length++;
		}
	}
	return (p_list);
}

/* Inserer un element */
Dlist		*dlist_insert(Dlist *p_list, int data, int position)
{
	if (p_list != NULL)
	{
		struct node *p_temp = p_list->p_head;
		int i;
		i = 0;
		while (p_temp != NULL && i <= position)
		{
			if (position == i)
			{
				if (p_temp->p_next == NULL)
				{
					p_list = dlist_append(p_list, data);
				}
				else if (p_temp->p_prev == NULL)
				{
					p_list = dlist_prepend(p_list, data);
				}
				else
				{
					struct node *p_new = malloc(sizeof *p_new);
					if (p_new != NULL)
					{
						p_new->data = data;
						p_temp->p_next->p_prev = p_new;
						p_temp->p_prev->p_next = p_new;
						p_new->p_prev = p_temp->p_prev;
						p_new->p_next = p_temp;
						p_list->length++;
					}
				}
			}
			else
			{
				p_temp = p_temp->p_next;
			}
			i++;
		}
	}
	return (p_list);
}

/* Liberer une liste  */
void		dlist_delete(Dlist **p_list)
{
	if (*p_list != NULL)
	{
		struct node *p_temp = (*p_list)->p_head;
		while (p_temp != NULL)
		{
			struct node *p_del = p_temp;
			p_temp = p_temp->p_next;
			free(p_del);
		}
		free (*p_list), *p_list = NULL;
	}
}

void		dlist_display(Dlist *p_list)
{
	if (p_list != NULL)
	{
		struct node *p_temp = p_list->p_head;
		while (p_temp != NULL)
		{
			printf("%d -> ", p_temp->data);
			fflush(stdout);
			p_temp = p_temp->p_next;
		}
	}
	printf("NULL\n");
}

int		main(int ac, char **av)
{
	int i;
	i = 1;
	Dlist *list;
	list = dlist_new();
	if (ac == 1)
		ft_putendl("MANQUE LES ARGUNENTS");

	int j;
	j = 1;
	list = dlist_append(list, 1000);
	list = dlist_append(list, 1100);
	while (i < ac)
	{
		list = dlist_insert(list, ft_atoi(av[i++]), j);
		j++;
	}
	//ft_putnbr(ft_atoi(av[i++]));
	dlist_display(list);
}
