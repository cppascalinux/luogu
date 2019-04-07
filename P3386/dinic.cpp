#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int inf=0x7FFFFFFF;
int n,m,e,tot=1,s,t;
int edge[3004010],next[3004010],cap[3004010];
int cur[2010],head[2010],d[2010];
void add(int a,int b,int c)
{
	edge[++tot]=b;
	cap[tot]=c;
	next[tot]=head[a];
	head[a]=tot;
	edge[++tot]=a;
	cap[tot]=0;
	next[tot]=head[b];
	head[b]=tot;
}
int bfs()
{
	int x;
	memset(d,0,sizeof(d));
	d[s]=1;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		x=q.front();
		q.pop();
		for(int i=head[x];i;i=next[i])
			if(cap[i]&&!d[edge[i]])
			{
				d[edge[i]]=d[x]+1;
				q.push(edge[i]);
			}
	}
	return d[t];
}
int dfs(int x,int a)
{
	if(x==t||!a)
		return a;
	int f,totf=0;
	for(int &i=cur[x];i;i=next[i])
		if(d[edge[i]]==d[x]+1&&(f=dfs(edge[i],min(a,cap[i]))))
		{
			cap[i]-=f;
			cap[i^1]+=f;
			a-=f;
			totf+=f;
			if(!a)
				break;
		}
	return totf;
}
int flow()
{
	int totf=0;
	while(bfs())
	{
		for(int i=1;i<=n+m+2;i++)
			cur[i]=head[i];
		totf+=dfs(s,inf);
	}
	return totf;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("bin.in","r",stdin);
	freopen("bin.out","w",stdout);
	#endif
	scanf("%d%d%d",&n,&m,&e);
	s=n+m+1;
	t=n+m+2;
	for(int i=1;i<=n;i++)
		add(s,i,1);
	for(int i=1;i<=m;i++)
		add(i+n,t,1);
	int a,b;
	for(int i=1;i<=e;i++)
	{
		scanf("%d%d",&a,&b);
		if(a<=n&&b<=m)
			add(a,b+n,1);
	}
	printf("%d",flow());
	return 0;
}