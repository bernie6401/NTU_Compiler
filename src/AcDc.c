#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "header.h"

/*-----------------------Homework------------------------*/
/*tree_node.name is just a char, so u must find another char from [a-z^fip]
  and the assignment note said the number of different variables will not exceed 23
  implement in makeDeclarationNode function*/
Token Identifier_name[23];
int num_of_new_Identifier = 0;
/*-----------------------Homework------------------------*/

int main( int argc, char *argv[] )
{
    FILE *source, *target;
    Program program;
    SymbolTable symtab;

    source = fopen("/home/sbk/NTU/Compiler Technology of Programming Language/NTU_Compiler/test/constfold.ac", "r");//Reference-AcDc/
    target = fopen("/home/sbk/NTU/Compiler Technology of Programming Language/NTU_Compiler/src/output1", "w");

    // if( argc == 3)
    // {
    //     source = fopen(argv[1], "r");
    //     target = fopen(argv[2], "w");
    //     if( !source )
    //     {
    //         printf("can't open the source file\n");
    //         exit(2);
    //     }
    //     else if( !target )
    //     {
    //         printf("can't open the target file\n");
    //         exit(2);
    //     }
    //     else
    //     {
            program = parser(source);
            fclose(source);
            symtab = build(program);
            check(&program, &symtab);
            gencode(program, target);
    //     }
    // }
    // else
    // {
    //     printf("Usage: %s source_file target_file\n", argv[0]);
    // }


    return 0;
}

/********************************************* 
  Self-Defined
 *********************************************/
void unget_token(FILE *source, Token token)
{
    int len_identifier = 0;
    len_identifier = strlen(token.tok);
    for( int j = len_identifier - 1; j > -1; j-- )  //e.g. identifier abc -> 1st. push back c then b then a finally
        ungetc(token.tok[j], source);
}

void ConstFold( Expression *expr )
{
    Expression *left = expr->leftOperand;
    Expression *right = expr->rightOperand;
    if((left->v).type == IntConst && (right->v).type == IntConst)
    {
        //e.g. i 3 * i 10
        int lvalue = (left->v).val.ivalue;
        int rvalue = (right->v).val.ivalue;

        switch((expr->v).type)
        {
            case PlusNode:
                (expr->v).val.ivalue = lvalue + rvalue; break;
            case MinusNode:
                (expr->v).val.ivalue = lvalue - rvalue; break;
            case MulNode:
                (expr->v).val.ivalue = lvalue * rvalue; break;
            case DivNode:
                (expr->v).val.ivalue = lvalue / rvalue; break;
        }
        (expr->v).type = IntConst;
        expr->leftOperand = expr->rightOperand = NULL;
    }
    else if((left->v).type == FloatConst && (right->v).type == IntToFloatConvertNode && (right->leftOperand->v).type == IntConst)
    {
        //add "(right->leftOperand->v).type == IntConst" in if-stmt to avoid (35 + identifier) this kind of expr access into if-stmt
        //e.g. f 3.5 * i 10
        float lvalue = (left->v).val.fvalue;
        int rvalue = (right->leftOperand->v).val.ivalue;

        switch((expr->v).type)
        {
            case PlusNode:
                (expr->v).val.fvalue = lvalue + rvalue; break;
            case MinusNode:
                (expr->v).val.fvalue = lvalue - rvalue; break;
            case MulNode:
                (expr->v).val.fvalue = lvalue * rvalue; break;
            case DivNode:
                (expr->v).val.fvalue = lvalue / rvalue; break;
        }
        (expr->v).type = FloatConst;
        expr->leftOperand = expr->rightOperand = NULL;
    }
    else if((left->v).type == IntToFloatConvertNode && (right->v).type == FloatConst && (left->leftOperand->v).type == IntConst)
    {
        //e.g. i 3 * f 10.5
        int lvalue = (left->leftOperand->v).val.ivalue;    //must revise
        float rvalue = (right->v).val.fvalue;

        switch((expr->v).type)
        {
            case PlusNode:
                (expr->v).val.fvalue = lvalue + rvalue; break;
            case MinusNode:
                (expr->v).val.fvalue = lvalue - rvalue; break;
            case MulNode:
                (expr->v).val.fvalue = lvalue * rvalue; break;
            case DivNode:
                (expr->v).val.fvalue = lvalue / rvalue; break;
        }
        (expr->v).type = FloatConst;
        expr->leftOperand = expr->rightOperand = NULL;
    }
    else if((left->v).type == FloatConst && (right->v).type == FloatConst)
    {
        //e.g. f 3.5 * f 10.5
        float lvalue = (left->v).val.fvalue;
        float rvalue = (right->v).val.fvalue;

        switch((expr->v).type)
        {
            case PlusNode:
                (expr->v).val.fvalue = lvalue + rvalue; break;
            case MinusNode:
                (expr->v).val.fvalue = lvalue - rvalue; break;
            case MulNode:
                (expr->v).val.fvalue = lvalue * rvalue; break;
            case DivNode:
                (expr->v).val.fvalue = lvalue / rvalue; break;
        }
        (expr->v).type = FloatConst;
        expr->leftOperand = expr->rightOperand = NULL;
    }
}

/********************************************* 
  Scanning 
 *********************************************/
Token getNumericToken( FILE *source, char c )
{
    Token token;
    int i = 0;

    /* ------------To get Integer Value------------ */
    while( isdigit(c) ) //get all the single number that connected, e.g. 123456
    {
        token.tok[i++] = c;
        c = fgetc(source);
    }

    if( c != '.' )
    {
        ungetc(c, source);  //write char c back to source file
        token.tok[i] = '\0';
        token.type = IntValue;
        return token;
    }


    /* ------------To get Floating Value------------ */
    token.tok[i++] = '.';

    c = fgetc(source);
    if( !isdigit(c) )
    {
        ungetc(c, source);
        printf("Expect a digit : %c\n", c);
        exit(1);
    }

    while( isdigit(c) )
    {
        token.tok[i++] = c;
        c = fgetc(source);
    }

    ungetc(c, source);
    token.tok[i] = '\0';
    token.type = FloatValue;
    return token;
}

Token scanner( FILE *source )
{
    char c;
    Token token;

    while( !feof(source) )
    {
        c = fgetc(source);  //to get one char for each time in source file
        while( isspace(c) ) c = fgetc(source);  //if the char is space, then continuue reading next char

        /* ------------To examine num token value------------ */
        if( isdigit(c) )    //examine the token is a decimal num or not
            return getNumericToken(source, c);

        /* ------------To examine alphabet char token type------------ */
        token.tok[0] = c;
        token.tok[1] = '\0';
        if( islower(c) )    //to examine char c is lower case alphabet or nots
        {
            /*-----------------------Homework------------------------*/
            int i = 0;
            while (islower(c))
            {
                token.tok[i] = c;
                i++;
                c = fgetc(source);
            }
            ungetc(c, source);
            token.tok[i] = '\0';

            /* the token is a preserved declaration */
            if( i == 1 )
            {
                if( strcmp(token.tok, "f") == 0 )  //must use double-quote to represent string compare
                    {token.type = FloatDeclaration; return token;}
                else if( strcmp(token.tok, "i") == 0 )
                    {token.type = IntegerDeclaration; return token;}
                else if( strcmp(token.tok, "p") == 0 )
                    {token.type = PrintOp; return token;}
            }

            //tree_node.name is just a char, so u must find another char from [a-z^fip]
            token.type = Alphabet;
            //put alphabet token name to identifier_name
            for( int j = 0; j < 23; j++ )
            {
                /* cannot use this stmt -> token.tok == Identifier_name[j].tok
                    because of the data structure. u can watch it in debugger*/
                if( strcmp(token.tok, Identifier_name[j].tok) == 0)
                    return token;
            }
            //token.tok is a new variable
            Identifier_name[num_of_new_Identifier] = token;
            num_of_new_Identifier++;
            return token;
            /*-----------------------Homework------------------------*/
        }

        /* ------------To examine operator char token type------------ */
        switch(c)
        {
            case '=':
                token.type = AssignmentOp;
                return token;
            case '+':
                token.type = PlusOp;
                return token;
            case '-':
                token.type = MinusOp;
                return token;
            case '*':
                token.type = MulOp;
                return token;
            case '/':
                token.type = DivOp;
                return token;
            case EOF:
                token.type = EOFsymbol;
                token.tok[0] = '\0';
                return token;
            default:
                printf("Invalid character : %c\n", c);
                exit(1);
        }
    }

    token.tok[0] = '\0';
    token.type = EOFsymbol;
    return token;
}

/********************************************************
  Parsing - Objective: get the parse tree
 *********************************************************/
Declaration parseDeclaration( FILE *source, Token token )
{
    Token token2;
    switch(token.type)
    {
        /* variable name(2nd token) cannot be f or i or p */
        case FloatDeclaration:
        case IntegerDeclaration:
            token2 = scanner(source);
            if (strcmp(token2.tok, "f") == 0 || strcmp(token2.tok, "i") == 0 || strcmp(token2.tok, "p") == 0)
            {
                printf("Syntax Error: %s cannot be used as id\n", token2.tok);
                exit(1);
            }
            return makeDeclarationNode( token, token2 );
        default:
            printf("Syntax Error: Expect Declaration %s\n", token.tok);
            exit(1);
    }
}

Declarations *parseDeclarations( FILE *source )
{
    Token token = scanner(source);  //每一次執行scanner，都會return一個token回來
    Declaration decl;
    Declarations *decls;

    switch(token.type)
    {
        /* parse to Float or Integer means the current part is still in declaration part */
        case FloatDeclaration:
        case IntegerDeclaration:
            decl = parseDeclaration(source, token); //it will get 2nd token in the subprocess
            decls = parseDeclarations(source);  //call itself until parse all declaration part
            return makeDeclarationTree( decl, decls );
        
        /* parse to PrintOP or Alphabet means access to statement part,
         so it must return NULL and let other function to parse */
        case PrintOp:
        case Alphabet:
            //u must push the whole chars back to source by reverse order
            unget_token(source, token);
            //ungetc(token.tok[0], source); -> this is not enough for multi-char identifier
            return NULL;
        case EOFsymbol:
            return NULL;
        default:
            printf("Syntax Error: Expect declarations %s\n", token.tok);
            exit(1);
    }
}

/* In charge of getting the stmt value, return 
(value->v).type / (value->v).val.id or ivalue or fvalue .*/
Expression *parseValue( FILE *source ) //a little diff
{
    Token token = scanner(source);
    Expression *value = (Expression *)malloc( sizeof(Expression) );
    value->leftOperand = value->rightOperand = NULL;

    switch(token.type)
    {
        case Alphabet:
            (value->v).type = Identifier;
            /*-----------------------Homework------------------------*/
            //tree_node.name is just a char, so u must find another char from [a-z^fip]
            //find another char to replace origin identifier
            for( int i = 0; i < 23; i++)
            {
                //if we can find identifier name in Identifier_name
                //then we return a-z except reserved word
                if(strcmp(Identifier_name[i].tok, token.tok) == 0)//cannot use this stmt-> Identifier_name[i].tok == identifier.tok 
                {
                    (value->v).val.id = 'a' + i;    //transfer String to Int
                    break;
                }
            }
            break;
            /*-----------------------Homework------------------------*/
        case IntValue:
            (value->v).type = IntConst;
            (value->v).val.ivalue = atoi(token.tok);
            break;
        case FloatValue:
            (value->v).type = FloatConst;
            (value->v).val.fvalue = atof(token.tok);
            break;
        default:
            printf("Syntax Error: Expect Identifier or a Number %s\n", token.tok);
            exit(1);
    }

    return value;
}

/*-----------------------Homework------------------------*/
/* In charge of analyze mul/div operator, return
(expr->v).type / (expr->v).val.op / expr->leftOperand / expr->rightOperand .
This block is aim to analyze what operator beside the operand.
Why analyze mul/div op first u can refer to structure map in md file? 
The answer is we want to calculate mul/div op first --> fundamental arithmetic */
Expression *parseTermTail( FILE *source, Expression *lvalue )
{
    Token token = scanner(source);
    Expression *expr;

    switch(token.type)
    {
        case MulOp:
            expr = (Expression *)malloc( sizeof(Expression) );
            (expr->v).type = MulNode;
            (expr->v).val.op = Mul;
            expr->leftOperand = lvalue;
            expr->rightOperand = parseValue(source);
            return parseTermTail(source, expr);
        case DivOp:
            expr = (Expression *)malloc( sizeof(Expression) );
            (expr->v).type = DivNode;
            (expr->v).val.op = Div;
            expr->leftOperand = lvalue;
            expr->rightOperand = parseValue(source);
            return parseTermTail(source, expr);
        case PlusOp:
        case MinusOp:
        case Alphabet:
        case PrintOp:
            unget_token(source, token);
            return lvalue;
        case EOFsymbol:
            return lvalue;
        default:
            printf("Syntax Error: Expect a numeric value or an identifier %s\n", token.tok);
            exit(1);
    }
}

Expression *parseTerm( FILE *source )
{
    Expression *expr = parseValue(source);
    return parseTermTail(source, expr);
}
/*-----------------------Homework------------------------*/

/* In charge of analyze plus/minus operator, return
(expr->v).type / (expr->v).val.op / expr->leftOperand / expr->rightOperand .
This block is aim to analyze what operator beside the operand. */
Expression *parseExpressionTail( FILE *source, Expression *lvalue ) //need change
{
    Token token = scanner(source);
    Expression *expr;

    switch(token.type)
    {
        case PlusOp:
            expr = (Expression *)malloc( sizeof(Expression) );
            (expr->v).type = PlusNode;
            (expr->v).val.op = Plus;
            expr->leftOperand = lvalue;
            expr->rightOperand = parseTerm(source); //this is important, u must back to last level, not parseValue
            return parseExpressionTail(source, expr);
        case MinusOp:
            expr = (Expression *)malloc( sizeof(Expression) );
            (expr->v).type = MinusNode;
            (expr->v).val.op = Minus;
            expr->leftOperand = lvalue;
            expr->rightOperand = parseTerm(source); //this is important, u must back to last level, not parseValue
            return parseExpressionTail(source, expr);
        /*-----------------------Homework------------------------*/
        case MulOp:
        case DivOp:
        case Alphabet:
        case PrintOp:
            unget_token(source, token);
            //ungetc(token.tok[0], source);
            return lvalue;
        /*-----------------------Homework------------------------*/
        case EOFsymbol:
            return lvalue;
        default:
            printf("Syntax Error: Expect a numeric value or an identifier %s\n", token.tok);
            exit(1);
    }
}

/*-----------------------Homework------------------------*/
Expression *parseExpression( FILE *source )
{
    Expression *expr = parseTerm(source);
    return parseExpressionTail(source, expr);
}
/*-----------------------Homework------------------------*/

Statement parseStatement( FILE *source, Token token )
{
    Token next_token;
    Expression *value, *expr;

    switch(token.type)
    {
        case Alphabet:
            next_token = scanner(source);
            if(next_token.type == AssignmentOp)
            {
                // value = parseValue(source); //(value->v).type = FloatConst;(value->v).val.fvalue = atof(token.tok);
                // expr = parseExpression(source, value);  //expr == NULL
                /*-----------------------Homework------------------------*/
                Expression *expr = parseExpression(source);
                for (int j = 0; j < 23; j++)
                {
                    if (strcmp(Identifier_name[j].tok, token.tok) == 0)
                    {
                        return makeAssignmentNode('a' + j, value, expr);
                    }
                }
                /*-----------------------Homework------------------------*/
            }
            else
            {
                printf("Syntax Error: Expect an assignment op %s\n", next_token.tok);
                exit(1);
            }
        case PrintOp:
            next_token = scanner(source);
            if(next_token.type == Alphabet)
            {
                for (int i = 0; i < 23; i++)
                {
                    if (strcmp(Identifier_name[i].tok, next_token.tok) == 0)
                    {
                        return makePrintNode('a' + i);
                    }
                }
            }
            else
            {
                printf("Syntax Error: Expect an identifier %s\n", next_token.tok);
                exit(1);
            }
            break;
        default:
            printf("Syntax Error: Expect a statement %s\n", token.tok);
            exit(1);
    }
}

Statements *parseStatements( FILE * source )
{

    Token token = scanner(source);   //token == zzz
    Statement stmt;
    Statements *stmts;

    switch(token.type)
    {
        case Alphabet:
        case PrintOp:
            stmt = parseStatement(source, token);
            stmts = parseStatements(source);
            return makeStatementTree(stmt , stmts);
        case EOFsymbol:
            return NULL;
        default:
            printf("Syntax Error: Expect statements %s\n", token.tok);
            exit(1);
    }
}


/*********************************************************************
  Build AST
 **********************************************************************/
Declaration makeDeclarationNode( Token declare_type, Token identifier ) //a little diff
{
    //identifier is just variable name
    Declaration tree_node;

    switch(declare_type.type)
    {
        case FloatDeclaration:
            tree_node.type = Float;
            break;
        case IntegerDeclaration:
            tree_node.type = Int;
            break;
        default:
            break;
    }

    /*-----------------------Homework------------------------*/
    //tree_node.name is just a char, so u must find another char from [a-z^fip]
    //find another char to replace origin identifier
    for( int i = 0; i < 23; i++)
    {
        //if we can find identifier name in Identifier_name
        //then we return a-z except reserved word
        if(strcmp(Identifier_name[i].tok, identifier.tok) == 0)//cannot use this stmt-> Identifier_name[i].tok == identifier.tok 
        {
            tree_node.name = 'a' + i;
            return tree_node;
        }
    }

    //tree_node.name = identifier.tok[0];
    /*-----------------------Homework------------------------*/
    return tree_node;
}

Declarations *makeDeclarationTree( Declaration decl, Declarations *decls )
{
    Declarations *new_tree = (Declarations *)malloc( sizeof(Declarations) );
    new_tree->first = decl;
    new_tree->rest = decls;

    return new_tree;
}

Statement makeAssignmentNode( char id, Expression *v, Expression *expr_tail )   // need change
{
    Statement stmt;
    AssignmentStatement assign;

    stmt.type = Assignment;
    assign.id = id;
    /*-----------------------Homework------------------------*/
    // if(expr_tail == NULL)
    //     assign.expr = v;
    // else
    assign.expr = expr_tail;
    /*-----------------------Homework------------------------*/
    stmt.stmt.assign = assign;

    return stmt;
}

Statement makePrintNode( char id )  //a little diff
{
    Statement stmt;
    stmt.type = Print;
    stmt.stmt.variable = id;

    return stmt;
}

Statements *makeStatementTree( Statement stmt, Statements *stmts )
{
    Statements *new_tree = (Statements *)malloc( sizeof(Statements) );
    new_tree->first = stmt;
    new_tree->rest = stmts;

    return new_tree;
}

/* parser */
Program parser( FILE *source )
{
    Program program;
    //In the program, we can split it two parts which are declarations(宣告) and statements(陳述)
    program.declarations = parseDeclarations(source);
    program.statements = parseStatements(source);

    return program;
}


/********************************************************
  Build symbol table
 *********************************************************/
void InitializeTable( SymbolTable *table )  //need change
{
    int i;

    for(i = 0 ; i < 26; i++)
        table->table[i] = Notype;
}

void add_table( SymbolTable *table, char c, DataType t )    //need change
{
    int index = (int)(c - 'a');

    if(table->table[index] != Notype)
        printf("Error : id %c has been declared\n", c);//error
    table->table[index] = t;
}

SymbolTable build( Program program )
{
    SymbolTable table;
    Declarations *decls = program.declarations;
    Declaration current;

    InitializeTable(&table);

    while(decls !=NULL)
    {
        current = decls->first;
        add_table(&table, current.name, current.type);
        decls = decls->rest;
    }

    return table;
}


/********************************************************************
  Type checking
 *********************************************************************/

void convertType( Expression * old, DataType type )
{
    if(old->type == Float && type == Int)
    {
        printf("error : can't convert float to integer\n");
        return;
    }
    if(old->type == Int && type == Float)
    {
        Expression *tmp = (Expression *)malloc( sizeof(Expression) );
        if(old->v.type == Identifier)
            printf("convert to float %c \n",old->v.val.id);
        else
            printf("convert to float %d \n", old->v.val.ivalue);
        tmp->v = old->v;
        tmp->leftOperand = old->leftOperand;
        tmp->rightOperand = old->rightOperand;
        tmp->type = old->type;

        Value v;
        v.type = IntToFloatConvertNode;
        v.val.op = IntToFloatConvert;
        old->v = v;
        old->type = Int;
        old->leftOperand = tmp;
        old->rightOperand = NULL;
    }
}

DataType generalize( Expression *left, Expression *right )
{
    if(left->type == Float || right->type == Float)
    {
        printf("generalize : float\n");
        return Float;
    }
    printf("generalize : int\n");
    return Int;
}

DataType lookup_table( SymbolTable *table, char c ) //need change
{
    int id = c-'a';
    if( table->table[id] != Int && table->table[id] != Float)
        printf("Error : identifier %c is not declared\n", c);//error
    return table->table[id];
}

void checkexpression( Expression * expr, SymbolTable * table )  //need change
{
    char c;
    if(expr->leftOperand == NULL && expr->rightOperand == NULL)
    {
        switch(expr->v.type)
        {
            case Identifier:
                c = expr->v.val.id;
                printf("identifier : %c\n",c);
                expr->type = lookup_table(table, c);
                break;
            case IntConst:
                printf("constant : int\n");
                expr->type = Int;
                break;
            case FloatConst:
                printf("constant : float\n");
                expr->type = Float;
                break;
                //case PlusNode: case MinusNode: case MulNode: case DivNode:
            default:
                break;
        }
    }
    else
    {
        Expression *left = expr->leftOperand;
        Expression *right = expr->rightOperand;

        checkexpression(left, table);
        checkexpression(right, table);

        DataType type = generalize(left, right);    // determine a data type
        convertType(left, type);
        convertType(right, type);
        expr->type = type;

        ConstFold( expr );
    }
}

void checkstmt( Statement *stmt, SymbolTable * table )
{
    if(stmt->type == Assignment)
    {
        AssignmentStatement assign = stmt->stmt.assign;
        printf("assignment : %c \n",assign.id);
        checkexpression(assign.expr, table);
        stmt->stmt.assign.type = lookup_table(table, assign.id);
        if (assign.expr->type == Float && stmt->stmt.assign.type == Int)
            printf("error : can't convert float to integer1\n");
        else
            convertType(assign.expr, stmt->stmt.assign.type);
    }
    else if (stmt->type == Print)
    {
        printf("print : %c \n",stmt->stmt.variable);
        lookup_table(table, stmt->stmt.variable);
    }
    else printf("error : statement error\n");//error
}

void check( Program *program, SymbolTable * table )
{
    Statements *stmts = program->statements;
    while(stmts != NULL)
    {
        checkstmt(&stmts->first, table);
        stmts = stmts->rest;
    }
}


/***********************************************************************
  Code generation
 ************************************************************************/
void fprint_op( FILE *target, ValueType op )
{
    switch(op){
        case MinusNode:
            fprintf(target, "-\n");
            break;
        case PlusNode:
            fprintf(target, "+\n");
            break;
        /*-----------------------Homework------------------------*/
        case MulNode:
            fprintf(target, "*\n");
            break;
        case DivNode:
            fprintf(target, "/\n");
            break;
        /*-----------------------Homework------------------------*/
        default:
            fprintf(target,"Error in fprintf_op ValueType = %d\n",op);
            break;
    }
}

void fprint_expr( FILE *target, Expression *expr) //need change
{
    if(expr->leftOperand == NULL)
    {
        switch( (expr->v).type )
        {
            case Identifier:
                fprintf(target,"l%c\n",(expr->v).val.id);
                break;
            case IntConst:
                fprintf(target,"%d\n",(expr->v).val.ivalue);
                break;
            case FloatConst:
                fprintf(target,"%f\n", (expr->v).val.fvalue);
                break;
            default:
                fprintf(target,"Error In fprint_left_expr. (expr->v).type=%d\n",(expr->v).type);
                break;
        }
    }
    else
    {
        fprint_expr(target, expr->leftOperand);
        if(expr->rightOperand == NULL)
            fprintf(target,"5k\n");
        else
        {
            //	fprint_right_expr(expr->rightOperand);
            fprint_expr(target, expr->rightOperand);
            fprint_op(target, (expr->v).type);
        }
    }
}

void gencode(Program prog, FILE * target)
{
    Statements *stmts = prog.statements;
    Statement stmt;

    while(stmts != NULL)
    {
        stmt = stmts->first;
        switch(stmt.type)
        {
            case Print:
                fprintf(target, "l%c\n", stmt.stmt.variable);
                fprintf(target, "p\n");
                break;
            case Assignment:
                fprint_expr(target, stmt.stmt.assign.expr);
                /*
                   if(stmt.stmt.assign.type == Int){
                   fprintf(target,"0 k\n");
                   }
                   else if(stmt.stmt.assign.type == Float){
                   fprintf(target,"5 k\n");
                   }*/
                fprintf(target,"s%c\n",stmt.stmt.assign.id);
                fprintf(target,"0 k\n");
                break;
        }
        stmts=stmts->rest;
    }

}


/***************************************
  For our debug,
  you can omit them.
 ****************************************/
void print_expr(Expression *expr)
{
    if(expr == NULL)
        return;
    else{
        print_expr(expr->leftOperand);
        switch((expr->v).type){
            case Identifier:
                printf("%c ", (expr->v).val.id);
                break;
            case IntConst:
                printf("%d ", (expr->v).val.ivalue);
                break;
            case FloatConst:
                printf("%f ", (expr->v).val.fvalue);
                break;
            case PlusNode:
                printf("+ ");
                break;
            case MinusNode:
                printf("- ");
                break;
            case MulNode:
                printf("* ");
                break;
            case DivNode:
                printf("/ ");
                break;
            case IntToFloatConvertNode:
                printf("(float) ");
                break;
            default:
                printf("error ");
                break;
        }
        print_expr(expr->rightOperand);
    }
}

void test_parser( FILE *source )
{
    Declarations *decls;
    Statements *stmts;
    Declaration decl;
    Statement stmt;
    Program program = parser(source);

    decls = program.declarations;

    while(decls != NULL)
    {
        decl = decls->first;
        if(decl.type == Int)
            printf("i ");
        if(decl.type == Float)
            printf("f ");
        printf("%c ",decl.name);
        decls = decls->rest;
    }

    stmts = program.statements;

    while(stmts != NULL)
    {
        stmt = stmts->first;
        if(stmt.type == Print)
            printf("p %c ", stmt.stmt.variable);

        if(stmt.type == Assignment)
        {
            printf("%c = ", stmt.stmt.assign.id);
            print_expr(stmt.stmt.assign.expr);
        }
        stmts = stmts->rest;
    }

}