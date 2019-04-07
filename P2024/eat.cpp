#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define rg register int
using namespace std;
int n,k;
int f[50009],w[50009];
int find(int x)
{
	if(x==f[x])
		return x;
	int t=find(f[x]);
	w[x]=(w[x]+w[f[x]])%3;
	return f[x]=t;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("eat.in","r",stdin);
	freopen("eat.out","w",stdout);
	#endif
	scanf("%d%d",&n,&k);
	for(rg i=1;i<=n;i++)
		f[i]=i;
	int a,b,c,ans=0,fb,fc;
	for(rg i=1;i<=k;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		if(b>n||c>n)
		{
			ans++;
			continue;
		}
		if(a==1)
		{
			fb=find(b);
			fc=find(c);
			if(fb==fc&&w[b]!=w[c])
			{
				ans++;
				continue;
			}
			f[fb]=fc;
			w[fb]=(w[c]-w[b]+3)%3;
		}
		else
		{
			if(b==c)
			{
				ans++;
				continue;
			}
			fb=find(b);
			fc=find(c);
			if(fb==fc&&w[b]!=(w[c]+5)%3)
			{
				ans++;
				continue;
			}
			f[fb]=fc;
			w[fb]=(w[c]-w[b]+5)%3;
		}
	}
	printf("%d",ans);
	return 0;
}	