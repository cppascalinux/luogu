//luogu4570 [BJWC2011]元素 线性基+贪心
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define pil pair<int,ll>
#define fi first
#define se second
using namespace std;
int n;
pil v[1009];
ll bs[69];
int ins(ll x)
{
	for(int i=62;i>=0;i--)
		if(x&(1LL<<i))
		{
			if(bs[i])
				x^=bs[i];
			else
			{
				for(int j=0;j<i;j++)
					if(x&(1LL<<j))
						x^=bs[j];
				for(int j=i+1;j<=62;j++)
					if(bs[j]&(1LL<<i))
						bs[j]^=x;
				bs[i]=x;
				return 1;
			}
		}
	return 0;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("base.in","r",stdin);
	freopen("base.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%d",&v[i].se,&v[i].fi);
	sort(v+1,v+n+1);
	int ans=0;
	for(int i=n;i>=1;i--)
		if(ins(v[i].se))
			ans+=v[i].fi;
	printf("%d",ans);
	return 0;
}