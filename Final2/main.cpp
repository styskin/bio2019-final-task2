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

typedef bitset<5> TBS;
typedef pair<int, TBS> pib;


bool wayToSort(const pib& i, const pib& j) {
    return i.first > j.first;
}



int main(int argc, const char * argv[]) {
    string path("/Users/styskin/bio2019/Final2/");
    ifstream in;
    in.open(path + "input_1.txt");
    ofstream out;
    out.open(path + "output_1.out");
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
    vector<pair<int, TBS> > can_states;
    for (auto& a : count) {
        can_states.push_back(pair<int, TBS>(a.second, a.first));
    }

    int KK = K + 1000;

    
    sort(can_states.begin(), can_states.end(), wayToSort);
//    for (int i = 0; i < KK; ++i) {
//        cout << can_states[i].first << " " << can_states[i].second.to_string() << endl;
//    }
    
    
    // TRY GET MINS
    vector<int> MINS(KK);
    
    for (int i = 0; i < M[0].length(); ++i) {
        TBS state;
        for (int j = 0; j < N; ++j) {
            state[j] = M[j][i] == '1';
        }
        // Choose min state
        int mn = 0;
        int diff = 100000000;
        for (int k = 0; k < KK; ++k) {
            int d = 0;
            for (int j = 0; j < N; ++j) {
                if (state[j] != can_states[k].second[j]) {
                    ++d;
                }
            }
            if (d < 10) {
                MINS[k] += N - d;
            }
            if (d < diff) {
                mn = k;
                diff = d;
            }
        }
    }
    vector<pair<int, TBS> > states;
    for (int k = 0; k < KK; ++k) {
        cout << MINS[k] << " vs " << can_states[k].first << endl;
        states.push_back(pair<int, TBS>(MINS[k], can_states[k].second));
    }
    
    sort(states.begin(), states.end(), wayToSort);

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
                if (state[j] != states[k].second[j]) {
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
    return 0;
}
