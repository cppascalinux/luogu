#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,tot,sum,t;
int dfn[210],low[210],ins[210],st[210],top;
int head[210],edge[40010],next[40010];
int color[210],in[210],out[210];
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
			ins[st[top]]=0;
			color[st[top]]=sum;
		}
	}
}
void rebuild()
{
	for(int i=1;i<=n;i++)
		for(int j=head[i];j;j=next[j])
			if(color[i]^color[edge[j]])
			{
				in[color[edge[j]]]++;
				out[color[i]]++;
			}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("network.in","r",stdin);
	freopen("network.out","w",stdout);
	#endif
	scanf("%d",&n);
	int a;
	for(int i=1;i<=n;i++)
	{
		while(1)
		{
			scanf("%d",&a);
			if(!a)
				break;
			add(i,a);
		}
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			dfs(i);
	rebuild();
	int ans1=0,ans2=0;
	for(int i=1;i<=sum;i++)
	{
		if(!in[i])
			ans1++;
		if(!out[i])
			ans2++;
	}
	if(sum==1)
		printf("%d\n%d",1,0);
	else
		printf("%d\n%d",ans1,max(ans1,ans2));
	return 0;
}