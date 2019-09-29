#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
struct Node{
	vector<int> to;
	long long num;
} tree[1000010];
bool share[1000010];

long long dfs(int id,int p){
	if(share[id])return tree[id].num;
	long long sum=0,vn=0;
	for(int t:tree[id].to){
		if(t==p)continue;
		sum+=dfs(t,id);
		vn++;
	}
	if(vn==0)return 0;
	return min(tree[id].num,sum);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<n;i++){
		int x;
		cin>>x;
		tree[i].to.emplace_back(x);
		tree[x].to.emplace_back(i);
	}
	for(int i=0;i<n;i++){
		cin>>tree[i].num;
	}
	for(int i=0;i<q;i++){
		int id;
		cin>>id;
		share[id] = true;
	}
	cout<<dfs(0,0)<<endl;
	return 0;
}

