// solution 1
#include<bits/stdc++.h>
#define int long long
#define maxn 1050000
#define endl '\n'
using namespace std;
struct node {
	int sum;
	int lmax,rmax;
	int lpos,rpos;
}seg[maxn<<2];
node merge(node lch,node rch) {
	node ret;
	ret.sum = lch.sum - lch.rmax + rch.sum - rch.lmax + max(lch.rmax,rch.lmax);
	ret.lmax = max(lch.lmax,(lch.lpos==-1 ? rch.lmax : 0));
	ret.rmax = max(rch.rmax,(rch.rpos==-1 ? lch.rmax : 0));
	ret.lpos = (lch.lpos==-1 ? rch.lpos : lch.lpos);
	ret.rpos = (rch.rpos==-1 ? lch.rpos : rch.rpos);
	return ret;
}
void build(int l,int r,int p) {
	if(l==r) {
		int val = 0;
		if(l&1)		cin >> val;
		seg[p] = node{val,val,val,-1,-1};
	}
	else {
		int mid = (l+r)>>1 , lch = p<<1 , rch = p<<1|1;
		build(l,mid,lch);
		build(mid+1,r,rch);
		seg[p] = merge(seg[lch],seg[rch]);
	}
}
void modify(int l,int r,int pos,int p,int new_val) {
	if(l==r) {
		if(new_val==-1)
			seg[p] = node{0,0,0,l,l};
		else
			seg[p] = node{new_val,new_val,new_val,-1,-1};
	}
	else {
		int mid = (l+r)>>1 , lch = p<<1 , rch = p<<1|1;
		if(pos<=mid)
			modify(l,mid,pos,lch,new_val);
		else
			modify(mid+1,r,pos,rch,new_val);
		seg[p] = merge(seg[lch],seg[rch]);
	}
}
node query(int l,int r,int ql,int qr,int p) {
	if(l==ql && r==qr)
		return seg[p];
	else {
		int mid = (l+r)>>1 , lch = p<<1 , rch = p<<1|1;
		if(qr<=mid)
			return query(l,mid,ql,qr,lch);
		else if(ql>mid)
			return query(mid+1,r,ql,qr,rch);
		else
			return merge(query(l,mid,ql,mid,lch),query(mid+1,r,mid+1,qr,rch)); 
	}
}
int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,q;
	cin >> n >> q;
	build(1,n*2-1,1);
	while(q--) {
		int type;
		cin >> type;
		if(type==1 || type==2) {
			int p;
			cin >> p;
			modify(1,n*2-1,p*2,1,(type==1 ? -1 : 0));
		}
		else if(type==3) {
			int p,v;
			cin >> p >> v;
			modify(1,n*2-1,p*2-1,1,v);
		}
		else {
			int l,r;
			cin >> l >> r;
			cout << query(1,n*2-1,l*2-1,r*2-1,1).sum << endl;
		}
	}
	return 0;
}
