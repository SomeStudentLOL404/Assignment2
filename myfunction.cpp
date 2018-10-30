#include "tokens.h"

using namespace std;

//We have a class called 'ostream'
ostream &operator<<(ostream &out, const Token &tok)
{
    /*
     We are overloading the << operator so now we type in cout followed by a token
     variable, then we will print out the token type, that is tok.GetTokenType(), followed
     by the Lexeme, which is tok.GetLexeme()
    */

    TokenType handleconvert = tok.GetTokenType();
    string handleconvstring;

    //CONVERTING INTEGERS TO PROPER HANDLE TYPE
    switch (handleconvert)
    {
        case PLUS:
            handleconvstring = "PLUS";
            break;
        case MINUS:
            handleconvstring = "MINUS";
            break;
        case STAR:
            handleconvstring = "STAR";
            break;
        case SLASH:
            handleconvstring = "SLASH";
            break;
        case ASSIGN:
            handleconvstring = "ASSIGN";
            break;
        case EQ:
            handleconvstring = "EQ";
            break;
        case NEQ:
            handleconvstring = "NEQ";
            break;
        case LT:
            handleconvstring = "LT";
            break;
        case LEQ:
            handleconvstring = "LEQ";
            break;
        case GT:
            handleconvstring = "GT";
            break;
        case GEQ:
            handleconvstring = "GEQ";
            break;
        case LOGICAND:
            handleconvstring = "LOGICAND";
            break;
        case LOGICOR:
            handleconvstring = "LOGICOR";
            break;
        case LPAREN:
            handleconvstring = "LPAREN";
            break;
        case RPAREN:
            handleconvstring = "RPAREN";
            break;
        case SC:
            handleconvstring = "SC";
            break;
        case PRINT:
            handleconvstring = "PRINT";
            break;
        case IF:
            handleconvstring = "IF";
            break;
        case THEN:
            handleconvstring = "THEN";
            break;
        case TRUE:
            handleconvstring = "TRUE";
            break;
        case FALSE:
            handleconvstring = "FALSE";
            break;
        case IDENT:
            handleconvstring = "IDENT";
            break;
        case ICONST:
            handleconvstring = "ICONST";
            break;
        case SCONST:
            handleconvstring = "SCONST";
            break;
        case ERR:
            handleconvstring = "ERR";
            break;
        case DONE:
            handleconvstring = "DONE";
            break;
    }

    //DO NOT REMOVE THIS!
    switch (handleconvert)
    {
        case IDENT:
            out << handleconvstring << '(' << tok.GetLexeme() << ')';
            break;
        case ICONST:
            out << handleconvstring << '(' << tok.GetLexeme() << ')';
            break;
        case SCONST:
            out << handleconvstring << '(' << tok.GetLexeme() << ')';
            break;
        default:
            out << handleconvstring;
    }
    return out;
}


