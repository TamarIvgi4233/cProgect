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