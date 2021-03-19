#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include "label.h"

lbl* label_search(lbl* head, char* str)
{
	lbl* tmp;
	tmp = head;
	while (tmp != NULL)
	{
		if (!strcmp(tmp->symbole, str))
			return tmp;
		else
			tmp = tmp->next;
	}
	return tmp;

}
lbl * add_label(lbl* head, char* str, int *DC, symbol_type type)
{
	lbl* tmp;
	char adr[4];
	adr[0] = '0' + ((*DC) / 1000);
	adr[1] = '0' + (((*DC) % 1000) / 100);
	adr[2] = '0' + (((*DC) % 100) / 10);
	adr[3] = '0' + ((*DC) % 10);
	(*DC) += 1;
	tmp = head;
	
	if(tmp==NULL)
	{
	    head=malloc(sizeof(lbl));
	    head->symbole = malloc(MAX_LABEL_LEN * sizeof(char));
	    head->address = malloc(4 * sizeof(char));
		strcpy(head->symbole, str);
		strcpy(head->address, adr);
		head->attribute = type;
		tmp=head->next;
	}
	else
	{
		while (tmp->next != NULL)
		    tmp = tmp->next;
		tmp->next =malloc(sizeof(lbl)); 
		tmp = tmp->next;
		tmp->symbole = malloc(MAX_LABEL_LEN * sizeof(char));
		tmp->address = malloc(4 * sizeof(char));
		strcpy(tmp->symbole, str);
		strcpy(tmp->address, adr);
		tmp->attribute = type;
		tmp=tmp->next;
	}
	return head;
}
bool valid_label_name(char* labelName)
{
	if( labelName[0] && strlen(labelName) <= 31 && isalpha(labelName[0]) )
	{
		int op, fun, reg;
		op_funct_code(labelName, &op, &fun);
		registerCod(labelName, &reg);
		if (op == NONE_OP || reg== NONE_REG ||!is_instruction(labelName)) return true;
	}
	return false;
}
