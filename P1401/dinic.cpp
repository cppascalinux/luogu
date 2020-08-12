//2020.08.10
//luoguP1401 城市 直接把边按长度排序，然后不停地加边的同时用dinic增广/二分加边的数量 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define INF 0x7F7F7F7F
using namespace std;
struct edge
{
	int u,v,l;
	bool operator<(const edge &p)const{return l<p.l;}
};
int n,m,k,s,t,tot=1;
int hd[209],eg[80009],nxt[80009],cap[80009];
int dep[209],cur[209];
edge e[40009];
void adde(int a,int b,int c)
{
	eg[++tot]=b;
	cap[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
int bfs()
{
	queue<int> q;
	memset(dep,0,sizeof(dep));
	dep[s]=1;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=hd[x],p=eg[i];i;i=nxt[i],p=eg[i])
			if(cap[i]&&!dep[p])
				dep[p]=dep[x]+1,q.push(p);
	}
	return dep[t];
}
int dfs(int x,int a)
{
	if(x==t||!a)
		return a;
	int f,totf=0;
	for(int &i=cur[x],p=eg[i];i;i=nxt[i],p=eg[i])
		if(cap[i]&&dep[p]==dep[x]+1&&(f=dfs(p,min(a,cap[i]))))
		{
			cap[i]-=f,cap[i^1]+=f;
			a-=f,totf+=f;
			if(!a)
				break;
		}
	return totf;
}
int flow()
{
	int totf=0;
	s=1,t=n;
	while(bfs())
	{
		// printf("bfs!!! totf:%d\n",totf);
		// fflush(stdout);
		memcpy(cur,hd,sizeof(hd));
		totf+=dfs(s,INF);
	}
	return totf;
}
int solve(int v)
{
	for(int i=1;i<=v;i++)
	{
		adde(e[i].u,e[i].v,1);
		adde(e[i].v,e[i].u,1);
	}
	int ret=0;
	if(flow()>=k)
		ret=1;
	// ret=flow();
	memset(hd,0,sizeof(hd));
	memset(nxt,0,(tot+1)<<2);
	tot=1;
	return ret;
}
void bin()
{
	int pl=1,pr=m;
	while(pl<pr)
	{
		int mid=(pl+pr)>>1;
		// printf("pl:%d pr:%d\n",pl,pr);
		// fflush(stdout);
		if(solve(mid))
			pr=mid;
		else
			pl=mid+1;
	}
	// printf("solve6:%d\n",solve(6));
	// printf("pl:%d\n",pl);
	printf("%d",e[pl].l);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("dinic.in","r",stdin);
	freopen("dinic.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1,a,b,c;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		e[i]=edge{a,b,c};
	}
	sort(e+1,e+m+1);
	bin();
	return 0;
}