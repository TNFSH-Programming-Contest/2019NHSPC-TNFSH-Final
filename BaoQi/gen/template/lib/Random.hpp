#ifndef _HEADER_

#define _HEADER_
#include<bits/stdc++.h>
using namespace std;

#endif

class Random {
	public:
		static long long random_64() {
			static random_device seed;
			static mt19937_64 Rand( seed() );
			return Rand();
		}
		static int random(int l,int r) {
			assert(l<=r);
			long long ret = random_64(l,r);
			assert(l<=ret && ret<=r);
			return (int)ret;
		}
		static long long random_64(long long l,long long r) {
			assert(l<=r);
			long long ret = (random_64() % (r-l+1) + (r-l+1)) % (r-l+1);
			assert(l<=ret+l && ret+l<=r);
			return ret + l;
		}
		static bool random(double P) {
			assert(0.0<=P && P<=100.0);
			int now = P*10000;
			return random(1,1000000) <= now;
		}
};
