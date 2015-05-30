/*
 * pile = stack
 */
#include <stdlib.h>
#include <stdio.h>

typedef struct	file
{
	int			donnee;
	struct file *suivant;
}				File;

/*
 * Implementation
 */
void	file_enqueue(File **p_file, int donnee)
{
	File *p_nouveau;
	p_nouveau = malloc(sizeof *p_nouveau);
	if (p_nouveau != NULL)
	{
		p_nouveau->suivant = NULL;
		p_nouveau->donnee = donnee;
		if (*p_file == NULL)
		{
			*p_file = p_nouveau;
		}
		else
		{
			File *p_tmp;
			p_tmp = *p_file;
			while (p_tmp->suivant != NULL)
			{
				p_tmp = p_tmp->suivant;
			}
			p_tmp->suivant = p_nouveau;
		}
	}
	else
		printf("fuckof\n");
}

/*
 * Retrait d'un element
 */
int		file_dequeue(File **p_file)
{
	int ret = -1;
	if (*p_file != NULL)
	{
		File *p_tmp = (*p_file)->suivant;
		ret = (*p_file)->donnee;
		free(*p_file);
		*p_file = NULL;
		*p_file = p_tmp;
	}
	return (ret);
}

/*
 * Vider la file
 */
void	file_clear(File **p_file)
{
	while (*p_file != NULL)
	{
		file_dequeue(p_file);
	}
}

void D_printFile(File *test)
{
	File *temp;

	temp = test;
	while (temp != NULL)
	{
		printf("%i\n", temp->donnee);
		temp = temp->suivant;
	}
}

int		main(void)
{
	File *pointeur_file;

	//pointeur_file = malloc(sizeof(File) * 2);
	pointeur_file = NULL;
	/*
	pointeur_file[0].donnee = 5;
	pointeur_file[0].suivant = &pointeur_file[1];
	pointeur_file[1].donnee = 594949;
	pointeur_file[1].suivant = NULL;
	*/

	file_enqueue(&pointeur_file, 7000);
	if (pointeur_file->donnee == file_dequeue(&pointeur_file))
		printf("pointeur file delete ok\n");

	file_enqueue(&pointeur_file, 7);
	file_enqueue(&pointeur_file, 799);
	file_enqueue(&pointeur_file, 667);

	D_printFile(pointeur_file);
	file_clear(&pointeur_file);

	return (0);
}
