//luoguP3690 【模板】Link Cut Tree （动态树）
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define nrt(x) x==lc(f[x])||x==rc(f[x])
#define upd(x) sm[x]=sm[lc(x)]^sm[rc(x)]^v[x]
#define down(x) if(lz[x]) swap(lc(x),rc(x)),lz[x]=0,lz[lc(x)]^=1,lz[rc(x)]^=1
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m;
int f[300009],ch[300009][2],v[300009],lz[300009],sm[300009],st[300009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+ch-'0',ch=gc();
}
void rot(int x)
{
	int y=f[x],z=f[y];
	int dx=x==rc(y),dy=y==rc(z);
	if(nrt(y))
		ch[z][dy]=x;
	if(ch[x][dx^1])
		f[ch[x][dx^1]]=y;
	f[x]=z;
	f[y]=x;
	ch[y][dx]=ch[x][dx^1];
	ch[x][dx^1]=y;
	upd(y);
	upd(x);
}
void splay(int x)
{
	int tp=0;
	int y,z;
	for(y=x;nrt(y);y=f[y])
		st[++tp]=y;
	st[++tp]=y;
	for(;tp;tp--)
		down(st[tp]);
	while(nrt(x))
	{
		y=f[x],z=f[y];
		if(nrt(y))
			rot((x==rc(y))^(y==rc(z))?x:y);
		rot(x);
	}
}
void access(int x)
{
	for(int y=0;x;y=x,x=f[x])
	{
		splay(x);
		rc(x)=y;
		upd(x);
	}
}
void makert(int x)
{
	access(x);
	splay(x);
	lz[x]^=1;
}
int findrt(int x)
{
	access(x);
	splay(x);
	while(lc(x))
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
		upd(x);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("lct.in","r",stdin);
	freopen("lct.out","w",stdout);
#endif
	rd(n),rd(m);
	for(int i=1;i<=n;i++)
		rd(v[i]);
	for(int i=1,a,b,c;i<=m;i++)
	{
		rd(a),rd(b),rd(c);
		if(a==0)
		{
			split(b,c);
			printf("%d\n",sm[c]);
		}
		else if(a==1)
			link(b,c);
		else if(a==2)
			cut(b,c);
		else
		{
			splay(b);
			v[b]=c;
			upd(b);
		}
	}
	return 0;
}