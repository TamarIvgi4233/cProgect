#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include"util.h"
#include "ScondPass.h"


bool SecondProceesLine(line currLine, int* DC, int* IC, lbl* head)
{
	int i = 0;
	int j;
	char temp[MAX_LINE_LENGTH];
	i = moveToNotWhiteSpace(currLine, i);
	if (i > MAX_LINE_LENGTH)
	{
		return true;
	}
	for (j = 0;currLine.info[i] && currLine.info[i] != ' ' && currLine.info[i] != '\n' && currLine.info[i] != '\t' && currLine.info[i] != EOF;i += 1, j += 1)
	{
		temp[j] = currLine.info[i];
	}
	if (temp[j - 1] == ':')
	{

		i = moveToNotWhiteSpace(currLine, i);


	}
	else
	{
		i = moveToNotWhiteSpace(currLine, 0);

	}
	if (currLine.info[i] == '.')
	{
		return true;
	}
	else
	{
		return codeProcessing(currLine, i, IC);
	}

}
bool SecondCodeProcessing(line lineCode, int i, int* IC)
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

		Wrd newWord = cmd_builder(op, fun, src_address, dest_address);
		cmd_input_arr(newWord, 'A', IC);
	}
	if (operandsNum == 1)
	{
		i = moveToNotWhiteSpace(lineCode, i);
		dest_address = addressing_type(lineCode.info + i);
		Wrd newWord = cmd_builder(op, fun, src_address, dest_address);
		cmd_input_arr(newWord, 'A', IC);
		extraWord(lineCode, i, IC);

	}
	if (operandsNum == 2)
	{
		i = moveToNotWhiteSpace(lineCode, i);
		src_address = addressing_type(lineCode.info + i);
		while (isspace(lineCode.info[j]) == 0)	j += 1;
		j = moveToNotWhiteSpace(lineCode, j);
		if (lineCode.info[j] == ',')j += 1;
		else return;
		j = moveToNotWhiteSpace(lineCode, j);
		dest_address = addressing_type(lineCode.info + j);
		Wrd newWord = cmd_builder(op, fun, src_address, dest_address);
		cmd_input_arr(newWord, 'A', IC);
		extraWord(lineCode, i, IC);
		extraWord(lineCode, j, IC);

	}

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