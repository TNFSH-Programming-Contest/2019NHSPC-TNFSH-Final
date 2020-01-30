#include "../template/task_input_generate.hpp"
#include "../template/mylib.hpp"

#define path "input/3"
// |A_i - A_{i+1}| = |B_i - B_{i+1}| = 10^6 , for all i < N


int32_t main() {
	int A_1[] = {0,1000000,0,1000000};
	int B_1[] = {0,1000000,1000000,0};
	for(int kase=1;kase<=4;kase++) {
		int N = -1 , Q = -1;
		vector<int> A,B;
		vector<QUERY> ques;
		
		N = 6000;
		Q = 1000000;
		
		A.emplace_back(A_1[kase-1]);
		for(int i=1;i<N;i++)	A.emplace_back(1000000-A.back());
		B.emplace_back(B_1[kase-1]);
		for(int i=1;i<N;i++)	B.emplace_back(1000000-B.back());
		// check
		for(int i=0;i<N-1;i++)	assert(abs(A[i]-A[i+1])==1000000 && abs(B[i]-B[i+1])==1000000);
		
		if(kase==1) {	// random case
			for(int i=0;i<Q;i++) {
				int l = Random::random(1,N);
				int r = Random::random(l,N);
				ques.emplace_back(QUERY{l,r});
			}
		}
		else if (kase==2) {		// make all kinds of reversed-points exist
			for(int i=0;i<N;i++) {
				int mid = i+1;
				int min_len = min(mid-1,N-mid);
				int len = Random::random(0,min_len);
				int l = mid - len , r = mid + len;
				ques.emplace_back(QUERY{l,r});
			}
			for(int i=N;i<2*N-1;i++) {
				int pos = i-N+1;
				int l = pos , r = pos+1;
				int min_len = min(l-1,N-r);
				int len = Random::random(0,min_len);
				l -= len , r += len;
				ques.emplace_back(QUERY{l,r});
			}
			for(int i=2*N-1;i<Q;i++) {
				int l = Random::random(1,N);
				int r = Random::random(l,N);
				ques.emplace_back(QUERY{l,r});				
			}
			for(int i=0;i<Q;i++)	swap(ques[Random::random(0,Q-1)],ques[Random::random(0,Q-1)]);	// shuffle
		}
		else {		// TLE case
			int range = (kase&1) ? 30 : 800;
			for(int i=0;i<Q;i++) {
				int l = Random::random(1,1+range);
				int r = Random::random(N-range,N);
				ques.emplace_back(QUERY{l,r});
			}
		}
		
		check(N,Q,A,B,ques);
		output(path,N,Q,A,B,ques);	
	}
	return 0;
}

