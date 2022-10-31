%option noyywrap 
%{
#include <stdio.h>
#include "header.h"

/* Self-defined */
#ifndef FALSE 
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
/* Self-defined */

int linenumber;
symtab * lookup();
symtab * ptr;
void     insertID();
void 	   printSymTab();
/* You need to define for all tokens in C--, here are some examples */
/* Reserved Words */
#define RETURN       0
#define TYPEDEF      1
#define IF           2
#define ELSE         3
#define INT          10
#define FLOAT        11
#define FOR          4
#define VOID         5
#define WHILE        6

/* Symbols and operators */
#define OP_PLUS      7
#define OP_MINUS     8
#define OP_MUL       9
#define OP_DIV       16
#define OP_LESS      17
#define OP_GREAT     18
#define OP_GREAT_EQ  19
#define OP_LESS_EQ   20
#define OP_UN_EQ     21
#define OP_EQ        22
#define OP_OR        13
#define OP_AND       23
#define OP_NOT       24
#define OP_ASSIGN 	12

/* Separators */
#define MK_lbrace    25
#define MK_rbrace    26
#define MK_rbracket  27
#define MK_lbracket  28
#define MK_LPAREN 	14
#define MK_RPAREN 	15
#define MK_semicol   29
#define MK_comma     30
#define MK_dot       31
#define ERROR        100
%}

/* All regular expression appear here */
letter            [A-Za-z]
digit             [0-9]
ID                {letter}({letter}|{digit}|"_")*
WS                [ \t]+
Int_constant      {digit}+
Float_constant    {Int_constant}[.]{digit}*
String_constant   ["“].*[”"]
line_comment      "//".*\n
block_comment     "/*"


/* Reserved Words */
RWInt       (int)
RWFloat     (float)
RWRturn     (return)
RWTypedef   (typedef)
RWIf        (if)
RWElse      (else)
RWFor       (for)
RWVoid      (void)
RWWhile     (while)


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
DL_l2quotes "“"
DL_r2quotes "”"
DL_colon    ":"
DL_2quotes  "\""
error    .

%%

{WS}              {}
{RWInt}           
{RWFloat}         
{RWRturn}         
{RWTypedef}       
{RWIf}            
{RWElse}          
{RWFor}           
{RWVoid}          
{RWWhile}         
{ID}              {
                     ptr = lookup(yytext);
                     if (ptr == NULL)
                        insertID(yytext);	
                     else 
                        ptr->counter++;
                  }
{Int_constant}    
{Float_constant}  
{DL_l2quotes}     
{DL_r2quotes}     
{String_constant} ECHO;
{line_comment}    ECHO;
{block_comment}   {
                     char c;
                     int done = FALSE;
                     ECHO;
                     c = input();
                     int state = 2;
                     while(!done)
                     {
                        if(c==0)
                        {
                           printf("eof , parsing error!");
                           break;
                        }
                        switch(state)
                        {
                           case 2:{if(c=='*'){state = 3;} else {}}break;
                           case 3:{if(c=='/'){state = 4;} else if(c=='*'){} else {state = 2;}}break;
                           case 4:{done = TRUE;}break;
                        }
                        putchar(c);
                        c = input();
                     }
                  }



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
{OP_or}           
{OP_and}          
{OP_not}          
{OP_assign}       


{DL_lbrace}       
{DL_rbrace}       
{DL_rbracket}     
{DL_lbracket}     
{DL_lparen}       
{DL_rparen}       
{DL_semicol}      
{DL_comma}        
{newline}         linenumber += 1;
{DL_colon}        
{DL_2quotes}      
{error}           printf("ERR \n");/* return ERROR; */


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