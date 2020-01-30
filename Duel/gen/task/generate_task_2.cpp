#include "../template/task_input_generate.hpp"
#include "../template/mylib.hpp"

#define path "input/2"
// 1 <= N,Q <= 3000


int32_t main() {
	for(int kase=1;kase<=3;kase++) {
		int N = -1 , Q = -1;
		vector<int> A,B;
		vector<QUERY> ques;
		if(kase==1) {	// random case
			N = Q = 3000;
			for(int i=0;i<N;i++)	A.emplace_back(Random::random(0,1000000));
			for(int i=0;i<N;i++)	B.emplace_back(Random::random(0,1000000));
			for(int i=0;i<Q;i++) {
				int l = Random::random(1,N);
				int r = Random::random(l,N);
				ques.emplace_back(QUERY{l,r});
			}
		}
		else if(kase==2) {		// overflow case
			N = Q = 3000;
			for(int i=0;i<N;i++)	A.emplace_back(Random::random(0,100));
			for(int i=0;i<N;i++)	B.emplace_back(Random::random(1000000-100,1000000));
			for(int i=0;i<Q;i++) {
				int l = Random::random(1,100);
				int r = Random::random(N-99,N);
				ques.emplace_back(QUERY{l,r});
			}
		}
		else {		// make all reversed-points different
			N = Q = 3000;
			for(int i=0;i<N;i++)	A.emplace_back(Random::random(0,1000000));
			for(int i=0;i<N;i++)	B.emplace_back(Random::random(0,1000000));
			for(int i=0;i<Q;i++) {
				int mid = i+1;
				int min_len = min(mid-1,N-mid);
				int len = Random::random(0,min_len);
				int l = mid - len , r = mid + len;
				ques.emplace_back(QUERY{l,r});
			}
			for(int i=0;i<Q;i++)	swap(ques[Random::random(0,Q-1)],ques[Random::random(0,Q-1)]);	// shuffle
		}
		check(N,Q,A,B,ques);
		output(path,N,Q,A,B,ques);	
	}
	return 0;
}

