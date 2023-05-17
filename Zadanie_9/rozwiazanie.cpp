#include <iostream>
#define STR_SIZE 32

using std::cout;
using std::cin;

void copyStr(char* a, char* b){
    for(int x = 0; x < STR_SIZE; x++){
        b[x] = a[x];
    }
}

struct Hunter{
    char name[STR_SIZE];
    int k_i, p_i;
    Hunter* next = NULL;
    Hunter* last = NULL;

    Hunter(char* name, int k_i, int p_i){
        copyStr(name, this->name);
        this->k_i = k_i;
        this->p_i = p_i;
    }

    void setLast(Hunter* a){
        if(next == NULL){
            next = a;
            last = a;
        } else {
            last->next = a;
            last = a;
        }
    }

    void display(){
        cout << this->name << " ";
        if(next != NULL){
            next->display();
        }
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int result[100][10] = {};

    int n;
    char name[STR_SIZE];
    int k_i, p_i;

    cin >> n;
    Hunter* arr[n];

    for(int x = 0; x < n; x++){
        cin >> name;
        cin >> k_i >> p_i;
        arr[x] = new Hunter(name, k_i, p_i);
    }

    for(int x = 0; x < n; x++){
        if(result[arr[x]->k_i][arr[x]->p_i] != 0){
            arr[result[arr[x]->k_i][arr[x]->p_i]-1]->setLast(arr[x]);
        } else {
            result[arr[x]->k_i][arr[x]->p_i] = x + 1;
        }
    }

    for(int x = 99; x >= 0; x--){
        for(int y = 0; y < 10; y++){
            if(result[x][y] != 0){
                arr[result[x][y] - 1]->display();
            }
        }
    }
    return 0;
}