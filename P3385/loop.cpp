#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define rg register
using namespace std;
int n,m,tot,loop;
int head[2010],next[6010],edge[6010],len[6010];
int dist[2010],vist[2010],depth[2010],used[2010];
queue<int> q;
void add(int a,int b,int c)
{
	edge[++tot]=b;
	len[tot]=c;
	next[tot]=head[a];
	head[a]=tot;
}
void spfa(int s)
{
	dist[s]=0;
	vist[s]=1;
	used[s]=1;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(rg int i=head[x];i;i=next[i])
		{
			used[edge[i]]=1;
			if(dist[edge[i]]>dist[x]+len[i])
			{
				dist[edge[i]]=dist[x]+len[i];
				depth[edge[i]]=depth[x]+1;
				if(depth[edge[i]]>=n)
				{
					loop=1;
					return;
				}
				if(!vist[edge[i]])
				{
					vist[edge[i]]=1;
					q.push(edge[i]);
				}
			}
		}
		vist[x]=0;
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("loop.in","r",stdin);
	freopen("loop.out","w",stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		loop=0;
		tot=0;
		memset(head,0,sizeof(head));
		while(!q.empty())
			q.pop();
		scanf("%d%d",&n,&m);
		for(rg int i=1;i<=m;i++)
		{
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			add(a,b,c);
			if(c>=0)
				add(b,a,c);
		}
		memset(vist,0,sizeof(vist));
		memset(dist,127,sizeof(dist));
		memset(depth,0,sizeof(depth));
		memset(used,0,sizeof(used));
		for(rg int i=1;i<=n&&!used[i]&&!loop;i++)
			spfa(i);
		if(loop)
			printf("YE5\n");
		else
			printf("N0\n");
	}
	return 0;
}