#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,root,root1;
int st[500010],tot,num[500010];
int ch[500010][2],val[500010],f[500010],s[500010],sum[500010];
int maxl[500010],maxr[500010],maxm[500010],lazy1[500010],lazy2[500010];
char ss[110];
void update(int p)
{
	if(!p)
		return;
	int lp=ch[p][0],rp=ch[p][1];
	s[p]=s[lp]+s[rp]+1;
	sum[p]=sum[lp]+sum[rp]+val[p];
	maxm[p]=max(maxr[lp]+maxl[rp]+val[p],max(maxm[lp],maxm[rp]));
	maxl[p]=max(maxl[lp],maxl[rp]+sum[lp]+val[p]);
	maxr[p]=max(maxr[rp],maxr[lp]+sum[rp]+val[p]);
}
void down(int p)
{
	int lp=ch[p][0],rp=ch[p][1];
	if(lazy1[p]^1001)
	{
		int c=lazy1[p];
		lazy1[p]=1001;
		lazy1[lp]=c;
		val[lp]=c;
		sum[lp]=c*s[lp];
		maxl[lp]=maxr[lp]=c>0?sum[lp]:0;
		maxm[lp]=c>0?sum[lp]:c;
		lazy1[rp]=c;
		val[rp]=c;
		sum[rp]=c*s[rp];
		maxl[rp]=maxr[rp]=c>0?sum[rp]:0;
		maxm[rp]=c>0?sum[rp]:c;
	}
	if(lazy2[p])
	{
		lazy2[p]=0;
		swap(ch[p][0],ch[p][1]);
		lazy2[lp]^=1;
		lazy2[rp]^=1;
		swap(maxl[lp],maxr[lp]);
		swap(maxl[rp],maxr[rp]);
	}
}
void rotate(int x)
{
	int y=f[x],z=f[f[x]];
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
		int y=f[x],z=f[f[x]];
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
	int p=st[tot--];
	if(!fa)
		root1=p;
	else
	{
		f[p]=fa;
		ch[fa][c]=p;
	}
	ch[p][0]=ch[p][1]=lazy2[p]=0;
	lazy1[p]=1001;
	s[p]=1;
	int mid=(l+r)>>1;
	sum[p]=val[p]=num[mid];
	maxl[p]=maxr[p]=val[p]>0?val[p]:0;
	maxm[p]=val[p];
	build(l,mid-1,p,0);
	build(mid+1,r,p,1);
	update(p);
}
int kth(int x)
{
	down(root);
	int p=root,now=s[ch[root][0]]+1;
	while(x^now)
	{
		down(p);
		if(x>now)
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
void insert()
{
	int pos,l,r,cnt;
	scanf("%d%d",&pos,&cnt);
	for(int i=1;i<=cnt;i++)
		scanf("%d",num+i);
	n+=cnt;
	l=kth(pos+1);
	r=kth(pos+2);
	splay(l,0);
	splay(r,l);
	build(1,cnt,0,0);
	f[root1]=r;
	ch[r][0]=root1;
	update(r);
	update(l);
}
void recycle(int p)
{
	if(!p)
		return;
	st[++tot]=p;
	recycle(ch[p][0]);
	recycle(ch[p][1]);
}
void del()
{
	int pos,l,r,cnt;
	scanf("%d%d",&pos,&cnt);
	n-=cnt;
	l=kth(pos);
	r=kth(pos+cnt+1);
	splay(l,0);
	splay(r,l);
	recycle(ch[r][0]);
	ch[r][0]=0;
	update(r);
	update(l);
}
void set()
{
	int pos,l,r,cnt,c;
	scanf("%d%d%d",&pos,&cnt,&c);
	l=kth(pos);
	r=kth(pos+cnt+1);
	splay(l,0);
	splay(r,l);
	int p=ch[r][0];
	val[p]=c;
	sum[p]=s[p]*c;
	maxl[p]=maxr[p]=c>0?sum[p]:0;
	maxm[p]=c>0?sum[p]:c;
	lazy1[p]=c;
	update(r);
	update(l);
}
void reverse()
{
	int pos,l,r,cnt;
	scanf("%d%d",&pos,&cnt);
	l=kth(pos);
	r=kth(pos+cnt+1);
	splay(l,0);
	splay(r,l);
	int p=ch[r][0];
	lazy2[p]^=1;
	swap(maxl[p],maxr[p]);
}
int getsum()
{
	int pos,l,r,cnt;
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
	return maxm[ch[r][0]];
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("splay.in","r",stdin);
	freopen("splay.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=500000;i++)
		st[++tot]=i;
	for(int i=1;i<=n;i++)
		scanf("%d",num+i);
	num[0]=num[n+1]=-10000;
	maxm[0]=0x80000000;
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