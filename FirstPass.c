#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include"util.h"
#include "FirstPass.h"
bool proceesLine(line currLine, int* DC, int* IC, lbl* head)
{
	int i = 0;
	int j;
	bool addLabel = false;
	char* lableName = (char*) malloc(MAX_LINE_LENGTH * sizeof(char));
	char *temp= (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
	lbl* labelWord = ((lbl*)malloc(sizeof(lbl)));
	bool proceesSuccessful = true;
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
		strcpy(lableName, temp);
		lableName[j - 1] = '\n';
		labelWord = label_search(lableName);
		if (labelWord == NULL || labelWord->attribute == ENTRY|| valid_label_name(lableName))
		{
			addLabel = true;
			i = moveToNotWhiteSpace(currLine, i);
		}
		else
		{
			printf("Error In % s: % ld : ", currLine.file_name, currLine.line_number);
			printf(" Attempt to define an existing label \n");
			return false;
		}
	}
	else
	{
		i = moveToNotWhiteSpace(currLine, 0);

	}
	if (currLine.info[i] == '.')
	{
		i += 1;
		for (j = i;currLine.info[i] && currLine.info[i] != ' ' && currLine.info[i] != '\n' && currLine.info[i] != '\t' && currLine.info[i] != EOF;i += 1, j += 1)
		{
			temp[j] = currLine.info[i];
		}
		temp[j] = '\n';
		if (strcmp(temp, "data"))
		{
			if (addLabel)
			{
				add_label(head, lableName, DC, DATA);
			}
			proceesSuccessful = processData(currLine, i, DC);
		}
		else if (strcmp(temp, "string"))
		{
			if (addLabel)
			{
				add_label(head, lableName, DC, STRING);
			}
			proceesSuccessful = processString(currLine, i, DC);
		}
		else if (strcmp(temp, "entry"))
		{
			i = moveToNotWhiteSpace(currLine, i);
			while (currLine.info[i] && currLine.info[i] != ' ' && currLine.info[i] != '\n' && currLine.info[i] != '\t' && currLine.info[i] != EOF)
			{
				i += 1;
			}
			lableName[j] = '\n';
			i = moveToNotWhiteSpace(currLine, i);
			if (i < MAX_LINE_LENGTH)
			{
				printf("Error In % s: % ld : ", currLine.file_name, currLine.line_number);
				printf(" invalid entry label\n");
				return false;
			}
			else
			{
				return true;
			}

		}
		else if (strcmp(temp, "extren"))
		{
			i = moveToNotWhiteSpace(currLine, i);
			for (j = 0;currLine.info[i] && currLine.info[i] != ' ' && currLine.info[i] != '\n' && currLine.info[i] != '\t' && currLine.info[i] != EOF;i += 1, j += 1)
			{
				lableName[j] = currLine.info[i];
			}
			lableName[j] = '\n';
			add_label(head, lableName, 0, EXTERN);


		}
	}
	else
	{
		if (addLabel)
		{
			head = add_label(head, lableName, IC, CODE);
		}
		return codeProcessing(currLine, i, IC);
	}

}
bool processString(line lineString, int i, int* DC)
{
	int j;
	char temp[MAX_LINE_LENGTH];
	char* endQuotationMarks;
	i = moveToNotWhiteSpace(lineString, i);
	if (lineString.info[i] != '"')
	{
		printf("Error In % s: % ld : ", lineString.file_name, lineString.line_number);
		printf("Missing opening quote of string\n");
		return false;

	}
	endQuotationMarks = strrchr(lineString.info, '"');
	if (endQuotationMarks == &lineString.info[i])
	{

		printf("Error In % s: % ld : ", lineString.file_name, lineString.line_number);
		printf("Missing closing quote of string\n");
		return false;
	}
	else
	{


		for (j = 0;lineString.info[i] && lineString.info[i] != EOF && lineString.info[i] != '\n' && lineString.info[i] != '"';i += 1, j += 1)
		{
			temp[j] = lineString.info[i];
		}

		temp[j] = '\0';

		i += 1;
		for (j = 0;temp[j] != EOF && temp[j] != '\0';j += 1)
		{
			Wrd  wordChar;
			AsciNumber(wordChar.code, temp[j]);
			data_input_arr(wordChar, DC);
		}


	}

	return true;
}
bool dataProcessing(line lineData, int* DC, int i)
{
	instruction instruc;
	int j;
	char temp[MAX_LINE_LENGTH];
	i = moveToNotWhiteSpace(lineData, i);
	if (lineData.info[i] != '.')
	{

		instruc = NONE;
	}
	else i += 1;
	for (j = 0;lineData.info[i] && lineData.info[i] != ' ' && lineData.info[i] != '\n' && lineData.info[i] != '\t';i += 1, j += 1)
	{
		temp[j] = lineData.info[i];
	}
	temp[j] = '\n';
	if (strcmp(temp, "data"))
		return processString(lineData, i, DC);
	if (strcmp(temp, "string"))
		return processString(lineData, i, DC);
	if (strcmp(temp, "entry"))
		instruc = ENTRY;
	if (strcmp(temp, "extern"))
		instruc = EXTERN;
	else  instruc = ERROR_INST;


}
bool processData(line lineData, int i, int* DC)
{
	int j;
	char temp[MAX_LINE_LENGTH];

	i = moveToNotWhiteSpace(lineData, i);
	while (lineData.info[i] && lineData.info[i] != ' ' && lineData.info[i] != '\n' && lineData.info[i] != '\t')
	{
		for (j = 0;lineData.info[i] && lineData.info[i] != ' ' && lineData.info[i] != '\n' && lineData.info[i] != '\t' && lineData.info[i] != ',';i += 1, j += 1)
		{
			temp[j] = lineData.info[i];
		}
		if (ifItInt(temp) == false)
		{
			printf("Error In % s: % ld : ", lineData.file_name, lineData.line_number);
			printf("Expected integer for .data instruction\n");
			return false;

		}
		if (ifItInt(temp) == true)
		{
			Wrd number;
			numberCod(temp, number.code);
			data_input_arr(number, DC);
		}
		i = moveToNotWhiteSpace(lineData, i);
		if (lineData.info[i] == ',')i += 1;
		i = moveToNotWhiteSpace(lineData, i);
	}
	if (lineData.info[i - 1] == ',')
	{
		printf("Error In % s: % ld : ", lineData.file_name, lineData.line_number);
		printf("Expected integer for .data instruction\n");
		return false;
	}
	return true;
}
bool codeProcessing(line lineCode, int i, int* IC)
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

		Wrd *newWord = cmd_builder(op, fun, src_address, dest_address);
		cmd_input_arr(*newWord, 'A', IC);
	}
	if (operandsNum == 1)
	{
		i = moveToNotWhiteSpace(lineCode, i);
		dest_address = addressing_type(lineCode.info + i);
		Wrd *newWord = cmd_builder(op, fun, src_address, dest_address);
		cmd_input_arr(*newWord, 'A', IC);
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
		Wrd *newWord = cmd_builder(op, fun, src_address, dest_address);
		cmd_input_arr(*newWord, 'A', IC);
		extraWord(lineCode, i, IC);
		extraWord(lineCode, j, IC);

	}

}
