//2019.04.09
//luoguP4248 [AHOI2013]差异 后缀数组+并查集
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n;
char s[500009];
int sa[500009],t1[500009],t2[500009],c[500009],rnk[500009],h[500009];
pii st[500009];
int f[500009],sz[500009];
void getsa()
{
	int *x=t1,*y=t2,m=26;
	for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
	for(int i=1;i<=m;i++) c[i]+=c[i-1];
	for(int i=1;i<=n;i++) sa[c[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int p=0;
		for(int i=n-k+1;i<=n;i++)
			y[++p]=i;
		for(int i=1;i<=n;i++)
			if(sa[i]>=k+1)
				y[++p]=sa[i]-k;
		memset(c,0,(m+1)<<2);
		for(int i=1;i<=n;i++) c[x[i]]++;
		for(int i=1;i<=m;i++) c[i]+=c[i-1];
		for(int i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i];
		p=0;
		for(int i=1;i<=n;i++)
			y[sa[i]]=x[sa[i]]==x[sa[i-1]]&&x[sa[i]+k]==x[sa[i-1]+k]?p:++p;
		swap(x,y);
		if((m=p)>=n)
			break;
	}
}
void geth()
{
	for(int i=1;i<=n;i++)
		rnk[sa[i]]=i;
	int p=0;
	for(int i=1;i<=n;i++)
	{
		if(p)
			p--;
		int np=sa[rnk[i]-1];
		while(s[i+p]==s[np+p])
			p++;
		h[rnk[i]]=p;
	}
}
int fnd(int x)
{
	return x==f[x]?x:f[x]=fnd(f[x]);
}
void solve()
{
	for(int i=2;i<=n;i++)
		st[i-1]=pii(h[i],i);
	sort(st+1,st+n);
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		f[i]=i;
		sz[i]=1;
	}
	for(int i=n-1;i>=1;i--)
	{
		int a=fnd(st[i].se),b=fnd(st[i].se-1);
		ans-=2LL*sz[a]*sz[b]*st[i].fi;
		f[a]=b;
		sz[b]+=sz[a];
	}
	ans+=(ll)n*(n+1)*(n-1)/2;
	printf("%lld",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sa.in","r",stdin);
	freopen("sa.out","w",stdout);
#endif
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		s[i]-='a'-1;
	getsa();
	geth();
	solve();
	return 0;
}