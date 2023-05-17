#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

struct Node{
    Node* right;
    Node* left;   
    string text;
    unsigned int count;

    Node(){};
    ~Node(){};
    Node(string text){
        this->text = text;
        this->count = 1;
    }

    bool addNew(string value){
        if(this->text == value){
            this->count++;
            return 1;
        }
        if(this->text > value){
            if (this->left != NULL){
                return this->left->addNew(value);
            } else {
                this->left = new Node(value);
                return 0;
            }
        } else {
            if (this->right != NULL){
                return this->right->addNew(value);
            } else {
                this->right = new Node(value);
                return 0;
            }
        }
    }

    void display(){
        if(this->left != NULL){
            this->left->display();
        }
        for(; this->count > 0; this->count--){
            cout << this->text << "\n";
        }
        if(this->right != NULL){
            this->right->display();
        }
        delete this;
    }
};

int main(){
    std::ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    unsigned int n;
    string text;
    cin >> n;
    cin >> text;
    Node* top = new Node(text);

    for(;n > 1; n--){
        cin >> text;
        top->addNew(text);
    }
    top->display();

    return 0;
}