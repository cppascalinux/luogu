#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define rg register int
using namespace std;
int n,m,s,t,tot;
int head[10010],edge[400010],nxt[400010];
int to[10010];
int dist[10010],vist[10010];
void ins(int a,int b)
{
	edge[++tot]=b;
	nxt[tot]=head[a];
	head[a]=tot;
}
void dfs(int x)
{
	if(to[x])
		return;
	to[x]=1;
	for(int i=head[x];i;i=nxt[i])
		if(!(i&1))
			dfs(edge[i]);
}
int bfs()
{
	queue<int> q;
	q.push(s);
	vist[s]=1;
	dist[s]=0;
	int x;
	while(!q.empty())
	{
		x=q.front();
		q.pop();
		int flag=1;
		for(rg i=head[x];i;i=nxt[i])
			if(i&1)
				if(!to[edge[i]])
				{
					flag=0;
					break;
				}
		if(!flag)
			continue;
		for(rg i=head[x];i;i=nxt[i])
			if(i&1)
				if(!vist[edge[i]])
				{
					vist[edge[i]]=1;
					dist[edge[i]]=dist[x]+1;
					if(edge[i]==t)
						return dist[edge[i]];
					q.push(edge[i]);
				}
	}
	return -1;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	int a,b;
	for(rg i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		ins(a,b);
		ins(b,a);
	}
	scanf("%d%d",&s,&t);
	dfs(t);
	printf("%d",bfs());
	return 0;
}