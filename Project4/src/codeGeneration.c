#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "header.h"
#include "symbolTable.h"
#include "macros.h"

typedef int REG;

void codeGeneration(AST_NODE *root);
void genProgramNode(AST_NODE *root);
void genVariableDeclList(AST_NODE *declListNode);
void genTypeDecl(AST_NODE *typeDeclNode);
void genVariableDecl(AST_NODE *variableDeclNode);
void genFunctionDecl(AST_NODE *functionDeclNode);
void countDeclListInBlock(AST_NODE *curr, int* size);
void countVariableListSize(AST_NODE *declListNode, int* size);
void countVariableSize(AST_NODE *declNode, int* size);
void genBlock(AST_NODE *block);
void genFunctionPrologue(int size);
void genFunctionEpilogue(int size, DATA_TYPE returnType);
void genStmtList(AST_NODE *stmtList);
void genStmt(AST_NODE *stmt);
void genWhile(AST_NODE *whileNode);
void genAssignStmt(AST_NODE *assignNode);
void genIf(AST_NODE *ifNode);
void genFunctionCall(AST_NODE *functionCallNode);
void genReturn(AST_NODE *returnNode);
void genWrite(AST_NODE *functionCallNode);

REG getReg();
void freeReg(REG reg);
REG genExprRelated(AST_NODE *exprRelated);
REG genRelopExpr(AST_NODE *relopExpr);
REG genVariableRef(AST_NODE *idNode);
REG genArrayRef(AST_NODE *idNode);
void genVariableAssign(AST_NODE *idNode, REG val);
void genArrayAssign(AST_NODE *idNode, REG val);
REG genConstValue(AST_NODE *constValueNode);

int genIntLiteral(int i);
int genFloatLiteral(float i);
void genAlignment();

FILE *output;
int const_n;

void codeGeneration(AST_NODE *root)
{
    output = fopen("output.s", "w");
    genProgramNode(root);
    fclose(output);
    return;
}

void genProgramNode(AST_NODE *root)
{
    AST_NODE *it = root->child;
    forEach(it){
        if (it->nodeType == VARIABLE_DECL_LIST_NODE){
            fprintf(output, ".data\n");
            genVariableDeclList(it);
        } else if (it->nodeType == DECLARATION_NODE){
            fprintf(output, ".text\n");
            genFunctionDecl(it);
        } else {
            assert("not variable nor function declare" == 0);
        }
    }
}

void genVariableDeclList(AST_NODE *declListNode)
{
    AST_NODE *it = declListNode->child;
    forEach(it){
        assert(it->nodeType == DECLARATION_NODE);
        switch (getDeclKind(it)){
            case TYPE_DECL:
                genTypeDecl(it->child);
                break;
            case VARIABLE_DECL:
                genVariableDecl(it->child);
                break;
            default:
                printf("Undefined variable list kind\n");
        }
    }
}

void genTypeDecl(AST_NODE *typeDeclNode)
{
    // Nothing to do
    return;
}

int getArrayCount(AST_NODE *dim){
    int size = 1;
    forEach(dim){
        size *= getExprValue(dim);
    }
    return size;
}

void genVariableDecl(AST_NODE *variableDeclNode)
{
    AST_NODE *it = variableDeclNode;
    unpack(it, type, id_list);
    forEach(id_list){
        setIDGlobal(id_list, 1);
        TypeDescriptor* typeDescriptor = getIDTypeDescriptor(id_list);
        int varSize = 4;

        if (typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR) {
            ArrayProperties* arr = &typeDescriptor->properties.arrayProperties;
            for (int i=0; i<arr->dimension; i++) {
                varSize *= arr->sizeInEachDimension[i];
            }
        }

        if (id_list->child){
            varSize *= getArrayCount(id_list->child);
        }

        fprintf(output, "_g_%s: .space %d\n", getIDName(id_list), varSize);
    }
}

void genFunctionDecl(AST_NODE *functionDeclNode)
{
    AST_NODE *it = functionDeclNode->child;
    unpack(it, head, id, param, block);

    TypeDescriptor *td = getTypeDescriptor(head);
    DATA_TYPE returnType = td->properties.dataType;
    fprintf(output, "_start_%s:\n", getIDName(id));
    // this hw only has parameterless function call
    // no need to proceed param
    
    int size = 0;
    // size = ...
    countDeclListInBlock(block, &size);
    printf("local stack size %d\n", size);
    genFunctionPrologue(size);

    genBlock(block);

    genFunctionEpilogue(size, returnType);
}

void genDeclList(AST_NODE *declList){
    AST_NODE *declIter = declList->child;
    forEach(declIter){
        AST_NODE *type = declIter->child;
        AST_NODE *it = type->rightSibling;
        forEach(it){
            if (it->child){
                REG reg = genExprRelated(it->child);
                REG addr = genIntLiteral(getIDOffset(it));
                fprintf(output, "sub x%d, x29, x%d\n", addr, addr);
                if (type->dataType == INT_TYPE){
                    fprintf(output, "str w%d, [x%d, #0]\n", reg, addr);
                } else if (type->dataType == FLOAT_TYPE){
                    fprintf(output, "str s%d, [x%d, #0]\n", reg, addr);
                }
                freeReg(addr);
                freeReg(reg);
            }
        }
    }
}

void genBlock(AST_NODE *block)
{
    assert(block->nodeType == BLOCK_NODE);
    
    AST_NODE *it = block->child;
    // block -> decl_list stmt_list
    if (it->rightSibling){
        unpack(it, decl_list, stmt_list);
        assert(decl_list->nodeType == VARIABLE_DECL_LIST_NODE);
        assert(stmt_list->nodeType == STMT_LIST_NODE);
        genDeclList(decl_list);
        genStmtList(stmt_list);
    }
    // block -> decl_list | stmt_list
    else {
        if (it->nodeType == VARIABLE_DECL_LIST_NODE){
            genDeclList(it);
        } else if (it->nodeType == STMT_LIST_NODE){
            genStmtList(it);
        } else {
            puts("Undefined block child nodeType");
        }
    }

    //__asm__("int3");
}

void countDeclListInBlock(AST_NODE *curr, int* size)
{
    if (curr->child){
        AST_NODE *it = curr->child;
        forEach(it){
            if (it->nodeType == VARIABLE_DECL_LIST_NODE){
                countVariableListSize(it, size);
            }
            countDeclListInBlock(it, size);
        }
    }
}

void countVariableListSize(AST_NODE *declListNode, int* size)
{
    AST_NODE *it = declListNode->child;
    forEach(it){
        assert(it->nodeType == DECLARATION_NODE);
        switch (getDeclKind(it)){
            case TYPE_DECL:
                // nothing to do
                break;
            case VARIABLE_DECL:
                countVariableSize(it->child, size);
                break;
            default:
                printf("Undefined variable list kind\n");
        }
    }
}

void countVariableSize(AST_NODE *declNode, int* size)
{
    AST_NODE *it = declNode;
    unpack(it, type, id_list);
    assert ( id_list->nodeType == IDENTIFIER_NODE );
    assert ( getIDEntry(id_list) != NULL );
    assert ( getIDAttr(id_list)->attributeKind == VARIABLE_ATTRIBUTE );
    forEach(id_list){
        setIDOffset(id_list, *size);
        printf("%s offset %d\n", getIDName(id_list), getIDOffset(id_list));
        setIDGlobal(id_list, 0);
        
        TypeDescriptor* typeDescriptor = getIDTypeDescriptor(id_list);
        int varSize = 4;

        if (typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR) {
            ArrayProperties* arr = &typeDescriptor->properties.arrayProperties;
            for (int i=0; i<arr->dimension; i++) {
                varSize *= arr->sizeInEachDimension[i];
            }
        }

        if (id_list->child && getIDKind(id_list) == ARRAY_ID){
            varSize *= getArrayCount(id_list->child);
            printf("it is array with size %d\n", varSize);
        } else{
            printf("it is var with size %d\n", varSize);
        }
        *size += varSize;
        //printf("size: %d\n", *size);
    }
}

void genFunctionPrologue(int size)
{
    fprintf(output, "str x30, [sp, #-8]\n");
    fprintf(output, "str x29, [sp, #-16]\n");
    int offset = 16;
    for(int i = 19; i <= 29; ++i){
        offset += 8;
        fprintf(output, "str x%d, [sp, #%d]\n", i, -offset);
    }
    fprintf(output, "add x29, sp, #-112\n");
    fprintf(output, ".data\n");
    fprintf(output, "_AR_SIZE_%d: .word %d\n", const_n, ((size-1)|0xf)+1);
    fprintf(output, ".align 3\n");
    fprintf(output, ".text\n");
    fprintf(output, "ldr w19, _AR_SIZE_%d\n", const_n);
    fprintf(output, "sub sp, x29, w19\n");
    ++const_n;
    //_offset = 0
}

// does not need size actually
void genFunctionEpilogue(int size, DATA_TYPE returnType)
{
    fprintf(output, "add sp, x29, #112\n");
    int offset = 0;
    for (int i = 29; i >= 19; --i){
        offset += 8;
        fprintf(output, "ldr x%d, [x29, #%d]\n", i, offset);
    }
    fprintf(output, "ldr x30, [sp, #-8]\n");
    fprintf(output, "ldr x29, [sp, #-16]\n");
    fprintf(output, "ret x30\n");
}

void genStmtList(AST_NODE *stmtList)
{
    AST_NODE *it = stmtList->child;
    forEach(it){
        genStmt(it);
    }
}

void genStmt(AST_NODE *stmt)
{
    switch(stmt->nodeType){
        case BLOCK_NODE:
            genBlock(stmt);
            break;
        case STMT_NODE:
            switch(getStmtKind(stmt)){
                case WHILE_STMT:
                    genWhile(stmt->child);
                    break;
                case ASSIGN_STMT:
                    genAssignStmt(stmt->child);
                    break;
                case IF_STMT:
                    genIf(stmt->child);
                    break;
                case FUNCTION_CALL_STMT:
                    genFunctionCall(stmt->child);
                    break;
                case RETURN_STMT:
                    genReturn(stmt->child);
                    break;
                default:
                    puts("Undefined statement");
            }
            break;
        case NUL_NODE:
            // nothing to do
            break;
        default:
            puts("Undefined stmt node");
    }
}

void genWhile(AST_NODE *whileNode)
{
    AST_NODE *it = whileNode;
    unpack(it, test, stmt);
    int while_n = const_n++;

    fprintf(output, "_WHILE_%d:\n", while_n);
    if (test->nodeType == STMT_NODE && getStmtKind(test) == ASSIGN_STMT){
        genAssignStmt(test);
        test = test->child;
    }
    REG reg = genExprRelated(test);
    if (test->dataType == FLOAT_TYPE)
        fprintf(output, "fcvtzs w%d, s%d\n", reg, reg);

    fprintf(output, "cmp w%d, #0\n", reg);
    freeReg(reg);
    fprintf(output, "beq _WHILE_END_%d\n", while_n);
    genStmt(stmt);
    fprintf(output, "b _WHILE_%d\n", while_n);
    fprintf(output, "_WHILE_END_%d:\n", while_n);
}

void genArrayAssign(AST_NODE *idNode, REG val)
{
    assert ( idNode->nodeType == IDENTIFIER_NODE );
    assert ( getIDEntry(idNode) != NULL );
    assert ( getIDAttr(idNode)->attributeKind == VARIABLE_ATTRIBUTE );
    assert ( getIDKind(idNode) == ARRAY_ID );
    TypeDescriptor* typeDescriptor = getIDTypeDescriptor(idNode);

    REG varReg;
    if(getIDGlobal(idNode)){
        varReg = getReg();
        fprintf(output, "ldr x%d, =_g_%s\n", varReg, getIDName(idNode));
    }else{
        int stackOffset = getIDOffset(idNode);
        varReg = genIntLiteral(stackOffset);
        fprintf(output, "sub x%d, x29, x%d\n", varReg, varReg);
        fprintf(stderr, "Array assign name: %s, offset: %d\n", getIDName(idNode), stackOffset);
    }

    int i = 0;
    int *sizes = typeDescriptor->properties.arrayProperties.sizeInEachDimension;
    AST_NODE *dimNode = idNode->child;

    REG offsetReg = getReg();
    fprintf(output, "mov x%d, #0\n", offsetReg);
    forEach(dimNode){
        REG sizeReg = genIntLiteral(sizes[i]);
        fprintf(output, "mul x%d, x%d, x%d\n", offsetReg, offsetReg, sizeReg);
        freeReg(sizeReg);

        REG indexReg = genExprRelated(dimNode);
        fprintf(output, "lsl x%d, x%d, #2\n", indexReg, indexReg);
        fprintf(output, "add x%d, x%d, x%d\n", offsetReg, offsetReg, indexReg);
        freeReg(indexReg);

        ++i;
    }

    if(getIDGlobal(idNode))
        fprintf(output, "add x%d, x%d, x%d\n", varReg, varReg, offsetReg);
    else
        fprintf(output, "sub x%d, x%d, x%d\n", varReg, varReg, offsetReg);

    freeReg(offsetReg);
    if(idNode->dataType == INT_TYPE){
        fprintf(output, "str w%d, [x%d, #0]\n", val, varReg);
    }else{
        fprintf(output, "str s%d, [x%d, #0]\n", val, varReg);
    }
    freeReg(varReg);

}

void genVariableAssign(AST_NODE *idNode, REG val)
{
    assert ( idNode->nodeType == IDENTIFIER_NODE );
    assert ( getIDEntry(idNode) != NULL );
    assert ( getIDAttr(idNode)->attributeKind == VARIABLE_ATTRIBUTE );
    TypeDescriptor* typeDescriptor = getIDTypeDescriptor(idNode);

    if(getIDKind(idNode) == ARRAY_ID){
        genArrayAssign(idNode, val);
        return;
    }else{
        REG addr;
        if(getIDGlobal(idNode)){
            addr = getReg();
            fprintf(output, "ldr x%d, =_g_%s\n", addr, getIDName(idNode));
        }else{
            int offset = getIDOffset(idNode);
            addr = genIntLiteral(offset);
            fprintf(output, "sub x%d, x29, x%d\n", addr, addr);
            fprintf(stderr, "Var assign name: %s, offset: %d\n", getIDName(idNode), offset);
        }

        if(idNode->dataType == INT_TYPE){
            fprintf(output, "str w%d, [x%d, #0]\n", val, addr);
        }else{
            fprintf(output, "str s%d, [x%d, #0]\n", val, addr);
        }

        freeReg(addr);
    }
    return;
}

void genAssignStmt(AST_NODE *assignNode)
{
    AST_NODE *it = assignNode;
    unpack(it, id, relop_expr);
    REG reg = genExprRelated(relop_expr);
    // TODO variable reference
    // stack[offset] = right_reg
    genVariableAssign(id, reg);
    freeReg(reg);
}

void genIf(AST_NODE *ifNode)
{
    AST_NODE *it = ifNode;
    unpack(it, test, stmt, elseStmt);
    int if_n = const_n++;
    
    fprintf(output, "_IF_%d:\n", if_n);
    if (test->nodeType == STMT_NODE && getStmtKind(test) == ASSIGN_STMT){
        genAssignStmt(test);
        test = test->child;
    }
    REG reg = genExprRelated(test);
    if (test->dataType == FLOAT_TYPE)
        fprintf(output, "fcvtzs w%d, s%d\n", reg, reg);

    fprintf(output, "cmp w%d, #0\n", reg);
    freeReg(reg);
    fprintf(output, "beq _ELSE_%d\n", if_n);
    genStmt(stmt);
    fprintf(output, "b _END_IF_%d\n", if_n);
   

    fprintf(output, "_ELSE_%d:\n", if_n);
    //if (elseStmt->nodeType != NUL_NODE)
    genStmt(elseStmt);
    fprintf(output, "_END_IF_%d:\n", if_n);
}

void genWrite(AST_NODE *functionCallNode){
    AST_NODE *it = functionCallNode;
    unpack(it, id, paramList);
    AST_NODE *param = paramList->child;
    
    REG reg = genExprRelated(param);
    switch(param->dataType){
        case INT_TYPE:
            fprintf(output, "mov w0, w%d\n", reg);
            fprintf(output, "bl _write_int\n");
            break;
        case FLOAT_TYPE:
            fprintf(output, "fmov s0, s%d\n", reg);
            fprintf(output, "bl _write_float\n");
            break;
        case CONST_STRING_TYPE:
            fprintf(output, "mov x0, x%d\n", reg);
            fprintf(output, "bl _write_str\n");
            break;
    }
    freeReg(reg);
}

void genFunctionCall(AST_NODE *functionCallNode)
{
    AST_NODE *it = functionCallNode;
    unpack(it, id, param);

    char *name = getIDName(id);
    if (!strcmp(name, "write")){
        genWrite(functionCallNode);
    } else if (!strcmp(name, "read")){
        fprintf(output, "bl _read_int\n");
    } else if (!strcmp(name, "fread")){
        fprintf(output, "bl _read_float\n");
    } else {
        fprintf(output, "bl _start_%s\n", name);
    }
}

void genReturn(AST_NODE *returnNode)
{
    AST_NODE *it = returnNode;
    unpack(it, exprRelated);
    REG reg;
    if (exprRelated->nodeType != NUL_NODE){
        reg = genExprRelated(exprRelated);
    }

    AST_NODE *parent = returnNode;
    findParentDecl(parent, FUNCTION_DECL);
    FunctionSignature *fs = getHeadFunctionSignature(parent->child);
    switch(fs->returnType){
        case INT_TYPE:
            if (returnNode->dataType == INT_TYPE)
                fprintf(output, "mov w0, w%d\n", reg);
            else if (returnNode->dataType == FLOAT_TYPE){
                fprintf(output, "fmov s0, s%d\n", reg);
                fprintf(output, "fcvtzs w0, s0\n");
            } else {
                puts("return type error");
            }
            break;
        case FLOAT_TYPE:
            if (returnNode->dataType == INT_TYPE){
                fprintf(output, "mov w0, w%d\n", reg);
                fprintf(output, "scvtf s0, w0\n");
            } else if (returnNode->dataType == FLOAT_TYPE){
                fprintf(output, "fmov s0, s%d\n", reg);
            } else {
                puts("return type error");
            }
            break;
        case VOID_TYPE:
            break;
        default:
            puts("Undefined return type");
            break;
    }
    freeReg(reg);
}

REG genExprRelated(AST_NODE *exprRelatedNode)
{
    REG reg;
    switch(exprRelatedNode->nodeType)
    {
    case EXPR_NODE:
        return genRelopExpr(exprRelatedNode);
        break;
    case STMT_NODE:
        //function call
		genFunctionCall(exprRelatedNode->child);
        reg = getReg();
        switch(exprRelatedNode->dataType){
          case INT_TYPE:
            fprintf(output, "mov w%d, w0\n", reg);
            break;
          case FLOAT_TYPE:
            fprintf(output, "fmov s%d, s0\n", reg);
            break;
        }
        return reg;
        break;
    case IDENTIFIER_NODE:
        return genVariableRef(exprRelatedNode);
        break;
    case CONST_VALUE_NODE:
        return genConstValue(exprRelatedNode);
        break;
    default:
        printf("Unhandle case in void genExprRelated(AST_NODE* exprRelatedNode)\n");
        break;
    }
}

int isRegInUse[29 - 19];

REG getReg()
{
    for (int i=19; i<29; ++i) {
        if (!isRegInUse[i]) {
            isRegInUse[i] = 1;
            //printf("getReg %d\n", i);
            return i;
        }
    }
    assert ( 0 && "No freed register" );
}

void freeReg(REG reg)
{
    assert ( reg >= 19 && reg < 29 );
    //printf("freeReg %d\n", reg);
    isRegInUse[reg] = 0;
}


REG genIntLiteral(int i){
    static int counter = 0;
    fprintf(output, ".data\n");
    fprintf(output, "_INT_CONST_%d: .word %d\n", counter, i);
    genAlignment();
    fprintf(output, ".text\n");
    REG reg = getReg();
    fprintf(output, "ldr x%d, _INT_CONST_%d\n", reg, counter);
    counter++;
    return reg;
}

REG genFloatLiteral(float f){
    static int counter = 0;
    fprintf(output, ".data\n");
    fprintf(output, "_FLOAT_CONST_%d: .float %f\n", counter, f);
    genAlignment();
    fprintf(output, ".text\n");
    REG reg = getReg();
    fprintf(output, "ldr s%d, _FLOAT_CONST_%d\n", reg, counter);
    counter++;
    return reg;
}

REG genStrLiteral(char* s){
    static int counter = 0;
    fprintf(output, ".data\n");
    fprintf(output, "_STR_CONST_%d: .asciz %s\n", counter, s);
    genAlignment();
    fprintf(output, ".text\n");
    REG reg = getReg();
    fprintf(output, "ldr x%d, =_STR_CONST_%d\n", reg, counter);
    counter++;
    return reg;
}

void genAlignment(){
    fprintf(output, ".align 3\n");
}

/*
void genBranchBoolean(REG LReg, REG RReg, char* branch, bool isFloat)
{
    static int counter = 0;
    if (isFloat) {
        fprintf(output, "cmp s%d, s%d\n", LReg, RReg);
    } else {
        fprintf(output, "cmp w%d, w%d\n", LReg, RReg);
    }
    fprintf(output, "%s _TRUE_%d\n", branch, counter);
    fprintf(output, "mov w%d, #0\n", LReg);
    fprintf(output, "b _BOOLEAN_END_%d\n", counter);
    fprintf(output, "_TRUE_%d:\n", counter);
    fprintf(output, "mov w%d, #1\n", LReg);
    fprintf(output, "_BOOLEAN_END_%d:\n", counter);
    counter++;
}
*/

REG genRelopExpr(AST_NODE *exprNode)
{
    AST_NODE* it = exprNode->child;

    if (isConstExpr(exprNode))
        return genConstValue(exprNode);

    if (getExprKind(exprNode) == BINARY_OPERATION) {
        unpack(it, lvalue, rvalue);

        REG LReg = genExprRelated(lvalue);
        REG RReg = genExprRelated(rvalue);

        if(lvalue->dataType == INT_TYPE && rvalue->dataType == INT_TYPE){
            switch(getExprOp(exprNode)){
                case BINARY_OP_ADD:
                    fprintf(output, "add w%d, w%d, w%d\n", LReg, LReg, RReg);
                    break;
                case BINARY_OP_SUB:
                    fprintf(output, "sub w%d, w%d, w%d\n", LReg, LReg, RReg);
                    break;
                case BINARY_OP_MUL:
                    fprintf(output, "mul w%d, w%d, w%d\n", LReg, LReg, RReg);
                    break;
                case BINARY_OP_DIV:
                    fprintf(output, "sdiv w%d, w%d, w%d\n", LReg, LReg, RReg);
                    break;

                case BINARY_OP_EQ:
                    fprintf(output, "cmp w%d, w%d\n", LReg, RReg);
                    fprintf(output, "cset w%d, eq\n", LReg);
                    break;
                case BINARY_OP_GE:
                    fprintf(output, "cmp w%d, w%d\n", LReg, RReg);
                    fprintf(output, "cset w%d, ge\n", LReg);
                    break;
                case BINARY_OP_LE:
                    fprintf(output, "cmp w%d, w%d\n", LReg, RReg);
                    fprintf(output, "cset w%d, le\n", LReg);
                    break;
                case BINARY_OP_NE:
                    fprintf(output, "cmp w%d, w%d\n", LReg, RReg);
                    fprintf(output, "cset w%d, ne\n", LReg);
                    break;
                case BINARY_OP_GT:
                    fprintf(output, "cmp w%d, w%d\n", LReg, RReg);
                    fprintf(output, "cset w%d, gt\n", LReg);
                    break;
                case BINARY_OP_LT:
                    fprintf(output, "cmp w%d, w%d\n", LReg, RReg);
                    fprintf(output, "cset w%d, lt\n", LReg);
                    break;

                case BINARY_OP_AND:
                    fprintf(output, "cmp w%d, #0\n", LReg);
                    fprintf(output, "cset w%d, ne\n", LReg);
                    fprintf(output, "cmp w%d, #0\n", RReg);
                    fprintf(output, "cset w%d, ne\n", RReg);
                    fprintf(output, "and w%d, w%d, w%d\n", LReg, LReg, RReg);
                    break;
                case BINARY_OP_OR:
                    fprintf(output, "cmp w%d, #0\n", LReg);
                    fprintf(output, "cset w%d, ne\n", LReg);
                    fprintf(output, "cmp w%d, #0\n", RReg);
                    fprintf(output, "cset w%d, ne\n", RReg);
                    fprintf(output, "orr w%d, w%d, w%d\n", LReg, LReg, RReg);
                    break;
            }
        }else{
            // Float expr
            if(lvalue->dataType == INT_TYPE)
                fprintf(output, "scvtf s%d, w%d\n", LReg, LReg);

            if(rvalue->dataType == INT_TYPE)
                fprintf(output, "scvtf s%d, w%d\n", RReg, RReg);

            switch(getExprOp(exprNode)){
                case BINARY_OP_ADD:
                    fprintf(output, "fadd s%d, s%d, s%d\n", LReg, LReg, RReg);
                    break;
                case BINARY_OP_SUB:
                    fprintf(output, "fsub s%d, s%d, s%d\n", LReg, LReg, RReg);
                    break;
                case BINARY_OP_MUL:
                    fprintf(output, "fmul s%d, s%d, s%d\n", LReg, LReg, RReg);
                    break;
                case BINARY_OP_DIV:
                    fprintf(output, "fdiv s%d, s%d, s%d\n", LReg, LReg, RReg);
                    break;
                case BINARY_OP_EQ:
                    fprintf(output, "fcmp s%d, s%d\n", LReg, RReg);
                    fprintf(output, "cset w%d, eq\n", LReg);
                    break;
                case BINARY_OP_GE:
                    fprintf(output, "fcmp s%d, s%d\n", LReg, RReg);
                    fprintf(output, "cset w%d, ge\n", LReg);
                    break;
                case BINARY_OP_LE:
                    fprintf(output, "fcmp s%d, s%d\n", LReg, RReg);
                    fprintf(output, "cset w%d, le\n", LReg);
                    break;
                case BINARY_OP_NE:
                    fprintf(output, "fcmp s%d, s%d\n", LReg, RReg);
                    fprintf(output, "cset w%d, ne\n", LReg);
                    break;
                case BINARY_OP_GT:
                    fprintf(output, "fcmp s%d, s%d\n", LReg, RReg);
                    fprintf(output, "cset w%d, gt\n", LReg);
                    break;
                case BINARY_OP_LT:
                    fprintf(output, "fcmp s%d, s%d\n", LReg, RReg);
                    fprintf(output, "cset w%d, lt\n", LReg);
                    break;
                case BINARY_OP_AND:
                    fprintf(output, "fcmp s%d, #0\n", LReg);
                    fprintf(output, "cset w%d, ne\n", LReg);
                    fprintf(output, "fcmp s%d, #0\n", RReg);
                    fprintf(output, "cset w%d, ne\n", RReg);
                    fprintf(output, "orr w%d, w%d, w%d\n", LReg, LReg, RReg);
                    break;
                case BINARY_OP_OR:
                    fprintf(output, "fcmp s%d, #0\n", LReg);
                    fprintf(output, "cset w%d, ne\n", LReg);
                    fprintf(output, "fcmp s%d, #0\n", RReg);
                    fprintf(output, "cset w%d, ne\n", RReg);
                    fprintf(output, "orr w%d, w%d, w%d\n", LReg, LReg, RReg);
                    break;
            }
        }
        freeReg(RReg);
        return LReg;
    }else{
        // Unary operation
 
        unpack(it, value);
        REG reg = genExprRelated(value);

        if(value->dataType == INT_TYPE){
            switch(getExprOp(exprNode)){
                case UNARY_OP_POSITIVE:
                    break;
                case UNARY_OP_NEGATIVE:
                    fprintf(output, "neg w%d, w%d", reg, reg);
                    break;
                case UNARY_OP_LOGICAL_NEGATION:
                    fprintf(output, "cmp w%d, #0\n", reg);
                    fprintf(output, "cset w%d, eq\n", reg);
                    break;
            }
        }else{
            switch(getExprOp(exprNode)){
                case UNARY_OP_POSITIVE:
                    break;
                case UNARY_OP_NEGATIVE:
                    fprintf(output, "fneg s%d, s%d", reg, reg);
                    break;
                case UNARY_OP_LOGICAL_NEGATION:
                    fprintf(output, "fcmp s%d, #0\n", reg);
                    fprintf(output, "cset w%d, eq\n", reg);
                    break;
            }
        }
        return reg;
    }
}

REG genArrayRef(AST_NODE *idNode)
{
    assert ( idNode->nodeType == IDENTIFIER_NODE );
    assert ( getIDEntry(idNode) != NULL );
    assert ( getIDAttr(idNode)->attributeKind == VARIABLE_ATTRIBUTE );
    assert ( getIDKind(idNode) == ARRAY_ID );
    TypeDescriptor* typeDescriptor = getIDTypeDescriptor(idNode);

    REG varReg;
    if(getIDGlobal(idNode)){
        varReg = getReg();
        fprintf(output, "ldr x%d, =_g_%s\n", varReg, getIDName(idNode));
    }else{
        int stackOffset = getIDOffset(idNode);
        varReg = genIntLiteral(stackOffset);
        fprintf(output, "sub x%d, x29, x%d\n", varReg, varReg);
        fprintf(stderr, "Array ref name: %s, offset: %d\n", getIDName(idNode), stackOffset);
    }

    int i = 0;
    int *sizes = typeDescriptor->properties.arrayProperties.sizeInEachDimension;
    AST_NODE *dimNode = idNode->child;

    REG offsetReg = getReg();
    fprintf(output, "mov x%d, #0\n", offsetReg);
    forEach(dimNode){
        REG sizeReg = genIntLiteral(sizes[i]);
        fprintf(output, "mul x%d, x%d, x%d\n", offsetReg, offsetReg, sizeReg);
        freeReg(sizeReg);

        REG indexReg = genExprRelated(dimNode);
        fprintf(output, "lsl x%d, x%d, #2\n", indexReg, indexReg);
        fprintf(output, "add x%d, x%d, x%d\n", offsetReg, offsetReg, indexReg);
        freeReg(indexReg);

        ++i;
    }

    if(getIDGlobal(idNode))
        fprintf(output, "add x%d, x%d, x%d\n", varReg, varReg, offsetReg);
    else
        fprintf(output, "sub x%d, x%d, x%d\n", varReg, varReg, offsetReg);

    freeReg(offsetReg);
    if(idNode->dataType == INT_TYPE){
        fprintf(output, "ldr w%d, [x%d, #0]\n", varReg, varReg);
    }else{
        fprintf(output, "ldr s%d, [x%d, #0]\n", varReg, varReg);
    }

    return varReg;
}

REG genVariableRef(AST_NODE *idNode)
{
    assert ( idNode->nodeType == IDENTIFIER_NODE );
    assert ( getIDEntry(idNode) != NULL );
    assert ( getIDAttr(idNode)->attributeKind == VARIABLE_ATTRIBUTE );
    TypeDescriptor* typeDescriptor = getIDTypeDescriptor(idNode);

    REG reg;

    if(getIDKind(idNode) == ARRAY_ID){
        return genArrayRef(idNode);
    }else{
        if(getIDGlobal(idNode)){
            reg = getReg();
            fprintf(output, "ldr x%d, =_g_%s\n", reg, getIDName(idNode));
        }else{
            int offset = getIDOffset(idNode);
            fprintf(stderr, "Var ref name: %s, offset: %d\n", getIDName(idNode), offset);
            reg = genIntLiteral(offset);
            fprintf(output, "sub x%d, x29, x%d\n", reg, reg);
        }
        if(idNode->dataType == INT_TYPE){
            fprintf(output, "ldr w%d, [x%d, #0]\n", reg, reg);
        }else{
            fprintf(output, "ldr s%d, [x%d, #0]\n", reg, reg);
        }
    }
    return reg;
}

REG genConstValue(AST_NODE *constValueNode)
{
    assert ( constValueNode->nodeType == CONST_VALUE_NODE ||
            (constValueNode->nodeType == EXPR_NODE && isConstExpr(constValueNode)) );

    REG reg;

    if(constValueNode->dataType == INT_TYPE){
        reg = genIntLiteral(getExprValue(constValueNode));
    }else if(constValueNode->dataType == FLOAT_TYPE){
        reg = genFloatLiteral(getExprValue(constValueNode));
    }else{
        reg = genStrLiteral(constValueNode->semantic_value.const1->const_u.sc);
    }

    return reg;
}
