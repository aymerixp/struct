#include <stdlib.h>
#include <stdio.h>

typedef struct	file
{
	int donnee;
	struct file *suivant;
}				File;

// Implementation
void	file_enqueue(File **p_file, int donnee)
{
	File *p_nouveau = malloc(sizeof *p_nouveau);
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
			File *p_tmp = *p_file;
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

// Retrait d'un element
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

// Vidage de la file
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
		//printf("%i\n", temp->donnee);
		temp = temp->suivant;
	}
}

int		main(void)
{
	File *test;

	test = malloc (sizeof (File));
	if (test == NULL)
		printf("failed malloc\n");
	test[0].donnee = 1;
	//test[1].donnee = 40000;
	//test[0].suivant = &test[1];
	file_enqueue(&test, 5);
	D_printFile(test);

	return (0);
}
