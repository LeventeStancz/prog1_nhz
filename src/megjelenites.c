#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "debugmalloc.h"
#include "global.h"

char FoMenu(){
    char valasztas = '9';
    do{
        system("cls");
        printf("Telefonkönyv - Stancz Levente\n\nFőmenü:\n"
        "1. Kontakt import/export (vCard)\n"
        "2. Kontaktok kezelése (új, szerk., törlés)\n"
        "3. Keresés (speciális, általános)\n"
        "4. Összes kontakt kilistázása\n"
        "0. Kilépés\n"
        "Menü sorszáma: ");
        scanf(" %c", &valasztas);
    }while(valasztas != '0' && valasztas != '1' && valasztas != '2' && valasztas != '3' && valasztas != '4');

    return valasztas;
}

char ImportExportMenu(){
    char valasztas = '9';
    do{
        system("cls");
        printf("Telefonkönyv - Stancz Levente\n\nImport/Export (vCard):\n"
        "1. Importálás vCard fájlból\n"
        "2. Exportálás vCard fájlba (Kontakt id szükséges)\n"
        "0. Vissza\n"
        "Menü sorszáma: ");
        scanf(" %c", &valasztas);
    }while(valasztas != '0' && valasztas != '1' && valasztas != '2');

    return valasztas;
}

void ImportKontaktMenu(char*eleresi){
    system("cls");
    printf("0. Vissza\nvCard formátumú fájl elérési útvonala:\n");
    scanf(" %[^\n]", eleresi);
}

char ExportMenu(){
    char valasztas = '0';

    system("cls");
    printf("Telefonkönyv - Stancz Levente\n\nExport (vCard):\n"
    "Exportálni kivánt kontakt id:\n");

    scanf(" %c", &valasztas);

    return valasztas;
}

char KontaktKezeleseMenu(){
    char valasztas = '9';
    do{
        system("cls");
        printf("Telefonkönyv - Stancz Levente\n\nKontaktok kezelése:\n"
        "1. Új kontakt felvétele\n"
        "2. Kontakt adatainak szerkesztése (Kontakt id szükséges)\n"
        "3. Kontakt törlése (Kontakt id szükséges)\n"
        "0. Vissza\n"
        "Menü sorszáma: ");
        scanf(" %c", &valasztas);
    }while(valasztas != '0' && valasztas != '1' && valasztas != '2' && valasztas != '3');

    return valasztas;
}

char UjKontaktMenu(ListaElem *lm){
    char valasztas = '9';

    Kontakt k = {
        .id = (char*)malloc(4*sizeof(char)),
        .nev = (char*)malloc(MAX_NEV*sizeof(char)),
        .telszam = (char*)malloc(MAX_TSZAM*sizeof(char)),
        .email = (char*)malloc(MAX_EMAIL*sizeof(char)),
        .nem = (char*)malloc(MAX_NEM*sizeof(char)),
        .sznap = (char*)malloc(MAX_SZNAP*sizeof(char)),
        .cim = (char*)malloc(MAX_CIM*sizeof(char)),
    };

    strcpy(k.id, "-1");

    system("cls");
    char nev[MAX_NEV];
    printf("Amelyik mezőt nem szeretné kitölteni, tegyen X-et.\n\nAdja meg az új kontakt nevét:\nMax karakter - 70\n>>");
    scanf(" %70[^\n]", &nev);
    strcpy(k.nev, nev);

    system("cls");
    char telszam[MAX_TSZAM];
    printf("Amelyik mezőt nem szeretné kitölteni, tegyen X-et.\n\nAdja meg az új kontakt telefonszámát:\nMax karakter - 15\n>>");
    scanf(" %15[^\n]", &telszam);
    strcpy(k.telszam, telszam);

    system("cls");
    char email[MAX_EMAIL];
    printf("Amelyik mezőt nem szeretné kitölteni, tegyen X-et.\n\nAdja meg az új kontakt email címét:\nMax karakter - 320\n>>");
    scanf(" %320[^\n]", &email);
    strcpy(k.email, email);

    system("cls");
    char nem[MAX_NEM];
    printf("Amelyik mezőt nem szeretné kitölteni, tegyen X-et.\n\nAdja meg az új kontakt nemét:\nMax karakter - 5\n>>");
    scanf(" %5[^\n]", &nem);
    strcpy(k.nem, nem);

    system("cls");
    char sznap[MAX_SZNAP];
    printf("Amelyik mezőt nem szeretné kitölteni, tegyen X-et.\n\nAdja meg az új kontakt születési dátumát:\nMax karakter - 10\n>>");
    scanf(" %10[^\n]", &sznap);
    strcpy(k.sznap, sznap);

    system("cls");
    char cim[MAX_CIM];
    printf("Amelyik mezőt nem szeretné kitölteni, tegyen X-et.\n\nAdja meg az új kontakt címét:\nMax karakter - 65\n>>");
    scanf(" %65[^\n]", &cim);
    strcpy(k.cim, cim);

    system("cls");
    printf("Megfelelőek az adatok?\n\nNév: %s\nTelefonszám: %s\nEmail cím: %s\nNem: %s\nSzületési dátum: %s\nCím: %s\n\n1. Igen, mentés\n0. Mégse\nMenü sorszáma: ",
           k.nev, k.telszam, k.email, k.nem, k.sznap, k.cim);

    scanf(" %c", &valasztas);

    if(valasztas == '1'){
        lm->kontakt = k;
        lm->kov = NULL;
    }

    return valasztas;
}

int csakSzam(const char *str)
{
    while(*str != '\0')
    {
        if(*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

char *KontaktSzerkMenu(){
    char *id = (char*)malloc(5*sizeof(char));

    do{
        system("cls");
        printf("0. Vissza\nAdja meg a szerkeszteni kivánt kontakt id számát:\n");
        scanf(" %4[^\n]", id);
    }while(csakSzam(id) != 1);

    return id;
}

char KontaktSzerkesztes(ListaElem *szerkLM){
    char valasztas = '9';


    char *nev = (char*)malloc(MAX_NEV*sizeof(char));
    system("cls");
    printf("Adja meg a kontakt nevét: - %s\n>>", szerkLM->kontakt.nev);
    scanf(" %70[^\n]", nev);

    char *telszam = (char*)malloc(MAX_TSZAM*sizeof(char));
    system("cls");
    printf("Adja meg a kontakt telefonszámát: - %s\n>>", szerkLM->kontakt.telszam);
    scanf(" %15[^\n]", telszam);

    char *email = (char*)malloc(MAX_EMAIL*sizeof(char));
    system("cls");
    printf("Adja meg a kontakt email címét: - %s\n>>", szerkLM->kontakt.email);
    scanf(" %320[^\n]", email);

    char *nem = (char*)malloc(MAX_NEM*sizeof(char));
    system("cls");
    printf("Adja meg a kontakt nemét: - %s\n>>", szerkLM->kontakt.nem);
    scanf(" %5[^\n]", nem);

    char *sznap = (char*)malloc(MAX_SZNAP*sizeof(char));
    system("cls");
    printf("Adja meg a kontakt születési dátumát: - %s\n>>", szerkLM->kontakt.sznap);
    scanf(" %10[^\n]", sznap);

    char *cim = (char*)malloc(MAX_CIM*sizeof(char));
    system("cls");
    printf("Adja meg a kontakt címét: - %s\n>>", szerkLM->kontakt.cim);
    scanf(" %65[^\n]", cim);

    system("cls");
    printf("Megfelelőek az adatok?\n\nNév: %s\nTelefonszám: %s\nEmail cím: %s\nNem: %s\nSzületési dátum: %s\nCím: %s\n\n1. Igen, mentés\n0. Mégse\nMenü sorszáma: ",
          nev, telszam, email, nem, sznap, cim);

    scanf(" %c", &valasztas);

    if(valasztas == '1'){
        free(szerkLM->kontakt.nev);
        free(szerkLM->kontakt.telszam);
        free(szerkLM->kontakt.email);
        free(szerkLM->kontakt.nem);
        free(szerkLM->kontakt.sznap);
        free(szerkLM->kontakt.cim);
        szerkLM->kontakt.nev = nev;
        szerkLM->kontakt.telszam = telszam;
        szerkLM->kontakt.email = email;
        szerkLM->kontakt.nem = nem;
        szerkLM->kontakt.sznap = sznap;
        szerkLM->kontakt.cim = cim;
        return '1';
    }else{
        free(nev);
        free(telszam);
        free(email);
        free(nem);
        free(sznap);
        free(cim);
        return '0';
    }
}

char *KontaktTorlesMenu(){
    char *id = (char*)malloc(5*sizeof(char));

    do{
        system("cls");
        printf("0. Vissza\nAdja meg a törölni kivánt kontakt id számát:\n");
        scanf(" %4[^\n]", id);
    }while(csakSzam(id) != 1);

    return id;
}

char KontaktTrlMegerosites(ListaElem *torlLM){
    char valasztas = '9';
    do{
        system("cls");

        printf("Biztosan törli a következő kontaktot?\n\nNév: %s\nTelefonszám: %s\nEmail cím: %s\nNem: %s\nSzületési dátum: %s\nCím: %s\n",
               torlLM->kontakt.nev,torlLM->kontakt.telszam,torlLM->kontakt.email,torlLM->kontakt.nem,torlLM->kontakt.sznap,torlLM->kontakt.cim);

        printf("1. Törlés\n"
        "0. Vissza\n"
        "Menü sorszáma: ");

        scanf(" %c", &valasztas);
    }while(valasztas != '0' && valasztas != '1');

    return valasztas;
}

char OsszKontaktKiirasa(ListaElem *eleje){
    ListaElem *tmp = eleje;
    char valasztas = '9';

    do{
        system("cls");
        printf("# | Név | Telefonszám | Email cím | Nem | Születési dátum | Cím\n\n");
        while(tmp != NULL){
            printf("%s | %s | %s | %s | %s | %s | %s\n",
                   tmp->kontakt.id, tmp->kontakt.nev, tmp->kontakt.telszam, tmp->kontakt.email, tmp->kontakt.nem, tmp->kontakt.sznap, tmp->kontakt.cim);
            tmp = tmp->kov;
        }
        printf("\n0. Vissza\n>>");

        scanf(" %c", &valasztas);
    }while(valasztas != '0');

    return valasztas;
}


