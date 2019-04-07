//2019.02.10
//luogu2387 [NOI2014]魔法森林 LCT动态维护最小生成树
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define nrt(x) x==lc(f[x])||x==rc(f[x])
#define getmx(x,y) v[x]>v[y]?x:y
#define down(x) if(rv[x]) swap(lc(x),rc(x)),rv[lc(x)]^=1,rv[rc(x)]^=1,rv[x]=0
#define inf 0x7FFFFFFF
using namespace std;
struct node
{
	int u,v,l1,l2;
	bool operator <(const node &p) const
	{
		return l1<p.l1;
	}
};
int n,m;
node e[100009];
int fn[50009];
int f[150009],ch[150009][2],rv[150009],mx[150009],v[150009],st[150009];
int fnd(int x)
{
	return x==fn[x]?x:fn[x]=fnd(fn[x]);
}
void update(int x)
{
	mx[x]=getmx(mx[lc(x)],mx[rc(x)]);
	mx[x]=getmx(x,mx[x]);
}
void rotate(int x)
{
	int y=f[x],z=f[y],dx=x==rc(y),dy=y==rc(z);
	if(ch[x][dx^1])
		f[ch[x][dx^1]]=y;
	if(nrt(y))
		ch[z][dy]=x;
	f[x]=z;
	f[y]=x;
	ch[y][dx]=ch[x][dx^1];
	ch[x][dx^1]=y;
	update(y);
	update(x);
}
void splay(int x)
{
	int y,z,tp=0;
	for(y=x;nrt(y);y=f[y])
		st[++tp]=y;
	st[++tp]=y;
	for(int i=tp;i>=1;i--)
		down(st[i]);
	while(nrt(x))
	{
		y=f[x],z=f[y];
		if(nrt(y))
			rotate((x==rc(y))^(y==rc(z))?x:y);
		rotate(x);
	}
}
void access(int x)
{
	for(int y=0;x;y=x,x=f[x])
	{
		splay(x);
		rc(x)=y;
		update(x);
	}
}
void makert(int x)
{
	access(x);
	splay(x);
	rv[x]^=1;
}
void split(int x,int y)
{
	makert(x);
	access(y);
	splay(y);
}
void add(int a)
{
	int x=e[a].u,y=e[a].v;
	split(x,y);
	int t=mx[y];
	if(v[a+n]<v[t])
	{
		// if(rc(t))
		// 	cerr<<"sfsfwerfwer";
		makert(t);
		access(t);
		splay(e[t-n].u);
		splay(e[t-n].v);
		f[e[t-n].u]=f[e[t-n].v]=0;
		makert(x);
		makert(y);
		f[x]=f[y]=a+n;
	}
}
void solve()
{
	sort(e+1,e+m+1);
	for(int i=1;i<=n;i++)
		fn[i]=i;
	for(int i=1;i<=m;i++)
		v[i+n]=e[i].l2;
	for(int i=1;i<=n+m;i++)
		mx[i]=i;
	int ans=inf,sm=n-1;
	for(int i=1;i<=m;i++)
	{
		int x=e[i].u,y=e[i].v;
		if(fnd(x)!=fnd(y))
		{
			fn[fnd(x)]=fnd(y);
			makert(x);
			makert(y);
			f[x]=f[y]=i+n;
			sm--;
		}
		else
			add(i);
		if(fnd(1)==fnd(n))
		{
			split(1,n);
			ans=min(ans,v[mx[n]]+e[i].l1);
		}
	}
	if(fnd(1)!=fnd(n))
		printf("-1");
	else
		printf("%d",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d%d",&e[i].u,&e[i].v,&e[i].l1,&e[i].l2);
	solve();
	return 0;
}