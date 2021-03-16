#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include "label.h"

lbl* label_search(char* str)
{
	lbl* tmp = (lbl*)malloc(sizeof(lbl));
	tmp = NULL;
	while (tmp != NULL)
	{
		if (!strcmp(tmp->symbole, str))
			return tmp;
		else
			tmp = tmp->next;
	}
	return tmp;
}

void add_label(lbl* head, char* str, int* DC, symbol_type type)
{
	lbl* tmp;
	char adr[4];
	adr[0] = '0' + ((*DC) / 1000);
	adr[1] = '0' + (((*DC) % 1000) / 100);
	adr[2] = '0' + (((*DC) % 100) / 10);
	adr[3] = '0' + ((*DC) % 10);
	(*DC) += 1;
	tmp = label_search(head, str);
	if (tmp == NULL)
	{
		tmp = head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(lbl));
		tmp = tmp->next;
		tmp->symbole = malloc(MAX_LABEL_LEN * sizeof(char));
		tmp->address = malloc(MAX_LABEL_LEN * sizeof(char));
		strcpy(tmp->symbole, str);
		strcpy(tmp->address, adr);
		tmp->attribute = type;
		tmp->next = NULL;
	}
}