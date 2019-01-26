#include <stdio.h>
#include <windows.h>
#include "DvostrukaLista.h"

int main(){
    DvostrukaLista<int> a;
    a.dodajIza(1);
    a.dodajIza(9);
    a.dodajIza(8);
    a.dodajIza(7);
    a.dodajIza(6);
    a.dodajIza(5);
    a.dodajIza(4);
    a.dodajIza(3);
    a.dodajIza(2);
    a.Ispisi();
    a.presloziElemente(0,4,2);
    a.Ispisi();
//    char niz[]="Dan je Dobar";
//    CharUpperA(niz);
//    printf("%s",niz);
//    getchar();
    return 0;
}