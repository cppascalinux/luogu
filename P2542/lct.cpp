//2019.02.06
//luogu2542 [AHOI2005]航线规划 LCT+并查集+倒序
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<map>
#define pii pair<int,int>
#define fi first
#define se second
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define nrt(x) x==lc(f[x])||x==rc(f[x])
#define update(x) sz[x]=sz[lc(x)]+sz[rc(x)]+1;
#define down(x) if(rv[x]) swap(lc(x),rc(x)),rv[lc(x)]^=1,rv[rc(x)]^=1,rv[x]=0;
using namespace std;
int n,m,cnt;
int ch[100009][2],f[100009],rv[100009],sz[100009];
int fn[100009],st[100009];
pii e[100009];
int del[100009],ont[100009];
pii q[100009];
int typ[100009],ans[100009];
map<pii,int> mp;
int fnd(int x)
{
	return x==fn[x]?x:fn[x]=fnd(fn[x]);
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
	for(int y=0;x;y=x,x=fnd(f[x]))
	{
		if(y)
			f[y]=x;
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
int findrt(int x)
{
	access(x);
	splay(x);
	while(1)
	{
		down(x);
		if(!lc(x))
			break;
		x=lc(x);
	}
	splay(x);
	return x;
}
int link(int x,int y)
{
	makert(x);
	if(findrt(y)==x)
		return 0;
	f[x]=y;
	return 1;
}
void merge(int x,int y)
{
	makert(x);
	access(y);
	splay(y);
	queue<int> q;
	q.push(y);
	while(!q.empty())
	{
		int t=q.front();
		q.pop();
		fn[fnd(t)]=fnd(y);
		if(lc(t))
			q.push(lc(t));
		if(rc(t))
			q.push(rc(t));
	}
	lc(y)=rc(y)=0;
	update(y);
}
int ask(int x,int y)
{
	makert(x);
	access(y);
	splay(y);
	return sz[y]-1;
}
void init()
{
	for(int i=1;i<=n;i++)
	{
		fn[i]=i;
		sz[i]=1;
	}
	for(int i=1;i<=m;i++)
		if(!del[i])
			ont[i]=link(e[i].fi,e[i].se);
	for(int i=1;i<=m;i++)
		if(!del[i]&&!ont[i])
			merge(fnd(e[i].fi),fnd(e[i].se));
}
void dbg(int x)
{
	for(int i=1;i<=n;i++)
		printf("i:%d f:%d fn:%d sz:%d lc:%d rc:%d rv:%d\n",i,f[i],fnd(i),sz[i],lc(i),rc(i),rv[i]);
}
void solve()
{
	for(int i=cnt;i>=1;i--)
	{
		// printf("case %d:\n",i);
		// printf("x:%d y:%d\n",fnd(q[i].fi),fnd(q[i].se));
		if(!typ[i])
			merge(fnd(q[i].fi),fnd(q[i].se));
		else
			ans[i]=ask(fnd(q[i].fi),fnd(q[i].se));
		// dbg(i);
	}
	for(int i=1;i<=cnt;i++)
		if(typ[i])
			printf("%d\n",ans[i]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("chain.in","r",stdin);
	freopen("lct.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		e[i]=pii(a,b);
		mp[e[i]]=i;
	}
	int c,a,b;
	scanf("%d",&c);
	while(c!=-1)
	{
		scanf("%d%d",&a,&b);
		q[++cnt]=pii(a,b);
		if(!c)
			del[mp[q[cnt]]]=1;
		else
			typ[cnt]=1;
		scanf("%d",&c);
	}
	init();
	solve();
	return 0;
}