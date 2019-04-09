//2019.04.09
//P3804 【模板】后缀自动机 后缀数组+并查集
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define pii pair<int,int>
#define fi first
#define se second
#define ll long long
using namespace std;
int n;
char s[1000009];
int sa[1000009],c[1000009],t1[1000009],t2[1000009],h[1000009],rnk[1000009];
pii st[1000009];
int f[1000009],sz[1000009];
int fnd(int x)
{
	return x==f[x]?x:f[x]=fnd(f[x]);
}
void getsa()
{
	int *x=t1,*y=t2;
	int m=26;
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
		int q=sa[rnk[i]-1];
		while(s[i+p]==s[q+p])
			p++;
		h[rnk[i]]=p;
	}
}
void dbg()
{
	for(int i=1;i<=n;i++)
		printf("i:%d sa:%d h:%d\n",i,sa[i],h[i]);
}
void solve()
{
	for(int i=2;i<=n;i++)
		st[i-1]=pii(h[i],i);
	sort(st+1,st+n);
	for(int i=1;i<=n;i++)
	{
		f[i]=i;
		sz[i]=1;
	}
	ll ans=0;
	for(int i=n-1;i>=1;i--)
	{
		pii t=st[i];
		int a=fnd(t.se),b=fnd(t.se-1);
		f[a]=b;
		sz[b]+=sz[a];
		ans=max(ans,(ll)sz[b]*t.fi);
	}
	printf("%lld",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sam.in","r",stdin);
	freopen("sa1.out","w",stdout);
#endif
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		s[i]-='a'-1;
	getsa();
	geth();
	// dbg();
	solve();
	return 0;
}