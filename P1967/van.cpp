#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int inf=0x7F7F7F7F;
int n,m,tot,q;
int edge[20010],next[20010],head[10010],len[20010];
int f[10010],d[10010];
int fx[10010][20],fm[10010][20];
struct node
{
	int x,y,len;
	bool operator < (const node &o) const
	{
		return len>o.len;
	}
}e[50010];
void add(int a,int b,int c)
{
	edge[++tot]=b;
	len[tot]=c;
	next[tot]=head[a];
	head[a]=tot;
}
int find(int x)
{
	if(x==f[x])
		return x;
	return x=find(f[x]);
}
void dfs(int x,int fa)
{
	for(int i=1;(1<<i)<=d[x];i++)
	{
		fx[x][i]=fx[fx[x][i-1]][i-1];
		fm[x][i]=min(fm[x][i-1],fm[fx[x][i-1]][i-1]);
	}
	for(int i=head[x];i;i=next[i])
		if(edge[i]^fa)
		{
			d[edge[i]]=d[x]+1;
			fx[edge[i]][0]=x;
			fm[edge[i]][0]=len[i];
			dfs(edge[i],x);
		}
}
int lca(int a,int b)
{
	if(d[a]<d[b])
		swap(a,b);
	int l=d[a]-d[b],ans=inf;
	for(int i=0;i<=18;i++)
		if(l&(1<<i))
		{
			ans=min(ans,fm[a][i]);
			a=fx[a][i];
		}
	if(a==b)
		return ans;
	for(int i=18;i>=0;i--)
		if(fx[a][i]^fx[b][i])
		{
			ans=min(ans,min(fm[a][i],fm[b][i]));
			a=fx[a][i];
			b=fx[b][i];
		}
	ans=min(ans,min(fm[a][0],fm[b][0]));
	return ans;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("van.in","r",stdin);
	freopen("van.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].len);
	sort(e+1,e+m+1);
	for(int i=1;i<=n;i++)
		f[i]=i;
	int fa,fb,t=0;
	for(int i=1;i<=m;i++)
	{
		fa=find(e[i].x);
		fb=find(e[i].y);
		if(fa^fb)
		{
			t++;
			f[fa]=fb;
			add(e[i].x,e[i].y,e[i].len);
			add(e[i].y,e[i].x,e[i].len);
		}
		if(t>=n-1)
			break;
	}
	fa=find(1);
	for(int i=1;i<=n;i++)
	{
		fb=find(i);
		if(fa^fb)
		{
			f[fb]=fa;
			add(1,i,-1);
			add(i,1,-1);
		}
	}
	memset(fm,inf,sizeof(fm));
	dfs(1,0);
	scanf("%d",&q);
	int a,b;
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&a,&b);
		printf("%d\n",lca(a,b));
	}
	return 0;
}