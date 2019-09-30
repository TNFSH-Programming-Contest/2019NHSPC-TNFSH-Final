#include<bits/stdc++.h>
#include "testlib.h"
#define endl '\n'
using namespace std;
int tree[1000010],arr[1000010],costref[105];
struct Node{
	vector<int> to;
	int cnum,cost,dep;
}t2 [1000010];
vector<pair<int,int>> Ans;
vector<pair<int,int>> queries;

int main(int argc,char* argv[]){
	ios::sync_with_stdio(0);
	cin.tie(0);
	registerGen(argc, argv, 1);
	memset(tree,-1,sizeof(tree));
	int n,q,branchmax,branchnum,randomcost,special;
	n = atoi(argv[2])-1;
	q = atoi(argv[3]);
	branchmax = atoi(argv[4]);
	branchnum = atoi(argv[5]);
	randomcost = atoi(argv[6]);
	special = atoi(argv[7]);
	costref[1] = 1000000000;
	for(int i=2;i<=100;i++){
		costref[i] = max(1,costref[i-1]/(branchmax+1));
	}
	for(int i=1;i<=n;i++){
		arr[i-1] = i;
	}
	shuffle(arr,arr+n);
	queue<pair<int,int>> qu;
	queue<int> numpool;
	for(int i=0;i<n;i++){
		numpool.push(arr[i]);
		//cout<<arr[i]<<endl;
	}
	qu.push(make_pair(0,0));
	t2[0].cost = 1000000000;
	t2[0].dep = 0;
	queries.push_back(make_pair(0,0));
	while(!qu.empty()&&!numpool.empty()){
		int bnum = rnd.next(0,min(branchmax,(int)numpool.size()));
		if(branchnum)bnum=branchnum;
		pair<int,int> now = qu.front();
		//Ans.push_back(make_pair(now.second,now.first));
		qu.pop();
		if(special>=0){
			//cout<<"debug"<<endl;
			if(special>0){
				bnum = rnd.next(2,branchmax);
				special--;
				queries.push_back(make_pair(rnd.next(max(0,t2[now.first].dep-t2[now.first].dep/2),t2[now.first].dep+t2[now.first].dep/2),now.first));
			}
			else{
				bnum = 1;
			}
		}
		if(qu.empty())bnum = max(bnum,1);
		for(int i=0;i<bnum;i++){
			int x;
			while(!numpool.empty()){
				x = numpool.front();
				numpool.pop();
				if(tree[x]!=-1)continue;
				tree[x] = now.first;
				t2[now.first].to.push_back(x);
				t2[now.first].cnum++;
				t2[x].dep = t2[now.first].dep+1;
				if(randomcost){
					t2[x].cost = rnd.next(0,1000000000);
				}
				else{
					if(t2[x].dep>=100){
						t2[x].cost = rnd.next(0,5);
					}
					else{
						t2[x].cost = rnd.next(max(0,costref[t2[x].dep]-10),min(1000000000,costref[t2[x].dep]+10));
					}
				}
				if(special<0)queries.push_back(make_pair(rnd.next(max(0,t2[x].dep-t2[x].dep/2),t2[x].dep+t2[x].dep/2),x));
				
				qu.push(make_pair(x,now.second+1));
				break;
			}
		}
	}
	sort(queries.begin(),queries.end());
	reverse(queries.begin(),queries.end());
	
	cout<<n+1<<" "<<q<<endl;
	for(int i=1;i<=n;i++){
		assert(tree[i]!=-1);
		if(i>1)cout<<" ";
		cout<<tree[i];
	}
	cout<<endl;
	for(int i=0;i<=n;i++){
		//assert(tree[i]!=-1);
		if(i>0)cout<<" ";
		cout<<t2[i].cost;
	}
	cout<<endl;
	assert(queries.size()>=q);
	for(int i=0;i<q;i++){
		if(i>0)cout<<" ";
		cout<<queries[i].second;
	}
	cout<<endl;
	/*
	for(pair<int,int> x:queries){
		cout<<x.second<<" "<<x.first<<endl;
	}
	cout<<endl;*/
	return 0;
}

