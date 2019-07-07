//2019.07.07
//luoguP1912 [NOI2009]诗人小G 首先可以写出一个O(n^2)的dp,然后不难发现转移具有决策单调性(若j<k,且现在j比k优,那么j就永远都比k优),然后就可以使用单调队列去维护,
//满足队列中每个点优于前一个点的时间单调增,每次取出队首即可
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define ldb long double
#define li long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,m,p;
char s[100009][31];
ldb f[100009];
pii q[100009];
int pre[100009],sm[100009];
ldb qpow(ldb a,int b)
{
	ldb ans=1;
	for(;b;b>>=1,a*=a)
		if(b&1)
			ans*=a;
	return ans;
}
ldb cal(int x,int t)
{
	return f[x]+qpow(abs(sm[t]-sm[x]-m),p);
}
int gett(int a,int b)//a<b, the minimum time for b to be better than a
{
	int l=1,r=n+1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(cal(b,mid)<=cal(a,mid))
			r=mid;
		else
			l=mid+1;
	}
	return l;
}
void solve()
{
	int l=1,r=0;
	q[++r]=pii(0,n+1);
	for(int i=1;i<=n;i++)
	{
		while(l<r&&q[l].se<=i)
			l++;
		pre[i]=q[l].fi;
		f[i]=cal(q[l].fi,i);
		while(l<r&&q[r-1].se>=gett(q[r].fi,i))
			r--;
		q[r].se=gett(q[r].fi,i);
		q[++r]=pii(i,n+1);
	}
}
void outs(int x)
{
	if(!x)
		return;
	outs(pre[x]);
	for(int i=pre[x]+1;i<x;i++)
		printf("%s ",s[i]);
	printf("%s\n",s[x]);
}
void output()
{
	if(f[n]>1e18)
		printf("Too hard to arrange\n");
	else
	{
		printf("%lld\n",(li)f[n]);
		outs(n);
	}
	for(int i=1;i<=20;i++)
		printf("-");
	printf("\n");
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("poet.in","r",stdin);
	freopen("poet.out","w",stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&n,&m,&p);
		m++;
		for(int i=1;i<=n;i++)
		{
			scanf("%s",s[i]);
			sm[i]=sm[i-1]+strlen(s[i])+1;
		}
		solve();
		output();
	}
	return 0;
}