#include <stdio.h>
#include <algorithm>

const int N = 1000005;
const int M = 10000005;
const int SQM = 32000;
const int NAM_LEN = 32;

int tbl[M];
int dp_pf[M], dp_f[M], dp_mpf[M], dp_fts[M];
int ary[N], idx[N];
char name[N][NAM_LEN];

bool comp(int p, int q)
{
	p = ary[p];
	q = ary[q];
	if (dp_pf[p] != dp_pf[q])
	{
		return dp_pf[p] > dp_pf[q];
	}
	if (dp_f[p] != dp_f[q])
	{
		return dp_f[p] > dp_f[q];
	}
	if (dp_mpf[p] != dp_mpf[q])
	{
		return dp_mpf[p] > dp_mpf[q];
	}
	if (dp_fts[p] != dp_fts[q])
	{
		return dp_fts[p] > dp_fts[q];
	}
	return p > q;
}

int main()
{
	int i, j, k, p, t, n, first;
	for (i=3; i<SQM; i+=2)
	{
		if (!tbl[i])
		{
			for (j=i*i, k=i+i; j<M; j+=k)
			{
				tbl[j] = i;
			}
		}
	}
	dp_pf[1] = 0;
	dp_f[1] = 1;
	dp_mpf[1] = 1;
	dp_fts[1] = 0;
	for (i=2; i<M; i++)
	{
		if (!(i & 1))
		{
			p = 2;
		}
		else if (tbl[i])
		{
			p = tbl[i];
		}
		else
		{
			p = i;
		}
		for (t=1, j=i/p; j>1&&!(j%p); t++, j/=p);
		dp_pf[i] = dp_pf[j] + 1;
		dp_f[i] = dp_f[j] * (t+1);
		dp_mpf[i] = std::max(dp_mpf[j], p);
		dp_fts[i] = dp_fts[j] + t;
	}
	first = 1;
	while (scanf("%d", &n) == 1)
	{
		if (!first)
		{
			puts("");
		}
		first = 0;
		for (i=0; i<n; i++)
		{
			scanf("%s%d", name[i], &ary[i]);
			idx[i] = i;
		}
		std::sort(idx, idx+n, comp);
		for (i=0; i<n; i++)
		{
			puts(name[idx[i]]);
		}
	}
	return 0;
}
