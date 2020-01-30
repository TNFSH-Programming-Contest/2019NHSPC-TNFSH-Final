#include<bits/stdc++.h>
#define int long long
#define maxn 100005
#define endl '\n'
using namespace std;
int n,q;
int bit[maxn];
inline int lowbit(int x) {
	return x&-x;
}
void add(int p,int val) {
	while(p <= n) {
		bit[p] += val;
		p += lowbit(p);
	}
}
int sum(int p) {
	if(p==0)	return 0;
	int ret = 0;
	while(p > 0) {
		ret += bit[p];
		p -= lowbit(p);
	}
	return ret;
}
int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> q;
	int val = -1;
	for(int i=1,now;i<=n;i++) {
		cin >> now;
		assert(val==-1 || val==now);
		val = now;
	}
	while(q--) {
		int t;
		cin >> t;
		if(t==1 || t==2) {
			int p;
			cin >> p;
			add(p,(t==1 ? 1 : -1));
		}
		else if(t==3) {
			int p,v;
			cin >> p >> v;
			assert(val==v);
		}
		else {
			int l,r;
			cin >> l >> r;
			int now = sum(r-1) - sum(l-1);
			cout << val * (now+1) << endl;
		}
	}
	return 0;
}

