// solution 2 - Treap with segment tree
#include<bits/stdc++.h>
#define maxn 500005
#define int long long
#define endl '\n'
using namespace std;
int arr[maxn];
int seg[maxn<<1];
void modify(int l,int r,int pos,int p,int new_val) {
	if(l==r)
		seg[p] = new_val;
	else {
		int mid = (l+r)>>1 , lch = p<<1 , rch = p<<1|1;
		if(pos <= mid)
			modify(l,mid,pos,lch,new_val);
		else
			modify(mid+1,r,pos,rch,new_val);
		seg[p] = max(seg[lch],seg[rch]);
	}
}
int query(int l,int r,int ql,int qr,int p) {
	if(l==ql && r==qr)
		return seg[p];
	else {
		int mid = (l+r)>>1 , lch = p<<1 , rch = p<<1|1;
		if(qr<=mid)
			return query(l,mid,ql,qr,lch);
		else if(ql>mid)
			return query(mid+1,r,ql,qr,rch);
		else
			return max(query(l,mid,ql,mid,lch),query(mid+1,r,mid+1,qr,rch));
	}
}
mt19937 Rand(1313);
struct Treap {
	Treap *lch,*rch;
	int l,r;
	int val,sum;
	int pri,size;
	Treap() {}
	Treap(int _l,int _r,int _val) {
		lch = rch = nullptr;
		l = _l;		r = _r;
		val = sum = _val;
		pri = Rand();
		size = 1;
	}
	~Treap() {
		if(lch!=nullptr)	delete lch;
		if(rch!=nullptr)	delete rch;
	}
};
inline int SZ(Treap *p) {
	return p==nullptr ? 0 : p->size;
}
inline int SUM(Treap *p) {
	return p==nullptr ? 0 : p->sum;
}
inline void pull(Treap *p) {
	p->size = 1 + SZ(p->lch) + SZ(p->rch);
	p->sum = p->val + SUM(p->lch) + SUM(p->rch);
}
Treap* Merge(Treap *a,Treap *b) {
	if(a==nullptr)	return b;
	if(b==nullptr)	return a;
	if(a->pri > b->pri) {
		a->rch = Merge(a->rch,b);
		pull(a);
		return a;
	}
	else {
		b->lch = Merge(a,b->lch);
		pull(b);
		return b;
	}
}
void Split_r(Treap *root,Treap *&a,Treap *&b,int k) {
	if(root==nullptr) {
		a = b = nullptr;
		return;
	}
	if(root->r <= k) {
		a = root;
		Split_r(root->rch,a->rch,b,k);
		pull(a);
	}	
	else {
		b = root;
		Split_r(root->lch,a,b->lch,k);
		pull(b);
	}
}
void Split_sz(Treap *root,Treap *&a,Treap *&b,int k) {
	if(root==nullptr) {
		a = b = nullptr;
		return;
	}
	if(SZ(root->lch) < k) {
		a = root;
		Split_sz(root->rch,a->rch,b,k-SZ(root->lch)-1);
		pull(a);
	}	
	else {
		b = root;
		Split_sz(root->lch,a,b->lch,k);
		pull(b);
	}
}
int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int N,Q;
	cin >> N >> Q;
	
	for(int i=1,val;i<=N;i++) {
		cin >> val;
		modify(1,N,i,1,val);
	}
	
	Treap *root = new Treap(1,N,query(1,N,1,N,1));
	
	while(Q--) {
		int t;
		cin >> t;
		if(t==1) {
			int p;
			cin >> p;
			Treap *l,*r;
			Split_r(root,l,root,p);
			Split_sz(root,root,r,1);
			int L = root->l , R = root->r;
			root = Merge(l,Merge(new Treap(L,p,query(1,N,L,p,1)),Merge(new Treap(p+1,R,query(1,N,p+1,R,1)),r)));
		}
		else if(t==2) {
			int p;
			cin >> p;
			Treap *l,*r;
			Split_r(root,l,root,p-1);
			Split_sz(root,root,r,2);
			Treap *a,*b;
			Split_sz(root,a,b,1);
			int L = a->l , R = b->r;
			root = Merge(l,Merge(new Treap(L,R,query(1,N,L,R,1)),r));
		}
		else if(t==3) {
			int p,v;
			cin >> p >> v;
			modify(1,N,p,1,v);
			Treap *l,*r;
			Split_r(root,l,root,p-1);
			Split_sz(root,root,r,1);
			int L = root->l , R = root->r;
			root = Merge(l,Merge(new Treap(L,R,query(1,N,L,R,1)),r));
		}
		else {
			int l,r;
			cin >> l >> r;
			Treap *a,*b;
			Split_r(root,root,b,r);
			Split_r(root,a,root,l-1);
			cout << root->sum << endl;
			root = Merge(a,Merge(root,b));
		}
	}
	return 0;
}
