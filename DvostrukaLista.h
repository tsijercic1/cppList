//
// Created by tsijercic1 on 1/26/2019.
//

#ifndef CPPLIST_DVOSTRUKALISTA_H
#define CPPLIST_DVOSTRUKALISTA_H


#include <iostream>
#include "Lista.h"
template<typename tip>
class Iterator;

template <typename tip>
struct Cvor{
    tip x;
    Cvor* next;
    Cvor* previous;
};


template <typename tip>
class DvostrukaLista:public Lista<tip>
{
    int velicina=0;
    Cvor<tip>* lista=nullptr;
    Cvor<tip>* mjesto=nullptr;
    Cvor<tip>* end=nullptr;
public:
    DvostrukaLista() {};
    DvostrukaLista(const DvostrukaLista<tip>& l);
    DvostrukaLista(DvostrukaLista<tip>&& l);
    DvostrukaLista& operator=(const DvostrukaLista<tip> &temp);
    DvostrukaLista& operator=(DvostrukaLista<tip> &&l);
    int brojElemenata()const;
    tip trenutni()const;
    tip& trenutni();
    bool sljedeci();
    bool prethodni();
    void pocetak();
    void kraj();
    void obrisi();
    void dodajIspred(const tip& a);
    void dodajIza(const tip& a);
    const tip& operator[](int i)const;
    tip& operator[](int i);
    void Ispisi()const;
    ~DvostrukaLista();
    void presloziElemente(int n, int k, int t);
    friend class Iterator<tip>;
};

template<typename tip>
DvostrukaLista<tip>::~DvostrukaLista()
{
    for(; mjesto;) {
        lista->previous=nullptr;
        mjesto= lista->next;
        delete lista;
        lista = mjesto;
    }
    velicina = 0;
}

template<typename tip>
void DvostrukaLista<tip>::Ispisi()const
{
    if(velicina==0)throw "Lista prazna!";
    Cvor<tip>* klizni=lista;
    std::cout<<"\nLista:";
    for(; klizni; klizni=klizni->next) {
        std::cout<<" "<<klizni->x;
    }
    std::cout<<std::endl;
}

template<typename tip>
const tip& DvostrukaLista<tip>::operator[](int  i)const
{
    if(i>=velicina && i<0)throw "Iskocili ste iz niza";
    Cvor<tip>* klizni=lista;
    for(int j=0; j<i; j++) {
        klizni=klizni->next;
    }
    return klizni->x;
}

template<typename tip>
tip& DvostrukaLista<tip>::operator [](int i)
{
    if(i>=velicina || i<0)throw "Iskocili ste iz niza";
    Cvor<tip>* klizni=lista;
    for(int j=0; j<i; j++) {
        klizni=klizni->next;
    }
    return klizni->x;
}

template<typename tip>
void DvostrukaLista<tip>::obrisi()
{
    if(velicina==0)throw "Lista prazna!";
    if(mjesto==lista) {
        if(velicina == 1) {
            lista = nullptr;
            delete mjesto;
            mjesto = nullptr;
            end=nullptr;
            velicina--;
        } else {
            lista=mjesto->next;
            delete mjesto;
            mjesto = lista;
            velicina--;
        }
        return ;
    }
    Cvor<tip>*klizni=mjesto->previous;
    klizni->next=mjesto->next;

    Cvor<tip>* drugi_klizni = mjesto->next;
    if(drugi_klizni)drugi_klizni->previous = klizni;
    delete mjesto;
    mjesto=klizni->next;
    if(mjesto == nullptr){
        mjesto = klizni;
        end = klizni;
    }
    velicina--;
}

template <typename tip>
void DvostrukaLista<tip>::kraj()
{
    if(velicina==0)throw "Lista prazna!";
    mjesto=end;
}

template<typename tip>
void DvostrukaLista<tip>::pocetak()
{
    if(velicina==0)throw "Lista prazna!";
    mjesto = lista;
}

template <typename tip>
bool DvostrukaLista<tip>::prethodni()
{
    if(velicina==0)throw "Lista prazna!";
    if(mjesto==lista)return false;
    mjesto=mjesto->previous;
    return true;
}

template <typename tip>
bool DvostrukaLista<tip>::sljedeci()
{
    if(velicina==0)throw "Lista prazna!";
    if(mjesto->next==nullptr)return false;
    mjesto = mjesto->next;
    return true;
}

template <typename tip >
tip DvostrukaLista<tip>::trenutni()const
{
    if(velicina==0)throw "Lista prazna!";
    return mjesto->x;
}

template <typename tip>
tip& DvostrukaLista<tip>::trenutni()
{
    if(velicina==0)throw "Lista prazna!";
    return mjesto->x;
}

template<typename tip>
int DvostrukaLista<tip>::brojElemenata()const
{
    return velicina;
}

template <typename tip>
void DvostrukaLista<tip>::dodajIza(const tip& a)
{
    try {
        Cvor<tip>* novi = new Cvor<tip> {a, nullptr,nullptr};
        if(velicina == 0) {
            lista = novi;
            mjesto = novi;
            end = novi;
        } else {
            novi->previous = mjesto;
            novi -> next = mjesto->next;
            if(mjesto->next)mjesto->next->previous = novi;
            if(novi->next==nullptr)end=novi;
            mjesto->next = novi;
        }
        velicina++;
    } catch(...) {
        for(; mjesto;) {
            mjesto->previous=nullptr;
            mjesto= lista->next;
            delete lista;
            lista = mjesto;
        }
        velicina = 0;
        throw "no memory";
    }
}

template <typename tip>
void DvostrukaLista<tip>::dodajIspred(const tip& a)
{
    try {
        if(velicina == 0) {
            lista = new Cvor<tip> {a,nullptr,nullptr};
            mjesto = lista;
            end=lista;
            velicina++;
        } else {
            if (mjesto == lista) {
                Cvor<tip>* novi = new Cvor<tip> {a,mjesto,nullptr};
                lista->previous = novi;
                lista = novi;
                velicina++;
            } else {
                Cvor<tip>* novi = new Cvor<tip> {a,mjesto,mjesto->previous};
                mjesto->previous->next=novi;
                mjesto->previous = novi;
                velicina++;
            }
        }
    } catch(...) {
        for(; mjesto;) {
            mjesto->previous=nullptr;
            mjesto= lista->next;
            delete lista;
            lista = mjesto;
        }
        velicina = 0;
        throw "no memory";
    }
}

template <typename tip>
DvostrukaLista<tip>::DvostrukaLista(const DvostrukaLista<tip>& l)
{
    try {
        velicina = l.velicina;
        if(l.lista) {
            Cvor<tip>* klizni=l.lista,*temp;

            for(; klizni; klizni=klizni->next) {
                if(l.lista==klizni) {
                    lista = new Cvor<tip> {klizni->x,nullptr,nullptr};
                    mjesto = lista;
                    temp=mjesto;
                    if(l.end==klizni)end=mjesto;
                } else {
                    mjesto ->next = new Cvor<tip> {klizni->x,nullptr,mjesto};
                    mjesto = mjesto->next;
                    if(l.mjesto==klizni)temp=mjesto;
                    if(l.end==klizni)end=mjesto;
                }
            }
            mjesto=temp;
            velicina = l.velicina;
        } else {
            lista = nullptr;
            mjesto = nullptr;
            velicina = 0;
        }
    } catch(...) {
        for(; mjesto;) {
            mjesto= lista->next;
            delete lista;
            lista = mjesto;
        }
        velicina = 0;
        throw "no memory";
    }
}

template <typename tip>
DvostrukaLista<tip>::DvostrukaLista(DvostrukaLista<tip>&& l)
{
    //*this=std::move(l);
    velicina = l.velicina;
    l.velicina = 0;
    lista=l.lista;
    l.lista=nullptr;
    mjesto=l.mjesto;
    l.mjesto=nullptr;
    end=l.end;
    l.end=nullptr;
}

template <typename tip>
DvostrukaLista<tip>& DvostrukaLista<tip>::operator=(const DvostrukaLista<tip>& temp)
{
    if(&temp==this)return *this;
    DvostrukaLista<tip> l(temp);
    int vel=velicina;
    this->velicina = l.velicina;
    l.velicina=vel;
    Cvor<tip>* zamjenski=lista;
    lista=l.lista;
    l.lista=zamjenski;
    zamjenski = mjesto;
    mjesto=l.mjesto;
    l.mjesto=zamjenski;
    zamjenski=end;
    end=l.end;
    l.end=zamjenski;
    return *this;
}

template <typename tip>
DvostrukaLista<tip>& DvostrukaLista<tip>::operator=(DvostrukaLista<tip>&& l)
{
    if(&l == this)return *this;
    int vel=velicina;
    this->velicina = l.velicina;
    l.velicina=vel;
    Cvor<tip>* temp=lista;
    lista=l.lista;
    l.lista=temp;
    temp = mjesto;
    mjesto=l.mjesto;
    l.mjesto=temp;
    temp=end;
    end=l.end;
    l.end=temp;
    return *this;
}

template<typename tip>
class Iterator{
    const DvostrukaLista<tip>* dvostruka=nullptr;
    Cvor<tip>* start=nullptr;
    Cvor<tip>* end=nullptr;
    Cvor<tip>* place=nullptr;
public:
    Iterator(const DvostrukaLista<tip>& l){
        dvostruka=&l;
        start=l.lista;
        end=l.end;
        place=start;
    }
    void pocetak(){
        place=start;
    }
    void kraj(){
        place=end;
    }
    bool sljedeci(){
        if(place==end)return false;
        place=place->next;
        return true;
    }
    bool prethodni(){
        if(place==start)return false;
        place=place->previous;
        return true;
    }
    const tip& trenutni()const{
        return place -> x;
    }

    int brojElemenata()const{
        return dvostruka->brojElemenata();
    }
};

template<typename tip>
void DvostrukaLista<tip>::presloziElemente(int n, int k, int t) {
    Cvor<tip>* pocetak=end,*poc=end,*left=end,*temp=end;
    if(n+k+t>=velicina)throw "Hell no!";
    int x = 0;
    for (int i = 0; i < velicina; ++i) {
        if(mjesto == temp)break;
        x++;
        temp = temp->previous;
    }
    for(int i=0;i<n;i++){
        pocetak = pocetak -> previous;
    }
    for(int i=0;i<n+k;i++){
        poc = poc -> previous;
    }
    for (int i = 0; i < n + k + t; ++i) {
        left = left->previous;
    }
    if(left->previous){
        left->previous -> next = poc -> next;
    }
    poc->next->previous = left->previous;
    pocetak->previous -> next = left;
    left -> previous = pocetak -> previous;
    pocetak -> previous = poc;
    poc -> next = pocetak;
    temp = end;
    for (int i = 0; i < velicina; ++i) {
        if(i == x){
            mjesto =temp;
        }
        if(temp->previous)lista = temp -> previous;
        temp = temp -> previous;
    }
}



template<typename tip>
tip dajMaksimum(const Lista<tip>& l){
    const DvostrukaLista<tip>* x=(const DvostrukaLista<tip>*)&l;
    Iterator<tip> it(*x);
    it.pocetak();
    tip max = it.trenutni();
    for(int i=0;i<it.brojElemenata();i++){
        if(it.trenutni()>max)max=it.trenutni();
        it.sljedeci();
    }
    return max;
}

#endif //CPPLIST_DVOSTRUKALISTA_H
