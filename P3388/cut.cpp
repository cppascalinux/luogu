#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,t,tot;
int edge[200010],next[200010],head[100010];
int dfn[100010],low[100010],cut[100010];
void add(int a,int b)
{
	edge[++tot]=b;
	next[tot]=head[a];
	head[a]=tot;
}
void dfs(int x,int fa)
{
	int child=0;
	dfn[x]=low[x]=++t;
	for(int i=head[x];i;i=next[i])
		if(!dfn[edge[i]])
		{
			child++;
			dfs(edge[i],x);
			low[x]=min(low[x],low[edge[i]]);
			if(low[edge[i]]>=dfn[x])
				cut[x]=1;
		}
		else if(edge[i]^fa)
			low[x]=min(low[x],dfn[edge[i]]);
	if(!fa&&child==1)
		cut[x]=0;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("cut.in","r",stdin);
	freopen("cut.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	int a,b;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			dfs(i,0);
	int ans=0;
	for(int i=1;i<=n;i++)
		if(cut[i])
			ans++;
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
		if(cut[i])
			printf("%d ",i);
	return 0;
}