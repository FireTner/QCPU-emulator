/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOK_LIM 0
#define TOK_CND 1

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
    r->data = (char*)malloc(sizeof(r->cap + 1));
    r->data[0] = '\0';
    return r;
}

string* string_init1(const char* data)
{
    string* r = (string*)malloc(sizeof(string));
    r->size = strlen(data);
    r->cap = r->size;
    r->data = (char*)malloc(sizeof(r->cap + 1));
    memcpy(r->data, data, r->size + 1);
    return r;
}

string* stringcat0(string* a, const string b)
{
    if((a->size + b.size) >= a->cap)
        a->cap = 2 * (a->size + b.size);
    a->data = (char*)realloc(a->data, sizeof(a->cap + 1));
    a->data[a->size + b.size] = '\0';
    memcpy(a->data + a->size, b.data, b.size);
    a->size += b.size;
    return a;
}

string* stringcat1(string* a, const char* b)
{
    if((a->size + strlen(b)) >= a->cap)
        a->cap = 2 * (a->size + strlen(b));
    a->data = (char*)realloc(a->data, sizeof(a->cap + 1));
    a->data[a->size + strlen(b)] = '\0';
    memcpy(a->data + a->size, b, strlen(b));
    a->size += strlen(b);
    return a;
}

string* stringcat2(string* a, const char b)
{
    if((a->size + 1) >= a->cap)
        a->cap = 2 * (a->size + 1);
    a->data = (char*)realloc(a->data, sizeof(a->cap + 1));
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

typedef struct _token
{
    string _tokdata;
    char type;
} token;

typedef struct _tokstream
{
    token* _toks;
    size_t _tokssize;
} tokstream;


const char* _ALPHANUMSYM = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.$";

const tokstream* tok_file(FILE* fp)
{
    fseek(fp, 0L, SEEK_END);
    const size_t fsize = ftell(fp);
    rewind(fp);
    char* fdata = malloc(fsize + 1);
    fread(fdata, fsize, 1, fp);
    fdata[fsize] = '\0';
    fclose(fp);
    token* _toks = (token*)malloc(sizeof(token));
    size_t _tokssize = 0;
    size_t _tokscap = 1;
    for(size_t i = 0; i < fsize; i++)
    {
        if(fdata[i] == ';')
        {
            do
            {
                i++;
            }
            while(fdata[i] != '\n');
        }
        else if(strchr(_ALPHANUMSYM, fdata[i]) != NULL)
        {
            _toks[_tokssize]._tokdata = *string_init0();
            if((_tokssize + 1) >= _tokscap)
                _tokscap = 2 * (_tokssize + 1);
            do
            {
                stringcat2(&_toks[_tokssize]._tokdata, fdata[i]);
                i++;
            }
            while(strchr(_ALPHANUMSYM, fdata[i]) != NULL);
            _tokssize++;
            _toks = (token*)realloc(_toks, _tokscap * sizeof(token));
        }
    }
    free(fdata);
    tokstream* _tokstream = (tokstream*)malloc(sizeof(tokstream));
    _tokstream->_tokssize = _tokssize;
    _tokstream->_toks = _toks;
    for(size_t i = 0; i < _tokstream->_tokssize; i++)
    {
        if(stringcmp1(_tokstream->_toks[i]._tokdata, "LIM") == 0)
        {
            _tokstream->_toks[i].type = TOK_LIM;
        }
        else if(stringcmp1(_tokstream->_toks[i]._tokdata, "CND") == 0)
        {
            _tokstream->_toks[i].type = TOK_CND;
        }
    }
    return _tokstream;
}

void free_tokstream(tokstream _tokstream)
{
    for(size_t i = 0; i < _tokstream._tokssize; i++)
    {
        free(_tokstream._toks[i]._tokdata.data);
    }
    free(_tokstream._toks);
}

int main(int argc, char const *argv[])
{
    if(argc != 2)
        exit(EXIT_FAILURE);
    FILE* fp = fopen(argv[1], "r");
    tokstream _tokstream = *tok_file(fp);
    for(size_t i = 0; i < _tokstream._tokssize; i++)
    {
        printf("%s", _tokstream._toks[i]._tokdata.data);
    }
    free_tokstream(_tokstream);
    return 0;
}
*/

//Online Lexer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    r->data = (char*)malloc(r->cap + 1);
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

struct _unit;
typedef struct unit* _unit;

typedef struct _span
{
    size_t idl; // left index
    size_t idr; // right index
    size_t ln; // line number
    _unit* unit; // the compilation unit the span is in
} span;

typedef enum _toktype
{
    TT_ALPHANUMSYM
} toktype;

typedef struct _token
{
    span span;
    string data;
    toktype type;
} token;

token* token_init()
{
    token* r = (token*)malloc(sizeof(token));
    r->data = *string_init0();
    return r;
}

typedef struct _lexer
{
    token tokcurr;
    size_t pos;
    size_t ln;
} lexer;

typedef struct _unit
{
    string fname;
    string fdata; // the entire source string for the compilation unit
    lexer lexer; // the compilation unit's lexer state
} unit;

token lexer_any(unit *u);

unit* unit_init(const char* fname, const char* fdata)
{
    unit* r = (unit*)malloc(sizeof(unit));
    r->fname = *string_init1(fname);
    r->fdata = *string_init1(fdata);
    r->lexer.tokcurr = *token_init();
    r->lexer.pos = 0;
    r->lexer.ln = 0;
    lexer_any(r);
    return r;
}

const char* _ALPHANUMSYM = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.$";

token lexer_any(unit *u) // give me any token (this does all the actual code)
{
    token res = u->lexer.tokcurr;
    token* toknext = NULL;
    while(!toknext)
    {
        if(u->fdata.data[u->lexer.pos] == ';')
        {
            do
            {
                u->lexer.pos++;
            }
            while(u->fdata.data[u->lexer.pos] != '\n');
        }
        if(u->fdata.data[u->lexer.pos] == '\n')
        {
            u->lexer.pos++;
            u->lexer.ln++;
        }
        else if(strchr(_ALPHANUMSYM, u->fdata.data[u->lexer.pos]))
        {
            toknext = token_init();
            toknext->span.idl = u->lexer.pos;
            do
            {
                stringcat2(&toknext->data, u->fdata.data[u->lexer.pos]);
                u->lexer.pos++;
            }
            while(strchr(_ALPHANUMSYM, u->fdata.data[u->lexer.pos]));
            toknext->span.idr = u->lexer.pos;
            toknext->span.ln = u->lexer.ln;
            toknext->type = TT_ALPHANUMSYM;
        }
        else
            u->lexer.pos++;
    }
    u->lexer.tokcurr = *toknext;
    return res;
}
//token lexer_expect(unit *u, toktype t); // require that the next token has this given tag, error otherwise.
//token* lexer_accept(unit *u, toktype t); // if the current token has this given tag, return a token; otherwise return nothing. if you don't want to create a "maybe_tkn" type you could just use "maybe_tkn *" with NULL.
int main(int argc, char const *argv[])
{
    if(argc != 2)
        exit(EXIT_FAILURE);
    FILE* fp = fopen(argv[1], "r");
    fseek(fp, 0L, SEEK_END);
    const size_t fsize = ftell(fp);
    rewind(fp);
    char* fdata = malloc(fsize + 1);
    fread(fdata, fsize, 1, fp);
    fdata[fsize] = '\0';
    fclose(fp);
    unit u = *unit_init(argv[1], fdata);
    token testtok = lexer_any(&u);
    return 0;
}
