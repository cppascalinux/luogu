//2019.02.09
//luogu4180【模板】严格次小生成树[BJWC2010] kruskal+主席树(其实是我懒得维护次大值)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define long long long
#define cp(a,b) lp[a]=lp[b],rp[a]=rp[b],sm[a]=sm[b]
#define inf 0x7FFFFFFF
using namespace std;
char *p1,*p2,buffer[10000009];
struct node
{
	int u,v,l;
	bool operator <(const node &o) const
	{
		return l<o.l;
	}
};
int n,m,tot,cnt;
int hd[100009],eg[200009],nxt[200009],len[200009];
node e[300009];
int ont[300009];
int fn[100009],f[100009][17],dep[100009];
int rt[100009],lp[3200009],rp[3200009],sm[3200009];
long ans;
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
int fnd(int x)
{
	return x==fn[x]?x:fn[x]=fnd(fn[x]);
}
void ins(int a,int b,int c)
{
	eg[++tot]=b;
	len[tot]=c;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void add(int &a,int l,int r,int x)
{
	int p=++cnt;
	cp(p,a);
	a=p;
	sm[a]++;
	if(l<r)
	{
		int mid=(l+r)>>1;
		if(x<=mid)
			add(lp[a],l,mid,x);
		else
			add(rp[a],mid+1,r,x);
	}
}
int ask(int a1,int a2,int a3,int l,int r,int x)
{
	int tsm=sm[a1]+sm[a2]-2*sm[a3];
	if(!tsm)
		return 0;
	if(l==r)
		return l;
	int mid=(l+r)>>1;
	if(x>=mid+1)
	{
		int tp=ask(rp[a1],rp[a2],rp[a3],mid+1,r,x);
		if(tp)
			return tp;
	}
	return ask(lp[a1],lp[a2],lp[a3],l,mid,x);
}
void dfs(int x,int fa,int flen)
{
	if(fa)
	{
		rt[x]=rt[fa];
		add(rt[x],0,1000000000,flen);
	}
	dep[x]=dep[fa]+1;
	f[x][0]=fa;
	for(int i=1;i<=16;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
			dfs(eg[i],x,len[i]);
}
int getlca(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	int l=dep[x]-dep[y];
	for(int i=0;i<=16;i++)
		if(l&(1<<i))
			x=f[x][i];
	if(x==y)
		return x;
	for(int i=16;i>=0;i--)
		if(f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}
void init()
{
	for(int i=1;i<=n;i++)
		fn[i]=i;
	sort(e+1,e+m+1);
	for(int i=1;i<=m;i++)
	{
		int a=e[i].u,b=e[i].v;
		if(fnd(a)!=fnd(b))
		{
			fn[fnd(a)]=fnd(b);
			ins(a,b,e[i].l);
			ins(b,a,e[i].l);
			ont[i]=1;
			ans+=e[i].l;
		}
	}
	dfs(1,0,0);
}
int get(int x,int y,int l)
{
	int lca=getlca(x,y);
	int t=ask(rt[x],rt[y],rt[lca],0,1000000000,l-1);
	return l-t;
}
void solve()
{
	// printf("ans:%lld\n",ans);
	int dt=inf;
	for(int i=1;i<=m;i++)
		if(!ont[i])
			dt=min(dt,get(e[i].u,e[i].v,e[i].l));
	printf("%lld",ans+dt);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("mst.in","r",stdin);
	freopen("mst.out","w",stdout);
#endif
	rd(n),rd(m);
	for(int i=1;i<=m;i++)
		rd(e[i].u),rd(e[i].v),rd(e[i].l);
	init();
	solve();
	return 0;
}