//
//  main.cpp
//  Final2
//
//  Created by Andrey Styskin on 23.02.2019.
//  Copyright © 2019 Andrey Styskin. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <bitset>
#include <unordered_map>
#include <stdlib.h>
#include <math.h>
using namespace std;

typedef bitset<100> TBS;
typedef vector<int> BS;
typedef pair<int, BS> pib;


bool wayToSort(const pib& i, const pib& j) {
    return i.first > j.first;
}



int main(int argc, const char * argv[]) {
    for (int T = 1; T <= 4; ++T) {
        string path("/Users/styskin/bio2019/Final2/");
        ifstream in;
        in.open(path + "input_" + to_string(T) + ".txt");
        ofstream out;
        out.open(path + "output_" + to_string(T) +  ".out");
        int K;
        in >> K;
        vector<string> M;
        string s;
        getline(in, s);
        while (getline(in, s)) {
            M.push_back(s);
        }
        unordered_map<TBS, int> count;
        
        size_t N = M.size();
        for (int i = 0; i < M[0].length(); ++i) {
            TBS state;
            for (int j = 0; j < N; ++j) {
                state[j] = M[j][i] == '1';
            }
            ++count[state];
        }
        // Get top K states and code them
        vector<pair<int, BS> > can_states;
        for (auto& a : count) {
            BS bs;
            for (int i = 0; i < N; ++i) {
                bs.push_back(a.first[i]);
            }
            can_states.push_back(pair<int, BS>(a.second, bs));
        }
        
        sort(can_states.begin(), can_states.end(), wayToSort);
        for (int i = 0; i < can_states.size(); ++i) {
            can_states[i].first = 1;
        }
        // K-means analogue
        for (int i = 0; i < M[0].length(); ++i) {
            TBS state;
            for (int j = 0; j < N; ++j) {
                state[j] = M[j][i] == '1';
            }
            // Choose min state
            int mn = 0;
            int diff = 100000000;
            for (int k = 0; k < K; ++k) {
                int d = 0;
                for (int j = 0; j < N; ++j) {
                    if (state[j] != (can_states[k].second[j] > can_states[k].first / 2) ) {
                        ++d;
                    }
                }
                if (d < diff) {
                    mn = k;
                    diff = d;
                }
            }
            
            // UPDATE K-means
            ++can_states[mn].first;
            for (int j = 0; j < N; ++j) {
                can_states[mn].second[j] += state[j];
            }
        }
        
        for (int k = 0; k < K; ++k) {
            cout << "Clastered: " << can_states[k].first << endl;
        }
        
        // OUTPUT
        for (int i = 0; i < M[0].length(); ++i) {
            TBS state;
            for (int j = 0; j < N; ++j) {
                state[j] = M[j][i] == '1';
            }
            // Choose min state
            int mn = 0;
            int diff = 100000000;
            for (int k = 0; k < K; ++k) {
                int d = 0;
                for (int j = 0; j < N; ++j) {
                    if (state[j] != (can_states[k].second[j] > can_states[k].first / 2)) {
                        ++d;
                    }
                }
                if (d < diff) {
                    mn = k;
                    diff = d;
                }
            }
            // mn - state
            if (i > 0) {
                out << " ";
            }
            out << mn;
        }
        out << endl;
        
        in.close();
        out.close();
    }
    return 0;
}
