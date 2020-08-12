//2020.08.12
//luoguP1402 酒店之王 直接建图然后dinic
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define INF 0x7F7F7F7F
using namespace std;
int n,m1,m2,s,t,tot=1;
int hd[409],eg[40609],nxt[40609],cap[40609];
int cur[409],dep[409];
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
	int f=0,totf=0;
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
	while(bfs())
	{
		memcpy(cur,hd,sizeof(hd));
		totf+=dfs(s,INF);
	}
	return totf;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("dinic.in","r",stdin);
	freopen("dinic.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m1,&m2);
	for(int i=1;i<=n;i++)
		adde(i+m1,i+n+m1,1),adde(i+n+m1,i+m1,0);
	for(int i=1;i<=n;i++)
		for(int j=1,a;j<=m1;j++)
		{
			scanf("%d",&a);
			if(a)
				adde(j,i+m1,1),adde(i+m1,j,0);
		}
	for(int i=1;i<=n;i++)
		for(int j=1,a;j<=m2;j++)
		{
			scanf("%d",&a);
			if(a)
				adde(i+n+m1,j+2*n+m1,1),adde(j+2*n+m1,i+n+m1,0);
		}
	s=2*n+m1+m2+1,t=s+1;
	for(int i=1;i<=m1;i++)
		adde(s,i,1),adde(i,s,0);
	for(int i=1;i<=m2;i++)
		adde(i+m1+2*n,t,1),adde(t,i+m1+2*n,0);
	printf("%d",flow());
	return 0;
}