#pragma once
#define MAX_LABEL_LEN 31/*אורך התווית*/
#define MAX_ARR_LEN 150/*אורך המערכים*/
#define WRD_ARR_BITS_LEN 12/*אורך המחרוזת של הביטים*/
#define TABLE_SIZE (sizeof(lookuptable)/sizeof(code))
typedef struct Label {
	char* symbole;
	char* address;
	symbol_type attribute;
	struct Label* next;
}lbl;
lbl* label_search( char* str)
{
	lbl* tmp;
	tmp = NULL;/******/
	while (tmp != NULL)
	{
		if (!strcmp(tmp->symbole, str))
			return tmp;
		else
			tmp = tmp->next;
	}
	return tmp;

}

typedef enum symbol_type {
	CODE=0,
	DATA,
	EXTERNAL,
	ENTRY
} symbol_type;

typedef enum opcodes {
	MOV_OP = 0,
	CMP_OP = 1,
	ADD_OP = 2,
	SUB_OP = 2,
	LEA_OP = 4,
	CLR_OP = 5,
	NOT_OP = 5,
	INC_OP = 5,
	DEC_OP = 5,
	JMP_OP = 9,
	BNE_OP = 9,
	JSR_OP = 9,
	RED_OP = 12,
	PRN_OP = 13,
	RTS_OP = 14,
	STOP_OP = 15,
	NONE_OP = -1
} opcode;
typedef enum funct {
	MOV_FUNCT = 0,
	CMP_FUNCT = 0,
	ADD_FUNCT = 10,
	SUB_FUNCT = 11,
	LEA_FUNCT = 0,
	CLR_FUNCT = 10,
	NOT_FUNCT = 11,
	INC_FUNCT = 12,
	DEC_FUNCT = 13,
	JMP_FUNCT = 10,
	BNE_FUNCT = 11,
	JSR_FUNCT = 12,
	RED_FUNCT = 0,
	PRN_FUNCT = 0,
	RTS_FUNCT = 0,
	STOP_FUNCT = 0

	
} funct;
typedef struct machine_word {
	
	short length;

	union word {
		Data* data;
		Wrd*  code;
	} word;
} machine_word;
typedef struct line {
	long line_number;
	char* file_name;
	char* info;
} line;

typedef enum addres_type {

	IMMEDIATE = 0,

	DIRECT = 1,

	RELATIVE = 2,

	REGISTER = 3,

	NONE_ADDR = -1
} addres_type;
typedef enum registers {
	R0 = 0,
	R1=1,
	R2=2,
	R3=3,
	R4=4,
	R5=5,
	R6=6,
	R7=7,
	NONE_REG = -1
} registers;
typedef enum instruction {
	DATA,
	EXTERN,
	ENTRY,
	STRING,
	NONE,
	ERROR_INST
} instruction;


typedef struct Word {
	char code[WRD_ARR_BITS_LEN];
}Wrd;
typedef struct Command {
	char* address;
	Wrd word;
	char tag;
}Cmd;
typedef struct Data {
	char* address;
	Wrd word;
}Data;
typedef struct { char* string; opcode op_table;funct funct_table; } code;
static code lookuptable[] = {
	{"mov", MOV_OP, MOV_FUNCT},{"cmp",CMP_OP, CMP_FUNCT},{"add",ADD_OP, ADD_FUNCT},{"sub",SUB_OP, SUB_FUNCT},{"lea",LEA_OP, LEA_FUNCT},
	{"clr",CLR_OP, CLR_FUNCT},{"not",NOT_OP, NOT_FUNCT},{"inc",INC_OP, INC_FUNCT},{"dec",DEC_OP, DEC_FUNCT},{"jmp",JMP_OP, JMP_FUNCT},
	{"bne",BNE_OP, BNE_FUNCT},{"jsr",JSR_OP, JSR_FUNCT},{"red",RED_OP, RED_FUNCT},{"prn",PRN_OP, PRN_FUNCT},{"rts",RTS_OP, RTS_FUNCT},
	{"stop",STOP_OP, STOP_FUNCT}
};
bool ifItInt(char* );


