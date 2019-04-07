#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define update(x) s[x]=s[ch[x][0]]+s[ch[x][1]]+1
using namespace std;
int n,m,tot,root;
int val[100010],ch[100010][2],f[100010],lazy[100010],s[100010];
int ans[100010],top;
void down(int x)
{
	if(lazy[x])
	{
		lazy[x]=0;
		swap(ch[x][0],ch[x][1]);
		lazy[ch[x][0]]^=1;
		lazy[ch[x][1]]^=1;
	}
}
void rotate(int x)
{
	int y=f[x];
	int z=f[y];
	int kx=ch[y][1]==x,ky=ch[z][1]==y;
	f[x]=z;
	f[y]=x;
	f[ch[x][kx^1]]=y;
	ch[z][ky]=x;
	ch[y][kx]=ch[x][kx^1];
	ch[x][kx^1]=y;
	update(y);
	update(x);
}
void splay(int x,int fa)
{
	while(f[x]^fa)
	{
		int y=f[x];
		int z=f[y];
		if(z^fa)
			(ch[y][1]==x)^(ch[z][1]==y)?rotate(x):rotate(y);
		rotate(x);
	}
	if(!fa)
		root=x;
}
void build(int l,int r,int fa,int c)
{
	if(l>r)
		return;
	int mid=(l+r)>>1;
	int p=++tot;
	val[p]=mid;
	if(fa)
	{
		f[p]=fa;
		ch[fa][c]=p;
	}
	build(l,mid-1,p,0);
	build(mid+1,r,p,1);
	update(p);
}
int kth(int x)
{
	down(root);
	int p=root,now=s[ch[root][0]]+1;
	while(x^now&&p)
		if(now<x)
		{
			p=ch[p][1];
			down(p);
			now+=s[ch[p][0]]+1;
		}
		else
		{
			p=ch[p][0];
			down(p);
			now-=s[ch[p][1]]+1;
		}
	return p;
}
void dfs(int x)
{
	if(!x)
		return;
	down(x);
	dfs(ch[x][0]);
	ans[++top]=val[x];
	dfs(ch[x][1]);
}
void flip(int a,int b)
{
	int l=kth(a);
	int r=kth(b+2);
	splay(l,0);
	splay(r,l);
	lazy[ch[r][0]]^=1;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("splay.in","r",stdin);
	freopen("splay.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	int a,b;
	build(0,n+1,0,0);
	root=1;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		flip(a,b);
	}
	dfs(root);
	for(int i=2;i<=n+1;i++)
		printf("%d ",ans[i]);
	return 0;
}