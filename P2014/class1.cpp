#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
using namespace std;
int n,m,tot;
int v[310];
int f[310][310];
int head[310],edge[310],nxt[310];
void ins(int a,int b)
{
	edge[++tot]=b;
	nxt[tot]=head[a];
	head[a]=tot;
}
void dfs(int x)
{
	for(int i=head[x];i;i=nxt[i])
	{
		memcpy(f[edge[i]],f[x],sizeof(f[x]));
		dfs(edge[i]);
		for(rg j=1;j<=m;j++)
			f[x][j]=max(f[x][j],f[edge[i]][j]);
	}
	if(x)
	{
		for(rg i=1;i<=m;i++)
			f[x][i]=f[x][i-1]+v[x];
		f[x][0]=0;
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("class.in","r",stdin);
	freopen("class1.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	int a;
	for(rg i=1;i<=n;i++)
	{
		scanf("%d%d",&a,v+i);
		ins(a,i);
	}
	dfs(0);
	printf("%d",f[0][m]);
	return 0;
}