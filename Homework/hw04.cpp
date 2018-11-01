/* Juan Garcia
 * CMPS 223
 * Homework 4
 * April 26, 2013
 */

#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstring>
#include <cstdlib>
using namespace std;

#ifndef ELEMTYPE
#define ELEMTYPE int
#endif

#ifndef ZEROELEM
#define ZEROELEM 0
#endif

#ifndef MAX_SIZE
#define MAX_SIZE 100
#endif

struct arrayStack
{
    ELEMTYPE array[MAX_SIZE];
    int count;
};

void initStack(arrayStack *);
bool empty(arrayStack *);
bool full(arrayStack *);
bool push(arrayStack *, ELEMTYPE);
bool pop(arrayStack *);
ELEMTYPE top(arrayStack *);
bool isInteger(char *);
bool isDouble(char *);
bool isOperator(char *);
void evaluatePostfix();

int main()
{
    char response[10];
    bool flag;

    do
    {
        evaluatePostfix();
        cout << endl;

        cout << "Do you wish to enter another expression? [Y|n] ";
        cin >> setw(10) >> response;

        while(cin.fail())
        {
            cin.clear();
            cin.ignore(50, '\n');
            cout << "You can only enter up to 9 characters.\n";
            cout << "Do you wish to continue? (y|N) ";
            cin >> setw(10) >> response;
        }

        cin.ignore();

        for(int i = 0; i < strlen(response); i++)
        {
            response[i] = tolower(response[i]);
        }

        if(strlen(response) > 1)
        {
            flag = (strcmp(response, "yes") == 0);
        }
        else
        {
            flag = (response[0] == 'y');
        }

    }while(flag);

    return 0;
}

void initStack(arrayStack *s)
{
    for(int i = 0; i < MAX_SIZE; i++)
    {
        s->array[i] = 0;
    }
    s->count = 0;
}

bool empty(arrayStack *s)
{
    return(s->count == 0);
}

bool full(arrayStack *s)
{
    return(s->count == MAX_SIZE);
}

bool push(arrayStack *s, ELEMTYPE x)
{
    if(full(s))
    {
        cout << "Stack Full. push() failed\n";
        return(false);
    }
    s->array[s->count] = x;
    s->count++;
    cout << "Push(" << x << ")\n";

    return(true);
}

bool pop(arrayStack *s)
{
    if(empty(s))
    {
        cout << "Stack Empty. pop() failed\n";
        return(false);
    }
    s->count--;
    cout << "pop(): removed " << s->array[s->count] << endl;
    s->array[s->count] = 0;

    return(true);
}

ELEMTYPE top(arrayStack *s)
{
    if(empty(s))
    {
        return(0);
    }

    return(s->array[s->count - 1]);
}

bool isInteger(char *str)
{
    if(strlen(str) < 1)
    {
        return(false);
    }

    for(int i = 0; i < strlen(str); i++)
    {
        if(i == 0 && (str[i] == '-' || str[i] == '+'))
        {
            if(strlen(str) == 1)
            {
                return(false);
            }
        }
        else if(!isdigit(str[i]))
        {
            return(false);
        }
    }

    return(true);
}

bool isDouble(char *str)
{
    int dot = 0;

    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] == '.')
        {
            dot++;
            if(dot > 1)
            {
                return(false);
            }
        }
        else if(i == 0 && (str[i] == '-' || str[i] == '+'))
        {
            if(strlen(str) == 1)
            {
                return(false);
            }
        }
        else if(!isdigit(str[i]))
        {
            return(false);
        }
    }

    return(true);
}

bool isOperator(char *str)
{
    if(strlen(str) != 1)
    {
        return(false);
    }

    return(str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/' || str[0] == '%');
}

void evaluatePostfix()
{
    char line[256];
    char* *tokens = NULL;
    int count = 0;

    arrayStack Stack;
    initStack(&Stack);

    cout << "Enter a postfix expression: ";
    cin.getline(line, 256);

    for(int i = 0; i < strlen(line); i++)
    {
        if(isspace(line[i]))
        {
            count++;
            while(isspace(line[++i]) && i < strlen(line));
            i--;
        }
    }

    try
    {
        tokens = new char* [count + 1];
    }
    catch(bad_alloc)
    {
        tokens = NULL;
        exit(1);
    }

    int slot = 0;
    int len = strlen(line);
    int i = 0;
    while(i < len)
    {
        if(isspace(line[i]))
        {
            line[i++] = '\0';
        }
        else
        {
            tokens[slot++] = &(line[i]);
            while(!isspace(line[++i]) && i < len);
            line[i++] = '\0';
        }
    }

    for(int i = 0; i <= count; i++)
    {
        if(isInteger(tokens[i]))
        {
            int num = atoi(tokens[i]);
            if(!push(&Stack, num))
            {
                cout << "Error...";
                delete [] tokens;
            }
        }
        else if(isDouble(tokens[i]))
        {
            int num = atof(tokens[i]);
            if(!push(&Stack, num))
            {
                cout << "Error...";
                delete [] tokens;
            }
        }
        else if(isOperator(tokens[i]))
        {
            char op = tokens[i][0];

            /*if(!pop(&Stack))
            {
                cout << "Error...";
                delete [] tokens;
                return;
            }*/

            int right = top(&Stack);
            pop(&Stack);

            /*if(!pop(&Stack))
            {
                cout << "Error...";
                delete [] tokens;
                return;
            }*/

            int left = top(&Stack);
            pop(&Stack);

            if(op == '+')
            {
                push(&Stack, left + right);
            }
            else if(op == '-')
            {
                push(&Stack, left - right);
            }
            else if(op == '*')
            {
                push(&Stack, left * right);
            }
            else if(op == '/')
            {
                push(&Stack, left / right);
            }
            else if(op == '%')
            {
                push(&Stack, left % right);
            }
        }
        else
        {
            cout << "Error..." << endl;
        }
    }

    if(Stack.count == 1)
    {
        cout << top(&Stack);
    }
    else
    {
        cout << "Error. Invalid PostFix Expression..." << endl;
    }
}
