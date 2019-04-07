#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,s,tot;
int edge[1000010],next[1000010],head[500010];
int f[500010][20],d[500010];
void add(int a,int b)
{
	edge[++tot]=b;
	next[tot]=head[a];
	head[a]=tot;
}
void dfs(int x,int fa)
{
	d[x]=d[fa]+1;
	f[x][0]=fa;
	for(int k=1;(1<<k)<=d[x];k++)
		f[x][k]=f[f[x][k-1]][k-1];
	for(int i=head[x];i;i=next[i])
		if(edge[i]^fa)
			dfs(edge[i],x);
}
int lca(int a,int b)
{
	if(d[a]<d[b])
		swap(a,b);
	int l=d[a]-d[b];
	for(int i=0;i<=18;i++)
		if(l&(1<<i))
			a=f[a][i];
	if(a==b)
		return a;
	for(int i=18;i>=0;i--)
		if(f[a][i]^f[b][i])
		{
			a=f[a][i];
			b=f[b][i];
		}
	return f[a][0];
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("lca.in","r",stdin);
	freopen("lca.out","w",stdout);
	#endif
	scanf("%d%d%d",&n,&m,&s);
	int a,b;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	dfs(s,0);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		printf("%d\n",lca(a,b));
	}
	return 0;
}