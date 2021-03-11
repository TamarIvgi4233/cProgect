#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
bool ifItInt(char* string)
{
	int i = 0;
	if (string[0] == '-' || string[0] == '+') string++; 
	for (; string[i]; i++)
		if (isdigit(string[i]))
		{
			return false;
		}
if(i > 0)return true;
else return false;
}
bool codeProcessing(line lineCode, int* IC, int i)
{
	int j;
	int operandsNum;
	char* operecion;
	opcode* op;
	funct* fun;
	addres_type src_address = IMMEDIATE;
	addres_type dest_address = IMMEDIATE;
	i = moveToNotWhiteSpace(lineCode, i);
	for (j = 0; lineCode.info[i] != '\n' && lineCode.info[i] != ' ' && lineCode.info[i] != '\t' && lineCode.info[i] != EOF && j < 6;j++)
	{
		operecion[j] = lineCode.info[i];
		i += 1;
	}
	operecion[j] = '\n';
	op_funct_code(operecion, op, fun);
	if (op == NONE_OP)
	{
		printf("Error In % s: % ld : ", lineCode.file_name, lineCode.line_number);
		printf("Unknown instruction word\n");
		return false;
	}
	operandsNum = countOperands(lineCode, i);
	if (!rightOperans(op, operandsNum))
	{
		printf("Error In % s: % ld : ", lineCode.file_name, lineCode.line_number);
		printf("invalid number of operands\n");
		return false;
	}
	if (operandsNum == 0)
	{
		
		Wrd newWord= cmd_builder( op, fun, src_address, dest_address);
		cmd_input_arr(newWord, 'A', IC);
	}
	if (operandsNum == 1)
	{
		i=moveToNotWhiteSpace(lineCode, i);
		dest_address = addressing_type(lineCode.info + i);
		Wrd newWord = cmd_builder(op, fun, src_address, dest_address);
		cmd_input_arr(newWord, 'A', IC);
		extraWord(lineCode, i, IC);
			
	}
	if (operandsNum == 2)
	{
		i=moveToNotWhiteSpace(lineCode, i);
		src_address = addressing_type(lineCode.info + i);		
		while (isspace(lineCode.info[j]) == 0)	j += 1;
		j=moveToNotWhiteSpace(lineCode, j);
		if (lineCode.info[j] == ',')j += 1;
		else return;
		j=moveToNotWhiteSpace(lineCode, j);
		dest_address = addressing_type(lineCode.info + j);
		Wrd newWord = cmd_builder(op, fun, src_address, dest_address);
		cmd_input_arr(newWord, 'A', IC);
		extraWord(lineCode, i, IC);
		extraWord(lineCode, j, IC);
		
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
bool rightOperans(opcode op, int number)
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
		return false;
	}
}
void extraWord(line lineCode, int i, int* IC)
{
	addres_type src_address = IMMEDIATE;
	addres_type dest_address = IMMEDIATE;
	dest_address = addressing_type(lineCode.info + i);
	
	if (dest_address == REGISTER)
	{
		register reg = 0;
		registerCod(lineCode.info + i, reg);
		Wrd newWord = cmd_builder(0,0, src_address, dest_address);
		cmd_input_arr(newWord, 'A', IC);
	}
	if (dest_address == DIRECT)
	{
		Wrd newWord = cmd_builder(0, 0, src_address, dest_address);
		cmd_input_arr(newWord, '?', IC);
	}
	if (dest_address == IMMEDIATE)
	{
		if (lineCode.info[i] == '-' || lineCode.info[i] == '+')i += 1;
		Wrd binary;
		numberCod(lineCode.info + i, binary);
		
		cmd_input_arr(binary, 'A', IC);

	}
	if (dest_address == RELATIVE)
	{
		Wrd newWord = cmd_builder(0, 0, src_address, dest_address);
		cmd_input_arr(newWord, '?', IC);
	}
