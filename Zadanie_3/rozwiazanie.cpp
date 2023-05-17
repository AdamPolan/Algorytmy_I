#include <iostream>

using std::cout;
using std::cin;

struct Person
{
    unsigned int nr;
    bool suspended = false;
    Person* left;
    Person* right;
    Person* pair;
    Person(){};
    ~Person(){};
    Person(const Person& a){
        nr = a.nr;
        suspended = a.suspended;
        left = a.left;
        right = a.right;
        pair = a.pair;
    }
};

Person* move(Person* pivot, int steps, bool ctrclockwise){
    for(int x = 0; x < steps; x++){
        pivot = ctrclockwise ? pivot->left : pivot->right;
    }
    return pivot;
}

void display(Person* pivot, int size, bool ctrclockwise){
    for(int x = 0; x < size; x++){
        cout<<pivot->nr<<" ";
        pivot = ctrclockwise ? pivot->left : pivot->right;
    }
}

int main(){
    // std::ios_base::sync_with_stdio(false);
    // cout.tie(nullptr);
    // cin.tie(nullptr);
    unsigned int n, p;
    bool k;

    cin>>n>>p>>k;

    unsigned int size = n*2;

    Person* pivot = new Person();           // tworze pierwszą osobe
    Person* tempPerson = pivot;             // drugi wskaznik na ta sama osobe
    pivot->nr = 0;
    pivot->right = new Person();            // tworze nastepna osobe    
    pivot->right->left = pivot;             // aby wykorzystać ja w petli
    pivot = pivot->right;

    for(int x = 1; x < size - 1; x++){
        if(x % 2 == 0){                     // jezeli x jest parzysty
            pivot->nr = x/2;                // przypisuje po kolei nr pary
        } else {                                // w przeciwnym wypadku
            pivot->nr = (n - 1 + (x/2)) % n;    // przypisuje numer po zamianie
        }                                       
        pivot->right = new Person();
        pivot->right->left = pivot;
        pivot = pivot->right;
    }
    pivot->nr = n - 2;                  // przypisuje nr pary ostatniej osobie
    pivot->right = tempPerson;          // i domykam "okrąg"
    tempPerson->left = pivot;
    pivot = tempPerson;

    // petla, która przypisuje kazdej osobie, drugą osobe z pary
    for(int x = 0; x < n; x++){     
        pivot->pair = pivot->right->right->right;
        pivot->right->right->right->pair = pivot;
        pivot = pivot->right->right;
    }

    // ustawiam wskaznik na osobę rozpoczynającą rozgrywke
    pivot = move(tempPerson, p*2, 0);

    unsigned int m;
    unsigned int op;
    unsigned int x;
    bool flag;
    Person* suspendedPair = new Person();
    Person* firstSuspended = NULL;
    Person tempPivot;
    cin >> m;

    for(;m > 0; m--){
        cin >> op;
        // operator 0: przesuń wskażnik o x-1 i wyświetl
        if(op == 0){
            cin >> x;
            pivot = move(pivot, x - 1, k);
            display(pivot, size, k);
            cout << "\n";
        }

        // operator 1: usuń osobę i w zależnosci od flagi oraz innych okoliczności wstaw dwie nowe
        if(op == 1){
            cin >> x;  
            // przesuwam wskaznik, usuwam osobe i zmieniam kierunek
            pivot = move(pivot, x - 1, k);
            pivot->left->right = pivot->right;
            pivot->right->left = pivot->left;
            pivot->suspended = true;
            k = !k;
            tempPivot = Person(*pivot);     // kopiuje usunieta osobe

            // jezeli osoba z pary tez jest zawieszona, dodaje ją do listy zawieszonych osób i ustawiam wskażnik na pierwsza taka osobe (do listy zostanie dodana tylko jedna osoba z kazdej pary)
            if(pivot->pair->suspended){
                suspendedPair->right = pivot;
                if(firstSuspended == NULL){
                    firstSuspended = pivot;
                }
                suspendedPair->right->left = suspendedPair;
                suspendedPair->right->right = NULL;
                suspendedPair = suspendedPair->right;
            }
            size--;     // rozmiar okręgu zmniejsza sie o jeden
            pivot = &tempPivot;

            cin >> flag;

            //jezeli lista osob usunietych nie jest pusta, a flaga jest ustawiona na true, lub rozmiar okregu jest mniejszy niz 4, dodaje 2 osoby do okregu
            if((flag || (size < 4)) && (firstSuspended != NULL)){
                tempPerson = firstSuspended;
                // ustawiam wskaznik na nastepna pare do wstawienia
                if(tempPerson->right != NULL){
                    firstSuspended = tempPerson->right;
                } else {
                    firstSuspended = NULL;
                    suspendedPair = new Person();
                }
                // wstawiam nowe osoby do listy, i powiekszam jej rozmiar o 2
                tempPerson->suspended = false;
                tempPerson->left = pivot->left->left;
                tempPerson->right = pivot->left;
                pivot->left->left->right = tempPerson;
                pivot->left->left = tempPerson;
                tempPerson = tempPerson->pair;
                tempPerson->suspended = false;
                tempPerson->left = pivot->right;
                tempPerson->right = pivot->right->right;
                pivot->right->right->left = tempPerson;
                pivot->right->right = tempPerson;
                size += 2;
            }
            pivot = move(pivot, 1, k);
        }
        // operator 2: przesuń wskażnik o x-1 i odwróć kierunek
        if(op == 2){
            cin >> x;
            pivot = move(pivot, x - 1, k);
            k = !k;
        }
    }

    return 0;
}