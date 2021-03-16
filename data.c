#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include "data.h"


void data_input_arr(Wrd word_in, int* DC)/*הכנסה למערך נתונים*/
{

	strcpy(data_arr[(*DC)].word.code, word_in.code);
	data_arr[(*DC)].address[0] = '0' + ((*DC) / 1000);
	data_arr[(*DC)].address[1] = '0' + (((*DC) % 1000) / 100);
	data_arr[(*DC)].address[2] = '0' + (((*DC) % 100) / 10);
	data_arr[(*DC)].address[3] = '0' + ((*DC) % 10);
	(*DC) += 1;
}
void cmd_input_arr(Wrd word_in, char tag_in, int* IC)/*הכנסה למערך הוראות*/
{
	cmd_arr[(*IC)].word = word_in;
	cmd_arr[(*IC)].tag = tag_in;
	cmd_arr[(*IC)].address[0] = '0' + ((*IC) / 1000);
	cmd_arr[(*IC)].address[1] = '0' + (((*IC) % 1000) / 100);
	cmd_arr[(*IC)].address[2] = '0' + (((*IC) % 100) / 10);
	cmd_arr[(*IC)].address[3] = '0' + ((*IC) % 10);
	(*IC) += 1;
}
void init_cmd_array()
{
	int i, j;
	i = j = 0;
	while (i < MAX_ARR_LEN)
	{
	    cmd_arr[i].address=(char *)malloc(4*sizeof(char));
		cmd_arr[i].address="0100";
		for (j=0;j < WRD_ARR_BITS_LEN;j++)
			cmd_arr[i].word.code[j] = '0';
		cmd_arr[i].tag = 'A';
		i++;
	}
	
}

void init_data_array()
{
	int i, j;
	i = j = 0;
	while (i < MAX_ARR_LEN)
	{
	    data_arr[i].address=malloc(4*sizeof(char));
		data_arr[i].address = "0000";
		for (j=0;j < WRD_ARR_BITS_LEN;j++)
		    data_arr[i].word.code[j] = '0';
		i++;
	}
}
Wrd* cmd_builder( opcode  op , funct fun, addres_type src_address, addres_type dest_address)/*use "bin" to input the binary code in the array,look at the Wrd array in left to right** when we paste we need to paste in reverse*/
{
	int i;
	Wrd *word = (Wrd*) malloc(sizeof(Wrd));
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
		word->code[i] = destAddress[i];
		word->code[i + 2] = srcAddress[i];
		i++;
	}
	i = 0;
	while (i < 4)
	{
		word->code[i + 4] = funct_b[i];
		word->code[i + 8] = op_code[i];
		i++;
	}
	return word;
}
void updateAdrressData(int ICF)
{
	int i;
	int add = 0;
	char* temp = (char*)malloc(sizeof(char));
	for (i = 0;i < ICF - IcStart;i += 1)
	{
		add = binToDecimal(cmd_arr[i].address);
		bin(temp, i + add);
		strcpy(cmd_arr->address, temp);
	}
	free(temp);
}
