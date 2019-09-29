#include "../dummy.c"

union runtime__union {
	bool boolean;
	int number;
	char* string;
	double dval;
	uintptr_t deadbeef;
	void* ptr;
	}

enum runtime__type {boolean,number,string,dval,deadbeef,ptr}

struct runtime__arg {
runtime__union data;
runtime__type type;
}

struct runtime__instruction {
struct runtime__instruction *prev
struct runtime__instruction *next

runtime__OPCODES type

runtime__arg left
runtime__arg right
runtime__arg foo
runtime__arg bar
}

struct runtime__list {
struct runtime__list *prev;
struct runtime__list *next;
YYSTYPE data
}

enum runtime__OPCODES {OPCODE_FETCH,OPCODE_ASSIGN,OPCODE_VALUE,
OPCODE_CAST,OPCODE_DEREF,OPCODE_STRUCT,OPCODE_STRUCT_POINTER,
OPCODE_ARRAYSUB,OPCODE_EXPRESSION,OPCODE_FUNCTION,OPCODE_IF,OPCODE_IF_ELSE,
OPCODE_WHILE,OPCODE_UNTIL,OPCODE_FOREVER,OPCODE_FOR,OPCODE_FORNOT,
OPCODE_PRE_INCR,OPCODE_POST_INCR,OPCODE_PRE_DECR,OPCODE_POST_DECR,
OPCODE_ADD,OPCODE_SUB,OPCODE_MULT,OPCODE_DIV,OPCODE_MOD,OPCODE_LOGAND,
OPCODE_LOGOR,OPCODE_LOGNAND,OPCODE_LOGNOR,OPCODE_LOGXOR,OPCODE_IFF,
OPCODE_LOGNOT,OPCODE_AND,OPCODE_OR,OPCODE_NAND,OPCODE_NOR,OPCODE_XOR,
OPCODE_EQ,OPCODE_NOT,OPCODE_GT,OPCODE_GE,OPCODE_EQUAL,OPCODE_NE,OPCODE_LT,
OPCODE_LE,OPCODE_APPROX,OPCODE_EXP,OPCODE_TETRA,OPCODE_RETURN,OPCODE_BREAK,
OPCODE_NPR,OPCODE_NCR,OPCODE_FACT,OPCODE_ROLL}
/*each opcode defines what to do to the arguments*/

