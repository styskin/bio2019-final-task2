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
#include <algorithm>
#include <random>

using namespace std;

typedef bitset<5> TBS;
typedef vector<int> BS;
typedef pair<int, BS> pib;


bool wayToSort(const pib& i, const pib& j) {
    return i.first > j.first;
}

int myrandom (int i) {
    return std::rand() % i;
}

int min(int a, int b) {
    return a < b ? a : b;
}


int main(int argc, const char * argv[]) {
    for (int T = 1; T <= 4; ++T) {
//        cout << "=========== Test " << T << endl;
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
        size_t N = M.size();
        int KK = K;
        
        vector<int> shuffled;
        for (int i = 0; i < M[0].length(); ++i) {
            shuffled.push_back(i);
        }
        std::srand ( unsigned ( std::time(0) ) );
        random_shuffle(shuffled.begin(), shuffled.end(), myrandom);
        
        
        // GET RANDOM STARTING POINTS

        vector<pair<int, BS> > can_states;
        for (int i = 0; i < KK; ++i) {
            BS bs(N);
            for (int j = 0; j < N; ++j) {
                bs[j] = M[j][shuffled[i]] == '1';
            }
            can_states.push_back(pair<int, BS>(0, bs));
        }

        
//        unordered_map<TBS, int> count;
//        for (int i = 0; i < M[0].length(); ++i) {
//            TBS state;
//            for (int j = 0; j < N; ++j) {
//                state[j] = M[j][i] == '1';
//            }
//            ++count[state];
//        }
//        vector<pair<int, BS> > can_states;
//        for (auto& a : count) {
//            BS bs;
//            for (int i = 0; i < N; ++i) {
//                bs.push_back(a.first[i]);
//            }
//            can_states.push_back(pair<int, BS>(a.second, bs));
//        }
//        sort(can_states.begin(), can_states.end(), wayToSort);
//        for (int i = 0; i < can_states.size(); ++i) {
//            can_states[i].first = 0;
//        }


        
        // K-means analogue
        for (int i = 0; i < M[0].length(); ++i) {
            TBS state;
            for (int j = 0; j < N; ++j) {
                state[j] = M[j][shuffled[i]] == '1';
            }
            // Choose min state
            int mn = 0;
            int diff = 100000000;
            for (int k = 0; k < KK; ++k) {
                int d = 0;
                for (int j = 0; j < N; ++j) {
                    if (state[j] != (can_states[k].second[j] > can_states[k].first / 2) ) {
                        ++d;
                    }
                }
                // Distance
                d = min(d, N - d);
                
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
        
        // Output clusters
//        int total = 0;
//        for (int k = 0; k < KK; ++k) {
//            cout << "Clastered: " << can_states[k].first << " ";
//            total += can_states[k].first;
//            for (int j = 0; j < N; ++j) {
//                cout << (can_states[k].second[j] > can_states[k].first / 2 ? 1 : 0);
//            }
//            cout << endl;
//        }
//        cout << total << " from " << M[0].length() << endl;
        
        can_states.clear();
        can_states.push_back(pair<int, BS>(1, BS(5)));
        can_states.push_back(pair<int, BS>(1, BS(5)));
        can_states.push_back(pair<int, BS>(1, BS(5)));
        can_states.push_back(pair<int, BS>(1, BS(5)));
        can_states[0].second = vector<int>({0, 0, 0, 0, 0});
        can_states[1].second = vector<int>({0, 0, 1, 0, 0});
        can_states[2].second = vector<int>({0, 1, 0, 0, 0});
        can_states[3].second = vector<int>({0, 1, 1, 0, 0});


        

        if (0) {
            int totaldiff = 100000000;
            vector<TBS> res;
            
            for (int i1 = 0; i1 < (1 << 5); ++i1) {
                for (int i2 = i1 + 1; i2 < (1 << 5); ++i2) {
                    for (int i3 = i2 + 1; i3 < (1 << 5); ++i3) {
                        for (int i4 = i3 + 1; i4 < (1 << 5); ++i4) {
                            vector<TBS> m;
                            m.push_back(TBS(i1));
                            m.push_back(TBS(i2));
                            m.push_back(TBS(i3));
                            m.push_back(TBS(i4));

                            int tdiff = 0;
                            for (int i = 0; i < M[0].length(); ++i) {
                                TBS state;
                                for (int j = 0; j < N; ++j) {
                                    state[j] = M[j][i] == '1';
                                }
                                // Choose min state
                                int mn = 0;
                                int diff = 100000000;
                                for (int k = 0; k < m.size(); ++k) {
                                    int d = 0;
                                    for (int j = 0; j < N; ++j) {
                                        if (state[j] != m[k][j]) {
                                            ++d;
                                        }
                                    }
                                    
                                    d = min(d, N - d);
                                    if (d < diff) {
                                        mn = k;
                                        diff = d;
                                    }
                                }
                                tdiff += diff;
                            }
                            if (tdiff < totaldiff) {
                                totaldiff = tdiff;
                                cout << "New min " << tdiff << endl;
                                res = m;
                            }
                        }
                    }
                }
            }
            cout << totaldiff << endl;
            for (int j = 0; j < res.size(); ++j) {
                cout << res[j].to_string() << endl;
            }


        }
        
        
        
        int totaldiff = 0;
        // OUTPUT
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
                    if (state[j] != (can_states[k].second[j] > can_states[k].first / 2)) {
                        ++d;
                    }
                }
                //Distance
                d = min(d, N - d);

                if (d < diff) {
                    mn = k;
                    diff = d;
                }
            }
            totaldiff += diff;
            // mn - state
            if (i > 0) {
                out << " ";
            }
            out << mn;
        }
        out << endl;
        cout << "Test " << T << ": " << totaldiff << endl;
        
        in.close();
        out.close();
    }
    return 0;
}
