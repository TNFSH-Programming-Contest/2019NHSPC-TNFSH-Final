#include<bits/stdc++.h>
using namespace std;

mt19937 mt(46416);

string name(int mx = 31)
{
    int len = 3+mt()%(mx-3+1);
    static const string base =  "abcdefghijklmnopqrstuzwxyz"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                "0123456789!@#$%^&*()-=";
                                
    string res;
    
    while( len-- ) res.push_back( base[mt()%base.size()] );
    return res;
}

unordered_set<string> ms;
string uname(int mx = 31)
{
    string res;
    do{
        res = name(mx);
    }while( ms.find(res) != ms.end() );
    return res;
}


void gen(vector<int> v, int mx=10)
{assert( v.size() <= 100000 );
    static int cid = 0;
    cid++;
    
    shuffle(v.begin(), v.end(), mt);
    char buf[256];
    
    sprintf(buf, "%02d.in", cid);
    cout<<" "<<buf<<endl;
    ofstream fout(buf);
    
    fout<<v.size()<<'\n';
    ms.clear();
    for(int i:v)
    {
        assert(i>=2);
        fout<<uname(mx)<<' '<<i<<'\n';
    }
    fout.close();
    
    sprintf(buf, "ac <%02d.in >%02d.ans", cid, cid);
    system(buf);
}

vector<int> plist;
vector<bool> isp(1E7+1, true);

void makep()
{
    isp[0]=isp[1]=false;
    for(size_t i=2;i<isp.size();++i)
    {
        if( isp[i] )
        {
            plist.emplace_back(i);
            for(size_t j=i*i;j<isp.size();j+=i)
                isp[j]=false;
        }
    }
}

int main()
{
    makep();
    uniform_int_distribution<> pindex(0, plist.size()-1);
    uniform_int_distribution<> fullid(2, 10000000);
    
    
    cout<<"Case1 n<=100, val <=100"<<endl;
    {
        vector<int> a(100);
        iota(a.begin(), a.end(), 1);
        
        a[0] = 2;
        gen(a, 31);
        
        a[0] = 55;
        gen(a, 31);
        
        a[0] = 64;
        gen(a, 31);
    }
    
    cout<<"Case2 val is prime"<<endl;
    {
        for(int n:{100,1000,10000,100000,100000})
        {
            vector<int> a(n);
            for(int &i:a) i = plist[pindex(mt)];
            gen(a, 5);
        }
    }
    
    cout<<"Case3 val <= 10000"<<endl;
    {
        uniform_int_distribution<> case3(2, 10000);
        for(int n:{100,1000,10000,100000})
        {
            vector<int> a(n);
            for(int &i:a) i = case3(mt);
            gen(a, 5);
        }
    }

    cout<<"Case4 n<=2000"<<endl;
    {
        vector<int> a(2000);
        iota(a.begin(), a.end(), 2);
        gen(a);

        for(int i=1;i<9;++i)
        {
            a.clear();
            for(int j=0;j<i*100;++j)
                a.emplace_back( fullid(mt) );
                
            while( a.size() < 2000 )
                a.emplace_back( plist[pindex(mt)] );
                
            gen(a);
        }
    }
    
    cout<<"Case5 n,id<=100000"<<endl;
    {
        vector<int> a(100000);
        uniform_int_distribution<> case5(2, 100000);

        int bound = upper_bound(plist.begin(), plist.end(), 100000) - plist.begin();
        uniform_int_distribution<> case5p(0, bound-1);

        iota(a.begin(), a.end(), 2);
        gen(a);

        for(int i=1;i<9;++i)
        {
            a.clear();
            for(int j=0;j<i*10000;++j)
                a.emplace_back( case5(mt) );
                
            while( a.size() < 100000 )
                a.emplace_back( plist[case5p(mt)] );
                
            gen(a);
        }
    }
    
    cout<<"Case6 n,id<=1000000"<<endl;
    {
        vector<int> a(100000);
        for(int &i:a) i = plist[pindex(mt)];
        gen(a,5);
        
        for(int i=0;i<2;++i)
        {
            a.clear();
            for(int i=0;i<100000;++i)
                a.emplace_back(fullid(mt));
            gen(a,5);
        }
    }
    return 0;
}
