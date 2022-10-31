%option noyywrap 
%{
#include <stdio.h>
#include "header.h" 
int linenumber;
symtab * lookup();
symtab * ptr;
void     insertID();
void 	   printSymTab();
/* You need to define for all tokens in C--, here are some examples */
/* Reserved Words */
#define RETURN
#define TYPEDEF
#define IF
#define ELSE
#define INT          10
#define FLOAT        11
#define FOR
#define VOID
#define WHILE

/* Symbols and operators */
#define OP_PLUS     
#define OP_MINUS    
#define OP_MUL      
#define OP_DIV      
#define OP_LESS     
#define OP_GREAT    
#define OP_GREAT_EQ 
#define OP_LESS_EQ  
#define OP_UN_EQ    
#define OP_EQ       
#define OP_OR        13
#define OP_AND      
#define OP_NOT
#define OP_ASSIGN 	12

/* Separators */
#define MK_lbrace   
#define MK_rbrace   
#define MK_rbracket 
#define MK_lbracket 
#define MK_LPAREN 	14
#define MK_RPAREN 	15
#define MK_semicol  
#define MK_comma    
#define MK_dot      
#define ERROR        100
%}

/* All regular expression appear here */
letter   [A-Za-z]
digit    [0-9]
ID	 {letter}({letter}|{digit}|"_")*
WS	 [ \t]+
Int_constant {digit}+
/* You need to define the following RE's */
Float_constant {Int_constant}[.]{digit}*
String_constant ["]{letter|digit|ID}*["]
comment [/][*]{String_constant}*[*][/]


/* All operators appear here */
/* Arithmetic operators */
OP_plus     "+"
OP_minus    "-"
OP_mul      "*"
OP_div      "/"
/* Relational operators */
OP_less     "<"
OP_great    ">"
OP_great_eq ">="
OP_less_eq  "<="
OP_un_eq    "!="
OP_eq       "=="
/* Logical operators */
OP_or       "||"
OP_and      "&&"
OP_not      "!"
/* Assignmet operators */
OP_assign   "="



newline  "\n"
/* All separators appear here */
DL_lbrace   "{"
DL_rbrace   "}"
DL_rbracket "["
DL_lbracket "]"
DL_lparen   "("
DL_rparen   ")"
DL_semicol  ";"
DL_comma    ","
DL_dot      "."

error    .

%%

{ID}              { 
                     ptr = lookup(yytext);
                     if (ptr == NULL)
                        insertID(yytext);	
                     else 
                        ptr->counter++;
                  }
{WS}              {}
{Int_constant}         {/* return INT; */ }
{Float_constant}       {/* return FLOAT; */}


{OP_plus}
{OP_minus}
{OP_mul}
{OP_div}
{OP_less}
{OP_great}
{OP_great_eq}
{OP_less_eq}
{OP_un_eq}
{OP_eq}
{OP_or}         /* return OP_OR; */
{OP_and}
{OP_not}
{OP_assign}     /* return OP_ASSIGN; */ 


{DL_lbrace}     /* return MK_LBRACE; */
{DL_rbrace}     /* return MK_RBRACE; */
{DL_rbracket}
{DL_lbracket}
{DL_lparen}     /* return MK_LPAREN; */
{DL_rparen}     /* return MK_RPAREN; */
{DL_semicol}    {}
{DL_comma}      {}
{newline}       linenumber += 1;
{error}         printf("ERR \n");/* return ERROR; */


%%

int main(int argc, char **argv)
{
   argc--;
   ++argv;
   if (argc > 0)
      yyin = fopen(argv[0], "r");
   else
      yyin = stdin;
   yylex();
   printSymTab();
}