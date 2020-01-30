// solutions 3 - normal segment-tree
#include<bits/stdc++.h>
#define int long long
#define maxn 500005
#define endl '\n'
using namespace std;
int mapping[maxn];
struct node {
	int max_val = 0 ,sum = 0;
}peo[maxn<<2],team[maxn<<2];
node merge(node lch,node rch) {
	node ret;
	ret.max_val = max(lch.max_val,rch.max_val);
	ret.sum = lch.sum + rch.sum;
	return ret;
}
void modify(int l,int r,int pos,int p,int new_val,node *seg) {
	if(l==r)
		seg[p].max_val = seg[p].sum = new_val;
	else {
		int mid = (l+r)>>1 , lch = p<<1 , rch = p<<1|1;
		if(pos <= mid)
			modify(l,mid,pos,lch,new_val,seg);
		else
			modify(mid+1,r,pos,rch,new_val,seg);
		seg[p] = merge(seg[lch],seg[rch]);
	}
}
node query(int l,int r,int ql,int qr,int p,node *seg) {
	if(l==ql && r==qr)
		return seg[p];
	else {
		int mid = (l+r)>>1 , lch = p<<1 , rch = p<<1|1;
		if(qr<=mid)
			return query(l,mid,ql,qr,lch,seg);
		else if(ql>mid)
			return query(mid+1,r,ql,qr,rch,seg);
		else
			return merge(query(l,mid,ql,mid,lch,seg),query(mid+1,r,mid+1,qr,rch,seg));
	}
}
int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int N,Q;
	cin >> N >> Q;
	for(int i=1,val;i<=N;i++) {
		cin >> val;
		modify(1,N,i,1,val,peo);
	}
	modify(1,N,N,1,query(1,N,1,N,1,peo).max_val,team);
	
	memset(mapping,-1,sizeof mapping);
	mapping[1] = N;		mapping[N] = 1;
	set<int> R;
	R.insert(N);
	
	while(Q--) {
		int t;
		cin >> t;
		if(t==1) {
			int p;
			cin >> p;
			
			int bl = p+1 , br = *R.lower_bound(p);
			int al = mapping[br] , ar = p;
			
			int max_val = query(1,N,al,ar,1,peo).max_val;
			modify(1,N,ar,1,max_val,team);
			max_val = query(1,N,bl,br,1,peo).max_val;
			modify(1,N,br,1,max_val,team);
			
			mapping[al]	= ar;	mapping[ar] = al;
			mapping[bl] = br;	mapping[br] = bl;
			
			R.insert(ar);
		}
		else if(t==2) {
			int p;
			cin >> p;
			
			int l = mapping[p] , r = mapping[p+1];
		
			modify(1,N,p,1,0,team);
			int max_val = query(1,N,l,r,1,peo).max_val;
			modify(1,N,r,1,max_val,team);
		
			mapping[l] = r;		mapping[r] = l;
			
			R.erase(p);
		}
		else if(t==3) {
			int p,v;
			cin >> p >> v;
			
			int r = *R.lower_bound(p);
			int l = mapping[r];
			
			modify(1,N,p,1,v,peo);
			int max_val = query(1,N,l,r,1,peo).max_val;
			modify(1,N,r,1,max_val,team);
		}
		else {
			int l,r;
			cin >> l >> r;
			cout << query(1,N,l,r,1,team).sum << endl;
		}
	}
	return 0;
}

