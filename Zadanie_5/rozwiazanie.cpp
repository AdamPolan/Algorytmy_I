#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::string;
using std::map;
using std::pair;
using std::vector;
using std::queue;

int main(){
    std::ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, temp, start;
    int result = 0;
    string text;
    cin>>n>>m;
    map<string, int> villages;
    vector<int>* neighbours = new vector<int>[n];
    int* distances = new int[n];

    for(int x = 0; x < n; x++){
        cin >> text;
        villages.insert(pair<string, int>(text, x));
        distances[x] = -1;
    }

    for(int x = 0; x < n; x++){
        while(true){
            cin >> text;
            if(text == "X"){
                break;
            }
            temp = villages.at(text);
            neighbours[x].push_back(temp);
        }
    }

    cin >> text;
    start = villages.at(text);
    distances[start] = 0;

    queue<int> paths;
    int w, q;
    paths.push(start);
    while(!paths.empty()){
        w = paths.front();
        while(!neighbours[w].empty()){
            q = neighbours[w].back();
            if(distances[q] == -1){
                distances[q] = distances[w] + 1;
                paths.push(q);
            }
            neighbours[w].pop_back();
        }
        paths.pop();
    }


    for(int x = 0; x < m; x++){
        cin >> text;
        temp = villages.at(text);
        if(result < distances[temp]){
            result = distances[temp];
        }
    }

    cout << result;


    return 0;
}