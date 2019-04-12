//2019.04.12
//luoguP2178 [NOI2015]品酒大会 后缀数组+并查集
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define pii pair<int,int>
#define fi first
#define se second
#define ll long long
using namespace std;
int n;
char s[300009];
int sa[300009],c[300009],t1[300009],t2[300009],rnk[300009],h[300009];
int v[300009];
pii st[300009];
int f[300009],sz[300009],mx[300009],mn[300009];
ll ans1[300009],ans2[300009];
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
			if(sa[i]>k)
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
	for(int i=1;i<=n;i++)
	{
		f[i]=i;
		sz[i]=1;
		mn[i]=mx[i]=v[sa[i]];
	}
	for(int i=2;i<=n;i++)
		st[i-1]=pii(h[i],i);
	sort(st+1,st+n);
	memset(ans2,0x80,sizeof(ans2));
	for(int i=n-1;i>=1;i--)
	{
		int a=fnd(st[i].se),b=fnd(st[i].se-1),l=st[i].fi;
		ans1[l]+=(ll)sz[a]*sz[b];
		ans2[l]=max(ans2[l],(ll)mx[a]*mx[b]);
		ans2[l]=max(ans2[l],(ll)mx[a]*mn[b]);
		ans2[l]=max(ans2[l],(ll)mn[a]*mx[b]);
		ans2[l]=max(ans2[l],(ll)mn[a]*mn[b]);
		// printf("a:%d b:%d mxa:%d mxb:%d\n",a,b,mx[a],mx[b]);
		f[b]=a;
		sz[a]+=sz[b];
		mx[a]=max(mx[a],mx[b]);
		mn[a]=min(mn[a],mn[b]);
	}
	for(int i=n-1;i>=0;i--)
	{
		ans1[i]+=ans1[i+1];
		ans2[i]=max(ans2[i],ans2[i+1]);
	}
	for(int i=0;i<=n-1;i++)
		printf("%lld %lld\n",ans1[i],ans1[i]?ans2[i]:0);
}
void dbg()
{
	for(int i=1;i<=n;i++)
		printf("%3d",sa[i]);
	printf("\n");
	for(int i=1;i<=n;i++)
		printf("%3d",h[i]);
	printf("\n");
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sa.in","r",stdin);
	freopen("sa.out","w",stdout);
#endif
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;i++)
		s[i]-='a'-1;
	for(int i=1;i<=n;i++)
		scanf("%d",v+i);
	getsa();
	geth();
	// dbg();
	solve();
	return 0;
}