#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

enum {
    MAX_NEV = 71,
    MAX_TSZAM = 16,
    MAX_EMAIL = 321,
    MAX_NEM = 6,
    MAX_SZNAP = 11,
    MAX_CIM = 66,
};

typedef struct Kontakt{
    char *id, *nev, *telszam, *email, *nem, *sznap, *cim;
} Kontakt;

typedef struct ListaElem{
    Kontakt kontakt;
    struct ListaElem *kov;
} ListaElem;

#endif // GLOBAL_H_INCLUDED
