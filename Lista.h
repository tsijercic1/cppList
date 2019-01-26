//
// Created by tsijercic1 on 1/26/2019.
//

#ifndef CPPLIST_LISTA_H
#define CPPLIST_LISTA_H




template <typename tip>
class Lista
{
public:
    Lista() {}
    Lista(const Lista& l) {}
    Lista(Lista&& l) {}
    Lista& operator=(const Lista& l);
    Lista& operator=(Lista &&l);
    virtual int brojElemenata()const=0;
    virtual tip trenutni()const=0;
    virtual tip& trenutni()=0;
    virtual bool sljedeci()=0;
    virtual bool prethodni()=0;
    virtual void pocetak()=0;
    virtual void kraj()=0;
    virtual void obrisi()=0;
    virtual void dodajIspred(const tip& a)=0;
    virtual void dodajIza(const tip& a)=0;
    virtual const tip& operator[](int i)const=0;
    virtual tip& operator[](int i)=0;
    virtual void Ispisi()const=0;
    virtual ~Lista() {}
};



#endif //CPPLIST_LISTA_H
