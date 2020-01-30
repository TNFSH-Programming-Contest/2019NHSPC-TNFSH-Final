#include<bits/stdc++.h>
#define int long long
#define maxn 6005
using namespace std;
int arr[maxn],brr[maxn];
int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int N,Q;
	cin >> N >> Q;
	for(int i=1;i<=N;i++)	cin >> arr[i];
	for(int i=1;i<=N;i++)	cin >> brr[i];
	for(int i=1;i<N;i++) {
		assert(abs(arr[i]-arr[i+1])==1000000);
		assert(abs(brr[i]-brr[i+1])==1000000);
	}
	while(Q--) {
		int l,r;
		cin >> l >> r;
		int len = r-l+1;
		int a = abs(arr[l]-brr[r]) * ((len+1)/2);
		int b = 0;
		if(l!=r) 	b = abs(arr[l+1]-brr[r-1]) * (len/2);
		cout << a+b << '\n';
	}
	return 0;
}

