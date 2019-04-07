#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define cp(a,b) {lp[a]=lp[b],rp[a]=rp[b],sum[a]=sum[b];}
using namespace std;
int n,m,tot,cnt,d;
int num[100010],xx[100010],id[100010];
int edge[200010],head[100010],nxt[200010];
int root[100010];
int lp[2000010],rp[2000010],sum[2000010];
int f[100010][20],dep[100010];
void ins(int a,int b)
{
	edge[++tot]=b;
	nxt[tot]=head[a];
	head[a]=tot;
}
void init()
{
	memcpy(xx,num,sizeof(xx));
	sort(xx+1,xx+n+1);
	d=unique(xx+1,xx+n+1)-xx-1;
	for(int i=1;i<=n;i++)
	{
		int t=num[i];
		num[i]=lower_bound(xx+1,xx+d+1,num[i])-xx;
		id[num[i]]=t;
	}
}
void add(int &a,int l,int r,int x)
{
	int p=++cnt;
	cp(p,a);
	a=p;
	sum[a]++;
	if(l^r)
	{
		int mid=(l+r)>>1;
		if(x<=mid)
			add(lp[a],l,mid,x);
		else
			add(rp[a],mid+1,r,x);
	}
}
void dfs(int x,int fa)
{
	dep[x]=dep[fa]+1;
	root[x]=root[fa];
	add(root[x],1,d,num[x]);
	f[x][0]=fa;
	for(int i=1;i<=18;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	for(int i=head[x];i;i=nxt[i])
		if(edge[i]^fa)
			dfs(edge[i],x);
}
int lca(int a,int b)
{
	if(dep[a]<dep[b])
		swap(a,b);
	int l=dep[a]-dep[b];
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
int ask(int a,int b,int c,int d,int l,int r,int k)
{
	if(l==r)
		return l;
	int lcnt=sum[lp[a]]+sum[lp[b]]-sum[lp[c]]-sum[lp[d]];
	int mid=(l+r)>>1;
	if(k<=lcnt)
		return ask(lp[a],lp[b],lp[c],lp[d],l,mid,k);
	else
		return ask(rp[a],rp[b],rp[c],rp[d],mid+1,r,k-lcnt);
}
int solve(int a,int b,int c)
{
	int ans=0;
	int fa=lca(a,b);
	int top=f[fa][0];
	ans=ask(root[a],root[b],root[fa],root[top],1,d,c);
	return ans;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",num+i);
	init();
	for(int i=1;i<=n-1;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		ins(a,b);
		ins(b,a);
	}
	dfs(1,0);
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		// a^=ans;
		ans=id[solve(a,b,c)];
		printf("%d\n",ans);
	}
	return 0;
}