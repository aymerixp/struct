/*
 * source : http://openclassrooms.com/courses/les-listes-doublement-chainees-en-langage-c
 */
#include <stdio.h>
#include "../libraire/libft.h"
/* Macro : supprimer le premier element de la liste */
#define dlist_remove_first(list) dlist_remove_id(list, 1)
/* Macro : supprimer le dernier element de la liste */
#define dlist_remove_last(list) dlist_remove_id(list, dlist_length(list))

typedef struct		s_node
{
	int data;
	struct s_node	*p_next;
	struct s_node	*p_prev;
}					t_node;

typedef struct		dlist
{
	size_t length;
	struct s_node	*p_tail;
	struct s_node	*p_head;
}					Dlist;

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
		t_node *p_new = malloc(sizeof *p_new); /* Creation d'un nouveau node */
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
		t_node *p_new = malloc(sizeof *p_new);
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
		t_node *p_temp = p_list->p_head;
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
					t_node *p_new = malloc(sizeof *p_new);
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
		t_node *p_temp = (*p_list)->p_head;
		while (p_temp != NULL)
		{
			t_node *p_del = p_temp;
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
		t_node *p_temp = p_list->p_head;
		while (p_temp != NULL)
		{
			ft_putnbr(p_temp->data);
			ft_putstr(" -> ");
			p_temp = p_temp->p_next;
		}
	}
	ft_putendl("NULL");
}

/* supprimer un element selon sa valeur  */
Dlist		*dlist_remove(Dlist *p_list, int data)
{
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->p_head;
		int found = 0;
		while (p_temp != NULL && !found)
		{
			if (p_temp->data == data)
			{
				if (p_temp->p_next == NULL)
				{
					p_list->p_tail = p_temp->p_prev;
					p_list->p_tail->p_next = NULL;
				}
				else if (p_temp->p_prev == NULL)
				{
					p_list->p_head = p_temp->p_next;
					p_list->p_head->p_prev = NULL;
				}
				else
				{
					p_temp->p_next->p_prev = p_temp->p_prev;
					p_temp->p_prev->p_next = p_temp->p_next;
				}
				free(p_temp);
				p_list->length--;
				found = 1;
			}
			else
			{
				p_temp = p_temp->p_next;
			}
		}
	}
	return (p_list);
}

/* supprimer un ensemble d'elements suivant une meme valeur */
Dlist		*dlist_remove_all(Dlist *p_list, int data)
{
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->p_head;
		while (p_temp != NULL)
		{
			if (p_temp->data == data)
			{
				if (p_temp->p_next == NULL)
				{
					p_list->p_tail = p_temp->p_prev;
					p_list->p_tail->p_next = NULL;
				}
				else if (p_temp->p_prev == NULL)
				{
					p_list->p_head = p_temp->p_next;
					p_list->p_head->p_prev = NULL;
				}
				else
				{
					p_temp->p_next->p_prev = p_temp->p_prev;
					p_temp->p_prev->p_next = p_temp->p_next;
				}
				free(p_temp);
				p_list->length--;
			}
			else
			{
				p_temp = p_temp->p_next;
			}
		}
	}
	return (p_list);
}

/* Supprimer un element selon sa position */
Dlist		*dlist_remove_id(Dlist *p_list, int position)
{
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->p_head;
		int i;
		i = 1;
		while (p_temp != NULL && i <= position)
		{
			if (position == i)
			{
				if (p_temp->p_next == NULL)
				{
					p_list->p_tail = p_temp->p_prev;
					p_list->p_tail->p_next = NULL;
				}
				else if (p_temp->p_prev == NULL)
				{
					p_list->p_head = p_temp->p_next;
					p_list->p_head->p_prev = NULL;
				}
				else
				{
					p_temp->p_next->p_prev = p_temp->p_prev;
					p_temp->p_prev->p_next = p_temp->p_next;
				}
				free(p_temp);
				p_list->length--;
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

/* Avoir la taille d'une liste chainee */
size_t		dlist_length(Dlist *p_list)
{
	size_t ret = 0;
	if (p_list != NULL)
	{
		ret = p_list->length;
	}
	return (ret);
}

/* Rechercher un element selon sa valeur */
Dlist		*dlist_find(Dlist *p_list, int data)
{
	Dlist *ret = NULL;
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->p_head;
		int found = 0;
		while (p_temp != NULL && !found)
		{
			if (p_temp->data == data)
			{
				ret = dlist_new();
				ret = dlist_append(ret, data);
				found = 1;
			}
			else
			{
				p_temp = p_temp->p_next;
			}
		}
	}
	return (ret);
}

/* Recherche un ensemble d'elements selon une meme valeur */
Dlist		*dlist_find_all(Dlist *p_list, int data)
{
	Dlist *ret = NULL;
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->p_head;
		while (p_temp != NULL)
		{
			if (p_temp->data == data)
			{
				if (ret == NULL)
				{
					ret = dlist_new();
				}
				ret = dlist_append(ret, data);
			}
			p_temp = p_temp->p_next;
		}
	}
	return (ret);
}

Dlist		*dlist_reverse(Dlist *p_list)
{
	Dlist *ret = NULL;
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->p_tail;
		ret = dlist_new();
		while (p_temp != NULL)
		{
			ret = dlist_append(ret, p_temp->data);
			p_temp = p_temp->p_prev;
		}
	}
	return (ret);
}

/* trie a bulle  */
int			croissant(int a, int b)
{
	return (a <= b);
}

t_node		*sort_list(t_node *lst, int (*cmp)(int, int))
{
	t_node		*tmp;
	tmp = lst;
	int stop;
	int tmp2;
	stop = 0;
	while (stop != 1)
	{
		stop = 1;
		tmp = lst;
		while (tmp->p_next)
		{
			if (!cmp(tmp->data, tmp->p_next->data))
			{
				tmp2 = tmp->data;
				tmp->data = tmp->p_next->data;
				tmp->p_next->data = tmp2;
				stop = 0;
			}
			tmp = tmp->p_next;
		}
		// print
	}
	return (lst);
}
/* fin trie a bulle  */

int			main(int ac, char **av)
{
	int i;
	i = 1;
	Dlist *list;
	list = dlist_new();
	if (ac == 1)
		ft_putendl("MANQUE LES ARGUNENTS");

	while (i < ac)
		list = dlist_prepend(list, ft_atoi(av[i++]));
	ft_putstr("premier :");
	ft_putnbr(list->p_head->data);
	ft_putchar('\n');
	ft_putstr("dernier :");
	ft_putnbr(list->p_tail->data);
	ft_putchar('\n');
	//ft_putnbr(ft_atoi(av[i++]));
	dlist_display(list);
	ft_putendl("sort list");
	list->p_head = sort_list(list->p_head, croissant);
	dlist_display(list);
	ft_putendl("reverse list");
	list = dlist_reverse(list);
	dlist_display(list);

}
