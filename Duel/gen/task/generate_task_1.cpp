#include "../template/task_input_generate.hpp"
#include "../template/mylib.hpp"

#define path "input/1"
// 1 <= N,Q <= 87


int32_t main() {
	for(int kase=1;kase<=3;kase++) {
		int N = -1 , Q = -1;
		vector<int> A,B;
		vector<QUERY> ques;
		if(kase==1) {
			N = 5;	Q = 4;
			A = {1,4,3,8,7};
			B = {2,6,5,1,9};
			ques = {{1,3},{1,5},{2,5},{3,3}};	
		}
		else if(kase==2) {	// random case
			N = Q = 87;
			for(int i=0;i<N;i++)	A.emplace_back(Random::random(0,1000000));
			for(int i=0;i<N;i++)	B.emplace_back(Random::random(0,1000000));
			for(int i=0;i<Q;i++) {
				int l = Random::random(1,N);
				int r = Random::random(l,N);
				ques.emplace_back(QUERY{l,r});
			}
		}
		else {
			N = Q = 87;
			for(int i=0;i<N;i++)	A.emplace_back(Random::random(0,100));
			for(int i=0;i<N;i++)	B.emplace_back(Random::random(0,100));
			for(int i=0;i<Q;i++) {
				int l = Random::random(1,9);
				int r = Random::random(N-8,N);
				ques.emplace_back(QUERY{l,r});
			}
		}
		check(N,Q,A,B,ques);
		output(path,N,Q,A,B,ques);	
	}
	return 0;
}

