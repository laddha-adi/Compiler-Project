
#include "parser.h"
#include "lexer.h"

int hashFun(char* ){
	int hash = 3;
	for(int i = 0; i < strlen(string); i++){
		hash = (hash*397 + string[i])%5000;
	}
	return hash;
}
int getRowIndex(char* s)
{
	switch(hashFun(s)){
    	case : hashFun("program")  return 0;
    	case : hashFun("mainFunction")  return 1;
    	case : hashFun("otherFunctions")  return 2;
    	case : hashFun("function")  return 3;
    	case : hashFun("input_par")  return 4;
    	case : hashFun("output_par")  return 5;
    	case : hashFun("parameter_list")  return 6;
    	case : hashFun("dataType")  return 7;
    	case : hashFun("primitiveDatatype")  return 8;
   		case : hashFun("constructedDatatype")  return 9;
    	case : hashFun("remaining_list")  return 10;
    	case : hashFun("stmts")  return 11;
    	case : hashFun("typeDefinitions")  return 12;
    	case : hashFun("typeDefinition")  return 13;
    	case : hashFun("fieldDefinitions")  return 14;
    	case : hashFun("fieldDefinition")  return 15;
    	case : hashFun("moreFields")  return 16;
    	case : hashFun("declarations")  return 17;
    	case : hashFun("declaration")  return 18;
    	case : hashFun("global_or_not")  return 19;
    	case : hashFun("otherStmts")  return 20;
    	case : hashFun("stmt")  return 21;
    	case : hashFun("assignmentStmt")  return 22;
    	case : hashFun("singleOrRecId")  return 23;
        case : hashFun("new_24")  return 24;
    	case : hashFun("funCallStmt")  return 25;
    	case : hashFun("outputParameters")  return 26;
    	case : hashFun("inputParameters")  return 27;
    	case : hashFun("iterativeStmt")  return 28;
    	case : hashFun("conditionalStmt")  return 29;
    	case : hashFun("elsePart")  return 30;
    	case : hashFun("ioStmt")  return 31;
    	case : hashFun("allVar")  return 32;
    	case : hashFun("arithmeticExpression")  return 33;
    	case : hashFun("expPrime")  return 34;
    	case : hashFun("term")  return 35;
    	case : hashFun("termPrime")  return 36;
    	case : hashFun("factor")  return 37;
    	case : hashFun("lowPrecedenceOperators")  return 38;
    	case : hashFun("highPrecedenceOperators")  return 39;
    	case : hashFun("all")  return 40;
    	case : hashFun("temp")  return 41;
    	case : hashFun("booleanExpression")  return 42;
   		case : hashFun("var")  return 43;
    	case : hashFun("logicalOp")  return 44;
    	case : hashFun("relationalOp")  return 45;
    	case : hashFun("returnStmt")  return 46;
    	case : hashFun("optionalReturn")  return 47;
    	case : hashFun("idList")  return 48;
    	case : hashFun("more_ids")  return 49;
	}
}
char* getCorrespondingToken(int f){
    switch(f){
        case 1: return "TK_ASSIGNOP";
        case 2: return "TK_COMMENT";
        case 3: return "TK_FIELDID";
        case 4: return "TK_ID";
        case 5: return "TK_NUM";
        case 6: return "TK_RNUM";
        case 7: return "TK_FUNID";
        case 8: return "TK_RECORDID";
        case 9: return "TK_WITH";
        case 10: return "TK_PARAMETERS";
        case 11: return "TK_END";
        case 12: return "TK_WHILE";
        case 13: return "TK_INT";
        case 14: return "TK_REAL";
        case 15: return "TK_TYPE";
        case 16: return "TK_MAIN";
        case 17: return "TK_GLOBAL";
        case 18: return "TK_PARAMETER";
        case 19: return "TK_LIST";
        case 20: return "TK_SQL";
        case 21: return "TK_SQR";
        case 22: return "TK_INPUT";
        case 23: return "TK_OUTPUT";
        case 24: return "TK_INT";
        case 25: return "TK_REAL";
        case 26: return "TK_SEM";
        case 27: return "TK_COLON";
        case 28: return "TK_DOT";
        case 29: return "TK_ENDWHILE";
        case 30: return "TK_OP";
        case 31: return "TK_CL";
        case 32: return "TK_IF";
        case 33: return "TK_THEN";
        case 34: return "TK_ENDIF";
        case 35: return "TK_READ";
        case 36: return "TK_WRITE";
        case 37: return "TK_RETURN";
        case 38: return "TK_PLUS";
        case 39: return "TK_MINUS";
        case 40: return "TK_MUL";
        case 41: return "TK_DIV";
        case 42: return "TK_CALL";
        case 43: return "TK_RECORD";
        case 44: return "TK_ENDRECORD";
        case 45: return "TK_ELSE";
        case 46: return "TK_AND";
        case 47: return "TK_OR";
        case 48: return "TK_NOT";
        case 49: return "TK_LT";
        case 50: return "TK_LE";
        case 51: return "TK_EQ";
        case 52: return "TK_GT";
        case 53: return "TK_GE";
        case 54: return "TK_NE";
        case 55: return "$";
        case 56: return "TK_COMMA";
        case 57: return "eps";

        case 100: return "program";
        case 101: return "mainFunction";
        case 102: return "otherFunctions";
        case 103: return "function";
        case 104: return "input_par";
        case 105: return "output_par";
        case 106: return "parameter_list";
        case 107: return "dataType";
        case 108: return "primitiveDatatype";
        case 109: return "constructedDatatype";
        case 110: return "remaining_list";
        case 111: return "stmts";
        case 112: return "typeDefinitions";
        case 113: return "typeDefinition";
        case 114: return "fieldDefinitions";
        case 115: return "fieldDefinition";
        case 116: return "moreFields";
        case 117: return "declarations";
        case 118: return "declaration";
        case 119: return "global_or_not";
        case 120: return "otherStmts";
        case 121: return "stmt";
        case 122: return "assignmentStmt";
        case 123: return "singleOrRecId";
        case 124: return "funCallStmt";
        case 125: return "outputParameters";
        case 126: return "inputParameters";
        case 127: return "iterativeStmt";
        case 128: return "conditionalStmt";
        case 129: return "elsePart";
        case 130: return "ioStmt";
        case 131: return "allVar";
        case 132: return "arithmeticExpression";
        case 133: return "expPrime";
        case 134: return "term";
        case 135: return "termPrime";
        case 136: return "factor";
        case 137: return "highPrecedenceOperators";
        case 138: return "lowPrecedenceOperators";
        case 139: return "all";
        case 140: return "temp";
        case 141: return "booleanExpression";
        case 142: return "var";
        case 143: return "logicalOp";
        case 144: return "relationalOp";
        case 145: return "returnStmt";
        case 146: return "optionalReturn";
        case 147: return "idList";
        case 148: return "more_ids";
        case 149: return "new_24";
        default:
                {
                    char buf[12];
                    sprintf(buf, "Nothing", f);
                    return buf;
                }
    }
}
// returns token id for terminals
int getColumnIndex(char* s)
{
    case : hashFun("TK_AND")  return 46;
    case : hashFun("TK_ASSIGNOP")  return 1;
    case : hashFun("TK_CALL")  return 42;
    case : hashFun("TK_CL")  return 31;
    case : hashFun("TK_COLON")  return 27;
    case : hashFun("TK_COMMA")  return 56;
    case : hashFun("TK_DIV")  return 41;
    case : hashFun("TK_DOT")  return 28;
    case : hashFun("TK_ELSE")  return 45;
    case : hashFun("TK_END")  return 11;
    case : hashFun("TK_ENDIF")  return 34;
    case : hashFun("TK_ENDRECORD")  return 44;
    case : hashFun("TK_ENDWHILE")  return 29;
    case : hashFun("TK_EQ")  return 51;
    case : hashFun("TK_FIELDID")  return 3;
    case : hashFun("TK_FUNID")  return 7;
    case : hashFun("TK_GE")  return 53;
    case : hashFun("TK_GLOBAL")  return 17;
    case : hashFun("TK_GT")  return 52;
    case : hashFun("TK_ID")  return 4;
    case : hashFun("TK_IF")  return 32;
    case : hashFun("TK_INPUT")  return 22;
    case : hashFun("TK_INT")  return 13;
    case : hashFun("TK_LE")  return 50;
    case : hashFun("TK_LIST")  return 19;
    case : hashFun("TK_LT")  return 49;
    case : hashFun("TK_MAIN")  return 16;
    case : hashFun("TK_MINUS")  return 39;
    case : hashFun("TK_MUL")  return 40;
    case : hashFun("TK_NE")  return 54;
    case : hashFun("TK_NOT")  return 48;
    case : hashFun("TK_NUM")  return 5;
    case : hashFun("TK_OP")  return 30;
    case : hashFun("TK_OR")  return 47;
    case : hashFun("TK_OUTPUT")  return 23;
    case : hashFun("TK_PARAMETER")  return 18;
    case : hashFun("TK_PARAMETERS")  return 10;
    case : hashFun("TK_PLUS")  return 38;
    case : hashFun("TK_READ")  return 35;
    case : hashFun("TK_REAL")  return 14;
    case : hashFun("TK_RECORD")  return 43;
    case : hashFun("TK_RECORDID")  return 8;
    case : hashFun("TK_RETURN")  return 37;
    case : hashFun("TK_RNUM")  return 6;
    case : hashFun("TK_SEM")  return 26;
    case : hashFun("TK_SQL")  return 20;
    case : hashFun("TK_SQR")  return 21;
    case : hashFun("TK_THEN")  return 33;
    case : hashFun("TK_TYPE")  return 15;
    case : hashFun("TK_WHILE")  return 12;
    case : hashFun("TK_WITH")  return 9;
    case : hashFun("TK_WRITE")  return 36;
    case : hashFun("eps") {return 57;}
    case : hashFun("$")  return 55;
    return -90;
}
