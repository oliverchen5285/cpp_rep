#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

vector<string> split_words(string words){
    words += ','; //>:)
    vector<string> words_vec;
    string cur = "";
    for(const auto &elem: words){
        if(elem != '"' && elem != ','){
            cur += elem;
        }
        else if(elem == ','){
            words_vec.push_back(cur);
            cur = "";
        }
    }
    return words_vec;
}

int tri_words(){
    ifstream fin("words.txt");
    
    int n = 1;

    vector<int> tri(1, 0);

    int count = 0;

    string words;
    fin >> words;
    
    vector<string> words_vec = split_words(words);
    for(const auto &word: words_vec){
        int score = 0;
        for(const auto &elem: word){
            score += (int)elem - 'A' + 1;
        }
        cout << word << " = " << score << endl;
        while(score > tri.back()){
            tri.push_back(tri.back() + n);
            ++n;
        }
        for(int i = tri.size() - 1; i >= 0; --i){
            if(score == tri[i]){
                ++count;
                break;
            }
        }
    }
    return count;
}

int main(){
    
    
    cout << tri_words() << endl;

}
