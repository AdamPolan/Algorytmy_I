#include <iostream>
#include <climits>

using std::cout;
using std::cin;

int n;
bool** matrix2d;
int** costMatrix;
int** occupiedMatrix;
int* finalAnswer;
int min_cost = 3001;

void occupy(int row, int col){
    occupiedMatrix[row][col] += 1;
    for(int y = row+1, x = col-1; y < n && x >= 0; y++, x--){    //sw
        occupiedMatrix[y][x]++;
    }

    for(int y = row+1; y < n; y++){    //s
        occupiedMatrix[y][col]++;
    }

    for(int y = row+1, x = col+1; y < n && x < n; y++, x++){    //se
        occupiedMatrix[y][x]++; 
    }
}

void deoccupy(int row, int col){
    occupiedMatrix[row][col] -= 1;
    for(int y = row+1, x = col-1; y < n && x >= 0; y++, x--){    //sw
        occupiedMatrix[y][x]--;
    }

    for(int y = row+1; y < n; y++){    //s
        occupiedMatrix[y][col]--;
    }

    for(int y = row+1, x = col+1; y < n && x < n; y++, x++){    //se
        occupiedMatrix[y][x]--; 
    }
}

void findAnswer(int row, int total_cost) {
    if (row == n) {
        if (total_cost < min_cost) {
            min_cost = total_cost;
            for (int y = 0; y < n; y++) {
                for (int x = 0; x < n; x++) {
                    if(matrix2d[y][x] == 1){
                        finalAnswer[y] = x;
                        break;
                    }
                }
            }
        }
        return;
    }
    for (int x = 0; x < n; x++) {
        
        if (occupiedMatrix[row][x] == 0 && total_cost < min_cost) {
            matrix2d[row][x] = 1;
            occupy(row, x);
            findAnswer(row + 1, total_cost + costMatrix[row][x]);
            matrix2d[row][x] = 0;
            deoccupy(row, x);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    cin >> n;

    matrix2d = new bool*[n];
    occupiedMatrix = new int*[n];
    costMatrix = new int*[n];
    finalAnswer = new int[n];

    for (int y = 0; y < n; y++) {
        matrix2d[y] = new bool[n]();
        occupiedMatrix[y] = new int[n]();
        costMatrix[y] = new int[n];
        for (int x = 0; x < n; x++) {
            cin >> costMatrix[y][x];
        }
    }
    findAnswer(0, 0);
    for (int y = 0; y < n; y++) {
        cout << finalAnswer[y] << " ";
    }
    cout << "\n";
    return 0;
}