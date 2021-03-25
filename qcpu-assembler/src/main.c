#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char* _ALPHANUMSYM = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.$";

typedef struct _string
{
    char* data;
    size_t size;
    size_t cap;
} string;

string* string_init0()
{
    string* r = (string*)malloc(sizeof(string));
    r->size = 0;
    r->cap = 1;
    r->data = (char*)malloc(2);
    r->data[0] = '\0';
    return r;
}

string* string_init1(const char* data)
{
    string* r = (string*)malloc(sizeof(string));
    r->size = strlen(data);
    r->cap = r->size;
    r->data = (char*)malloc(r->cap + 1);
    memcpy(r->data, data, r->size + 1);
    return r;
}

string* stringcat0(string* a, const string b)
{
    if((a->size + b.size) >= a->cap)
        a->cap = 2 * (a->size + b.size);
    a->data = (char*)realloc(a->data, a->cap + 1);
    a->data[a->size + b.size] = '\0';
    memcpy(a->data + a->size, b.data, b.size);
    a->size += b.size;
    return a;
}

string* stringcat1(string* a, const char* b)
{
    if((a->size + strlen(b)) >= a->cap)
        a->cap = 2 * (a->size + strlen(b));
    a->data = (char*)realloc(a->data, a->cap + 1);
    a->data[a->size + strlen(b)] = '\0';
    memcpy(a->data + a->size, b, strlen(b));
    a->size += strlen(b);
    return a;
}

string* stringcat2(string* a, const char b)
{
    if((a->size + 1) >= a->cap)
        a->cap = 2 * (a->size + 1);
    a->data = (char*)realloc(a->data, a->cap + 1);
    a->data[a->size + 1] = '\0';
    a->data[a->size] = b;
    a->size++;
    return a;
}

int stringcmp0(string a, const string b)
{
    return strcmp(a.data, b.data);
}

int stringcmp1(const string a, const char* b)
{
    return strcmp(a.data, b);
}

void free_string0(string r)
{
    free(r.data);
}

void free_string1(string* r)
{
    free(r->data);
    free(r);
}

typedef enum _toktype
{
    TT_ALPHANUMSYM
} toktype;

struct _unit;
typedef struct unit* _unit;

typedef struct _span
{
    size_t idl; // left index
    size_t idr; // right index
    size_t ln; // line number
    _unit* unit; // the compilation unit the span is in
} span;

typedef struct _token
{
    span span;
    string data;
    toktype type;
} token;

token* token_init0()
{
    token* r = (token*)malloc(sizeof(token));
    r->data = *string_init0();
    return r;
}

void free_token0(token token)
{
    free_string0(token.data);
}

void free_token1(token* token)
{
    free_string0(token->data);
    free(token);
}

typedef struct _lexer
{
    token* tokcurr;
    size_t pos;
    size_t ln;
} lexer;

typedef struct _unit
{
    string fname;
    string fdata; // the entire source string for the compilation unit
    lexer lexer; // the compilation unit's lexer state
} unit;

void lexer_advance(unit* u)
{
    u->lexer.tokcurr = NULL;
    while(!u->lexer.tokcurr)
    {
        if(u->fdata.data[u->lexer.pos] == '\n')
        {
            u->lexer.pos++;
            u->lexer.ln++;
        }
        else if(u->fdata.data[u->lexer.pos] == ';')
        {
            do
            {
                u->lexer.pos++;
            }
            while(u->fdata.data[u->lexer.pos] != '\n');
        }
        else if(strchr(_ALPHANUMSYM, u->fdata.data[u->lexer.pos]) != NULL && u->fdata.data[u->lexer.pos] != '\0')
        {
            u->lexer.tokcurr = token_init0();
            u->lexer.tokcurr->span.idl = u->lexer.pos;
            u->lexer.tokcurr->span.ln = u->lexer.ln;
            do
            {
                stringcat2(&u->lexer.tokcurr->data, u->fdata.data[u->lexer.pos++]);
            }
            while(strchr(_ALPHANUMSYM, u->fdata.data[u->lexer.pos]) != NULL && u->fdata.data[u->lexer.pos] != '\0');
            u->lexer.tokcurr->span.idr = u->lexer.pos;
            u->lexer.tokcurr->type = TT_ALPHANUMSYM;
        }
        else if(u->fdata.data[u->lexer.pos] == '\0')
        {
            break;
        }
        else u->lexer.pos++;
    }
}

token* lexer_any(unit *u) // give me any token (this does all the actual code)
{
    token* res = u->lexer.tokcurr;
    lexer_advance(u);
    return res;
}

unit* unit_init(const char* fname, const char* fdata)
{
    unit* r = (unit*)malloc(sizeof(unit));
    r->fname = *string_init1(fname);
    r->fdata = *string_init1(fdata);
    r->lexer.tokcurr = NULL;
    r->lexer.pos = 0;
    r->lexer.ln = 1;
    lexer_advance(r);
    return r;
}

int main(int argc, char const *argv[])
{
    if(argc != 2)
        exit(EXIT_FAILURE);
    FILE* fp = fopen(argv[1], "r");
    size_t fsize = 0;
    while(fgetc(fp) != EOF)
    {
        fsize++;
    }
    rewind(fp);
    char* fdata = malloc(fsize + 1);
    fread(fdata, fsize, 1, fp);
    fdata[fsize] = '\0';
    fclose(fp);
    unit u = *unit_init(argv[1], fdata);
    token* tok = lexer_any(&u);
    do
    {
        printf("%s", tok->data.data);
        tok = lexer_any(&u);
    }
    while(tok);
    return 0;
}