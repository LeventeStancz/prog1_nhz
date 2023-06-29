#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "global.h"
#include "debugmalloc.h"

const char *FORMAT_IN = "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n";
const char *FORMAT_OUT = "%s|%s|%s|%s|%s|%s|%s\n";

ListaElem *EloreBeszur(ListaElem *eleje, Kontakt k) {
   ListaElem *uj;
   uj = (ListaElem*) malloc(sizeof(ListaElem));
   uj->kontakt = k;
   uj->kov = eleje;
   return uj;
}

void KontaktFelszabadit(Kontakt k){
    free(k.id);
    free(k.nev);
    free(k.telszam);
    free(k.email);
    free(k.nem);
    free(k.sznap);
    free(k.cim);
}

void ListaFelszabadit(ListaElem *eleje){
    while(eleje != NULL){
        KontaktFelszabadit(eleje->kontakt);
        ListaElem*kovi = eleje->kov;
        free(eleje);
        eleje = kovi;
    }
}

ListaElem *FaljbolBeolvas(){
    FILE *fp;
    fp = fopen("db.txt", "r");
    if(fp == NULL){
        return NULL;
    }

    ListaElem *eleje = NULL;

    char sor[MAX_NEV+MAX_TSZAM+MAX_EMAIL+MAX_NEM+MAX_SZNAP+MAX_CIM];
    while(fgets(sor, sizeof(sor), fp) != NULL){
        char *newline = strchr(sor,'\n');
        if (newline){
            *newline = 0;
        }

        Kontakt k = {
            .id = (char*)malloc(4*sizeof(char)),
            .nev = (char*)malloc(MAX_NEV*sizeof(char)),
            .telszam = (char*)malloc(MAX_TSZAM*sizeof(char)),
            .email = (char*)malloc(MAX_EMAIL*sizeof(char)),
            .nem = (char*)malloc(MAX_NEM*sizeof(char)),
            .sznap = (char*)malloc(MAX_SZNAP*sizeof(char)),
            .cim = (char*)malloc(MAX_CIM*sizeof(char)),
        };

        char *item = strtok(sor, "|");
        strcpy(k.id,item);
        item = strtok(NULL, "|");

        strcpy(k.nev,item);
        item = strtok(NULL, "|");

        strcpy(k.telszam,item);
        item = strtok(NULL, "|");

        strcpy(k.email,item);
        item = strtok(NULL, "|");

        strcpy(k.nem,item);
        item = strtok(NULL, "|");

        strcpy(k.sznap,item);
        item = strtok(NULL, "|");

        strcpy(k.cim,item);
        item = strtok(NULL, "|");

        eleje = EloreBeszur(eleje, k);
    }

    fclose(fp);

    return eleje;
}

int UjKontaktFajlbaMentese(ListaElem *ujkontakt){
    ListaElem *eleje = FaljbolBeolvas();
    int regiid = atoi(eleje->kontakt.id);
    int ujid = regiid+1;
    sprintf(ujkontakt->kontakt.id, "%d", ujid);
    ListaFelszabadit(eleje);


    FILE *fp;

    fp = fopen("db.txt", "a");
    if (fp == NULL) {
        return 0;
    }

    fprintf(fp, FORMAT_OUT, ujkontakt->kontakt.id, ujkontakt->kontakt.nev, ujkontakt->kontakt.telszam, ujkontakt->kontakt.email,
            ujkontakt->kontakt.nem, ujkontakt->kontakt.sznap, ujkontakt->kontakt.cim);

    fclose(fp);

    KontaktFelszabadit(ujkontakt->kontakt);

    return 1;
}

ListaElem *KontaktKereses(ListaElem **eleje, char *id){
    *eleje = FaljbolBeolvas();
    ListaElem *tmp = *eleje;
    ListaElem *szerkLM;

    while(tmp != NULL){
        if(strcmp(tmp->kontakt.id, id) == 0)
        {
            szerkLM = tmp;
        }
        tmp = tmp->kov;
    }

    return szerkLM;
}

void ListaMegfordit(ListaElem **eleje){
    ListaElem *elozo = NULL;
    ListaElem *jelen = *eleje;
    ListaElem *kovi;
    while (jelen != NULL) {
        kovi = jelen->kov;
        jelen->kov = elozo;
        elozo = jelen;
        jelen = kovi;
    }
    *eleje = elozo;
}


int FajlUjraIr(ListaElem *eleje){
    ListaMegfordit(&eleje);
    FILE *fp;

    fp = fopen("db.txt", "w");
    if (fp == NULL) {
        return 0;
    }

    while(eleje != NULL){
        char *newline = strchr(eleje->kontakt.cim,'\n');
        if (newline){
           *newline = 0;
        }

        fprintf(fp, FORMAT_OUT, eleje->kontakt.id, eleje->kontakt.nev, eleje->kontakt.telszam, eleje->kontakt.email,
            eleje->kontakt.nem, eleje->kontakt.sznap, eleje->kontakt.cim);

        KontaktFelszabadit(eleje->kontakt);
        ListaElem *regi = eleje;
        eleje = eleje->kov;
        free(regi);
    }

    fclose(fp);

    return 1;
}

void KontaktTorlese(ListaElem **eleje, ListaElem **torlLM){
    ListaElem *temp;

    if((*eleje)->kontakt.id == (*torlLM)->kontakt.id){
        temp = *eleje;
        *eleje = (*eleje)->kov;
        KontaktFelszabadit(temp->kontakt);
        free(temp);
    }else{
        ListaElem *jelenlegi = *eleje;
        while(jelenlegi->kov != NULL){
            if(jelenlegi->kov->kontakt.id == (*torlLM)->kontakt.id){
                temp = jelenlegi->kov;
                jelenlegi->kov = jelenlegi->kov->kov;
                KontaktFelszabadit(temp->kontakt);
                free(temp);
                break;
            }else{
                jelenlegi = jelenlegi->kov;
            }
        }
    }
}

