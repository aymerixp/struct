/*
 * source :
 * http://openclassrooms.com/courses/les-listes-chainees-2
 * */
#include <stdlib.h>
#include <stdio.h>

#define ERREUR -1
typedef struct			s_element
{
	int					val;
	struct s_element	*next;
}						t_element;

// Est ce que la liste est vide ?
int estVide(t_element *liste)
{
	if (liste == NULL)
		return 1;
	else
		return 0;
}

// Ajouter en tete
t_element *ajouterEnTete(t_element *liste, int valeur)
{
	t_element *nouvelElement;
	if (!(nouvelElement = malloc(sizeof(t_element))))
		return (NULL);
	nouvelElement->val = valeur;
	nouvelElement->next = liste;

	return (nouvelElement);
}

// Ajouter en fin de liste
t_element *ajouterEnFin(t_element *liste, int valeur)
{
	t_element *nouvelElement;
	if (!(nouvelElement = malloc(sizeof(t_element))))
		return (NULL);
	nouvelElement->val = valeur;
	nouvelElement->next = NULL;
	if (liste == NULL)
	{
		return (nouvelElement);
	}
	else
	{
		t_element *temp;
		temp = liste;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = nouvelElement;
		return (liste);
	}
}

// Afficher Liste
void afficherListe(t_element *liste)
{
	t_element *tmp;
	tmp = liste;

	while (tmp != NULL)
	{
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
}

// Supprimer un element en tete
t_element *supprimerElementEnTete(t_element *liste)
{
	if (liste != NULL)
	{
		t_element *toReturn;
		toReturn = liste->next;
		free(liste);
		return (toReturn);
	}
	else
	{
		return (NULL);
	}
}

// Supprimer un element en fin de liste
t_element *supprimerElementEnFin(t_element *liste)
{
	if (liste == NULL)
		return (NULL);
	if (liste->next == NULL)
	{
		free(liste);
		return (NULL);
	}

	t_element *tmp;
	tmp = liste;
	t_element *ptmp;
	ptmp = liste;
	while (tmp->next != NULL)
	{
		ptmp = tmp;
		tmp = tmp->next;
	}
	ptmp->next = NULL;
	free(tmp);
	return (liste);
}

// Rechercher un element dans une liste
t_element *rechercherElement(t_element *liste, int valeur)
{
	t_element *tmp;
	tmp = liste;

	while (tmp != NULL)
	{
		if (tmp->val == valeur)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

// Compter le nombre d'occurences d'une valeur
int nombreOccurences(t_element *liste, int valeur)
{
	int i;
	i = 0;
	if (liste == NULL)
		return (0);

	while ((liste = rechercherElement(liste, valeur)) != NULL)
	{
		liste = liste->next;
		i++;
	}
	return (i);
}

// Recherche du i-eme element
t_element *element_i(t_element *liste, int indice)
{
	int i;
	i = 0;
	while (i < indice && liste != NULL)
	{
		liste = liste->next;
		i++;
	}

	if (liste == NULL)
		return (NULL);
	else
		return (liste);
}

// Recuperer la valeur d'un element
int valeur(t_element *liste)
{
	return ((liste == NULL) ? ERREUR : (liste->val));
}

// Compter le nombbre d'element d'une liste chainee
int nombreElement(t_element *liste)
{
	if (liste == NULL)
		return (0);
	return (nombreElement(liste->next) + 1);
}

// Effacer tous les element ayant une certaine valeur
t_element *supprimerElement(t_element *liste, int valeur)
{
	if (liste == NULL)
		return (NULL);

	if (liste->val == valeur)
	{
		t_element *tmp;
		tmp = liste->next;
		free(liste);
		tmp = supprimerElement(tmp, valeur);
		return (tmp);
	}
	else
	{
		liste->next = supprimerElement(liste->next, valeur);
		return (liste);
	}
}

// Effacer liste
t_element *effacerListe(t_element *liste)
{
	if (liste == NULL)
		return (NULL);
	else
	{
		t_element *tmp;
		tmp = liste->next;
		free(liste);
		return (effacerListe(tmp));
	}
}

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_element *ma_liste;
	ma_liste = NULL;

	int i;
	i = 1;
	while (i <= 10)
	{
		ma_liste = ajouterEnTete(ma_liste, i);
		ma_liste = ajouterEnFin(ma_liste, i);
		i++;
	}
	afficherListe(ma_liste);
	printf("\n");
	printf("%d", nombreElement(ma_liste));

	return (0);
}
