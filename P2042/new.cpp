#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,root,root1;
int num[500010];
int val[500010],ch[500010][2],f[500010],s[500010],sum[500010];
int mx[500010],ml[500010],mr[500010],lazy1[500010],lazy2[500010];
int st[500010],tot;
char ss[100];
void update(int p)
{
	int lp=ch[p][0],rp=ch[p][1];
	s[p]=s[lp]+s[rp]+1;
	sum[p]=sum[lp]+sum[rp]+val[p];
	mx[p]=max(mr[lp]+ml[rp]+val[p],max(mx[lp],mx[rp]));
	ml[p]=max(sum[lp]+val[p]+ml[rp],ml[lp]);
	mr[p]=max(sum[rp]+val[p]+mr[lp],mr[rp]);
}
void down(int p)
{
	int lp=ch[p][0],rp=ch[p][1];
	if(lazy1[p]^2000)
	{
		int c=lazy1[p];
		lazy1[p]=2000;
		lazy1[lp]=lazy1[rp]=c;
		val[lp]=val[rp]=c;
		sum[lp]=c*s[lp];
		sum[rp]=c*s[rp];
		ml[lp]=mr[lp]=c>0?sum[lp]:0;
		ml[rp]=mr[rp]=c>0?sum[rp]:0;
		mx[lp]=c>0?sum[lp]:c;
		mx[rp]=c>0?sum[rp]:c;
	}
	if(lazy2[p])
	{
		lazy2[p]=0;
		lazy2[lp]^=1;
		lazy2[rp]^=1;
		swap(ch[p][0],ch[p][1]);
		swap(ml[lp],mr[lp]);
		swap(ml[rp],mr[rp]);
	}
}
void rotate(int x)
{
	int y=f[x],z=f[f[x]];
	int kx=x==ch[y][1],ky=y==ch[z][1];
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
		int y=f[x],z=f[f[x]];
		if(z^fa)
			(x==ch[y][1])^(y==ch[z][1])?rotate(x):rotate(y);
		rotate(x);
	}
	if(!fa)
		root=x;
}
int kth(int x)
{
	down(root);
	int p=root,now=s[ch[root][0]]+1;
	while(x^now)
	{
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
	}
	return p;
}
void build(int l,int r,int fa,int c)
{
	if(l>r)
		return;
	int p=st[tot--];
	if(!fa)
	{
		root1=p;
		f[p]=0;
	}
	else
	{
		f[p]=fa;
		ch[fa][c]=p;
	}
	int mid=(l+r)>>1;
	val[p]=num[mid];
	ch[p][0]=ch[p][1]=0;
	lazy1[p]=2000;
	lazy2[p]=0;
	build(l,mid-1,p,0);
	build(mid+1,r,p,1);
	update(p);
}
void insert()
{
	int pos,cnt,l,r;
	scanf("%d%d",&pos,&cnt);
	n+=cnt;
	for(int i=1;i<=cnt;i++)
		scanf("%d",num+i);
	build(1,cnt,0,0);
	l=kth(pos+1);
	r=kth(pos+2);
	splay(l,0);
	splay(r,l);
	f[root1]=r;
	ch[r][0]=root1;
	update(r);
	update(l);
}
void dfs(int p)
{
	if(!p)
		return;
	st[++tot]=p;
	dfs(ch[p][0]);
	dfs(ch[p][1]);
}
void del()
{
	int pos,cnt,l,r;
	scanf("%d%d",&pos,&cnt);
	n-=cnt;
	l=kth(pos);
	r=kth(pos+cnt+1);
	splay(l,0);
	splay(r,l);
	dfs(ch[r][0]);
	ch[r][0]=0;
	update(r);
	update(l);
}
void set()
{
	int pos,cnt,c,l,r;
	scanf("%d%d%d",&pos,&cnt,&c);
	l=kth(pos);
	r=kth(pos+cnt+1);
	splay(l,0);
	splay(r,l);
	int p=ch[r][0];
	lazy1[p]=val[p]=c;
	sum[p]=c*s[p];
	ml[p]=mr[p]=c>0?sum[p]:0;
	mx[p]=c>0?sum[p]:c;
	update(r);
	update(l);
}
void reverse()
{
	int pos,cnt,l,r;
	scanf("%d%d",&pos,&cnt);
	l=kth(pos);
	r=kth(pos+cnt+1);
	splay(l,0);
	splay(r,l);
	int p=ch[r][0];
	lazy2[p]^=1;
	swap(ml[p],mr[p]);
	update(r);
	update(l);
}
int getsum()
{
	int pos,cnt,l,r;
	scanf("%d%d",&pos,&cnt);
	l=kth(pos);
	r=kth(pos+cnt+1);
	splay(l,0);
	splay(r,l);
	return sum[ch[r][0]];
}
int getmax()
{
	int l,r;
	l=kth(1);
	r=kth(n+2);
	splay(l,0);
	splay(r,l);
	return mx[ch[r][0]];
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("splay.in","r",stdin);
	freopen("new.out","w",stdout);
	#endif
	for(int i=1;i<=500000;i++)
		st[++tot]=i;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",num+i);
	num[0]=num[n+1]=-10000;
	mx[0]=0x80000000;
	build(0,n+1,0,0);
	root=root1;
	for(int i=1;i<=m;i++)
	{
		scanf("%s",ss);
		if(ss[0]=='I')
			insert();
		else if(ss[0]=='D')
			del();
		else if(ss[0]=='M'&&ss[2]=='K')
			set();
		else if(ss[0]=='R')
			reverse();
		else if(ss[0]=='G')
			printf("%d\n",getsum());
		else
			printf("%d\n",getmax());
	}
	return 0;
}