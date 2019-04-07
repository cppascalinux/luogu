//2019.02.09
//luogu4234 最小差值生成树 LCT动态维护最大生成树
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define nrt(x) x==lc(f[x])||x==rc(f[x])
#define down(x) if(rv[x]) swap(lc(x),rc(x)),rv[lc(x)]^=1,rv[rc(x)]^=1,rv[x]=0
#define getmn(x,y) v[x]<v[y]?x:y
#define inf 0x7FFFFFFF
using namespace std;
struct node
{
	int u,v,l;
	bool operator <(const node &p) const
	{
		return l<p.l;
	}
};
int n,m;
node e[200009];
int ont[200009];
int fn[50009];
int f[250009],ch[250009][2],v[250009],mn[250009],rv[250009],st[250009];
set<int> s;
set<int>::iterator it;
void update(int x)
{
	mn[x]=getmn(mn[lc(x)],mn[rc(x)]);
	mn[x]=getmn(mn[x],x);
}
void rotate(int x)
{
	int y=f[x],z=f[y],dx=x==rc(y),dy=y==rc(z);
	// if(ch[x][dx^1])
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
	for(;tp;tp--)
		down(st[tp]);
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
void split(int x,int y)
{
	makert(x);
	access(y);
	splay(y);
}
int fnd(int x)
{
	return x==fn[x]?x:fn[x]=fnd(fn[x]);
}
void add(int a)
{
	// v[a+n]=e[a].l;
	int x=e[a].u,y=e[a].v;
	split(x,y);
	int t=mn[y];
	s.erase(t-n);
	// printf("\na:%d t:%d x:%d y:%d\n",a,t,x,y);
	// for(int i=1;i<=n+m;i++)
	// 	printf("i:%d mn:%d v:%d\n",i,mn[i],v[i]);
	// for(it=s.begin();it!=s.end();it++)
	// 	printf("%d ",*it);
	// printf("\n");
	makert(t);
	f[lc(t)]=f[rc(t)]=0;
	lc(t)=rc(t)=0;
	makert(x);
	makert(y);
	f[x]=f[y]=a+n;
}
void solve()
{
	sort(e+1,e+m+1);
	for(int i=0;i<=n;i++)
	{
		fn[i]=i;
		v[i]=inf;
	}
	for(int i=1;i<=m;i++)
		v[i+n]=i;
	for(int i=1;i<=n+m;i++)
		mn[i]=i;
	int cnt=n-1,beg=0;
	for(int i=1;i<=m;i++)
	{
		int x=e[i].u,y=e[i].v;
		if(fnd(x)!=fnd(y))
		{
			ont[i]=1;
			beg=i;
			s.insert(i);
			fn[fnd(x)]=fnd(y);
			makert(x);
			makert(y);
			f[x]=f[y]=i+n;
			cnt--;
			if(!cnt)
				break;
		}
	}
	int ans=e[beg].l-e[*s.begin()].l;
	// printf("ans:%d\n",ans);
	for(int i=1;i<=m;i++)
		if(!ont[i])
		{
			if(e[i].u==e[i].v)
				continue;
			s.insert(i);
			add(i);
			it=s.end();
			it--;
			ans=min(ans,e[*it].l-e[*s.begin()].l);
		}
	printf("%d\n",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].l);
	solve();
	return 0;
}