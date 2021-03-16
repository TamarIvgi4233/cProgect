#define MAX_LABEL_LEN 31/*אורך התווית*/
#define MAX_ARR_LEN 150/*אורך המערכים*/
#define WRD_ARR_BITS_LEN 12/*אורך המחרוזת של הביטים*/
#define TABLE_SIZE (sizeof(lookuptable)/sizeof(code))
#define MAX_LINE_LENGTH 80
#define IcStart 100
#include "Header.h"

bool ifItInt(char* );
int moveToNotWhiteSpace(line , int );
int countOperands(line , int );
bool rightOperans(opcode , int );
void extraWord(line , int , int* );
void bin(char* , int );
int binToDecimal(char* );