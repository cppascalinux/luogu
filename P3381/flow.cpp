#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int inf=0x7F7F7F7F;
int n,m,s,t,tot=1,maxf,minc;
int head[5010],edge[100010],next[100010],cap[100010],cost[100010];
int cur[5010],dist[5010],vist[5010];
void add(int a,int b,int c,int d)
{
	edge[++tot]=b;
	cap[tot]=c;
	cost[tot]=d;
	next[tot]=head[a];
	head[a]=tot;
}
int spfa()
{
	queue<int> q;
	memset(vist,0,sizeof(vist));
	memset(dist,inf,sizeof(dist));
	vist[s]=1;
	dist[s]=0;
	q.push(s);
	int x;
	while(!q.empty())
	{
		x=q.front();
		q.pop();
		vist[x]=0;
		for(int i=head[x];i;i=next[i])
			if(cap[i]&&dist[edge[i]]>dist[x]+cost[i])
			{
				dist[edge[i]]=dist[x]+cost[i];
				if(!vist[edge[i]])
				{
					vist[edge[i]]=1;
					q.push(edge[i]);
				}
			}
	}
	if(dist[t]==inf)
		return 0;
	return 1;
}
struct node
{
	int num,len;
	node(){}
	node(int a,int b)
	{
		num=a;
		len=b;
	}
	bool operator < (const node &o) const
	{
		return len>o.len;
	}
};
int dij()
{
	priority_queue<node> pq;
	memset(vist,0,sizeof(vist));
	memset(dist,inf,sizeof(dist));
	dist[s]=0;
	node p;
	int top=0;
	pq.push(node(s,0));
	while(!pq.empty())
	{
		p=pq.top();
		pq.pop();
		if(vist[p.num])
			continue;
		vist[p.num]=1;
		for(int i=head[p.num];i;i=next[i])
			if(!vist[edge[i]]&&cap[i]&&dist[edge[i]]>p.len+cost[i])
			{
				dist[edge[i]]=p.len+cost[i];
				pq.push(node(edge[i],dist[edge[i]]));
			}
		if(++top>=n)
			break;
	}
	if(dist[t]==inf)
		return 0;
	return 1;
}
int dfs(int x,int a)
{
	if(x==t||a==0)
		return a;
	//printf("x:%d a:%d\n",x,a);
	int totf=0,f=0;
	vist[x]=1;
	for(int &i=cur[x];i;i=next[i])
		if(!vist[edge[i]]&&dist[edge[i]]==dist[x]+cost[i]&&(f=dfs(edge[i],min(a,cap[i]))))
		{
			cap[i]-=f;
			cap[i^1]+=f;
			a-=f;
			totf+=f;
			minc+=f*cost[i];
			if(!a)
				break;
		}
	vist[x]=0;
	return totf;
}
void flow()
{
	while(spfa())
	{
		for(int i=1;i<=n;i++)
			cur[i]=head[i];
		memset(vist,0,sizeof(vist));
		maxf+=dfs(s,inf);
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("flow.in","r",stdin);
	freopen("flow.out","w",stdout);
	#endif
	scanf("%d%d%d%d",&n,&m,&s,&t);
	int a,b,c,d;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		add(a,b,c,d);
		add(b,a,0,-d);
	}
	flow();
	printf("%d %d\n",maxf,minc);
	return 0;
}
	