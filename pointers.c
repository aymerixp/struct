/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/01 22:00:40 by gwells            #+#    #+#             */
/*   Updated: 2015/01/01 23:59:33 by gwells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		*ma_fonction(int *k);
int		*ma_deuxieme_fonction(int **k);

int main()
{
	/*Un pointeur est un type special qui contient une adresse*/
	int *k;//Je declare un pointeur
	int a; //Je declare un int
	k = 0;// Je dis que mon pointeur pointe sur NULL
	/*Je peux faire pointer mon pointeur sur n'importe quelle autre adresse :*/
	k = 0x675005;
	/*Ou plus correctement*/
	k = &a; //l'esperluette me donne l'adresse de a.
	
	ma_fonction(&a);
	ma_deuxieme_fonction(&k);
	return (0);
}

/* ma_fonction prend en parametre un pointeur, le DEFERENCE pour modifier la valeur pointe c'est a dire la valeur de a */
int		*ma_fonction(int *k)
{
	*k = 4;
	return (k);
}

int		*ma_deuxieme_fonction(int **k)
{
	int a;
	
	a = 4;
	*k = &a; 
	printf("%i\n", **k);
	return (0);
}
