//2019.02.02
//luoguP1501 [国家集训队]Tree II LCT
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 51061
#define ll long long
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define nrt(x) x==lc(f[x])||x==rc(f[x])
#define update(x) sz[x]=sz[lc(x)]+sz[rc(x)]+1,sm[x]=(sm[lc(x)]+sm[rc(x)]+v[x])%mod
using namespace std;
char typ[10];
int n,m;
int f[100009],ch[100009][2],sm[100009],ad[100009],ml[100009],rv[100009],v[100009],st[100009],sz[100009];
void down(int x)
{
	int &lx=lc(x),&rx=rc(x);
	if(rv[x])
	{
		swap(lx,rx);
		rv[lx]^=1;
		rv[rx]^=1;
		rv[x]=0;
	}
	if(ml[x]!=1)
	{
		int &t=ml[x];
		v[lx]=(ll)v[lx]*t%mod;
		v[rx]=(ll)v[rx]*t%mod;
		sm[lx]=(ll)sm[lx]*t%mod;
		sm[rx]=(ll)sm[rx]*t%mod;
		ml[lx]=(ll)ml[lx]*t%mod;
		ml[rx]=(ll)ml[rx]*t%mod;
		ad[lx]=(ll)ad[lx]*t%mod;
		ad[rx]=(ll)ad[rx]*t%mod;
		t=1;
	}
	if(ad[x])
	{
		int &t=ad[x];
		v[lx]=(v[lx]+t)%mod;
		v[rx]=(v[rx]+t)%mod;
		sm[lx]=(sm[lx]+(ll)sz[lx]*t)%mod;
		sm[rx]=(sm[rx]+(ll)sz[rx]*t)%mod;
		ad[lx]=(ad[lx]+t)%mod;
		ad[rx]=(ad[rx]+t)%mod;
		t=0;
	}
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
	int y,z,top=0;
	for(y=x;nrt(y);y=f[y])
		st[++top]=y;
	st[++top]=y;
	for(int i=top;i>=1;i--)
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
void link(int x,int y)
{
	makert(x);
	if(findrt(y)!=x)
		f[x]=y;
}
void cut(int x,int y)
{
	makert(x);
	if(findrt(y)==x&&f[y]==x&&!lc(y))
	{
		f[y]=rc(x)=0;
		update(x);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		v[i]=ml[i]=sm[i]=sz[i]=1;
	for(int i=1,a,b;i<=n-1;i++)
	{
		scanf("%d%d",&a,&b);
		link(a,b);
	}
	// makert(1);
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d f:%d sm:%d sz:%d v:%d\n",i,f[i],sm[i],sz[i],v[i]);
	for(int i=1,a,b,c,d;i<=m;i++)
	{
		scanf("%s",typ);
		if(typ[0]=='+')
		{
			scanf("%d%d%d",&a,&b,&c);
			split(a,b);
			v[b]=(v[b]+c)%mod;
			sm[b]=(sm[b]+(ll)sz[b]*c)%mod;
			ad[b]=(ad[b]+c)%mod;
		}
		else if(typ[0]=='*')
		{
			scanf("%d%d%d",&a,&b,&c);
			split(a,b);
			v[b]=(ll)v[b]*c%mod;
			sm[b]=(ll)sm[b]*c%mod;
			ml[b]=(ll)ml[b]*c%mod;
			ad[b]=(ll)ad[b]*c%mod;
		}
		else if(typ[0]=='-')
		{
			scanf("%d%d%d%d",&a,&b,&c,&d);
			cut(a,b);
			link(c,d);
		}
		else if(typ[0]=='/')
		{
			scanf("%d%d",&a,&b);
			split(a,b);
			printf("%d\n",sm[b]);
		}
	}
	return 0;
}