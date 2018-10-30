#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "tokens.h"

using namespace std;
Token tok;

Token getNextToken(istream *in, int *linenum)
{
    enum LexState
    {
        BEGIN, INID, INSTRING, ININT, INCOMMENT
    };
    LexState lexstate = BEGIN;
    string lexeme;
    char ch;

    while (in->get(ch))
    {
        if (ch == '\n')
        {
            (*linenum)++;
        }
        switch (lexstate)
        {
            case BEGIN:
                if (isspace(ch))
                {
                    continue;
                }
                else if (ch == '#')
                {
                    lexstate = INCOMMENT;
                }
                else if (isalpha(ch))
                {
                    lexeme.push_back(ch);
                    lexstate = INID;
                }
                else if (ch == '-' or isdigit(ch))
                {
                    lexeme.push_back(ch);
                    lexstate = ININT;
                }
                else if (ch == '"')
                {
                    lexstate = INSTRING;
                }
                else if (ch == '+')
                {
                    lexeme.push_back(ch);
                    return Token(PLUS, lexeme, *linenum);
                }
                else if (ch == '*')
                {
                    lexeme.push_back(ch);
                    return Token(STAR, lexeme, *linenum);
                }
                else if (ch == '/')
                {
                    lexeme.push_back(ch);
                    return Token(SLASH, lexeme, *linenum);
                }
                else if (ch == '=')
                {
                    if (in->peek() == '=')
                    {
                        in->get();
                        return Token(EQ, lexeme, *linenum);
                    }
                    else
                    {
                        lexeme.push_back(ch);
                        return Token(ASSIGN, lexeme, *linenum);
                    }
                }
                else if (ch == '!')
                {
                    if (in->peek() == '=')
                    {
                        in->get();

                        //lexeme.push_back(ch);
                        return Token(NEQ, lexeme, *linenum);
                    }
                    else
                    {
                        if (in->peek() == '\n')
                        {
                            (*linenum++);
                        }
                        cout << "Returne error at !" << endl;
                        return Token(ERR, lexeme, *linenum);
                    }
                }
                else if (ch == '<')
                {
                    if (in->peek() == '=')
                    {
                        in->get();
                        //lexeme.push_back(ch);
                        return Token(LEQ, lexeme, *linenum);
                    }
                    /*
                    else
                    {
                        if (in->peek() == '\n')
                        {
                            (*linenum++);
                        }
                        cout << "Returne error at <" << endl;
                        return Token(ERR, lexeme, *linenum);
                    }
                     */
                }
                else if (ch == '>')
                {
                    if (in->peek() == '=')
                    {
                        in->get();
                        // lexeme.push_back(ch);
                        return Token(GEQ, lexeme, *linenum);
                    }
                    /*
                    else
                    {
                        if (in->peek() == '\n')
                        {
                            (*linenum++);
                        }
                        cout << "Returne error at >" << endl;
                        return Token(ERR, lexeme, *linenum);
                    }
                     */
                }
                else if (ch == '&')
                {
                    if (in->peek() == '&')
                    {
                        in->get();
                        //lexeme.push_back(ch);
                        return Token(LOGICAND, lexeme, *linenum);
                    }
                    else
                    {
                        if (in->peek() == '\n')
                        {
                            (*linenum++);
                        }
                        cout << "Returne error at &" << endl;
                        return Token(ERR, lexeme, *linenum);
                    }
                }
                else if (ch == '|')
                {
                    if (in->peek() == '|')
                    {
                        in->get();
                        //lexeme.push_back(ch);
                        return Token(LOGICOR, lexeme, *linenum);
                    }
                    else
                    {
                        if (in->peek() == '\n')
                        {
                            (*linenum++);
                        }
                        cout << "Returne error at |" << endl;
                        return Token(ERR, lexeme, *linenum);
                    }

                }
                else if (ch == '(')
                {
                    lexeme.push_back(ch);
                    return Token(LPAREN, lexeme, *linenum);
                }
                else if (ch == ')')
                {
                    lexeme.push_back(ch);
                    return Token(RPAREN, lexeme, *linenum);
                }
                else if (ch == ';')
                {
                    lexeme.push_back(ch);
                    return Token(SC, lexeme, *linenum);
                }

                else
                {
                    if (in->peek() == '\n')
                    {
                        (*linenum++);
                    }
                    cout << "Returne error at FINALE" << endl;
                    return Token(ERR, lexeme, *linenum);
                }

                //
                break;
                //
            case INID:
                if (isalnum(ch))
                {
                    lexeme.push_back(ch);
                }
                else //if (isspace(ch))
                {
                    if(lexeme == "print" || lexeme == "PRINT")
                    {
                        lexeme.clear();
                        return Token(PRINT, lexeme, *linenum);
                    }
                    else if(lexeme == "if" || lexeme == "IF")
                    {
                        lexeme.clear();
                        return Token(IF, lexeme, *linenum);
                    }
                    else if(lexeme == "then" || lexeme == "THEN")
                    {
                        lexeme.clear();
                        return Token(THEN, lexeme, *linenum);
                    }
                    else if(lexeme == "true" || lexeme == "TRUE")
                    {
                        lexeme.clear();
                        return Token(TRUE, lexeme, *linenum);
                    }
                    else if(lexeme == "false" || lexeme == "FALSE")
                    {
                        lexeme.clear();
                        return Token(FALSE, lexeme, *linenum);
                    }
                    else
                    {
                        in->putback(ch);
                        (*linenum--);
                        return Token(IDENT, lexeme, *linenum);
                    }
                }
                break;
            case ININT:
                //If its not a digit
                if (!isdigit(ch))
                {
                    if (lexeme == "-")
                    {
                        if (ch == '\n')
                        {
                            (*linenum)--;
                        }
                        //(*linenum)--;
                        in->putback(ch);
                        return Token(MINUS, lexeme, *linenum);
                    }
                        //If it is
                    else
                    {
                        return Token(ICONST, lexeme, *linenum);
                    }
                }
                else
                {
                    lexeme.push_back(ch);
                    return Token(ICONST, lexeme, *linenum);
                }
                //Unreachable break
                //break;

            case INSTRING:
                if (ch == '"')
                {
                    return Token(SCONST, lexeme, *linenum);
                }
                else if (ch == '\n')
                {
                    lexeme.push_back(ch);
                    return Token(ERR, lexeme, *linenum);
                }
                lexeme.push_back(ch);
                break;

            case INCOMMENT:
                if (ch == '\n')
                {
                    (*linenum)--;
                    lexstate = BEGIN;
                }
                break;
        }
    }
    return Token(DONE, lexeme, *linenum);
}