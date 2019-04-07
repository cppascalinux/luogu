//luogu2257 YY的GCD 莫比乌斯反演+预处理
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
int tot,n=10000000;
int pm[1000009],vis[10000009],mu[10000009];
int sm[10000009];
void init()
{
	mu[1]=vis[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!vis[i])
		{
			pm[++tot]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=tot&&i*pm[j]<=n;j++)
		{
			vis[i*pm[j]]=1;
			if(i%pm[j]==0)
			{
				mu[i*pm[j]]=0;
				break;
			}
			mu[i*pm[j]]=-mu[i];
		}
	}
	// for(int i=1;i<=100;i++)
	// 	printf("i:%d mu:%d pm:%d\n",i,mu[i],pm[i]);
	for(int i=1;i<=tot;i++)
		for(int j=1;j*pm[i]<=n;j++)
			sm[j*pm[i]]+=mu[j];
	for(int i=1;i<=n;i++)
		sm[i]+=sm[i-1];
}
void solve(int a,int b)
{
	ll ans=0;
	for(int l=1,r;l<=min(a,b);l=r+1)
	{
		r=min(a/(a/l),b/(b/l));
		ans+=(ll)(a/l)*(b/l)*(sm[r]-sm[l-1]);
	}
	printf("%lld\n",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("gcd.in","r",stdin);
	freopen("gcd.out","w",stdout);
#endif
	init();
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		solve(a,b);
	}
	return 0;
}