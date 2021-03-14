#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

void main(void)
{
	
}
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
void add_label(lbl* head, char* str, int *DC, symbol_type type)
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
void init_cmd_array()
{
	int i, j;
	i = j = 0;
	Cmd cmd_arr[MAX_ARR_LEN];
	while (i < MAX_ARR_LEN)
	{
		cmd_arr[i].address = "0100";
		for (;j < WRD_ARR_BITS_LEN;j++)
			cmd_arr[i].word.code[j] = '0';
		cmd_arr[i].tag = 'A';
		i++;
	}
}
void init_data_array()
{
	int i, j;
	i = j = 0;
	Data data_arr[MAX_ARR_LEN];
	while (i < MAX_ARR_LEN)
	{
		data_arr[i].address = "0000";
		for (;j < WRD_ARR_BITS_LEN;j++)
			data_arr[i].word.code[j] = '0';
		i++;
	}
}
void bin(char* y, int x)/*converts to binary number */
{
	int i, j;
	j = strlen(y);
	i = 0;
	while (x > 0)
	{
		y[j - 1 - i] = (x % 2) + '0';
		x = x / 2;
		i++;
	}
}
Wrd cmd_builder( opcode  op , funct fun, addres_type src_address, addres_type dest_address)/*use "bin" to input the binary code in the array,look at the Wrd array in left to right** when we paste we need to paste in reverse*/
{
	int i;
	Wrd word;
	char* op_code;
	char* funct_b;
	char* srcAddress;
	char* destAddress;
	op_code = malloc(4 * sizeof(char));
	funct_b = malloc(4 * sizeof(char));
	srcAddress = malloc(2 * sizeof(char));
	destAddress = malloc(2 * sizeof(char));
	for (i = 0;i < 4;i++)
	{
		op_code[i] = '0';
		funct_b[i] = '0';
	}
	for (i = 0;i < 2;i++)
	{
		srcAddress[i] = '0';
		destAddress[i] = '0';
	}
	bin(op_code, op);
	bin(funct_b, fun);
	bin(srcAddress, src_address);
	bin(destAddress, dest_address);
	i = 0;
	while (i < 2)
	{
		word.code[i] = destAddress[i];
		word.code[i + 2] = srcAddress[i];
		i++;
	}
	i = 0;
	while (i < 4)
	{
		word.code[i + 4] = funct_b[i];
		word.code[i + 8] = op_code[i];
		i++;
	}

}
void HexaNumber (char * hexaNum )
{
	
	int i = 0;
	int j,count = 2;
	int sum = 0;
	static char* hex = "0123456789ABCDEF";
	while (count>=0)
	{
		for (j = 0;j < 4; j += 1)
		{
			if (hexaNum[i]=='1')
			{
				sum += (1 << j);

			}
			i += 1;
		}
		
		hexaNum[count] = hex[sum];
		sum = 0;
		
		count -= 1;
	}
	hexaNum[3] = '\0';
	
}
void AsciNumber(char* word, char asci)
{
	unsigned short int sing  = 1; 
	
	int j = WRD_ARR_BITS_LEN - 1;
	while (j>=0)
	{
		if (asci & sing)
		{
			word[j] = '1';
		}
		else
		{
			word[j] = '0';
		}
		sing <<= 1;
		j -= 1;
	}
	word[WRD_ARR_BITS_LEN] = '\0';
}
void registerCod(char * code, registers *reg)
{
	if (code[0]== 'r' && (code[1] >= 0 && code[1] <= 7)&& code[2]=='\n')
	{
		
		switch (code[1])
		{
		case '0':  *reg = R0;return;
		case '1':  *reg = R1; return;
		case '2':  *reg = R2; return;
		case '3':  *reg = R3; return;
		case '4':  *reg = R4; return;
		case '5':  *reg = R5; return;
		case '6':  *reg = R6; return;
		case '7':  *reg = R7; return;

		}

	}
	else
	{
		*reg = NONE_REG;
	}
}
void numberCod(char * num, char* binary)
{
	bool positve = true;
	int i = 1;
	unsigned int sum = 0;
	unsigned int number = 1;
	if (num[1] == '-')
	{
		i = 2;
		positve = false;
	}

	while (num[i] != '\0')
	{
		sum *= 10;
	
		sum +=( (int)(num[i])-48);
		
		i += 1;
	}
	
	i = 0;

	if (positve)
	{
		while (i < WRD_ARR_BITS_LEN)
		{
			if (number & sum)
			{
				binary[i] = '1';
			}
			else
			{
				binary[i] = '0';
			}
			number <<= 1;
			i += 1;
		}
	}
	else
	{
		while (i < WRD_ARR_BITS_LEN)
		{
			if (!positve)
			{
				if (number & sum)
				{
					binary[i] = '1';
					positve = true;
				}
				else
				{
					binary[i] = '0';
				}
			}
			else
			{
				if (number & sum)
				{
					binary[i] = '0';
					
				}
				else
				{
					binary[i] = '1';
				}
			}
			number <<= 1;
			i += 1;
		}

	}
	binary[WRD_ARR_BITS_LEN] = '\0';
}
addres_type  addressing_type(char * num  )
	{
		if (num[0] == '#' && is_int(num + 1))
		{
			return IMMEDIATE;
		}
		else if (label_search(num) != (lbl*)NULL)
		{
			return DIRECT;
		}
		else if (num[0] == '%'&& label_search(num+1)!=NULL)
		{
			return RELATIVE;
		}
		else if (num[0] == 'r' && num[1] >= '0' && num[1] <= '7' && num[2] == '\0')
		{
			return REGISTER;
		}
		else
		{
			return NONE_ADDR;
		}
	}
void op_funct_code(char* key, opcode * op, funct* fun )
{
	int i;
	*op = NONE_OP;
	*fun = STOP_FUNCT;
	for (i = 0; i < TABLE_SIZE; i++) {
		code sym = lookuptable[i];
		if (strcmp(sym.string, key) == 0)
		{
			*op = sym.op_table;
			*fun = sym.funct_table;
		}
	}
}
