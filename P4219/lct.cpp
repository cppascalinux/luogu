//2019.05.16
//luoguP4219 [BJOI2014]大融合 LCT维护子树大小(维护虚子树和)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define nrt(x) x==lc(f[x])||x==rc(f[x])
using namespace std;
int n,q;
int f[100009],ch[100009][2],rv[100009],sz[100009],si[100009],st[100009];
void down(int x)
{
	if(rv[x])
		rv[x]=0,swap(lc(x),rc(x)),rv[lc(x)]^=1,rv[rc(x)]^=1;
}
void update(int x)
{
	sz[x]=sz[lc(x)]+sz[rc(x)]+si[x]+1;
}
void rotate(int x)
{
	int y=f[x],z=f[y],dx=x==rc(y),dy=y==rc(z);
	if(nrt(y))
		ch[z][dy]=x;
	f[x]=z;
	f[y]=x;
	f[ch[x][dx^1]]=y;
	ch[y][dx]=ch[x][dx^1];
	ch[x][dx^1]=y;
	update(y);
	update(x);
}
void splay(int x)
{
	int tp=0,y,z;
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
		si[x]+=sz[rc(x)];
		si[x]-=sz[rc(x)=y];
		update(x);
	}
}
void makert(int x)
{
	access(x);
	splay(x);
	rv[x]^=1;
}
void lnk(int x,int y)
{
	makert(x);
	makert(y);
	f[y]=x;
	si[x]+=sz[y];
	update(x);
}
li ask(int x,int y)
{
	makert(x);
	access(y);
	splay(x);
	return (li)sz[y]*(sz[x]-sz[y]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("lct.in","r",stdin);
	freopen("lct.out","w",stdout);
#endif
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		sz[i]=1;
	for(int i=1,a,b;i<=q;i++)
	{
		// printf("i:%d--------------------------------------------------------\n",i);
		char s[2];
		scanf("%s%d%d",s,&a,&b);
		if(s[0]=='A')
			lnk(a,b);
		else
			printf("%lld\n",ask(a,b));
		// for(int j=1;j<=n;j++)
		// 	printf("j:%d sz:%d f:%d\n",j,sz[j],f[j]);
	}
	return 0;
}