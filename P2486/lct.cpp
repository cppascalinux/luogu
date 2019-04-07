//2019.02.05
//luogu2486 [SDOI2011]染色 LCT
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define nrt(x) lc(f[x])==x||rc(f[x])==x
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m;
int f[100009],ch[100009][2],cl[100009],sm[100009],lcl[100009],rcl[100009],rv[100009],lz[100009],st[100009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void rdc(char &ch)
{
	ch=0;
	while(ch<'A'||ch>'Z')
		ch=gc();
}
void update(int x)
{
	if(!x)
		return;
	int lx=lc(x),rx=rc(x);
	lcl[x]=lx?lcl[lx]:cl[x];
	rcl[x]=rx?rcl[rx]:cl[x];
	sm[x]=sm[lx]+sm[rx]+1;
	sm[x]-=cl[x]==rcl[lx];
	sm[x]-=cl[x]==lcl[rx];
}
void down(int x)
{
	int lx=lc(x),rx=rc(x);
	if(rv[x])
	{
		swap(lc(x),rc(x));
		swap(lcl[lx],rcl[lx]);
		swap(lcl[rx],rcl[rx]);
		rv[lx]^=1;
		rv[rx]^=1;
		rv[x]=0;
	}
	if(lz[x])
	{
		if(lx)
		{
			cl[lx]=lcl[lx]=rcl[lx]=lz[x];
			sm[lx]=1;
		}
		if(rx)
		{
			cl[rx]=lcl[rx]=rcl[rx]=lz[x];
			sm[rx]=1;
		}
		lz[lx]=lz[rx]=lz[x];
		lz[x]=0;
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
	swap(lcl[x],rcl[x]);
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
	f[x]=y;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("chain.in","r",stdin);
	freopen("lct.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		rd(cl[i]);
		lcl[i]=rcl[i]=cl[i];
		sm[i]=1;
	}
	for(int i=1,a,b;i<=n-1;i++)
	{
		rd(a),rd(b);
		link(a,b);
	}
	for(int i=1;i<=m;i++)
	{
		char ch;
		rdc(ch);
		if(ch=='C')
		{
			int a,b,c;
			rd(a),rd(b),rd(c);
			split(a,b);
			lz[b]=cl[b]=lcl[b]=rcl[b]=c;
			// down(b);
			sm[b]=1;
		}
		else if(ch=='Q')
		{
			int a,b;
			rd(a),rd(b);
			split(a,b);
			printf("%d\n",sm[b]);
		}
	}
	return 0;
}