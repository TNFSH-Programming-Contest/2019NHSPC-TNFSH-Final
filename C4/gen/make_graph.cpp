#include <iostream>
#include <algorithm>
#include <set>
#include <fstream>
#include <chrono>
#include <random>

#include <cmath>
#include <cstring>

#include <unistd.h>

using namespace std;

template <class URNG>
vector<pair<int,int>> makeGraph(int n, int m, URNG&& rnd) {
    
    vector<set<int>> G;
    G.resize(n);
	
	vector<pair<int,int>> edges;
	for(int i=0; i<n; i++) {
	    for(int j=i+1; j<n; j++) {
	        edges.push_back({i,j});
	    }
	}
	
	shuffle(edges.begin(), edges.end(), rnd);
	
	edges.resize(m);
	return edges;
}


int main(int argc, char* argv[]) {
    
    string fileName;
	int t = 1;
	int n = 2000;
	int m = 100000;
    
    int opt;
    if((opt = getopt(argc,argv,"o:t:")) != -1) {
        // fprintf(stderr, "opt = %c\n", (char)opt);
        // fprintf(stderr, "optarg = %s\n", optarg);
        switch(opt) {
        case 'o':
            fileName = optarg;
            break;
        case 't':
            t = atoi(optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s [-o <fileName>] [-t <nTestCases>] <n> <m>\n", argv[0]);
            exit(1);
        }
    }
    
    if(argc < optind+2) {
        fprintf(stderr, "Usage: %s [-o <fileName>] [-t <nTestCases>] <n> <m>\n", argv[0]);
        exit(1);
    }
    
    n = atoi(argv[optind]);
    m = atoi(argv[optind+1]);
    
    if(m > n*(n-1)/2) {
        cerr << "m <= n*(n-1) is required" << endl;
        exit(2);
    }
    
    
    ostream fout(cout.rdbuf());
    ofstream file;
	
	if(fileName != "") {
    	file.open(fileName, ios::out);
    	fout.rdbuf(file.rdbuf());
        fprintf(stderr,"The graphs would be saved to \"%s\"\n", fileName.c_str());
    }
	
	mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
	
	fout << t << '\n';
	while(t--) {
        fout << n << " " << m << '\n';
        vector<pair<int,int>> E = makeGraph(n,m,rnd);
    	for(int i=0; i<m; i++)
    	    fout << E[i].first << " " << E[i].second << '\n';
	}
	
	cerr << "done" << endl;
	
	return 0;
}

