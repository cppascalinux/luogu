//2019.02.02
//luogu3203 弹飞绵羊 LCT（其实也可以分块做）
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define update(x) s[x]=s[lc(x)]+s[rc(x)]+v[x]
#define down(x) if(lz[x]) swap(lc(x),rc(x)),lz[x]=0,lz[lc(x)]^=1,lz[rc(x)]^=1
#define nrt(x) x==lc(f[x])||x==rc(f[x])
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m;
int f[200009],ch[200009][2],v[200009],s[200009],lz[200009],st[200009];
int nxt[200009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void rotate(int x)
{
	int y=f[x],z=f[y],dx=x==rc(y),dy=y==rc(z);
	if(nrt(y))
		ch[z][dy]=x;
	if(ch[x][dx^1])
		f[ch[x][dx^1]]=y;
	f[x]=z;
	f[y]=x;
	ch[y][dx]=ch[x][dx^1];
	ch[x][dx^1]=y;
	update(y);
	update(x);
}
void splay(int x)
{
	int y,top=0,z;
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
	lz[x]^=1;
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
		rc(x)=f[y]=0;
		update(x);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sheep.in","r",stdin);
	freopen("sheep.out","w",stdout);
#endif
	rd(n);
	for(int i=1;i<=n+1;i++)
		s[i]=v[i]=1;
	for(int i=1;i<=n;i++)
	{
		rd(nxt[i]);
		nxt[i]=min(nxt[i]+i,n+1);
		link(i,nxt[i]);
	}
	// access(1);
	// for(int i=1;i<=n+1;i++)
	// 	printf("i:%d f:%d rt:%d\n",i,f[i],!(nrt(i)));
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d nxt:%d\n",i,nxt[i]);
	rd(m);
	for(int i=1,a,b,c;i<=m;i++)
	{
		rd(a);
		if(a==1)
		{
			rd(b);
			b++;
			split(n+1,b);
			printf("%d\n",s[lc(b)]);
		}
		else
		{
			rd(b),rd(c);
			b++;
			cut(b,nxt[b]);
			nxt[b]=min(c+b,n+1);
			link(b,nxt[b]);
		}
	}
	return 0;
}