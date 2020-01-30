#include "mylib.hpp"
#define pii pair<int,int>
struct QUERY {
	int t,p,v,l,r;
};
namespace DS {
	struct Treap {
		Treap *lch,*rch;
		int l,r;
//		int range;
		int pri,size;
		Treap() {}
		Treap(int _l,int _r) {
			assert(_l <= _r);
			lch = rch = nullptr;
			l = _l;		r = _r;
			pri = Random::random_64() % INT_MAX;
//			range = _r - _ l + 1;
			size = 1;
		}
		~Treap() {
			if(lch!=nullptr)	delete lch;
			if(rch!=nullptr)	delete rch;
		}
	};
	inline int SZ(Treap* p) {
		return p==nullptr ? 0 : p->size;
	}
	void pull(Treap* p) {
		p->size = 1 + SZ(p->lch) + SZ(p->rch);
	}
	Treap* Merge(Treap* a,Treap *b) {
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
	void Split_by_size(Treap *root,Treap *&a,Treap *&b,int k) {
		if(root==nullptr) {
			a = b = nullptr;
			return;
		}
		if(SZ(root->lch) < k) {
			a = root;
			Split_by_size(root->rch,a->rch,b,k-SZ(root->lch)-1);
			pull(a);
		}
		else {
			b = root;
			Split_by_size(root->lch,a,b->lch,k);
			pull(b);
		}
	}
	pii get_kth(Treap *&sup,int k,bool del_kth=false) {
		Treap *l,*r;
		Split_by_size(sup,sup,r,k);
		Split_by_size(sup,l,sup,k-1);
		pii ret = make_pair(sup->l,sup->r);
		if(del_kth)
			sup = Merge(l,r);
		else
			sup = Merge(Merge(l,sup),r);
		return ret;
	}
	void Split_by_r(Treap *root,Treap *&a,Treap *&b,int r) {
		if(root==nullptr) {
			a = b = nullptr;
			return;
		}
		if(root->r <= r) {
			a = root;
			Split_by_r(root->rch,a->rch,b,r);
			pull(a);
		}
		else {
			b = root;
			Split_by_r(root->lch,a,b->lch,r);
			pull(b);
		}
	}
	void insert_by_pos(Treap *&root,int k,Treap *new_node) {
		Treap *r;
		Split_by_size(root,root,r,k);
		root = Merge(Merge(root,new_node),r);
	}
	int divide_by_kth(Treap *&root,Treap *&sup,int k) {
		pii now = get_kth(sup,k,true);	// delete kth
		assert(now.first < now.second);
		
		Treap *l,*r;
		Split_by_r(root,root,r,now.second);
		Split_by_r(root,l,root,now.first-1);
		int p = Random::random(now.first,now.second-1);
		root = Merge(Merge(Merge(l,new Treap(now.first,p)),new Treap(p+1,now.second)),r);
		
		Treap *tem = nullptr;
		if(now.first != p)	tem = Merge(tem,new Treap(now.first,p));
		if(p+1 != now.second)	tem = Merge(tem,new Treap(p+1,now.second));
		insert_by_pos(sup,k-1,tem);
		
//		cout << "div : " << p << "   =   ";
		
		return p;
	}
	int merge(Treap *&root,Treap *&sup,int k) {
		assert(1<=k && k<SZ(root));
		
		Treap *l,*r;
		Split_by_size(root,root,r,k);
		Split_by_size(root,l,root,k-1);
		
		int p = root->r;
		
		Treap *a,*b;
		a = root;
		Split_by_size(r,b,r,1);
		
		Treap *tl,*tr;
		Split_by_r(sup,sup,tr,b->r);
		Split_by_r(sup,tl,sup,a->l-1);
		sup = Merge(Merge(tl,new Treap(a->l,b->r)),tr);
		
		
		root = Merge(Merge(l,new Treap(a->l,b->r)),r);

//		cout << "merge : " << p << "   =   " ;
		
		return p;
	}
	void get_l_r(Treap *root,int a,int b,int &l,int &r) {
		assert(1<=a && a<=b && b<=SZ(root));
		
		Treap *tl,*tr;
		
		Split_by_size(root,root,tr,b);
		Split_by_size(root,tl,root,b-1);
		r = root->r;
		root = Merge(Merge(tl,root),tr);
		
		Split_by_size(root,root,tr,a);
		Split_by_size(root,tl,root,a-1);
		l = root->l;
		root = Merge(Merge(tl,root),tr);
	}
	void output(Treap *p) {
		if(p==nullptr)	return;
		output(p->lch);
		cout << p->l << " , " << p->r << "  |  ";
		output(p->rch);
	}
	void divide_by_pos(Treap *&root,Treap *&sup,int pos) {
		Treap *l,*r;
		
		Split_by_r(root,l,root,pos);
		Split_by_size(root,root,r,1);
		int L = root->l , R = root->r;
		root = Merge(l,Merge(new Treap(L,pos),Merge(new Treap(pos+1,R),r)));
		
		Split_by_r(sup,sup,r,R);
		Split_by_r(sup,l,sup,L-1);
		Treap *tem = nullptr;
		if(L!=pos)	tem = Merge(tem,new Treap(L,pos));
		if(pos+1!=R)	tem = Merge(tem,new Treap(pos+1,R));
		sup = Merge(Merge(l,tem),r);
	}
}
