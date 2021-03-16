#include "Header.h"
#define MAX_LABEL_LEN 31/*אורך התווית*/
#define MAX_ARR_LEN 150/*אורך המערכים*/
#define WRD_ARR_BITS_LEN 12/*אורך המחרוזת של הביטים*/
#define TABLE_SIZE (sizeof(lookuptable)/sizeof(code))
#define MAX_LINE_LENGTH 80
#define IcStart 100
#include"util.h"
bool proceesLine(line , int* , int* , lbl* );
bool processString(line , int , int* );
bool dataProcessing(line, int* , int );
bool processData(line , int , int* );
bool codeProcessing(line , int , int* );