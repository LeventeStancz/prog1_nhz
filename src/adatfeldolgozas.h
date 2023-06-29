#ifndef ADATFELDOLGOZAS_H_INCLUDED
#define ADATFELDOLGOZAS_H_INCLUDED

#include "global.h"

ListaElem *FaljbolBeolvas();
int UjKontaktFajlbaMentese(ListaElem *ujkontakt);
ListaElem *KontaktKereses(ListaElem **eleje, char *id);
int FajlUjraIr(ListaElem *eleje);
void ListaFelszabadit(ListaElem *eleje);
void KontaktTorlese(ListaElem **eleje, ListaElem **torlLM);
void ListaMegfordit(ListaElem **eleje);

#endif // ADATFELDOLGOZAS_H_INCLUDED
