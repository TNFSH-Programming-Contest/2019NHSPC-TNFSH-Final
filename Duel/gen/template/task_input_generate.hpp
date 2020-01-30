#include "Type.hpp"

#ifndef _HEADER_

#define _HEADER_
#include<bits/stdc++.h>
using namespace std;

#endif

#define endl '\n'

void check(int N,int Q,vector<int> A,vector<int> B,vector<QUERY> ques) {
	const int maxn = 6000;
	const int maxq = 1000000;
	const int maxv = 1000000;
	assert(1<=N && N<=maxn);
	assert(1<=Q && Q<=maxq);
	assert(N == (int)A.size() && N == (int)B.size());
	assert(Q == (int)ques.size());
	for(int val : A)	assert(0<=val && val<=maxv);
	for(int val : B)	assert(0<=val && val<=maxv);
	for(QUERY now : ques)	assert(1<=now.l && now.l<=now.r && now.r<=N);
}

void output(string file,int N,int Q,vector<int> A,vector<int> B,vector<QUERY> ques) {	// file Example : "../input/5"
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
	for(int i=0;i<N;i++) {
		if(i!=0)	cout << " ";
		cout << B[i];
	}
	cout << endl;
	for(int i=0;i<Q;i++)
		cout << ques[i].l << " " << ques[i].r << endl;
//=======================================
	cout.flush();
}

