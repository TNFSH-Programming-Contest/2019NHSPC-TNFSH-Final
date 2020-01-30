// preprocessing 
#include<bits/stdc++.h>
#define maxn 6005
#define ll long long
using namespace std;
int arr[maxn],brr[maxn];
inline void reverse(int l,int r) {
	for(;l<r;l++,r--)	swap(brr[l],brr[r]);
}
ll sum[maxn],ans[maxn][maxn];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int N,Q;
	cin >> N >> Q;
	for(int i=1;i<=N;i++)	cin >> arr[i];
	for(int i=1;i<=N;i++)	cin >> brr[i];
	
	for(int i=1;i<=N;i++) {
		int min_len = min(i-1,N-i);
		int l = i - min_len , r = i + min_len;
		for(int j=0;j<=1;j++,l++) {
			if(l>1 && r<N)	l--,r++;
			if(l > r)		continue;
			reverse(l,r);	
			for(int k=1;k<=N;k++)
				sum[k] = sum[k-1] + abs(arr[k]-brr[k]);
			
			int half_len = (r-l+1+1)/2;		// ceil
			for(int x=l+half_len-1,y=r-half_len+1;x>=1 && y<=N;x--,y++)
				ans[x][y] = sum[y] - sum[x-1];
			reverse(l,r);	
		}
	}
	
	while(Q--) {
		int l,r;
		cin >> l >> r;
		cout << ans[l][r] << '\n';
	}
	return 0;
}

