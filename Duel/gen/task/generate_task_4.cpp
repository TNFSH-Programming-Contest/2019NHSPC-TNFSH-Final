#include "../template/task_input_generate.hpp"
#include "../template/mylib.hpp"

#define path "input/4"
// r_i - l_i = r_{i+1] - l_{i+1} , for all i < Q


int32_t main() {
	int Len[4] = {10,3000,78,800};
	for(int kase=1;kase<=4;kase++) {
		int N = -1 , Q = -1;
		vector<int> A,B;
		vector<QUERY> ques;
		
		int len = Len[kase-1];
		
		N = 6000;
		Q = 1000000;
		
		if(kase==2) {		// overflow case
			for(int i=0;i<N;i++)	A.emplace_back(Random::random(1000000-100,1000000));
			for(int i=0;i<N;i++)	B.emplace_back(Random::random(0,100));
		}
		else if(kase==4) {		// not many kinds of values
			for(int i=0;i<N;i++)	A.emplace_back(Random::random(0,87));
			for(int i=0;i<N;i++)	B.emplace_back(Random::random(0,87));
		}
		else {		// random case
			for(int i=0;i<N;i++)	A.emplace_back(Random::random(0,1000000));
			for(int i=0;i<N;i++)	B.emplace_back(Random::random(0,1000000));			
		}
		
		for(int i=len;i<=N;i++) {	// make all kinds of querys exist
			int r = i;
			int l = r-len+1;
			ques.emplace_back(QUERY{l,r});
		}
		for(int i=(N-len+1);i<Q;i++) {
			if(kase&1) {	// random
				int r = Random::random(len,N);
				int l = r - len + 1;
				ques.emplace_back(QUERY{l,r});
			}
			else {		// uniform kinds of querys
				int r = (len+i) % (N-len+1) + len;
				int l = r - len + 1;
				ques.emplace_back(QUERY{l,r});
			}
		}
		for(int i=0;i<Q;i++)	swap(ques[Random::random(0,Q-1)],ques[Random::random(0,Q-1)]);		// shuffle
		
		check(N,Q,A,B,ques);
		output(path,N,Q,A,B,ques);	
	}
	return 0;
}

