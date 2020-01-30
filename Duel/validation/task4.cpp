#include<bits/stdc++.h>
#define int long long
#define maxn 6005
#define endl '\n'
using namespace std;
int arr[maxn],brr[maxn];
int ans[maxn];
int32_t main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int N,Q;
	cin >> N >> Q;
	for(int i=1;i<=N;i++)	cin >> arr[i];
	for(int i=1;i<=N;i++)	cin >> brr[i];
	
	memset(ans,-1,sizeof ans);
	
	int len = -1;
		
	while(Q--) {
		int l,r;
		cin >> l >> r;
		assert(len==-1 || len == r-l+1);
		if(ans[l]==-1) {
			reverse(brr+l,brr+1+r);
			int sum = 0;
			for(int i=l;i<=r;i++)
				sum += abs(arr[i]-brr[i]);
			reverse(brr+l,brr+1+r);
			ans[l] = sum;
		}
		cout << ans[l] << endl;
		len = r-l+1;
	}
	return 0;
}

