#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,tot,t,ntot,sum,top;
int p[10010];
int head[10010],next[100010],edge[100010];
int dfn[10010],low[10010],st[10010],ins[10010];
int color[10010],in[10010];
int nhead[10010],nnext[100010],nedge[100010];
int f[10010],num[10010];
int q[10010],l,r=-1;
void add(int a,int b)
{
	edge[++tot]=b;
	next[tot]=head[a];
	head[a]=tot;
}
void nadd(int a,int b)
{
	nedge[++ntot]=b;
	nnext[ntot]=nhead[a];
	nhead[a]=ntot;
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
			num[sum]+=p[st[top]];
		}
	}
}
void rebuild()
{
	for(int i=1;i<=n;i++)
		for(int j=head[i];j;j=next[j])
			if(color[i]^color[edge[j]])
			{
				nadd(color[i],color[edge[j]]);
				in[color[edge[j]]]++;
			}
}
void dp()
{
	int x;
	for(int i=1;i<=sum;i++)
		if(!in[i])
		{
			f[i]=num[i];
			q[++r]=i;
		}
	while(l<=r)
	{
		x=q[l++];
		for(int i=nhead[x];i;i=nnext[i])
		{
			in[nedge[i]]--;
			f[nedge[i]]=max(f[nedge[i]],f[x]);
			if(!in[nedge[i]])
			{
				f[nedge[i]]+=num[nedge[i]];
				q[++r]=nedge[i];
			}
		}
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("tarjan.in","r",stdin);
	freopen("tarjan.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",p+i);
	int a,b;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			dfs(i);
	//for(int i=1;i<=n;i++)
	//	printf("i:%d color:%d\n",i,color[i]);
	rebuild();
	dp();
	int ans=0;
	for(int i=1;i<=sum;i++)
		ans=max(ans,f[i]);
	printf("%d",ans);
	return 0;
}