#include "../template/task_input_generate.hpp"

#define path "input/1"
// 1 <= N,Q <= 100


int32_t main() {
	for(int kase=1;kase<=3;kase++) {
		int N = -1 , Q = -1;
		vector<int> A;
		vector<QUERY> ques;

		if(kase==1) {
			N = 5;	Q = 11;
			A = {1,2,3,4,5};
			ques.emplace_back(QUERY{4,-1,-1,1,5});
			ques.emplace_back(QUERY{3,3,6,-1,-1});
			ques.emplace_back(QUERY{4,-1,-1,1,5});
			ques.emplace_back(QUERY{1,2,-1,-1,-1});
			ques.emplace_back(QUERY{4,-1,-1,1,2});
			ques.emplace_back(QUERY{4,-1,-1,1,5});
			ques.emplace_back(QUERY{1,3,-1,-1,-1});
			ques.emplace_back(QUERY{4,-1,-1,1,5});
			ques.emplace_back(QUERY{4,-1,-1,3,3});
			ques.emplace_back(QUERY{2,2,-1,-1,-1});
			ques.emplace_back(QUERY{4,-1,-1,1,5});
		}
		else if(kase==2) {		// random case
			N = Q = 100;
			for(int i=0;i<N;i++)	A.emplace_back(Random::random(1,1000000000));
			
			DS::Treap *root = new DS::Treap(1,N) , *sup = (N==1 ? nullptr : new DS::Treap(1,N));
			
			for(int i=0;i<Q;i++) {
				int t=-1,p=-1,v=-1,l=-1,r=-1;
				t = Random::random(1,4);
				if(t==1) {
					if(SZ(sup)==0) {
						i--;
						continue;
					}
					int k = Random::random(1,sup->size);
					p = divide_by_kth(root,sup,k);
				}	
				else if(t==2) {
					if(root->size==1) {
						i--;
						continue;
					}
					int k = Random::random(1,root->size-1);
					p = merge(root,sup,k);
				}
				else if(t==3) {
					p = Random::random(1,N);
					v = Random::random(1,1000000000);
				}
				else {
					int a = Random::random(1,root->size);
					int b = Random::random(a,root->size);
					get_l_r(root,a,b,l,r);
				}
				ques.emplace_back(QUERY{t,p,v,l,r});
			}
		}
		else {		// make group many enough
			N = Q = 100;
			for(int i=0;i<N;i++)	A.emplace_back(Random::random(1000000000-100,1000000000));
			
			DS::Treap *root = new DS::Treap(1,N) , *sup = (N==1 ? nullptr : new DS::Treap(1,N));
			for(int i=0;i<Q/2;i++) {
				int t=-1,p=-1,v=-1,l=-1,r=-1;
				
				t = 1;
				p = i*2+1;
				
				divide_by_pos(root,sup,p);
				
				ques.emplace_back(QUERY{t,p,v,l,r});
			}
			for(int i=0;i<Q/2;i++)	swap(ques[Random::random(0,Q/2)],ques[Random::random(0,Q/2)]);	// shuffle
			
			for(int i=Q/2;i<Q;i++) {
				int t=-1,p=-1,v=-1,l=-1,r=-1;
				
				t = Random::random(80) ? 4 : 2;
				
				if(t==2) {
					if(root->size==1) {
						i--;
						continue;
					}
					int k = Random::random(1,SZ(root)-1);
					p = merge(root,sup,k);
				}
				else {
					int a = Random::random(1,min(3,SZ(root)));
					int b = max(a,Random::random(max(SZ(root)-3,1),SZ(root)));
					get_l_r(root,a,b,l,r);
				}
				
				ques.emplace_back(QUERY{t,p,v,l,r});
			}
		}
		
		check(N,Q,A,ques);
		output(path,N,Q,A,ques);	
	}
	return 0;
}

