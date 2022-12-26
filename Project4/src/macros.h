#define STRINGIZE(arg)  STRINGIZE1(arg)
#define STRINGIZE1(arg) STRINGIZE2(arg)
#define STRINGIZE2(arg) #arg

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

#define FOR_EACH_1(what, iter, x) what(iter, x)
#define FOR_EACH_2(what, iter, x, ...)\
      what(iter, x);\
        FOR_EACH_1(what, iter, __VA_ARGS__)
#define FOR_EACH_3(what, iter, x, ...)\
      what(iter, x);\
        FOR_EACH_2(what, iter, __VA_ARGS__)
#define FOR_EACH_4(what, iter, x, ...)\
      what(iter, x);\
        FOR_EACH_3(what, iter,  __VA_ARGS__)
#define FOR_EACH_5(what, iter, x, ...)\
      what(iter, x);\
       FOR_EACH_4(what,  iter, __VA_ARGS__)
#define FOR_EACH_6(what, iter, x, ...)\
      what(iter, x);\
        FOR_EACH_5(what,  iter, __VA_ARGS__)
#define FOR_EACH_7(what, iter, x, ...)\
      what(iter, x);\
        FOR_EACH_6(what,  iter, __VA_ARGS__)
#define FOR_EACH_8(what, iter, x, ...)\
      what(iter, x);\
        FOR_EACH_7(what,  iter, __VA_ARGS__)

#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) FOR_EACH_ARG_N(__VA_ARGS__) 
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N 
#define FOR_EACH_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0

#define FOR_EACH_(N, what, iter, ...) CONCATENATE(FOR_EACH_, N)(what, iter, __VA_ARGS__)
#define FOR_EACH(what, iter, ...) FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), what, iter, __VA_ARGS__)

#define UNPACK_INTERNAL(iter, varname) AST_NODE* varname = iter; iter = iter->rightSibling

#define unpack(iter, ...) FOR_EACH(UNPACK_INTERNAL, iter, __VA_ARGS__)
#define new(type) ((type*) malloc(sizeof(type)))
#define forEach(iter) for(;iter;iter=iter->rightSibling)
       
#define loop1 for(int __loop1_it=1; __loop1_it; __loop1_it=0)

#define getIDName(idNode) (idNode->semantic_value.identifierSemanticValue.identifierName)
#define getIDKind(idNode) (idNode->semantic_value.identifierSemanticValue.kind)
#define getIDEntry(idNode) (idNode->semantic_value.identifierSemanticValue.symbolTableEntry)
#define setIDEntry(idNode, val) (idNode->semantic_value.identifierSemanticValue.symbolTableEntry = val)
#define getIDAttr(idNode) (getIDEntry(idNode)->attribute)
#define getIDTypeDescriptor(idNode) (getIDAttr(idNode)->attr.typeDescriptor)
#define getIDOffset(idNode) (getIDAttr(idNode)->offset)
#define setIDOffset(idNode, val) (getIDAttr(idNode)->offset = (val))
#define getIDGlobal(idNode) (getIDAttr(idNode)->global)
#define setIDGlobal(idNode, val) (getIDAttr(idNode)->global = (val))

#define getDeclKind(declNode) (declNode->semantic_value.declSemanticValue.kind)
#define setDeclKind(declNode, val) (declNode->semantic_value.declSemanticValue.kind = val)

#define getStmtKind(stmtNode) (stmtNode->semantic_value.stmtSemanticValue.kind)

#define getTypeEntry(idNode) getIDEntry(idNode)
#define setTypeEntry(idNode, val) setIDEntry(idNode, val)
#define getFunctionSignature(idNode) (getTypeEntry(idNode->child->rightSibling)->attribute->attr.functionSignature)
#define getHeadFunctionSignature(idNode) (getTypeEntry(idNode)->attribute->attr.functionSignature)
#define getTypeDescriptor(idNode) (getTypeEntry(idNode)->attribute->attr.typeDescriptor)
#define setTypeDescriptor(idNode, val) (getTypeEntry(idNode)->attribute->attr.typeDescriptor = val)

#define getParamType(param) (param->type->kind == SCALAR_TYPE_DESCRIPTOR ? \
        param->type->properties.dataType : \
        param->type->properties.arrayProperties.elementType)

#define isConstExpr(exprNode) (exprNode->nodeType == CONST_VALUE_NODE || (exprNode->nodeType == EXPR_NODE && exprNode->semantic_value.exprSemanticValue.isConstEval))
#define getConstType(constNode) (constNode->semantic_value.const1->const_type)
#define getExprType(exprNode) (exprNode->dataType)
#define getExprKind(exprNode) (exprNode->semantic_value.exprSemanticValue.kind)
#define getExprOp(exprNode) (getExprKind(exprNode) == UNARY_OPERATION ? exprNode->semantic_value.exprSemanticValue.op.unaryOp : exprNode->semantic_value.exprSemanticValue.op.binaryOp)
#define setExprType(exprNode, type) (exprNode->dataType = type)
#define getExprValue(exprNode) ( \
        getExprType(exprNode) == INT_TYPE ? \
            ( exprNode->nodeType == CONST_VALUE_NODE ? \
                exprNode->semantic_value.const1->const_u.intval : \
                exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue ) : \
            ( exprNode->nodeType == CONST_VALUE_NODE ? \
                exprNode->semantic_value.const1->const_u.fval : \
                exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue ) )
#define setExprValue(exprNode, val) ( \
        getExprType(exprNode) == INT_TYPE ? \
        (exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = val): \
        (exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = val) )

#define getParamDeclName(node) getIDName(node->child->rightSibling)
#define getParamDeclType(node) getTypeDescriptor(node->child->rightSibling)

#define addArrayDim(arrayProperties, val) ( \
        arrayProperties->dimension < MAX_ARRAY_DIMENSION ? \
        (arrayProperties->sizeInEachDimension[arrayProperties->dimension++] = val) : \
        false )

#define isNullNode(node) (node->nodeType == NUL_NODE)

#define true 1
#define false 0

#define findParentDecl(iter, type) \
        for(;iter;iter=iter->parent){ \
            if (iter->nodeType == DECLARATION_NODE && getDeclKind(iter) == type) \
                break; \
        }
 
/* unpack example
AST_NODE* it = parentNode->child;
unpack(it, a, b, d);

=>

a = it; it = it->rightSibling;
...
*/

/* new example
TYPE* x = new(TYPE);
*/

/* forEach example
AST_NODE* it = parentNode->child;
forEach (it) {
    it->...
}
*/
