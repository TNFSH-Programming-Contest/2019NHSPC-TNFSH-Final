#include "../template/task_input_generate.hpp"
#include "../template/mylib.hpp"

#define path "input/5"
// 1 <= N <= 6000 , 1 <= Q <= 1000000


int32_t main() {
	for(int kase=1;kase<=5;kase++) {
		int N = -1 , Q = -1;
		vector<int> A,B;
		vector<QUERY> ques;
		
		if(kase==1) {	// random case
			N = 6000;
			Q = 1000000;
			for(int i=0;i<N;i++)	A.emplace_back(Random::random(0,1000000));
			for(int i=0;i<N;i++)	B.emplace_back(Random::random(0,1000000));
			for(int i=0;i<Q;i++) {
				int l = Random::random(1,N);
				int r = Random::random(1,N);
				if(l > r)	swap(l,r);
				ques.emplace_back(QUERY{l,r});
			}
		}
		else {
			N = 6000;
			if(kase==2) {	// overflow case
				for(int i=0;i<N;i++)	A.emplace_back(Random::random(1000000-100,1000000));
				for(int i=0;i<N;i++)	B.emplace_back(Random::random(0,100));
			}
			else if(kase==3) {		// not many kinds of values
				for(int i=0;i<N;i++)	A.emplace_back(Random::random(48763,48763+16));
				for(int i=0;i<N;i++)	B.emplace_back(Random::random(48763,48763+16));
			}
			else if(kase==4) {		// make all kinds of values exist
				for(int i=0;i<N;i++)	A.emplace_back(i);
				for(int i=0;i<3*N;i++)	swap(A[Random::random(0,N-1)],A[Random::random(0,N-1)]);
				for(int i=0;i<N;i++)	B.emplace_back(i+1);
				for(int i=0;i<3*N;i++)	swap(B[Random::random(0,N-1)],B[Random::random(0,N-1)]);
			}
			else if(kase==5) {
				for(int i=0;i<N;i++)	A.emplace_back(Random::random(50) ? Random::random(0,1000) : Random::random(1000000-1000,1000000));
				for(int i=0;i<N;i++)	B.emplace_back(Random::random(50) ? Random::random(0,1000) : Random::random(1000000-1000,1000000));
			}
			
			Q = 1000000;
			if (kase==3) {		// make all kinds of reversed-points exist
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
			else if(kase==2 || kase==4) {		// TLE case
				int range = (kase == 2) ? 30 : 300;
				for(int i=0;i<Q;i++) {
					int l = Random::random(1,1+range);
					int r = Random::random(N-range,N);
					ques.emplace_back(QUERY{l,r});
				}
			}
			else {		// mixed case
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
					int range = 50;
					int l = Random::random(1,1+range);
					int r = Random::random(N-range,N);
					ques.emplace_back(QUERY{l,r});			
				}
				for(int i=0;i<3*Q;i++)	swap(ques[Random::random(0,Q-1)],ques[Random::random(0,Q-1)]);	// shuffle
			}
		}
		
		check(N,Q,A,B,ques);
		output(path,N,Q,A,B,ques);	
	}
	return 0;
}

