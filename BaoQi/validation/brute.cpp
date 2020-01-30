// brute-force O(QN)
#include<bits/stdc++.h>
#define int long long
#define maxn 500005
using namespace std;
int arr[maxn];
bool is_div[maxn];
int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,q;
	cin >> n >> q;
	for(int i=1;i<=n;i++)
		cin >> arr[i];
	while(q--) {
		int type;
		cin >> type;
		if(type==1 || type==2) {
			int p;
			cin >> p;
			is_div[p] = !is_div[p];
		}
		else if(type==3) {
			int pos,new_val;
			cin >> pos >> new_val;
			arr[pos] = new_val;
		}
		else {
			int l,r;
			cin >> l >> r;
			int ans = 0 , max_val = 0;
			for(int i=l;i<=r;i++) {
				max_val = max(max_val,arr[i]);
				if(is_div[i]) {
					ans += max_val;
					max_val = 0;
				}
			}
			ans += max_val;
			cout << ans << '\n';
		}
	}
	return 0;
}

