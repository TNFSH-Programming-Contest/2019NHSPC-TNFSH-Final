#include "../template/task_input_generate.hpp"

#define path "input/2"
// # of "t = 4" <= 100


int32_t main() {
	for(int kase=1;kase<=4;kase++) {
		int N = -1 , Q = -1;
		vector<int> A;
		vector<QUERY> ques;
		
		if(kase==1) {		// all distenses of the pair of "t = 4" is 5000
			N = Q = 100000;
			for(int i=0;i<N;i++)	A.emplace_back(Random::random(1000000000-10000000,1000000000));
			
			int tim = 1000;
			
			DS::Treap *root = new DS::Treap(1,N) , *sup = (N==1 ? nullptr : new DS::Treap(1,N));
			for(int i=0;i<Q;i++) {
				int t = -1 , p = -1 , v = -1 , l = -1 , r = -1;
				if(i % tim == 0) {		// query , make r-l+1 large enough
					t = 4;
					int sz = SZ(root);
					int a = Random::random(1,min(31,sz));
					int b = Random::random(max(a,sz-30),sz);
					get_l_r(root,a,b,l,r);
				}
				else {
					int x[] = {500,8000,20000,100000};
					int y[] = {95,87,79,33};
					int idx = 0;
					for(;idx<4 && SZ(root)<=x[idx];idx++);
					idx--;
					if(SZ(sup)!=0 && Random::random(y[idx]))
						t = 1;
					if(t==1) {
						int k = Random::random(1,sup->size);
						p = divide_by_kth(root,sup,k);
					}
					else {
						t = Random::random(50) && SZ(root)!=1 ? 2 : 3;
						if(t==2) {
							int k = Random::random(1,root->size-1);
							p = merge(root,sup,k);		
						}
						else {
							p = Random::random(1,N);
							v = Random::random(100000000,900000000);								
						}
					}
				}
				ques.emplace_back(QUERY{t,p,v,l,r});
			}
		}
		else if(kase==2) {		// random case
			N = Q = 100000;
			for(int i=0;i<N;i++)	A.emplace_back(Random::random(1,1000000000));
		
			DS::Treap *root = new DS::Treap(1,N) , *sup = (N==1 ? nullptr : new DS::Treap(1,N));
			int Q_life = 100;
			
			for(int i=0;i<Q;i++) {
				int t = -1 , p = -1 , v = -1 , l = -1 , r = -1;
				
				if(Q_life > 0 && Random::random(0.01))
					t = 4;
				while(t == -1) {
					t = Random::random(1,3);
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
					
					Q_life--;
				}
				
				ques.emplace_back(QUERY{t,p,v,l,r});
			}			
		}
		else {		// make group many enough (sqrt(N) and N/5) 
			N = Q = 100000;
			
			for(int i=0;i<N;i++)	A.emplace_back(Random::random(101648763,1000000000));
			
			int num = (kase&1 ? 300 : 20000);
			
			
			DS::Treap *root = new DS::Treap(1,N) , *sup = (N==1 ? nullptr : new DS::Treap(1,N));			
			int Q_life = 100;
			
			set<int> init;
			while((int)init.size() < num)	init.insert(Random::random(1,N));
			for(int pos : init) {
				int t = -1 , p = -1 , v = -1 , l = -1 , r = -1;
				
				t = 1;
				p = pos;
				divide_by_pos(root,sup,p);
				
				ques.emplace_back(QUERY{t,p,v,l,r});
			}
			for(int i=0;i<num;i++)	swap(ques[Random::random(0,num-1)],ques[Random::random(0,num-1)]);	// shuffle
			
			for(int i=num;i<Q;i++) {
				int t = -1 , p = -1 , v = -1 , l = -1 , r = -1;
				
				if(Q_life > 0 && Random::random(0.1))
					t = 4;
				else {
					int buf = max(0,num-SZ(root));
					if(SZ(root)!=N && Random::random(min(100,33+buf)))
						t = 1;
					else {
						t = SZ(root)!=1 && Random::random(50) ? 2 : 3;
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
					v = Random::random(1,1000000000);
				}	
				else {
					int a = -1 , b = -1;
					int sz = SZ(root);
					if(Random::random(80)) {	// 80%p r-l+1 is large enough
						a = Random::random(1,min(31,sz));
						b = Random::random(max(a,sz-30),sz);
					}	
					else {
						a = Random::random(1,sz);
						b = Random::random(a,sz);	
					}				
					get_l_r(root,a,b,l,r);
					
					Q_life--;
				}
				
				ques.emplace_back(QUERY{t,p,v,l,r});
			}
		}
		
		check(N,Q,A,ques);
		output(path,N,Q,A,ques);	
	}
	return 0;
}

