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
bool is_instruction(char* str);
char* HexaNumber(char* number);
void AsciNumber(char* word, char asci);
void registerCod(char* code, registers* reg);
void numberCod(char* num, char* binary);
addres_type  addressing_type(char* num);
void op_funct_code(char* key, opcode* op, funct* fun);
void data_free_arr();
void cmd_free_arr();
void label_free(lbl *head);
char *intToString(int k);
bool checkingEntry(lbl *head);
bool checkingExternal(lbl *head);
void printing_to_files(char* fileName,lbl *head ,int ICF,int DCF);
