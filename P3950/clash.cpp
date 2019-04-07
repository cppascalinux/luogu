//2019.02.06
//luogu3950 部落冲突 DFS序+树状数组
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lb(x) (x&-x)
using namespace std;
int n,m,tot,tme;
int hd[300009],eg[600009],nxt[600009];
int dfn[300009],ed[300009],c[300009],dep[300009];
int f[300009][20];
int ex[300009],ey[300009];
void add(int x,int val)
{
	for(int i=x;i;i-=lb(i))
		c[i]+=val;
}
int ask(int x)
{
	int ans=0;
	for(int i=x;i<=n;i+=lb(i))
		ans+=c[i];
	return ans;
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs(int x,int fa)
{
	ed[x]=dfn[x]=++tme;
	dep[x]=dep[fa]+1;
	f[x][0]=fa;
	for(int i=1;i<=19;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			dfs(eg[i],x);
			ed[x]=max(ed[x],ed[eg[i]]);
		}
}
int getlca(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	int l=dep[x]-dep[y];
	for(int i=0;i<=19;i++)
		if(l&(1<<i))
			x=f[x][i];
	if(x==y)
		return x;
	for(int i=19;i>=0;i--)
		if(f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}
void query(int x,int y)
{
	int lca=getlca(x,y);
	int l1=dep[x]+dep[y]-2*dep[lca];
	int l2=ask(dfn[x])+ask(dfn[y])-2*ask(dfn[lca]);
	if(l1!=l2)
		printf("No\n");
	else
		printf("Yes\n");
}
void modify(int x,int y,int val)
{
	if(dep[x]<dep[y])
		swap(x,y);
	add(ed[x],val);
	add(dfn[x]-1,-val);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("clash.in","r",stdin);
	freopen("clash.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=n-1;i++)
	{
		scanf("%d%d",&a,&b);
		ins(a,b);
		ins(b,a);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		add(ed[i],1);
		add(dfn[i]-1,-1);
	}
	int cnt=0;
	for(int i=1,a,b;i<=m;i++)
	{
		char ch[2];
		scanf("%s",ch);
		if(ch[0]=='Q')
		{
			scanf("%d%d",&a,&b);
			query(a,b);
		}
		else if(ch[0]=='C')
		{
			scanf("%d%d",&a,&b);
			ex[++cnt]=a;
			ey[cnt]=b;
			modify(a,b,1);
		}
		else
		{
			scanf("%d",&a);
			modify(ex[a],ey[a],-1);
		}
	}
	return 0;
}