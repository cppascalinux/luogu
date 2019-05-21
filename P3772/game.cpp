//2019.05.20
//P3772 [CTSC2017]游戏 期望dp转矩阵乘法,线段树维护区间乘积+前缀乘积区间和
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cassert>
#include<cmath>
#define db double
#define pii pair<int,int>
#define pmm  pair<mat,mat>
#define fi first
#define se second
using namespace std;
struct mat
{
	db v[2][2];
	mat(){v[0][0]=v[0][1]=v[1][0]=v[1][1]=0;}
	mat(db a,db b,db c,db d){v[0][0]=a,v[0][1]=b,v[1][0]=c,v[1][1]=d;}
	mat operator +(const mat &p) const{return mat(v[0][0]+p.v[0][0],v[0][1]+p.v[0][1],v[1][0]+p.v[1][0],v[1][1]+p.v[1][1]);}
	mat operator -(const mat &p) const{return mat(v[0][0]-p.v[0][0],v[0][1]-p.v[0][1],v[1][0]-p.v[1][0],v[1][1]-p.v[1][1]);}
	mat operator *(const mat p) const
	{
		mat ans;
		for(int i=0;i<=1;i++)
			for(int j=0;j<=1;j++)
				for(int k=0;k<=1;k++)
					ans.v[i][j]+=v[i][k]*p.v[k][j];
		return ans;
	}
	void output()
	{
		for(int i=0;i<=1;i++)
		{
			for(int j=0;j<=1;j++)
				printf("%.2lf ",v[i][j]);
			printf("\n");
		}
		fflush(stdout);
	}
};
int n,m;
mat org[200009];
int l[800009],r[800009];
pmm sm[800009];
pmm merge(pmm a,pmm b)
{
	pmm ans;
	ans.fi=a.fi*b.fi;
	ans.se=a.fi*b.se+a.se*b.fi;
	return ans;
}
void build(int a,int ll,int rr)
{
	l[a]=ll;
	r[a]=rr;
	if(ll==rr)
	{
		sm[a].fi=org[ll];
		sm[a].se=mat(1,0,0,0)*org[ll];
		// sm[a].fi.output(),sm[a].se.output();
		return;
	}
	int mid=(ll+rr)>>1;
	build(a<<1,ll,mid);
	build(a<<1|1,mid+1,rr);
	sm[a]=merge(sm[a<<1],sm[a<<1|1]);
}
void ask(int a,int ll,int rr,pmm &ans)
{
	if(l[a]>rr||r[a]<ll)
		return;
	if(l[a]>=ll&&r[a]<=rr)
	{
		ans=merge(ans,sm[a]);
		return;
	}
	ask(a<<1,ll,rr,ans);
	ask(a<<1|1,ll,rr,ans);
}
void solve()
{
	set<pii> s;
	set<pii>::iterator it1,it2,it3;
	s.insert(pii(0,1)),s.insert(pii(n+1,1));
	build(1,1,n+1);
	pmm tmp,stt(mat(1,0,0,1),mat());
	tmp=stt,ask(1,1,n+1,tmp);
	// tmp.fi.output(),tmp.se.output();
	db ans=tmp.se.v[1][1]/tmp.fi.v[1][1];
	// ans=0.0/0.0;
	// printf("ans:%lf isnormal:%d\n",ans,isnormal(ans)),fflush(stdout);
	// assert(isnormal(ans));
	for(int i=1,a,b;i<=m;i++)
	{
		char ss[10];
		scanf("%s%d",ss,&a);
		if(ss[0]=='a')
		{
			scanf("%d",&b);
			it1=it2=it3=s.insert(pii(a,b^1)).fi;
			it1--,it2++;
			int pl=it1->fi,pm=it3->fi,pr=it2->fi;
			int dl=it1->se,dm=it3->se,dr=it2->se;
			tmp=stt,ask(1,pl+1,pr,tmp);
			ans-=tmp.se.v[dl][dr]/tmp.fi.v[dl][dr];
			// assert(isnormal(ans));

			tmp=stt,ask(1,pl+1,pm,tmp);
			ans+=tmp.se.v[dl][dm]/tmp.fi.v[dl][dm];
			// assert(isnormal(ans));

			tmp=stt,ask(1,pm+1,pr,tmp);
			ans+=tmp.se.v[dm][dr]/tmp.fi.v[dm][dr];
			// assert(isnormal(ans));
		}
		else
		{
			it1=it2=it3=s.lower_bound(pii(a,0));
			it1--,it2++;
			int pl=it1->fi,pm=it3->fi,pr=it2->fi;
			int dl=it1->se,dm=it3->se,dr=it2->se;
			tmp=stt,ask(1,pl+1,pr,tmp);
			ans+=tmp.se.v[dl][dr]/tmp.fi.v[dl][dr];
			// assert(isnormal(ans));

			tmp=stt,ask(1,pl+1,pm,tmp);
			ans-=tmp.se.v[dl][dm]/tmp.fi.v[dl][dm];
			// assert(isnormal(ans));

			tmp=stt,ask(1,pm+1,pr,tmp);
			ans-=tmp.se.v[dm][dr]/tmp.fi.v[dm][dr];
			// assert(isnormal(ans));
			s.erase(it3);
		}
		printf("%.6lf\n",ans);
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	char typ[20];
	scanf("%d%d%s",&n,&m,typ);
	org[0]=org[n+1]=mat(0,1,0,1);
	db p,q;
	scanf("%lf",&q);
	org[1]=mat(q,1-q,q,1-q);
	for(int i=2;i<=n;i++)
	{
		scanf("%lf%lf",&p,&q);
		org[i]=mat(p,1-p,q,1-q);
	}
	solve();
	return 0;
}