#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define int64 int64_t
#define uint unsigned int
#define endl '\n'


vector<int> G[512];
bool mark[512];


int count_quad_with_diag(int v1, int v3) {
    memset(mark,false,sizeof(mark));
    for(int i=0; i<G[v1].size(); i++) {
        mark[G[v1][i]] = true;
    }
    
    int n_common = 0;
    for(int i=0; i<G[v3].size(); i++) {
        if(mark[G[v3][i]] == true) {
            n_common++;
        }
    }
    
    return n_common*(n_common-1)/2;
}

int count_quad(int n) {
    int cnt = 0;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            cnt += count_quad_with_diag(i,j);
        }
    }
    return cnt/2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while(T--) {
        int n,m;
        cin >> n >> m;
        
        for(int i=0; i<512; i++) {
            G[i].clear();
        }
        
        int a,b;
        for(int i=0; i<m; i++) {
            cin >> a >> b;
            G[a].push_back(b);
            G[b].push_back(a);
        }
        
        cout << count_quad(n) << endl;
    }

    return 0;
}



