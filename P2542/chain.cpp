//2019.02.06
//luogu2542 [AHOI2005]航线规划 树链剖分+线段树+操作倒序
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define pii pair<int,int>
#define fi first
#define se second
#define down(x) if(lz[x]) sm[x<<1]=sm[x<<1|1]=0,lz[x<<1]=lz[x<<1|1]=1,lz[x]=0
#define update(x) sm[x]=sm[x<<1]+sm[x<<1|1]
using namespace std;
int n,m,cnt,tot,tme;
pii e[100009],q[100009];
int ont[100009],del[100009],typ[100009],ans[100009];
int hd[100009],eg[200009],nxt[200009];
int top[100009],fat[100009],sz[100009],son[100009],dfn[100009],pos[100009],dep[100009];
int l[400009],r[400009],sm[400009],lz[400009];
int f[100009];
map<pii,int> mp;
int fnd(int x)
{
	return x==f[x]?x:f[x]=fnd(f[x]);
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs1(int x,int fa)
{
	dep[x]=dep[fa]+1;
	sz[x]=1;
	fat[x]=fa;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			dfs1(eg[i],x);
			sz[x]+=sz[eg[i]];
			if(sz[eg[i]]>sz[son[x]])
				son[x]=eg[i];
		}
}
void dfs2(int x,int tp)
{
	top[x]=tp;
	dfn[x]=++tme;
	pos[tme]=x;
	if(son[x])
		dfs2(son[x],tp);
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fat[x]&&eg[i]!=son[x])
			dfs2(eg[i],eg[i]);
}
void build(int a,int ll,int rr)
{
	l[a]=ll;
	r[a]=rr;
	sm[a]=rr-ll+1;
	if(ll<rr)
	{
		int mid=(ll+rr)>>1;
		build(a<<1,ll,mid);
		build(a<<1|1,mid+1,rr);
	}
}
void add(int a,int ll,int rr)
{
	if(l[a]>rr||r[a]<ll)
		return;
	if(l[a]>=ll&&r[a]<=rr)
	{
		sm[a]=0;
		lz[a]=1;
		return;
	}
	down(a);
	add(a<<1,ll,rr);
	add(a<<1|1,ll,rr);
	update(a);
}
int ask(int a,int ll,int rr)
{
	if(l[a]>rr||r[a]<ll)
		return 0;
	if(l[a]>=ll&&r[a]<=rr)
		return sm[a];
	down(a);
	return ask(a<<1,ll,rr)+ask(a<<1|1,ll,rr);
}
void modify(int x,int y)
{
	int fx=top[x],fy=top[y];
	while(fx!=fy)
	{
		if(dep[fx]<dep[fy])
			swap(x,y),swap(fx,fy);
		add(1,dfn[fx],dfn[x]);
		x=fat[fx];
		fx=top[x];
	}
	if(dfn[x]>dfn[y])
		swap(x,y);
	add(1,dfn[x]+1,dfn[y]);
}
int query(int x,int y)
{
	int fx=top[x],fy=top[y],ans=0;
	while(fx!=fy)
	{
		if(dep[fx]<dep[fy])
			swap(x,y),swap(fx,fy);
		ans+=ask(1,dfn[fx],dfn[x]);
		x=fat[fx];
		fx=top[x];
	}
	if(dfn[x]>dfn[y])
		swap(x,y);
	ans+=ask(1,dfn[x]+1,dfn[y]);
	return ans;
}
void init()
{
	for(int i=1;i<=n;i++)
		f[i]=i;
	for(int i=1;i<=m;i++)
		if(!del[i])
		{
			int x=e[i].fi,y=e[i].se;
			if(fnd(x)!=fnd(y))
			{
				f[fnd(x)]=fnd(y);
				ins(x,y);
				ins(y,x);
				ont[i]=1;
			}
		}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	for(int i=1;i<=m;i++)
		if(!del[i]&&!ont[i])
			modify(e[i].fi,e[i].se);
}
void solve()
{
	for(int i=cnt;i>=1;i--)
	{
		if(typ[i]==0)
			modify(q[i].fi,q[i].se);
		else
			ans[i]=query(q[i].fi,q[i].se);
	}
	for(int i=1;i<=cnt;i++)
		if(typ[i])
			printf("%d\n",ans[i]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("chain.in","r",stdin);
	freopen("chain.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		e[i]=pii(a,b);
		mp[e[i]]=i;
	}
	int c,a,b;
	scanf("%d%d%d",&c,&a,&b);
	while(c!=-1)
	{
		cnt++;
		q[cnt]=pii(a,b);
		if(c==0)
		{
			del[mp[pii(a,b)]]=1;
			typ[cnt]=0;
		}
		else
			typ[cnt]=1;
		scanf("%d%d%d",&c,&a,&b);
	}
	init();
	solve();
	return 0;
}