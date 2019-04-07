#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,e,tot;
int match[1010],vist[1010];
int head[1010],edge[1000010],next[1000010];
void add(int a,int b)
{
	edge[++tot]=b;
	next[tot]=head[a];
	head[a]=tot;
}
int dfs(int x)
{
	if(vist[x])
		return 0;
	vist[x]=1;
	for(int i=head[x];i;i=next[i])
		if(!match[edge[i]]||dfs(match[edge[i]]))
		{
			match[edge[i]]=x;
			return 1;
		}
	return 0;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("bin.in","r",stdin);
	freopen("bin.out","w",stdout);
	#endif
	scanf("%d%d%d",&n,&m,&e);
	int a,b;
	for(int i=1;i<=e;i++)
	{
		scanf("%d%d",&a,&b);
		if(a<=n&&b<=m)
			add(a,b);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		ans+=dfs(i);
		memset(vist,0,sizeof(vist));
	}
	printf("%d",ans);
	return 0;
}