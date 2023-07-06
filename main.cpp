//POP 2021-01-11 projekt 2 Sadowski Jakub EiT 5 184396 CodeBlocks 17.12
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <cstdio>

using namespace std;

struct pozycja {
    int nr_linii;
    int nr_slowa;
};

void wybor_opcji (){
    cout<<"Wybierz opcje: "<<endl;
    cout<<"1 - zaszyfruj plik wiadomosc.txt"<<endl;
    cout<<"2 - odszyfruj plik zaszyfrowana_w.txt"<<endl;
    cout<<"3 - zakoncz dzialanie programu"<<endl;
}

void szyfrowanie (int numer){
    fstream wiadomosc("wiadomosc.txt", ios::in);         //otwarcie pliku o nazwie "wiadomosc.txt"
    if(!wiadomosc){                                      //sprawdzenie, czy plik zostal otwarty
		cout<<"Plik nie zostal otwarty"<<endl;
	}

	int liczba_slow=0;                                     //liczba slow do zaszyfrowania
	string slowa[100];                                     //tablica ze slowami do zaszyfrowania

	string linia_w;
    getline(wiadomosc, linia_w);

    cout<<"Wiadomosc do zaszyfrowania: ";
    char wers_w[linia_w.size()];
    for(int i=0; i<linia_w.size(); i++){
        wers_w[i]=linia_w[i];
        cout<<linia_w[i];
    }
    cout<<endl;

	char* token_w = strtok(wers_w, " ,.-!?");                 //"rozbicie" wersu wiadomosci na pojedyncze slowa oddzielone w wiadomosci spacjami, badz znakami przestankowymi
    while (token_w!=NULL){
    slowa[liczba_slow]=token_w;                                //zapisywanie pojedynczych slow do tablicy
    liczba_slow++;
    token_w = strtok(NULL, " ,.-!?");
    }

	wiadomosc.close();


    pozycja tab[100];                                   //struktura z pozycjami zaszyfrowanych slow
    int licznik=1;                                      //przechowuje kolejnosc slowa w wersie
    int prawda=0;
    for(int n=0; n<liczba_slow; n++){

        fstream ksiazka("ksiazka.txt", ios::in);            //otwarcie pliku o nazwie "ksiazka.txt"
        if(!ksiazka){                                       //sprawdzenie, czy plik zostal otwarty
            cout<<"Plik nie zostal otwarty"<<endl;
        }

        for(int m=0; m<numer; m++){                           //petla "leci" po wierszach ksiazki
        if(prawda==1){                                   //dane slowo moze wystapic w ksiazce nawet kilkaset razy, dlatego jesli juz znalezlismy jakas jego pozycje, to petla nie wykonuje sie dalej
            prawda=0;
            break;
        }
        string linia_k;
        getline(ksiazka, linia_k);

        char wers_k[10000];
        for(int i=0; i<linia_k.size(); i++){
            wers_k[i]=linia_k[i];
            }

            char* token_k = strtok(wers_k, " ,.-!?");       //takie samo rozbijanie wersu co w przypadku wiadomosci do zaszyfrowania
            while (token_k!=NULL) {
                if(slowa[n]==token_k){
                    tab[n].nr_linii=m+1;                //zapisywanie do struktury pozycji odnalezionych slow w ksiazce
                    tab[n].nr_slowa=licznik;
                    prawda=1;
                    break;
                }
                licznik++;
                token_k = strtok(NULL, " ,.-!?");
            }
            licznik=1;
        }
        ksiazka.close();
    }
    cout<<"Pozycje zaszyfrowanych slow w ksiazce (w formacie nr_wersu - nr_slowa_w_wersie): "<<endl;
    for(int v=0; v<liczba_slow; v++){
        cout<<" "<<tab[v].nr_linii<<" "<<tab[v].nr_slowa<<endl;
    }
    cout<<"(powyzsze dane zostaly rowniez zapisane do pliku o nazwie szyfr.txt)"<<endl<<endl;
    fstream szyfr("szyfr.txt", ios::out);                                                                   //zapisywanie zaszyfrowanych slow do pliku
    for(int v=0; v<liczba_slow; v++){
        szyfr<<tab[v].nr_linii<<" "<<tab[v].nr_slowa<<endl;
    }
    szyfr.close();
}

void deszyfrowanie (int numer, int ilosc){
    fstream zaszyfrowana_w("zaszyfrowana_w.txt", ios::in);         //otwarcie pliku o nazwie "zaszyfrowana_w.txt"
    if(!zaszyfrowana_w){                                      //sprawdzenie, czy plik zostal otwarty
		cout<<"Plik nie zostal otwarty"<<endl;
    }

    pozycja tab[100];
    cout<<"Pozycje slow do odszyfrowania: "<<endl;
    for(int i=0; i<ilosc/2; i++){
        zaszyfrowana_w>>tab[i].nr_linii>>tab[i].nr_slowa;
        cout<<" "<<tab[i].nr_linii<<" "<<tab[i].nr_slowa<<endl;
    }
    zaszyfrowana_w.close();

    int licznik_wers=1;
    int licznik_slow=1;
    int prawda=0;
    string slowa[100];
    for(int n=0; n<ilosc/2; n++){
        fstream ksiazka("ksiazka.txt", ios::in);            //otwarcie pliku o nazwie "ksiazka.txt"
        if(!ksiazka){                                       //sprawdzenie, czy plik zostal otwarty
            cout<<"Plik nie zostal otwarty"<<endl;
        }

        for(int j=0; j<numer; j++){
            if(prawda==1){
                prawda=0;
                break;
        }

            string linia_k;
            getline(ksiazka, linia_k);

            if(tab[n].nr_linii==licznik_wers){
                char wers_k[10000];
                for(int i=0; i<linia_k.size(); i++){
                    wers_k[i]=linia_k[i];
                }

                char* token_k = strtok(wers_k, " ,.-!?");
                while(token_k!=NULL){
                    if(tab[n].nr_slowa==licznik_slow){
                        slowa[n]=token_k;
                        prawda=1;
                    }
                    licznik_slow++;
                    token_k = strtok(NULL, " ,.-!?");
                }
                licznik_slow=1;
            }
        licznik_wers++;
        }
    licznik_wers=1;
    ksiazka.close();
    }
    cout<<"Oto odszyfrowana wiadomosc: "<<endl;
    for(int k=0; k<ilosc/2; k++){
        cout<<slowa[k]<<" ";
    }
    cout<<endl<<endl;
}

int main()
{
    cout<<"Ksiazka szyfrujaca: Igrzyska Smierci"<<endl;
    fstream ksiazka("ksiazka.txt", ios::in);            //otwarcie pliku o nazwie "ksiazka.txt"
	if(!ksiazka){                                       //sprawdzenie, czy plik zostal otwarty
		cout<<"Plik nie zostal otwarty"<<endl;
		return -1;
	}

    int numer=0;
    int ilosc=0;
    string linijka;

    while(!ksiazka.eof()){                              //zliczanie liczby wersow w ksiazce szyfrujacej do momentu konca pliku
        getline(ksiazka, linijka);
        numer++;                                        //liczba wersów w ksiazce
    }
    cout<<"Ogolna liczba wersow w ksiazce: "<<numer<<endl<<endl;
    ksiazka.close();

    fstream zaszyfrowana_w("zaszyfrowana_w.txt", ios::in);         //otwarcie pliku o nazwie "zaszyfrowana_w.txt"
    if(!zaszyfrowana_w){                                      //sprawdzenie, czy plik zostal otwarty
		cout<<"Plik nie zostal otwarty"<<endl;
		return -1;
    }

    while(!zaszyfrowana_w.eof()){                              //zliczanie liczby wersow w ksiazce szyfrujacej do momentu konca pliku
        getline(zaszyfrowana_w, linijka);
        ilosc++;                                       //liczba wersów w pliku do odszyfrowania
    }
    zaszyfrowana_w.close();

    //MENU
    int opt;
    while(opt!=3){

    wybor_opcji();
    cin>>opt;
    cout<<endl;

    if(opt==1){
        szyfrowanie(numer);
    }

    if(opt==2){
        deszyfrowanie(numer, ilosc);
    }

    if(opt==3){
        return 0;
    }
}
}
