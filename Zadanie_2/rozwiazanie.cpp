#include <iostream>
#include <string>   //char* w niektórych sytuacjach wypisuje dodatkowe, niepożadane dane i nie mam pojecia jak sie z tym uporać

bool isSpecial(int n){
    return ((n & (n - 1)) == 0);    //potęga 2 to liczba zapisana w systemie binarnym jako pojedyncza jedynka pośród samych zer a liczba o jeden mniejsza w systemie binarnym to same jedynki (pomijając zera przed tymi jedynkami)
}                                   //dlatego n & (n - 1) wyglada np. tak (0000 1000 & 0000 0111) więc zadna jedynka nie pokryje się z inną jedynką, a wynik dzialania bedzie rowny 0

class Mountain{
public:
    std::string name;
    unsigned int height;

    Mountain(){};
    Mountain(const Mountain& x){        //konstruktor kopiujący potrzebny do sortowania
        this->name = x.name;
        this->height = x.height;
    };
    Mountain(std::string name, int height){
        this->name = name;
        this->height = height;
    };
    bool operator>(const Mountain& x){      //przeciążenie operatora w celu usprawnienia czytelności kodu
        return this->height > x.height;
    };

    void out(){
        std::cout << name << "-" << height << " ";
    };
};

void sortTables(Mountain* table, int tSize)     //sortowanie przez wstawianie dawało najlepsze wyniki w sprawdzarce
{
    int y;
    Mountain temp;

    for (int x = 1; x < tSize; x++)
    {
        temp = Mountain(table[x]);

        for(y = x - 1; y >= 0 && table[y] > temp; y--)
        {
            table[y + 1] = table[y];

        }
        table[y + 1] = temp;
    }
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    unsigned height, n, t;
    std::string name;
    Mountain* sTable;       //tabela wyróżnionych szczytów
    unsigned int sCount = 0;         //licznik wyróżnionych szczytów
    Mountain* nTable;       //tabela zwykłych szczytów
    unsigned int nCount = 0;         //licznik zwykłych szczytów

    std::cin >> t;
    for(int x = 0; x<t; x++){
        std::cin >> n;
        sTable = new Mountain[n];
        nTable = new Mountain[n];
        for(int y = 0; y<n; y++){
            std::cin >> name >> height;
            if(isSpecial(height)){
                sTable[sCount] = Mountain(name, height);
                sCount++;
            } else {
                nTable[nCount] = Mountain(name, height);
                nCount++;
            }
        }

        sortTables(sTable, sCount);
        sortTables(nTable, nCount);

        for(int y = 0; y<sCount; y++){      //wyswietlam najpierw tebelę z wyróżnionymi szczytami
            sTable[y].out();
        }
        for(int y = 0; y<nCount; y++){
            nTable[y].out();
        }
        sCount = 0;
        nCount = 0;
        std::cout << std::endl;
        delete[] sTable;
        delete[] nTable;
    }

    return 0;
}