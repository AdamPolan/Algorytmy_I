#include <iostream>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::string;

struct Wniosek{
    unsigned int nr;
    string name;
    string surname;
    Wniosek(){
        this->nr = 0;
        this->name = "";
        this->surname = "";
    };
    ~Wniosek(){};

    Wniosek(unsigned int nr, string name, string surname){
        this->nr = nr;
        this->name = name;
        this->surname = surname;
    };
    Wniosek(const Wniosek& a){
        this->nr = nr;
        this->name = name;
        this->surname = surname;
    }
    static void swap(Wniosek* a, Wniosek* b){
        Wniosek temp;
        temp.nr = a->nr;
        temp.name = a->name;
        temp.surname = a->surname;
        a->nr = b->nr;
        a->name = b->name;
        a->surname = b->surname;
        b->nr = temp.nr;
        b->name = temp.name;
        b->surname = temp.surname;
    }
};

int compare(const Wniosek& a, const Wniosek& b){
    if(a.nr != b.nr){
        return a.nr < b.nr ? 1 : -1;
    } else if(a.surname != b.surname){
        return a.surname < b.surname ? 1 : -1;
    } else if(a.name != b.name){
        return a.name < b.name ? 1 : -1;
    } else return 0;
}

void bubbleSort(Wniosek** arr, unsigned int size){
    for(int x = 0; x < size - 1; x++){
        for(int y = 0; y < size - 1; y++){
            if(compare(*arr[y + 1], *arr[y]) == 1){
                Wniosek::swap(arr[y], arr[y+1]);
            }
        }
    }
}

Wniosek* findMedian(Wniosek** arr, unsigned int size){
    if(size > 2){ 
        bubbleSort(arr, size);
        return arr[size / 2];
    } else if(size == 2){ 
        return arr[0] < arr[1] ? arr[0] : arr[1];
    } else return arr[0];
}

Wniosek* findK(Wniosek** arr, unsigned int k, unsigned int size){
    if(size < 11){
        bubbleSort(arr, size);
        return arr[k];
    }

    int r = 0;
    unsigned int medianCount = 0;
    Wniosek* temp[5];
    for(int i = 0; i < size; i++){
        r = i % 5;
        temp[r] = arr[i];
        if(r == 4 || i == size - 1){
            Wniosek::swap(findMedian(temp, r + 1), arr[medianCount]);
            medianCount++;
        }
    }

    Wniosek* medianOfMedians = findK(arr, medianCount / 2, medianCount);

    unsigned int lessCount = 0, moreCount = 0;
    int cmpResult;
    for(int x = 0; x < size; x++){
        cmpResult = compare(*arr[x], *medianOfMedians);
        if(cmpResult == 1){
            lessCount++;
        } else if(cmpResult == -1){   
            moreCount++;
        }
    }
    if(k == lessCount){
        return medianOfMedians;
    }
    int i = 0;
    Wniosek medianValue;
    medianValue.nr = medianOfMedians->nr;
    medianValue.name = medianOfMedians->name;
    medianValue.surname = medianOfMedians->surname;
    if(k < lessCount){
        for(int x = 0; x < size; x++){
            if(compare(*arr[x], medianValue) == 1){
                Wniosek::swap(arr[i],arr[x]);
                i++;
            }
        }
        return findK(arr, k, lessCount);
    } else {
        for(int x = 0; x < size; x++){
            if(compare(*arr[x], medianValue) == -1){
                Wniosek::swap(arr[i],arr[x]);
                i++;
            }
        }
        return findK(arr, k - (lessCount + 1), moreCount);
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    unsigned int n, k, nr;
    string name, surname;
    cin >> n >> k;

    Wniosek** list = new Wniosek*[n];

    for(int x = 0; x < n; x++){
        cin >> name;
        cin >> surname;
        cin >> nr;
        list[x] = new Wniosek(nr, name, surname);
    }

    Wniosek* answer = findK(list, k, n);

    cout << answer->name << "\n" << answer->surname << "\n";
    cout << answer->nr;

    return 0;
}