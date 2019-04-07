#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,t,tot;
int edge[100010],next[100010],head[10010];
int dfn[10010],low[10010],ins[10010],st[10010],top;
int color[10010],sum,num[10010];
int in[10010];
void add(int a,int b)
{
	edge[++tot]=b;
	next[tot]=head[a];
	head[a]=tot;
}
void dfs(int x)
{
	dfn[x]=low[x]=++t;
	st[++top]=x;
	ins[x]=1;
	for(int i=head[x];i;i=next[i])
		if(!dfn[edge[i]])
		{
			dfs(edge[i]);
			low[x]=min(low[x],low[edge[i]]);
		}
		else if(ins[edge[i]])
			low[x]=min(low[x],dfn[edge[i]]);
	if(dfn[x]==low[x])
	{
		sum++;
		for(;st[top+1]^x;top--)
		{
			color[st[top]]=sum;
			ins[st[top]]=0;
			num[sum]++;
		}
	}
}
void rebuild()
{
	for(int i=1;i<=n;i++)
		for(int j=head[i];j;j=next[j])
			if(color[i]^color[edge[j]])
				in[color[i]]++;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("cow.in","r",stdin);
	freopen("cow.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	int a,b;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			dfs(i);
	rebuild();
	int ans1=0,ans2=0;
	for(int i=1;i<=sum;i++)
		if(!in[i])
		{
			ans1++;
			ans2+=num[i];
		}
	if(ans1<=1)
		printf("%d",ans2);
	else
		printf("0");
	return 0;
}