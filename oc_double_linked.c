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
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct		s_dlist
{
	size_t length;
	struct s_node	*tail;
	struct s_node	*head;
}					t_dlist;

/* Allouer une nouvelle liste  */
t_dlist		*dlist_new(void)
{
	t_dlist *p_new = malloc(sizeof *p_new);
	if (p_new != NULL)
	{
		p_new->length = 0;
		p_new->head = NULL;
		p_new->tail = NULL;
	}
	return (p_new);
}

/* Ajout en fin de liste */
t_dlist		*dlist_append(t_dlist *p_list, int data)
{
	if (p_list != NULL) /* On verifie si notre liste a ete allouee */
	{
		t_node *p_new = malloc(sizeof *p_new); /* Creation d'un nouveau node */
		if (p_new != NULL)
		{
			p_new->data = data;
			p_new->next = NULL; /* On fait pointer next vers NULL  */
			if (p_list->tail == NULL) /* Cas ou notre liste est vide (pointeur vers la fin de liste a NULL) */
			{
				p_new->prev = NULL; /* On fait pointer prev vers NULL  */
				p_list->head = p_new; /* On fait pointer la tete de la liste vers le nouvel element */
				p_list->tail = p_new; /* On fait pointer la fin de la liste vers le nouvel element  */
			}
			else /* Cas ou des elements sont deja presents dans notre liste  */
			{
				p_list->tail->next = p_new; /* On relie le dernier element de la liste vers notre nouvel element (debut du chainage)  */
				p_new->prev = p_list->tail; /* On fait pointer prev vers le dernier element de la liste  */
				p_list->tail = p_new; /* On fait pointer la fin de liste vers notre nouvel element (fin du chainage : 3 etapes)  */
			}
			p_list->length++; /* Incrementation de la taille de la liste  */
		}
	}
	return (p_list); /* On retourne notre nouvelle liste  */
}

/* Ajout en debut de liste  */
t_dlist		*dlist_prepend(t_dlist *p_list, int data)
{
	if (p_list != NULL)
	{
		t_node *p_new = malloc(sizeof *p_new);
		if (p_new != NULL)
		{
			p_new->data = data;
			p_new->prev = NULL;
			if (p_list->tail == NULL)
			{
				p_new->next = NULL;
				p_list->head = p_new;
				p_list->tail = p_new;
			}
			else
			{
				/* Ce qui change : */
				p_list->head->prev = p_new;
				p_new->next = p_list->head;
				p_list->head = p_new;
			}
			p_list->length++;
		}
	}
	return (p_list);
}

/* Inserer un element */
t_dlist		*dlist_insert(t_dlist *p_list, int data, int position)
{
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->head;
		int i;
		i = 0;
		while (p_temp != NULL && i <= position)
		{
			if (position == i)
			{
				if (p_temp->next == NULL)
				{
					p_list = dlist_append(p_list, data);
				}
				else if (p_temp->prev == NULL)
				{
					p_list = dlist_prepend(p_list, data);
				}
				else
				{
					t_node *p_new = malloc(sizeof *p_new);
					if (p_new != NULL)
					{
						p_new->data = data;
						p_temp->next->prev = p_new;
						p_temp->prev->next = p_new;
						p_new->prev = p_temp->prev;
						p_new->next = p_temp;
						p_list->length++;
					}
				}
			}
			else
			{
				p_temp = p_temp->next;
			}
			i++;
		}
	}
	return (p_list);
}

/* Liberer une liste  */
void		dlist_delete(t_dlist **p_list)
{
	if (*p_list != NULL)
	{
		t_node *p_temp = (*p_list)->head;
		while (p_temp != NULL)
		{
			t_node *p_del = p_temp;
			p_temp = p_temp->next;
			free(p_del);
		}
		free (*p_list), *p_list = NULL;
	}
}

void		dlist_display(t_dlist *p_list)
{
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->head;
		while (p_temp != NULL)
		{
			ft_putnbr(p_temp->data);
			ft_putstr(" -> ");
			p_temp = p_temp->next;
		}
	}
	ft_putendl("NULL");
}

void		dlist_display_inversed(t_dlist *p_list)
{
	ft_putstr("NULL");
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->tail;
		while (p_temp != NULL)
		{
			ft_putstr(" <- ");
			ft_putnbr(p_temp->data);
			p_temp = p_temp->prev;
		}
	}
	ft_putchar('\n');
}

/* supprimer un element selon sa valeur  */
t_dlist		*dlist_remove(t_dlist *p_list, int data)
{
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->head;
		int found = 0;
		while (p_temp != NULL && !found)
		{
			if (p_temp->data == data)
			{
				if (p_temp->next == NULL)
				{
					p_list->tail = p_temp->prev;
					p_list->tail->next = NULL;
				}
				else if (p_temp->prev == NULL)
				{
					p_list->head = p_temp->next;
					p_list->head->prev = NULL;
				}
				else
				{
					p_temp->next->prev = p_temp->prev;
					p_temp->prev->next = p_temp->next;
				}
				free(p_temp);
				p_list->length--;
				found = 1;
			}
			else
			{
				p_temp = p_temp->next;
			}
		}
	}
	return (p_list);
}

/* supprimer un ensemble d'elements suivant une meme valeur */
t_dlist		*dlist_remove_all(t_dlist *p_list, int data)
{
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->head;
		while (p_temp != NULL)
		{
			if (p_temp->data == data)
			{
				if (p_temp->next == NULL)
				{
					p_list->tail = p_temp->prev;
					p_list->tail->next = NULL;
				}
				else if (p_temp->prev == NULL)
				{
					p_list->head = p_temp->next;
					p_list->head->prev = NULL;
				}
				else
				{
					p_temp->next->prev = p_temp->prev;
					p_temp->prev->next = p_temp->next;
				}
				free(p_temp);
				p_list->length--;
			}
			else
			{
				p_temp = p_temp->next;
			}
		}
	}
	return (p_list);
}

/* Supprimer un element selon sa position */
t_dlist		*dlist_remove_id(t_dlist *p_list, int position)
{
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->head;
		int i;
		i = 1;
		while (p_temp != NULL && i <= position)
		{
			if (position == i)
			{
				if (p_temp->next == NULL)
				{
					p_list->tail = p_temp->prev;
					p_list->tail->next = NULL;
				}
				else if (p_temp->prev == NULL)
				{
					p_list->head = p_temp->next;
					p_list->head->prev = NULL;
				}
				else
				{
					p_temp->next->prev = p_temp->prev;
					p_temp->prev->next = p_temp->next;
				}
				free(p_temp);
				p_list->length--;
			}
			else
			{
				p_temp = p_temp->next;
			}
			i++;
		}
	}
	return (p_list);
}

/* Avoir la taille d'une liste chainee */
size_t		dlist_length(t_dlist *p_list)
{
	size_t ret = 0;
	if (p_list != NULL)
	{
		ret = p_list->length;
	}
	return (ret);
}

/* Rechercher un node selon sa valeur */
t_node		*node_find(t_dlist *p_list, int data)
{
	t_node *ret = NULL;
	if (p_list != NULL)
	{
		t_node *p_tmp = p_list->head;
		int found = 0;
		while (p_tmp != NULL && !found)
		{
			if (p_tmp->data == data)
			{
				ret = p_tmp;
				found = 1;
			}
			else
			{
				p_tmp = p_tmp->next;
			}
		}
	}
	ft_putstr("j'ai trouve le node : ");
	ft_putnbr(ret->data);
	ft_putstr(" le node suivant est : ");
	if (ret->next != NULL)
		ft_putnbr(ret->next->data);
	else
		ft_putstr("NULL");
	ft_putstr(" le node precedent est : ");
	if (ret->prev != NULL)
		ft_putnbr(ret->prev->data);
	else
		ft_putstr("NULL");
	ft_putchar('\n');
	dlist_remove_id(p_list, data);
	return (ret);
}

/* Rechercher un element selon sa valeur */
t_dlist		*dlist_find(t_dlist *p_list, int data)
{
	t_dlist *ret = NULL;
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->head;
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
				p_temp = p_temp->next;
			}
		}
	}
	return (ret);
}

/* Recherche un ensemble d'elements selon une meme valeur */
t_dlist		*dlist_find_all(t_dlist *p_list, int data)
{
	t_dlist *ret = NULL;
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->head;
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
			p_temp = p_temp->next;
		}
	}
	return (ret);
}

t_dlist		*dlist_reverse(t_dlist *p_list)
{
	t_dlist *ret = NULL;
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->tail;
		ret = dlist_new();
		while (p_temp != NULL)
		{
			ret = dlist_append(ret, p_temp->data);
			p_temp = p_temp->prev;
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
		while (tmp->next)
		{
			if (!cmp(tmp->data, tmp->next->data))
			{
				tmp2 = tmp->data;
				tmp->data = tmp->next->data;
				tmp->next->data = tmp2;
				stop = 0;
			}
			tmp = tmp->next;
		}
		// print
	}
	return (lst);
}
/* fin trie a bulle  */

/* intervertit les 2 premiers elements au sommet de la pile a */
void		sa(t_dlist *p_list_a)
{
	t_dlist *tmp;
	tmp = p_list_a;
	int a;
	int b;
	a = p_list_a->tail->data;
	b = p_list_a->tail->prev->data;
	/* est ce que le premier est plus grand que le deuxieme de la liste ? */
	if (p_list_a->tail->data > p_list_a->tail->prev->data)
	{
		tmp->tail->data = b;
		tmp->tail->prev->data = a;
		//ft_putendl("sa");
		//ft_putstr("yes");
	}
	//ft_putnbr(tmp->tail->data);
}

/* prend le premier element au sommet de b et le met sur a */
void		pa(t_dlist *p_list_a, t_dlist *p_list_b)
{
	dlist_append(p_list_a, p_list_b->tail->data);
	dlist_remove_last(p_list_b);
}

/* prend le premier element au sommet de a et le met sur b */
void		pb(t_dlist *p_list_a, t_dlist *p_list_b)
{
	/* /!\ append ou prepend */
	//ft_putstr("start");
	//ft_putnbr(dlist_find(p_list_a, 1)->head->data);
	//ft_putstr("end");
	dlist_append(p_list_b, p_list_a->tail->data);
	node_find(p_list_a, p_list_a->tail->data);
	//dlist_remove_last(p_list_a);
}

void		test_pb_remove(t_dlist *p_list_a, t_dlist *p_list_b)
{
	dlist_append(p_list_b, p_list_a->tail->data);
	p_list_a->head = NULL;
	p_list_b->length--;
}

/* rotate a */
/* le dernier devient le premier */
t_dlist		*rotate(t_dlist *p_list)
{
	t_node *tmp;
	int data_head;
	data_head = p_list->head->data; // va devenir le next

	tmp = p_list->head;
	while (tmp->next != NULL)
	{
		tmp->data = tmp->next->data;
		tmp = tmp->next;
	}
	p_list->tail->data = data_head;
	return (p_list);
}

/* le premier devient le dernier */
t_dlist		*rotate_inverse(t_dlist *p_list)
{
	t_node *tmp;
	int data_tail;
	data_tail = p_list->tail->data;

	tmp = p_list->tail;
	while (tmp->prev != NULL)
	{
		tmp->data = tmp->prev->data;
		tmp = tmp->prev;
	}
	p_list->head->data = data_tail;
	return (p_list);
}

void		push_swap(t_dlist *p_list_a, t_dlist *p_list_b)
{
	if (p_list_a->head->data > p_list_b->head->data)
		ft_putstr("le head de a est plus grand que le head de b");
	else
		ft_putstr("non");
}

// attendu : sa pb pb pb sa pa pa pa
int			main(int ac, char **av)
{
	int i;
	i = 1;
	t_dlist *list_a;
	list_a = dlist_new();
	t_dlist *list_b;
	list_b = dlist_new();
	if (ac == 1)
		ft_putendl("MANQUE LES ARGUMENTS");

	while (i < ac)
		list_a = dlist_prepend(list_a, ft_atoi(av[i++]));

	ft_putchar('\n');
	ft_putstr("liste a : ");
	dlist_display(list_a);
	ft_putstr("liste b : ");
	dlist_display(list_b);

	sa(list_a);
	pb(list_a, list_b);
	pb(list_a, list_b);
	pb(list_a, list_b);
	rotate_inverse(list_a); // ra
	rotate_inverse(list_b); // rb
	rotate(list_a); // rra
	rotate(list_b); // rrb
	sa(list_a);
	pb(list_b, list_a);
	pb(list_b, list_a);
	//pb(list_b, list_a);
	//test_pb_remove(list_b, list_a);
	//test_pb_remove(list_b, list_a);
	//pb(list_b, list_a);
	/* attention a pb quand il n'en reste qu'un a copier */
	ft_putchar('\n');
	ft_putstr("length list b : ");
	ft_putnbr(list_b->length);

	ft_putchar('\n');
	ft_putstr("liste a : ");
	dlist_display(list_a);
	ft_putstr("liste b : ");
	dlist_display(list_b);
	/* je peux creer la liste b dans la premiere fonction appele ? comme ca je n'en envoie qu'une ? */
}
