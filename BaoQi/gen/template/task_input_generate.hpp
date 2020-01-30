#include "Type.hpp"

#ifndef _HEADER_

#define _HEADER_
#include<bits/stdc++.h>
using namespace std;

#endif

//#define endl '\n'

void check(int N,int Q,vector<int> A,vector<QUERY> ques) {
	const int maxn = 100000;
	const int maxq = 100000;
	const int maxv = 1000000000;
	assert(1<=N && N<=maxn);
	assert(1<=Q && Q<=maxq);
	assert(N == (int)A.size());
	assert(Q == (int)ques.size());
	for(int val : A)
		assert(1<=val && val<=maxv);
		
	vector<bool> div(N-1,false);
	for(QUERY now : ques) {
		assert(1<=now.t && now.t<=4);
		if(now.t==1) {
			assert(1<=now.p && now.p<N);
			assert(div[now.p-1]==false);
			div[now.p-1] = true;
		}
		else if(now.t==2) {
			assert(1<=now.p && now.p<N);
			assert(div[now.p-1]==true);
			div[now.p-1] = false;
		}
		else if(now.t==3) {
			assert(1<=now.p && now.p<=N);
			assert(1<=now.v && now.v<=maxv);
		}
		else {
			assert(1<=now.l && now.l<=now.r && now.r<=N);
			assert(now.l==1 || div[now.l-1-1]==true);
			assert(now.r==N || div[now.r-1]==true);
		}
	}
}

void output(string file,int N,int Q,vector<int> A,vector<QUERY> ques) {	// file Example : "../input/5"
							// ( generate 5th subtask in "../input" )

//=======================================
	// file name setting 
	static int task_idx = 1;
	file += "0";
	auto int_to_string = [=](int idx)->string{
		assert(idx<10);		// otherwise there are too many task such that judge will be too slow
		string ret = "";
		ret += (char)('0'+idx);
		return ret;
	};
	file += int_to_string(task_idx);;
	file += ".in";
	
	task_idx++;
	freopen(file.c_str(),"w",stdout);
//=======================================
	// write output here
	cout << N << " " << Q << endl;
	for(int i=0;i<N;i++) {
		if(i!=0)	cout << " ";
		cout << A[i];
	}
	cout << endl;
	for(QUERY now : ques) {
		cout << now.t << " ";
		if(now.t==1 || now.t==2) {
			cout << now.p << endl;
		}
		else if(now.t==3) {
			cout << now.p << " " << now.v << endl;
		}
		else {
			cout << now.l << " " << now.r << endl;
		}
	}
//=======================================
	cout.flush();
}

