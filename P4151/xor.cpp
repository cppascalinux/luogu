//luogu4151 [WC2011]最大XOR和路径 dfs树+线性基+贪心
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
int n,m,tot;
int hd[50009],eg[200009],nxt[200009];
ll len[200009];
ll dis[50009];
ll bs[69];
void ins(int a,int b,ll c)
{
	eg[++tot]=b;
	len[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void add(ll x)
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
				break;
			}
		}
}
void dfs(int x,int fa,ll sm)
{
	dis[x]=sm;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			if(dis[eg[i]])
				add(dis[eg[i]]^sm^len[i]);
			else
				dfs(eg[i],x,sm^len[i]);
		}
}
void solve()
{
	ll ans=dis[n];
	for(int i=62;i>=0;i--)
		if(!(ans&(1LL<<i)))
			ans^=bs[i];
	printf("%lld",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int a,b;
		ll c;
		scanf("%d%d%lld",&a,&b,&c);
		ins(a,b,c);
		ins(b,a,c);
	}
	dfs(1,0,0);
	// for(int i=0;i<=5;i++)
	// 	printf("i:%d bs:%d\n",i,bs[i]);
	solve();
	return 0;
}