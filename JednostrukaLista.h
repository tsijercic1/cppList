//
// Created by tsijercic1 on 1/26/2019.
//

#ifndef CPPLIST_JEDNOSTRUKALISTA_H
#define CPPLIST_JEDNOSTRUKALISTA_H



#include "Lista.h"
#include <iostream>

template <typename tip>
struct Cvor {
    tip x;
    Cvor* next;
};

template <typename tip>
class JednostrukaLista:public Lista<tip>
{
    int velicina=0;
    Cvor<tip>* lista=nullptr;
    Cvor<tip>* mjesto=nullptr;
    Cvor<tip>* end=nullptr;
    void pomocna(Cvor<tip>* prethodni, Cvor<tip>* trenutni, int& suma);
    void pomocnaObrni(Cvor<tip>*& lijevi,Cvor<tip>* lgranica, Cvor<tip>* desni, Cvor<tip>* granica);
public:
    JednostrukaLista() {};
    JednostrukaLista(const JednostrukaLista<tip>& l);
    JednostrukaLista(JednostrukaLista<tip>&& l);
    JednostrukaLista& operator=(const JednostrukaLista<tip> &temp);
    JednostrukaLista& operator=(JednostrukaLista<tip> &&l);
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
    ~JednostrukaLista();
    void Obrni(int n, int m);
    void brisiUnazadManjeOdSumePrethodnih();
};



template<typename tip>
void JednostrukaLista<tip>::brisiUnazadManjeOdSumePrethodnih() {
    int suma =0;
    pomocna(nullptr,lista,suma);
}



template<typename tip>
JednostrukaLista<tip>::~JednostrukaLista()
{
    for(; mjesto;) {
        mjesto= lista->next;
        delete lista;
        lista = mjesto;
    }
    end = nullptr;
    velicina = 0;
}

template<typename tip>
void JednostrukaLista<tip>::Ispisi()const
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
const tip& JednostrukaLista<tip>::operator[](int  i)const
{
    if(i>=velicina && i<0)throw "Iskocili ste iz niza";
    Cvor<tip>* klizni=lista;
    for(int j=0; j<i; j++) {
        klizni=klizni->next;
    }
    return klizni->x;
}

template<typename tip>
tip& JednostrukaLista<tip>::operator [](int i)
{
    if(i>=velicina || i<0)throw "Iskocili ste iz niza";
    Cvor<tip>* klizni=lista;
    for(int j=0; j<i; j++) {
        klizni=klizni->next;
    }
    return klizni->x;
}

template<typename tip>
void JednostrukaLista<tip>::obrisi()
{
    if(velicina==0)throw "Lista prazna!";
    if(mjesto==lista) {
        if(velicina == 1) {
            lista = nullptr;
            delete mjesto;
            mjesto = nullptr;
            velicina--;
            end=nullptr;
        } else {
            lista=mjesto->next;
            delete mjesto;
            mjesto = lista;
            velicina--;
        }
        return ;
    }
    Cvor<tip>*klizni=lista;
    for(; klizni->next!=mjesto; klizni=klizni->next);
    klizni->next=mjesto->next;
    delete mjesto;
    mjesto=klizni->next;
    if(mjesto == nullptr){
        mjesto = klizni;
        end = klizni;
    }
    velicina--;
}

template <typename tip>
void JednostrukaLista<tip>::kraj()
{
    if(velicina==0)throw "Lista prazna!";
    if(lista->next==nullptr) {
        mjesto=lista;
        return;
    }
    for(; mjesto->next!=nullptr; mjesto=mjesto->next);
}

template<typename tip>
void JednostrukaLista<tip>::pocetak()
{
    if(velicina==0)throw "Lista prazna!";
    mjesto = lista;
}

template <typename tip>
bool JednostrukaLista<tip>::prethodni()
{
    if(velicina==0)throw "Lista prazna!";
    if(mjesto==lista)return false;
    Cvor<tip>* klizni = lista;
    for(; klizni->next != mjesto; klizni=klizni->next);
    mjesto = klizni;
    return true;
}

template <typename tip>
bool JednostrukaLista<tip>::sljedeci()
{
    if(velicina==0)throw "Lista prazna!";
    if(mjesto->next==nullptr)return false;
    mjesto = mjesto->next;
    return true;
}

template <typename tip >
tip JednostrukaLista<tip>::trenutni()const
{
    if(velicina==0)throw "Lista prazna!";
    return mjesto->x;
}

template <typename tip>
tip& JednostrukaLista<tip>::trenutni()
{
    if(velicina==0)throw "Lista prazna!";
    return mjesto->x;
}

template<typename tip>
int JednostrukaLista<tip>::brojElemenata()const
{
    return velicina;
}

template <typename tip>
void JednostrukaLista<tip>::dodajIza(const tip& a)
{
    try {
        Cvor<tip>* novi = new Cvor<tip> {a, nullptr};
        if(velicina == 0) {
            lista = novi;
            mjesto = novi;
            end=novi;
        } else {
            novi -> next = mjesto->next;
            mjesto->next = novi;
            if(mjesto==end){
                end=mjesto->next;
            }
        }
        velicina++;
    } catch(...) {
        for(; mjesto;) {
            mjesto= lista->next;
            delete lista;
            lista = mjesto;
            end=nullptr;
        }
        velicina = 0;
        throw "no memory";
    }
}

template <typename tip>
void JednostrukaLista<tip>::dodajIspred(const tip& a)
{
    try{
        if(velicina == 0) {
            lista = new Cvor<tip> {a,nullptr};
            mjesto = lista;
            velicina++;
        } else {
            if (mjesto == lista) {
                Cvor<tip>* novi = new Cvor<tip> {a,mjesto};
                lista = novi;
                velicina++;
            } else {
                Cvor<tip>* klizni=lista;
                for(;;) {
                    if(klizni->next==mjesto)break;
                    klizni=klizni->next;
                }
                Cvor<tip>* novi = new Cvor<tip> {a,mjesto};
                klizni->next=novi;
                velicina++;
            }
        }
    }catch(...)
    {
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
JednostrukaLista<tip>::JednostrukaLista(const JednostrukaLista<tip>& l)
{
    try{
        velicina = l.velicina;
        if(l.lista) {
            Cvor<tip>* klizni=l.lista, *temp;
            for(; klizni; klizni=klizni->next) {
                if(l.lista==klizni) {
                    lista = new Cvor<tip> {klizni->x,nullptr};
                    mjesto = lista;
                    if(klizni == l.mjesto)temp=lista;
                } else {

                    if(klizni==l.mjesto)temp=mjesto;
                    mjesto ->next = new Cvor<tip> {klizni->x,nullptr};
                    mjesto = mjesto->next;
                    if(l.end == klizni){
                        end = mjesto;
                    }
                }
            }
            velicina = l.velicina;
        } else {
            lista = nullptr;
            mjesto = nullptr;
            end = nullptr;
            velicina = 0;
        }
    }catch(...)
    {
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
JednostrukaLista<tip>::JednostrukaLista(JednostrukaLista<tip>&& l)
{
    //*this=std::move(l);
    int vel=velicina;
    this->velicina = l.velicina;
    l.velicina=vel;
    Cvor<tip>* temp=lista;
    lista=l.lista;
    l.lista=temp;
    temp = mjesto;
    mjesto=l.mjesto;
    l.mjesto=temp;
    temp = l.end;
    l.end = end;
    end = temp;
}

template <typename tip>
JednostrukaLista<tip>& JednostrukaLista<tip>::operator=(const JednostrukaLista<tip>& temp)
{
    //*this=std::swap(l);
    if(this == &temp)return *this;
    JednostrukaLista<tip> l(temp);
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
    end = l.end;
    l.end = zamjenski;
    return *this;
}

template <typename tip>
JednostrukaLista<tip>& JednostrukaLista<tip>::operator=(JednostrukaLista<tip>&& l)
{
    //*this=std::swap(l);
    /*
    int velicina;
    Cvor<tip>* lista;
    Cvor<tip>* mjesto;*/
    int vel=velicina;
    this->velicina = l.velicina;
    l.velicina=vel;
    Cvor<tip>* temp=lista;
    lista=l.lista;
    l.lista=temp;
    temp = mjesto;
    mjesto=l.mjesto;
    l.mjesto=temp;
    temp = end;
    end = l.end;
    l.end = temp;
    return *this;
}

template<typename tip>
void JednostrukaLista<tip>::pomocna(Cvor<tip>* prethodni, Cvor<tip> *trenutni, int &suma) {
    if(trenutni->next!=nullptr){
        pomocna(trenutni,trenutni->next,suma);
    }
    if(suma > trenutni->x && trenutni != end ){
        //treba brisati
        Cvor<tip>* temp = trenutni;
        if (trenutni==mjesto){
            mjesto=trenutni -> next;
        }
        if(trenutni == lista){
            lista = lista->next;
        }
        if(prethodni)prethodni -> next = trenutni->next;
        delete temp;
        velicina--;

    } else{
        suma += trenutni->x;
    }
}

template<typename tip>
void JednostrukaLista<tip>::Obrni(int n, int m) {
    Cvor<tip> *lijevi,*desni,*lgranica,*dgranica;
    int x = (m+n)/2;
    desni = lista;
    lgranica = lista;
    lijevi = lista;
    dgranica = lista;
    for(int i=0;i<m;i++){
        if(i == n){
            lijevi = dgranica;
        }
        if(i == x){
            lgranica = dgranica;
        }
        if(i == x+1){
            desni = dgranica;
        }
        dgranica = dgranica -> next;
    }
    //std::cout<<"\n lgranica je : "<<lgranica->x<<"\n";
    pomocnaObrni(lijevi,lgranica,desni,dgranica);
    lijevi = lista;
    for(int i=0;i<x-1;i++){
        lijevi = lijevi -> next;
    }
    desni = lijevi -> next;
    lijevi -> next = desni -> next;
    if (desni == mjesto)mjesto = mjesto -> next;
    delete desni;
    velicina--;
}

template<typename tip>
void JednostrukaLista<tip>::pomocnaObrni(Cvor<tip> *&lijevi,Cvor<tip>*lgranica, Cvor<tip> *desni, Cvor<tip> *granica) {
    if(desni!=granica){
        pomocnaObrni(lijevi,lgranica,desni->next,granica);
    }
    if(lijevi!=lgranica){
        tip temp = lijevi -> x;
        lijevi -> x = desni -> x;
        desni -> x = temp;
        lijevi = lijevi -> next;
    }
}



#endif //CPPLIST_JEDNOSTRUKALISTA_H
