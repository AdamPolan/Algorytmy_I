#include <iostream>

int prio[3];

bool isBetter(int rank, unsigned int u, unsigned int _u, double w, double _w, unsigned int c, unsigned int _c){
    if(rank>2){         //jezeli ranga priorytetu jest wieksza niz 2, to oznacza ze kryteria sa identyczne
        return false;
    }
    switch (prio[rank]) {
        case 1:{
            if(u < _u)
                return true;
            else if (u == _u)
                return isBetter(rank + 1, u, _u, w, _w, c, _c);   //rekurencyjnie bada coraz nizsze priorytetowo kryteria
            else
                return false;
            break;
        }
        case 2:{
            if(w < _w)
                return true;
            else if (w == _w)
                return isBetter(rank + 1, u, _u, w, _w, c, _c);
            else
                return false;
            break;
        }
        case 3:{
            if(c < _c)
                return true;
            else if (c == _c)
                return isBetter(rank + 1, u, _u, w, _w, c, _c);
            return false;
            break;
        }
    }
}

int main()
{
    int n;
    int m;
    //wartosci s, u, w, c odpowiadaja danym osoby dotychczas najlepszej
    //wartosci _s, _u, _w, _c odpowiadaja danym osoby aktualnie rozpatrywanej
    char s[64];
    char _s[64];
    
    unsigned int u = 0, _u;
    double w = 0, _w;   //double poniewaz z float 1 + 2 = 3.000004
    unsigned int c = 0, _c;
    
    scanf("%d", &n);
    for(int x = 0; x<n; x++){
        scanf("%d", &m);
        scanf("%d %d %d", &prio[0], &prio[1], &prio[2]);    //ustalamy priorytety gdzie prio[0] jest najwazniejszym a prio[2] najmniej waznym
        for(int y = 0; y<m; y++){
            scanf("%s %u %f %u", _s, &_u, &_w, &_c);
            if(isBetter(0, u, _u, w, _w, c, _c)){
                for(int t = 0; t<64; t++)
                    s[t] = _s[t];
                u = _u;
                w = _w;
                c = _c;
            }
        }

        u = 0;
        w = 0;
        c = 0;

        for(int i = 0; i<64; i++){      //przy zwyklym uzyciu funkcji printf wystepuje blad w pamieci (w miejscu znaku \0 wyswietla przypadkowa wartosc)
            if(s[i] == 0){
                printf("\n");
                break;
            }
            printf("%c", s[i]);
        }
    }

    return 0;
}