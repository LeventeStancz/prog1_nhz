#include <stdio.h>
#include <stdlib.h>

#include "megjelenites.h"
#include "adatfeldolgozas.h"
#include "global.h"
#include "debugmalloc.h"

int main()
{
    MenuKezelo();
    return 0;
}

void MenuKezelo(){
    char valasztas = FoMenu();
    //0 Kilépés
    //1 Import Export
    //2 kontakt kezelése
    //3 keresés
    //4 ossz kiir
    switch (valasztas){
        case '0':
            system("exit");
        break;
        case '1':
            valasztas = ImportExportMenu();
            if(valasztas == '0'){
                MenuKezelo();
                return;
            }else if(valasztas == '1'){
                //import Vcard (1db kontakt)
                char *eleresi = (char*)malloc(260*sizeof(char));
                ImportKontaktMenu(eleresi);
                //0. Vissza
                if(strcmp(eleresi, "0") == 0){
                    MenuKezelo();
                    return;
                }else{
                    ///utvonal megvan -> import
                }
            }else{
                //export Vcard (1db vagy összes)
                valasztas = ExportMenu();
                ///Kontakt keresése -> exportálás
            }
        break;
        case '2':
            valasztas = KontaktKezeleseMenu();
            //1 kontakt létrehozás
            if(valasztas == '1'){
                ListaElem *ujkontakt = (ListaElem *)malloc(sizeof(ListaElem));
                valasztas = UjKontaktMenu(ujkontakt);
                if(valasztas == '1'){
                    //mentés
                    UjKontaktFajlbaMentese(ujkontakt);
                    free(ujkontakt);
                    MenuKezelo();
                    return;
                }else{
                    //megse
                    free(ujkontakt);
                    MenuKezelo();
                    return;
                }
            }else if(valasztas == '2'){
                //2 kontakt szerkesztés
                char *id = KontaktSzerkMenu();
                if(strcmp(id, "0") == 0){
                    //0 vissza
                    free(id);
                    MenuKezelo();
                    return;
                }else{
                    ListaElem *eleje;
                    ListaElem *szerkLM = KontaktKereses(&eleje, id);
                    valasztas = KontaktSzerkesztes(szerkLM);
                    int eredmeny = FajlUjraIr(eleje);
                    free(id);
                    MenuKezelo();
                    return;
                }
            }else if(valasztas == '3'){
                //3 torles
                char *id = KontaktTorlesMenu();
                if(strcmp(id, "0") == 0){
                    //0 vissza
                    free(id);
                    MenuKezelo();
                    return;
                }else{
                    ListaElem *eleje;
                    ListaElem *torlLM = KontaktKereses(&eleje, id);
                    valasztas = KontaktTrlMegerosites(torlLM);
                    if(valasztas == '0'){
                        //megse
                        ListaFelszabadit(eleje);
                        free(id);
                        MenuKezelo();
                        return;
                    }else{
                        ///kontakt torlese
                        KontaktTorlese(&eleje, &torlLM);
                        int eredmeny = FajlUjraIr(eleje);
                        free(id);
                        MenuKezelo();
                        return;
                    }
                }
            }else{
                //0 vissza
                MenuKezelo();
                return;
            }
        break;
        case '3':
            //kereses
        break;
        case '4': ;
            //ossz kiir
            ListaElem *eleje = FaljbolBeolvas();
            ListaMegfordit(&eleje);
            valasztas = OsszKontaktKiirasa(eleje);
            if(valasztas == '0'){
                ListaFelszabadit(eleje);
                MenuKezelo();
                return;
            }
        break;
        default:
            system("exit");
    }
}
