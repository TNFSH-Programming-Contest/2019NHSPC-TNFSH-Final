// brute-forces O(QN)
#include<bits/stdc++.h>
#define maxn 6005
#define int long long
using namespace std;
int arr[maxn],brr[maxn];
int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int N,Q;
	cin >> N >> Q;
	for(int i=1;i<=N;i++)	cin >> arr[i];
	for(int i=1;i<=N;i++)	cin >> brr[i];
	while(Q--) {
		int l,r;
		cin >> l >> r;
		reverse(brr+l,brr+1+r);
		int ans = 0;
		for(int i=l;i<=r;i++)
			ans += abs(arr[i]-brr[i]);
		cout << ans << '\n';
		reverse(brr+l,brr+1+r);
	}
	return 0;
}

