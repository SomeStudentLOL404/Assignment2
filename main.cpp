#include <iostream>
#include <cstring>
#include <fstream>
#include "tokens.h"
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

//

int main(int argc, char *argv[])
{
    ifstream infile1;
    bool flagv = false;
    bool flags = false;
    bool flaga = false;
    for (int i = 1; i < argc; i++)
    {

        //First character in the argument contains '-'
        if (argv[i][0] == '-')
        {
            //About strcmp = http://www.cplusplus.com/reference/cstring/strcmp/
            if (strcmp((argv[i]), "-v") == 0)
            {
                flagv = true;
            }
            else if (strcmp((argv[i]), "-sum") == 0)
            {
                flags = true;
            }
            else if (strcmp((argv[i]), "-allids") == 0)
            {
                flaga = true;
            }
            else
            {
                //A invalid flag was passed (e.g. -chocolate)
                cout << "INVALID FLAG " << argv[i] << endl;
                return -1;
            }
        }
            //If it does NOT contain a '-', then its a file
        else
        {
            infile1.open(argv[i]);

            //Change argc > 2 later, bad use
            if (argc > 5)
            {
                //If more than 1 file name is being passed, throw an error
                cout << "TOO MANY FILE NAMES" << endl;
                return -1;
            }
                //If unable to open, throw an error
            else if (!infile1.is_open())
            {
                cout << "UNABLE TO OPEN " << argv[i] << endl;
                return -1;
            }
                //Check to see if the text file is empty - If its empty, print nothing and exit
            else if (infile1.peek() == EOF)
            {
                return -1;
            }
            else
            {
                Token tok;
                int lineNumber = 0;

                int tokenCount = 0;
                int identCount = 0;
                int tStringCount = 0;

                vector<string> IDENTVect;
                vector<string> HandleDetect = {"PLUS", "MINUS", "STAR", "SLASH", "ASSIGN", "EQ", "NEQ", "LT", "LEQ", "GT", "GEQ", "LOGICAND", "LOGICOR", "LPAREN", "RPAREN", "SC",
                                                "PRINT", "IF", "THEN", "TRUE", "FALSE",
                                                "IDENT", "ICONST", "SCONST", "DONE"};

                while ((tok = getNextToken(&infile1, &lineNumber)) != DONE && tok != ERR)
                {

                    if (flagv)
                    {
                        cout << tok << endl;
                    }
                    if (flags)
                    {
                        //Not working, maybe done not properly?
                       tokenCount = tokenCount + 1;

                       //Checks to see how many identities - WORKING
                        if(tok == IDENT)
                        {
                            identCount = identCount + 1;
                        }
                        if(tok == SCONST)
                        {
                            tStringCount = tStringCount + 1;
                        }
                    }
                    if (flaga)
                    {
                        if(tok == IDENT)
                        {
                            IDENTVect.push_back(tok.GetLexeme());
                        }
                        else
                        {
                            // do nothing
                        }
                    }
                }
                if (tok == ERR)
                {
                    cerr << "Error on line " << lineNumber << " (\"" << tok.GetLexeme() << ")" << endl;
                }
                //Identities first
                if (flaga)
                {
                    sort(IDENTVect.begin(),IDENTVect.end());
                    cout << "IDENTIFIERS: ";
                    for(unsigned int i = 0; i <= IDENTVect.size() -1; ++i)
                    {
                        if (i == (IDENTVect.size() - 1))
                        {
                            cout << IDENTVect[i] << endl;
                        }
                        else
                        {
                            cout << IDENTVect[i] << ", ";
                        }
                    }
                }
                if (flags)
                {
                   cout << "Total lines: " << tok.GetLinenum() << endl;
                   cout << "Total tokens: " << tokenCount << endl;
                   cout << "Total identifiers: " << identCount << endl;
                   cout << "Total strings: " << tStringCount << endl;
                }

            }
            //cout << flush;
        }
    }
    return 0;
}


