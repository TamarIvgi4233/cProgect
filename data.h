#include "Header.h"
#define MAX_LABEL_LEN 31/*אורך התווית*/
#define MAX_ARR_LEN 150/*אורך המערכים*/
#define WRD_ARR_BITS_LEN 12/*אורך המחרוזת של הביטים*/
#define TABLE_SIZE (sizeof(lookuptable)/sizeof(code))
#define MAX_LINE_LENGTH 80
#define IcStart 100

Cmd cmd_arr[MAX_ARR_LEN];
Data data_arr[MAX_ARR_LEN];

void data_input_arr(Wrd , int* );/*הכנסה למערך נתונים*/
void cmd_input_arr(Wrd , char , int* );
void init_cmd_array();
void init_data_array();
Wrd cmd_builder(opcode  , funct , addres_type , addres_type );
void updateAdrressData(int );
