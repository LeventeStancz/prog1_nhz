#ifndef MEGJELENITES_H_INCLUDED
#define MEGJELENITES_H_INCLUDED

#include "global.h"

char FoMenu();
char ImportExportMenu();
void ImportKontaktMenu(char *eleresi);
char ExportMenu();
char KontaktKezeleseMenu();
char UjKontaktMenu(ListaElem *lm);
char * KontaktSzerkMenu();
char KontaktSzerkesztes(ListaElem *szerkLM);
char * KontaktTorlesMenu();
char KontaktTrlMegerosites(ListaElem *torlLM);
char OsszKontaktKiirasa();

#endif // MEGJELENITES_H_INCLUDED
