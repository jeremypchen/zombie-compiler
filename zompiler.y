%{
#include "node.h"
#include <iostream>
#include <string>
extern int yylex();
extern void yyerror(const char* s);

// Global for the main block
NBlock* g_MainBlock = nullptr;

// Disable the warnings that Bison creates
#pragma warning(disable: 4065)
%}

/* Add one union member for each Node* type */
%union {
    Node* node;
	NBlock* block;
	NStatement* statement;
	NNumeric* numeric;
	NBoolean* boolean;
	std::string* string;
	int token;
}

/* Terminal symbols */
%token <string> TINTEGER
%token <token> TLBRACE TRBRACE TSEMI TLPAREN TRPAREN TLBRACKET TRBRACKET TINCREMENT TDECREMENT TEQUALS
%token <token> TMAIN TROTATE TFORWARD TATTACK TRANGEDATTACK TSAVELOC TMEMORY
%token <token> TIF TELSE
%token <token> TISHUMAN TISZOMBIE TISPASSABLE TISRANDOM

/* Statements */
%type <block> main_loop block
%type <statement> statement rotate forward attack ranged_attack save_loc memory if else
 
/* Expressions */
%type <numeric> numeric

%%

main_loop	: TMAIN TLBRACE block TRBRACE { std::cout << "Main entry point found!" << std::endl; }
;

block		: statement { std::cout << "Single statement" << std::endl; }
		| block statement { std::cout << "Multiple statements" << std::endl }
/* TODO: Add support for multiple statements in a block */
;

statement	: rotate TSEMI
;
			
rotate		: TROTATE TLPAREN numeric TRPAREN { std::cout << "Rotate command" << std::endl; }
;

forward		: TFORWARD TLPAREN TRPAREN { std::cout << "Forward command" << std::endl; }
;

attack		: TATTACK TLPAREN TRPAREN { std::cout << "Attack command" << std::endl; }
;

ranged_attack	: TRANGEDATTACK TLPAREN TRPAREN { std::cout << "Ranged Attack command" << std::endl; }
;

save_loc	: TSAVELOC TLPAREN TRPAREN { std::cout << "Save Loc command" << std::endl; }
;

memory		: TMEMORY TLBRACKET numeric TRBRACKET TINCREMENT { std::cout << "Memory Increment command, value: " << *($1) << std::endl; }
			| TMEMORY TLBRACKET numeric TRBRACKET TDECREMENT { std::cout << "Memory Decrement command, value: " << *($1) << std::endl; }
			| TMEMORY TLBRACKET numeric TRBRACKET TEQUALS numeric { std::cout << "Memory Equals command, values: " << *($1) << ", " << *($2) << std::endl; } 
;
			
numeric		: TINTEGER { std::cout << "Numeric value of " << *($1) << std::endl; }
;

if		: TIF TLPAREN TISHUMAN TLPAREN numeric TRPAREN TRPAREN { std::cout << "If Is Human test, value: " << *($1) << std::endl; }
		| TIF TLPAREN TISZOMBIE TLPAREN numeric TRPAREN TRPAREN { std::cout << "If Is Zombie test, value: " << *($1) << std::endl; }
		| TIF TLPAREN TISPASSABLE TLPAREN TRPAREN { std::cout << "If Passable test" << std::endl; }
		| TIF TLPAREN TISRANDOM TLPAREN TRPAREN { std::cout << "If Random test" << std::endl; }
;

else		: TELSE  { std::cout << "Else statement" << std::endl; }

%%
