//utf-8 luogu2634 聪聪可可 点分治+桶
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
#define inf 0x7F7F7F7F
using namespace std;
int n,tot,ans,mn,rt;
int hd[20009],eg[40009],nxt[40009],len[40009];
int sz[20009],vis[20009];
int dis[20009],top;
int buc[3];
int gcd(int a,int b)
{
	if(!b)
		return a;
	return gcd(b,a%b);
}
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	len[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void getrt(int x,int fa,int siz)
{
	int mx=0;
	sz[x]=1;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]^fa&&!vis[eg[i]])
		{
			getrt(eg[i],x,siz);
			sz[x]+=sz[eg[i]];
			mx=max(mx,sz[eg[i]]);
		}
	mx=max(mx,siz-sz[x]);
	if(mx<mn)
	{
		mn=mx;
		rt=x;
	}
}
void dfs(int x,int fa,int suml)
{
	dis[++top]=suml;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]^fa&&!vis[eg[i]])
			dfs(eg[i],x,(suml+len[i])%3);
}
void cal(int x)
{
	memset(buc,0,sizeof(buc));
	buc[0]=1;
	for(int i=hd[x];i;i=nxt[i])
		if(!vis[eg[i]])
		{
			top=0;
			dfs(eg[i],0,len[i]);
			// printf("eg:%d top:%d\n",eg[i],top);
			// for(rg j=1;j<=top;j++)
			// 	printf("i:%d dis:%d\n",j,dis[j]);
			for(rg j=1;j<=top;j++)
				ans+=buc[(3-dis[j])%3];
			for(rg j=1;j<=top;j++)
				buc[dis[j]]++;
		}
}
void solve(int x,int siz)
{
	vis[x]=1;
	cal(x);
	// printf("x:%d ans:%d\n",x,ans);
	// for(rg i=0;i<=2;i++)
	// 	printf("i:%d buc:%d\n",i,buc[i]);
	for(int i=hd[x];i;i=nxt[i])
		if(!vis[eg[i]])
		{
			mn=inf;
			int nsiz=sz[eg[i]]>sz[x]?siz-sz[x]:sz[eg[i]];
			getrt(eg[i],0,nsiz);
			solve(rt,nsiz);
		}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	#endif
	scanf("%d",&n);
	int a,b,c;
	for(rg i=1;i<=n-1;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		c%=3;
		ins(a,b,c);
		ins(b,a,c);
	}
	mn=inf;
	getrt(1,0,n);
	solve(rt,n);
	ans=ans*2+n;
	int sum=n*n;
	int g=gcd(sum,ans);
	sum/=g;
	ans/=g;
	printf("%d/%d",ans,sum);
	return 0;
}