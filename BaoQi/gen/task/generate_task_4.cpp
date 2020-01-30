#include "../template/task_input_generate.hpp"

#define path "input/4"
// 1 <= N,Q <= 500000


int32_t main() {
	for(int kase=1;kase<=5;kase++) {
		int N = -1 , Q = -1;
		vector<int> A;
		vector<QUERY> ques;
		
		if(kase==1) {	// random case
			N = Q = 100000;
			
			for(int i=0;i<N;i++)	A.emplace_back(Random::random(1,1000000000));
			
			DS::Treap *root = new DS::Treap(1,N) , *sup = (N==1 ? nullptr : new DS::Treap(1,N));
			
			for(int i=0;i<Q;i++) {
				int t = -1 , p = -1 , v = -1 , l = -1 , r = -1;
				
				while(t == -1) {
					t = Random::random(1,4);
					if(t==1 && SZ(root)==N)	t = -1;
					if(t==2 && SZ(root)==1)	t = -1;
				}
				
				if(t==1) {
					int k = Random::random(1,sup->size);
					p = divide_by_kth(root,sup,k);
				}	
				else if(t==2) {
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
		else {	// make # of groups is always about sqrt(N) or 25 or 300000 or 5
			int tim = (time(NULL) + clock()) % 100000;
			while(tim--)	Random::random_64();
		
			N = Q = 100000;
			
			int NUM[] = {300,20,70000,6};
			int num = NUM[kase-2];
			
			for(int i=0;i<N;i++)	A.emplace_back(kase==2 ? Random::random(1234,4321) : Random::random(100000000+num,1000000000));
			
			DS::Treap *root = new DS::Treap(1,N) , *sup = (N==1 ? nullptr : new DS::Treap(1,N));			
			
			for(int i=0;i<Q;i++) {
				int t = -1 , p = -1 , v = -1 , l = -1 , r = -1;
				
				if(kase!=5) {
					int buf = max(0,num-SZ(root));
					if(SZ(root)!=N && Random::random(min(100,29+kase+buf)))
						t = 1;
					else {
						while(t == -1) {
							t = Random::random(2,4);
							if(t==2 && SZ(root)==1)	t = -1;
						}
					}
				}
				else {		// make event 1,2 many
					int buf = max(0,num-SZ(root));
					if(SZ(root)!=N && Random::random(min(100,40+kase+buf)))
						t = 1;
					else {
						if(Random::random(0.01)) {
							t = 4;
						}
						else {
							if(SZ(root)!=1 && Random::random(60))
								t = 2;
							else
								t = 3;
						}
					}					
				}
				
				if(t==1) {
					int k = Random::random(1,sup->size);
					p = divide_by_kth(root,sup,k);
				}	
				else if(t==2) {
					int k = Random::random(1,root->size-1);
					p = merge(root,sup,k);
				}
				else if(t==3) {
					p = Random::random(1,N);
					v = Random::random(81000,1000000000);
				}	
				else {
					int RANGE[] = {60,5,517,1};
					int range = RANGE[kase-2];
					
					int a = -1 , b = -1;
					int sz = SZ(root);
					if(Random::random(90)) {	// 90% r-l+1 is large enough
						a = Random::random(1,min(range,sz));
						b = Random::random(max(a,sz-range),sz);
					}	
					else {
						a = Random::random(1,sz);
						b = Random::random(a,sz);	
					}				
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

