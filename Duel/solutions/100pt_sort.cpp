// offline and sorting
#include<bits/stdc++.h>
#define maxn 6005
#define maxq 1000005
#define ll long long
using namespace std;
int arr[maxn],brr[maxn];
struct que {
	int l,r,tmp;
}ques[maxq];
inline void reverse(int l,int r) {
	for(;l<r;l++,r--)	swap(brr[l],brr[r]);
}
ll sum[maxn],ans[maxq];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int N,Q;
	cin >> N >> Q;
	for(int i=1;i<=N;i++)	cin >> arr[i];
	for(int i=1;i<=N;i++)	cin >> brr[i];
	for(int i=1;i<=Q;i++)	cin >> ques[i].l >> ques[i].r , ques[i].tmp = i;
	
	sort(ques+1,ques+1+Q,[=](que a,que b)->bool
		{return a.r+a.l < b.r+b.l;});
	for(int i=1,j;i<=Q;i=j) {
		int min_len = min(ques[i].l-1,N-ques[i].r);
		int l = ques[i].l - min_len , r = ques[i].r + min_len;
		reverse(l,r);
		for(int k=1;k<=N;k++)	sum[k] = sum[k-1] + abs(arr[k]-brr[k]);		

		j = i;
		while(j<=Q && ques[i].r+ques[i].l == ques[j].r+ques[j].l) {
			ans[ques[j].tmp] = sum[ques[j].r] - sum[ques[j].l-1];
			j++;
		}
		reverse(l,r);
	}
	
	for(int i=1;i<=Q;i++)
		cout << ans[i] << '\n';
	return 0;
}

