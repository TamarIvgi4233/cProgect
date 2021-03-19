#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include "util.h"
int ifItInt(char* string)
{
	int i = 0;
	int bool=0;
	if (string[0] == '-' || string[0] == '+') string++; 
	for (; string[i]; i++)
		if (!isdigit(string[i]))
		{
			return 1;
		}
if(i > 0)return 0;
else return 1;
}
int moveToNotWhiteSpace(line l, int i)
{
	while (isspace(l.info[i])&&(i<80))i+=1;
	return i;
}
int countOperands(line l, int i)
{
	int count = 0;
	while (i<80)
	{
		while (isspace(l.info[i]) == 0)	i+= 1;
		count += 1;
		i = moveToNotWhiteSpace(l, i);
		if (l.info[i] == ',') i += 1;
		i = moveToNotWhiteSpace(l, i);
	}
	return count;
}
int rightOperans(opcode op, int number)
{
	if (op<5)
	{
		return(number == 2);
	}
	if (op < 14)
	{
		return(number == 1);
	}
	if (op < 16)
	{
		return (number == 0);
	}
	else
	{
		return 1;
	}
}
void extraWord(line lineCode, int i, int* IC)
{
	Wrd* newWord = (Wrd*)malloc(sizeof(Wrd));
	addres_type src_address = IMMEDIATE;
	addres_type dest_address = IMMEDIATE;
	dest_address = addressing_type(lineCode.info + i);
	
	if (dest_address == REGISTER)
	{
		register* reg = (int *) malloc (sizeof(int));
		registerCod(lineCode.info + i, reg);
		newWord = cmd_builder(0,0, src_address, dest_address);
		cmd_input_arr(*newWord, 'A', IC);
	}
	if (dest_address == DIRECT)
	{
		 newWord = cmd_builder(0, 0, src_address, dest_address);
		cmd_input_arr(*newWord, '?', IC);
	}
	if (dest_address == IMMEDIATE)
	{
		
		Wrd binary;
		numberCod(lineCode.info + i, binary.code);
		
		cmd_input_arr(binary, 'A', IC);

	}
	if (dest_address == RELATIVE)
	{
		 newWord = cmd_builder(0, 0, src_address, dest_address);
		cmd_input_arr(*newWord, '?', IC);
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
int binToDecimal(char* bin)
{
    int x = 0;
	int i = 0;
	while (i < 12)
	{
        x+=((bin[i]-'0')*pow(2,11-i));  
	    i++;
	}
    return x;
}
void HexaNumber(char* hexaNum)
{

	int i = 0;
	int j, count = 2;
	int sum = 0;
	static char* hex = "0123456789ABCDEF";
	while (count >= 0)
	{
		for (j = 0;j < 4; j += 1)
		{
			if (hexaNum[i] == '1')
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
	unsigned short int sing = 1;

	int j = WRD_ARR_BITS_LEN - 1;
	while (j >= 0)
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
void registerCod(char* code, registers* reg)
{
	int i = code[1] - '0' ;
	char c = code[2];
	if (code[0] == 'r' && ((code[1]-'0' )>= 0 && (code[1] - '0') <= 7) && code[2] == '\0')
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
void numberCod(char* num, char* binary)
{
	bool positve = true;
	int i = 1;
	unsigned int sum = 0;
	unsigned int number = 1;
	
	while (num[i] != '\0')
	{
		sum *= 10;

		sum += ((int)(num[i]) - 48);

		i += 1;
	}
	i = WRD_ARR_BITS_LEN - 1;
	if (positve)
	{
		while (i >=0)
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
			i -= 1;
		}
	}
	else
	{
		while (i >=0 )
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
			i -= 1;
		}

	}
	binary[WRD_ARR_BITS_LEN] = '\0';
}
addres_type  addressing_type(char* num)
{
	if (num[0] == '#' && is_int(num + 1))
	{
		return IMMEDIATE;
	}
	else if (label_search(num) != (lbl*)NULL)
	{
		return DIRECT;
	}
	else if (num[0] == '%' && label_search(num + 1) != NULL)
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
void op_funct_code(char* key, opcode* op, funct* fun)
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
void data_free_arr()
{
    int c=0;
    while(c<MAX_ARR_LEN)
    {
        free(data_arr[c].address);
        c++;
    }
}
void cmd_free_arr()
{
    int c=0;
    while(c<MAX_ARR_LEN)
    {
        free(cmd_arr[c].address);
        c++;
    }
}
void label_free(lbl *head)
{
    lbl *tmp;
    tmp=head;
    while(tmp!=NULL)
    {
        free(tmp->symbole);
        free(tmp->address);
        tmp=tmp->next;
    }
    free(head);
}
char *intToString(int k)
{
    char *x;
    int g;
    int count,i,num;
    char const digit[]="0123456789";
    count=0;
    g=k;
    while(g>0)
    {
        g=g/10;
        count++;
    }
    x=malloc(count* sizeof(char));
    for(i=0;i<count;i++)
    {
        num=k/pow(10,count-1-i);
        x[i]=digit[num%10];
    }
    return x;
}
int checkEntry(head)
{
    lbl *lblTmp;
    lblTmp=head;
    while(lblTmp!=NULL)
	    {
	     if(lblTmp.attribute==ENTRY)
	         return 1;//true
	     lblTmp=lblTmp->next;
	    }
	    return 0;//false;
}
int checkExternal(head)
{
    lbl *lblTmp;
    lblTmp=head;
    while(lblTmp!=NULL)
	    {
	     if(lblTmp.attribute==EXTERNAL)
	         return 1;//true
	     lblTmp=lblTmp->next;
	    }
	    return 0;//false;
}
bool is_instruction(char* str)
{
	if (strcmp(str, "data") || strcmp(str, "string") || strcmp(str, "extern") || strcmp(str, "entry"))
		return true;
	else return false;
}
