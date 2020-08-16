//2020.08.16
//luoguP2588 [ZJOI2008]Risk 大概做法就是先走出来每一个最小的环,然后对于每一个点用射线法判断他是否在某个最小环内,这样就能求出每个环包含的点的编号
//国家相邻分为两种情况:第一种是相邻,这个可以直接通过记录每条边包含的国家来判断;第二种是包含,可以通过比较最小环集合来判断(bitset)
//总时间复杂度O(nm+n^3/64)
#include<algorithm>
#include<iostream>
#include<cstring>
#include<random>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cmath>
#include<map>
#define DB double
#define eps 1e-8
#define PII pair<int,int>
#define PPI pair<pt,int>
#define PB push_back
#define FI first
#define SE second
#define VET vector<edge>::iterator
#define BS bitset<609>
using namespace std;
int sgn(DB x)
{
	return x<-eps?-1:(x>eps?1:0);
}
struct pt
{
	DB x,y;
	bool operator<(const pt &p)const{return x<p.x||(x==p.x&&y<p.y);}
	bool operator==(const pt &p)const{return sgn(x-p.x)==0&&sgn(y-p.y)==0;}
	pt operator+(const pt &p)const{return pt{x+p.x,y+p.y};}
	pt operator-(const pt &p)const{return pt{x-p.x,y-p.y};}
	pt operator*(const DB &v)const{return pt{x*v,y*v};}
	DB operator*(const pt &p)const{return x*p.x+y*p.y;}
	DB operator^(const pt &p)const{return x*p.y-y*p.x;}
	DB operator()()const{return atan2(y,x);}
};
struct ln
{
	pt a,b;
	pt operator*(const ln &p)const
	{
		DB s1=(p.a-a)^(b-a),s2=(b-a)^(p.b-a);
		return p.a*(s2/(s1+s2))+p.b*(s1/(s1+s2));
	}
	bool operator<(const ln &p)const{return (b-a)()<(p.b-p.a)();}
};
struct edge
{
	pt a;
	int v,ide;
	bool operator<(const edge &p)const{return a()<p.a();}
};
pt q[609],pm[8009];
ln e0[4009];
PII e1[8009];
int n,m,tp,tpc,tpv,tpe;
int visv[8009],vise[8009];
int stv[8009],ste[8009];
int rep[609];
int ans[609][609];
mt19937 rnd;
BS bel[609];
vector<edge> e[8009];
vector<int> cir[8009];
vector<int> bed[4009];
map<pt,int> s0;
int dfs(int ei)
{
	int fm=e1[ei].FI,to=e1[ei].SE;
	vise[ei]=1;
	ste[++tpe]=ei;
	if(visv[to])
		return 1;
	visv[to]=1;
	stv[++tpv]=to;
	VET it;
	for(it=e[to].begin();it!=e[to].end();it++)
		if(it->v==fm)
			break;
	if(++it==e[to].end())
		it=e[to].begin();
	return dfs(it->ide);
}
void init()
{
	for(int i=1;i<=tp;i++)
		sort(e[i].begin(),e[i].end());
	for(int i=2;i<=2*m+1;i++)
		if(!vise[i])
		{
			tpv=tpe=0;
			stv[++tpv]=e1[i].FI;
			visv[e1[i].FI]=1;
			dfs(i);
			for(int i=1;i<=tpv;i++)
				visv[stv[i]]=0;
			DB sm=0;
			for(int i=1;i<=tpe;i++)
				sm+=pm[e1[ste[i]].FI]^pm[e1[ste[i]].SE];
			if(sgn(sm)>0)
				continue;
			tpc++;
			for(int i=1;i<=tpe;i++)
			{
				cir[tpc].PB(ste[i]);
				bed[ste[i]>>1].PB(tpc);
			}
		}
}
void dbgc()
{
	printf("tpc:%d\n",tpc);
	for(int i=1;i<=tpc;i++)
	{
		for(int t:cir[i])
			printf("%d ",t>>1);
		printf("\n");
	}
}
int judge(int p,int c)
{
	pt a=q[p],b=pt{((int)rnd()),((int)rnd())};
	while(a==b)
		b=pt{((int)rnd()),((int)rnd())};
	ln nl=ln{a,b};
	int sm=0;
	for(int t:cir[c])
	{
		ln tl=e0[t>>1];
		if(t&1)
			swap(tl.a,tl.b);
		pt np=nl*tl;
		if(sgn(np.x-a.x)!=sgn(b.x-a.x))
			continue;
		if(np==tl.a)
			sm++;
		else if(!(np==tl.b))
		{
			if(tl.b<tl.a)
				swap(tl.a,tl.b);
			if(tl.a<np&&np<tl.b)
				sm++;
		}
	}
	return sm&1;
}
void getb()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=tpc;j++)
		{
			int sm=0;
			for(int k=1;k<=15;k++)
				sm+=judge(i,j);
			if(sm>=8)
				bel[i][j]=1;
		}
	}
}
void dbgb()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=tpc;j++)
			printf("%d ",(bool)bel[i][j]);
		printf("\n");
	}
}
void solve()
{
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			if((bel[i]^bel[j]).count()==1)
			{
				BS ns=bel[i]^bel[j];
				int k=0;
				for(k=1;k<=tpc;k++)
					if(ns[k])
						break;
				int afo=0;
				for(int t:cir[k])
					if(bed[t>>1].size()==1)
						afo=1;
				if(afo)
					ans[i][j]=ans[j][i]=1;
			}
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=tpc;j++)
			if(bel[i][j])
				if(!rep[j]||bel[i].count()<bel[rep[j]].count())
					rep[j]=i;
	for(int i=1;i<=m;i++)
		if(bed[i].size()==2)
		{
			int x=rep[bed[i][0]],y=rep[bed[i][1]];
			ans[x][y]=ans[y][x]=1;
		}
	for(int i=1;i<=n;i++)
	{
		int sm=0;
		for(int j=1;j<=n;j++)
			sm+=ans[i][j];
		printf("%d",sm);
		for(int j=1;j<=n;j++)
			if(ans[i][j])
				printf(" %d",j);
		printf("\n");
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("risk.in","r",stdin);
	freopen("risk.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&q[i].x,&q[i].y);
	for(int i=1;i<=m;i++)
	{
		pt a,b;
		scanf("%lf%lf%lf%lf",&a.x,&a.y,&b.x,&b.y);
		if(b<a)
			swap(a,b);
		if(!s0.count(a))
			s0[a]=++tp,pm[tp]=a;
		if(!s0.count(b))
			s0[b]=++tp,pm[tp]=b;
		e[s0[a]].PB(edge{b-a,s0[b],i*2});
		e[s0[b]].PB(edge{a-b,s0[a],i*2+1});
		e1[i*2]=PII(s0[a],s0[b]);
		e1[i*2+1]=PII(s0[b],s0[a]);
		e0[i]=ln{a,b};
	}
	init();
	// dbgc();
	getb();
	// dbgb();
	solve();
	return 0;
}