//P2375 [NOI2014]动物园 拓展kmp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 1000000007
#define ll long long
using namespace std;
int n;
char s[1000009];
int f[1000009],mn[1000009],sm[1000009];
void init()
{
	memset(f,0,sizeof(f));
	int mx=0,id=1;
	for(int i=2;i<=n;i++)
	{
		int &p=f[i];
		p=min(mx-i+1,f[i-id+1]);
		p=max(p,0);
		while(s[p+1]==s[p+i])
			p++;
		if(i+p-1>mx)
		{
			mx=i+p-1;
			id=i;
		}
	}
}
void solve()
{
	memset(sm,0,sizeof(sm));
	memset(mn,0x7F,sizeof(mn));
	for(int i=1;i<=n;i++)
		mn[i+f[i]-1]=min(mn[i+f[i]-1],i);
	for(int i=n;i>=1;i--)
		mn[i]=min(mn[i],mn[i+1]);
	for(int i=1;i<=n;i++)
	{
		int p=max(0,i-mn[i]+1);
		sm[i]=sm[p]+1;
	}
	
	memset(mn,0x7F,sizeof(mn));
	for(int i=1;i<=n;i++)
	{
		int l=min(f[i],i-1);
		mn[i+l-1]=min(mn[i+l-1],i);
	}
	for(int i=n;i>=1;i--)
		mn[i]=min(mn[i],mn[i+1]);
	int ans=1;
	for(int i=1;i<=n;i++)
	{
		int p=max(0,i-mn[i]+1);
		ans=(ll)ans*(sm[p]+1)%mod;
	}
	printf("%d\n",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("zoo.in","r",stdin);
	freopen("exkmp.out","w",stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s",s+1);
		n=strlen(s+1);
		// printf("%s",s+1);
		// fflush(stdout);
		init();
		solve();
	}
	return 0;
}