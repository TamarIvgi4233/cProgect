#include "Header.h"
#define MAX_LABEL_LEN 31/*אורך התווית*/
#define MAX_ARR_LEN 150/*אורך המערכים*/
#define WRD_ARR_BITS_LEN 12/*אורך המחרוזת של הביטים*/
#define TABLE_SIZE (sizeof(lookuptable)/sizeof(code))
#define MAX_LINE_LENGTH 80
#define IcStart 100
lbl* label_search(char* );

void add_label(lbl* , char* , int* , symbol_type );
bool valid_label_name(char* labelName);
