
#define MAX_LABEL_LEN 31/*אורך התווית*/
#define MAX_ARR_LEN 150/*אורך המערכים*/
#define WRD_ARR_BITS_LEN 12/*אורך המחרוזת של הביטים*/
#define TABLE_SIZE (sizeof(lookuptable)/sizeof(code))
#define MAX_LINE_LENGTH 80
#define IcStart 100
#include "data.h"
#include "FirstPass.h"
#include "Header.h"
#include "label.h"
#include "ScondPass.h"
#include"util.h"
int main(int argc, char* argv[])
{
	int i;
	for (i = 1; i < argc; ++i)
	{
		
	fuleProcess(argv[i]);
	
	}
	return 0;

}
bool fileProcess(char* fileName)
{
	char temp;
	int IC = IcStart, DC = 0;
	int ICF, DCF;
	bool succes = true;
	lbl* head = NULL;
	FILE* currFile;
	char* fullFileName;
	line currLine;
	strcpy(fullFileName, fileName);
	strcat(fullFileName, ".as");
	currFile = fopen(fullFileName, "r");
	if (!currFile)
	{
		printf("Error: The file\"%s.as\" could not be opened for reading", fileName);
		free(fullFileName); 
		return false;
	}
	currLine.file_name = fullFileName;
	
	currLine.line_number = 0;
	while (fgets(currLine.info, MAX_LINE_LENGTH + 1, currFile))
	{
		currLine.line_number += 1;
		if (!strchr(currLine.info, '\n')&& (!feof(currFile)))
		{
			succes = false;
			while (temp != EOF && temp != '\n')
			{
				temp = fgetc(currFile);
			}
		}
		else
		{
			if (proceesLine(currLine, &DC, &IC, head) == false)
			{
				succes = false;
			}
		}
	}
	if (succes)
	{
		temp = ' ';
		ICF = IC;
		DCF = DC;
		IC = IcStart;
		DC = 0;
		updateAdrressData(ICF,DCF);
		updateAdrresslabel(ICF, head);

		rewind(currFile);
		while (fgets(currLine.info, MAX_LINE_LENGTH + 1, currFile))
		{
			currLine.line_number += 1;
			if (!strchr(currLine.info, '\n') && (!feof(currFile)))
			{
				succes = false;
				while (temp != EOF && temp != '\n')
				{
					temp = fgetc(currFile);
				}
			
			}
			else
			{
				if (secondProceesLine(currLine, &DC, &IC, head) == false)
				{
					succes = false;
				}
			}
		}

		
		if (succes) {
			
			/*succes = write_output; כאן צריך לשלוח ליצירת קטבי פלט*/
		}
	}


	return succes;
}
	

