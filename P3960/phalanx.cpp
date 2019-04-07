#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define long long long
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000010];
int n,m,q,tot,lastv;
int root[300010],lp[12000010],rp[12000010],s[12000010];
long num[12000010];
int siz[2400010];
long val[2400010];
int last[300010];
#define get(a,b) (max(min(b,m-1)-a+1,0))
void read(int &x)
{
	// rc ch=0;
	// x=0;
	// while(ch<'0'||ch>'9')
	// 	ch=gc();
	// while(ch>='0'&&ch<='9')
	// 	x=(x<<1)+(x<<3)+(ch&15),ch=gc();
	scanf("%d",&x);
}
void add(int &a,int l,int r,int pos,int x,long y)
{
	if(!a)
	{
		a=++tot;
		s[a]=get(l,r);
	}
	s[a]+=x;
	if(l==r)
		num[a]=y;
	else
	{
		int mid=(l+r)>>1;
		if(pos<=mid)
			add(lp[a],l,mid,pos,x,y);
		else
			add(rp[a],mid+1,r,pos,x,y);
	}
}
int kth(int &a,int l,int r,int x,int c,int &pos)
{
	if(!a)
	{
		a=++tot;
		s[a]=get(l,r);
		if(l==r&&l<=m-1)
			num[a]=(long)m*(c-1)+l;
	}
	if(l==r)
	{
		pos=l;
		return a;
	}
	int mid=(l+r)>>1;
	int ls=lp[a]?s[lp[a]]:get(l,mid);
	if(x<=ls)
		return kth(lp[a],l,mid,x,c,pos);
	return kth(rp[a],mid+1,r,x-ls,c,pos);
}
void build(int a,int l,int r)
{
	siz[a]=min(r,n)-l+1;
	siz[a]=max(siz[a],0);
	// printf("a:%d siz:%d\n",a,siz[a]);
	if(l==r)
	{
		if(l<=n)
			val[a]=(long)m*l;
		// printf("a:%d val:%d\n",a,val[a]);
	}
	else
	{
		int mid=(l+r)>>1;
		build(a<<1,l,mid);
		build(a<<1|1,mid+1,r);
	}
}
void set(int a,int l,int r,int pos,int x,long y)
{
	siz[a]+=x;
	if(l==r)
		val[a]=y;
	else
	{
		int mid=(l+r)>>1;
		if(pos<=mid)
			set(a<<1,l,mid,pos,x,y);
		else
			set(a<<1|1,mid+1,r,pos,x,y);
	}
}
int findkth(int a,int l,int r,int x,int &pos)
{
	if(l==r)
	{
		pos=l;
		return a;
	}
	else
	{
		int mid=(l+r)>>1;
		int ls=siz[a<<1];
		if(x<=ls)
			return findkth(a<<1,l,mid,x,pos);
		return findkth(a<<1|1,mid+1,r,x-ls,pos);
	}
}
long solve(int x,int y)
{
	if(y==m)
	{
		int pos;
		int t=findkth(1,1,n+q,x,pos);
		set(1,1,n+q,pos,-1,val[t]);
		lastv++;
		set(1,1,n+q,lastv,1,val[t]);
		// printf("pos:%d t:%d\n",pos,val[t]);
		return val[t];
	}
	int post,postmp;
	int t=findkth(1,1,n+q,x,post);
	int tmp=kth(root[x],1,m+q,y,x,postmp);
	// printf("post:%d postmp:%d t:%d tmp:%d\n",post,postmp,val[t],num[tmp]);
	set(1,1,n+q,post,-1,val[t]);
	lastv++;
	set(1,1,n+q,lastv,1,num[tmp]);
	add(root[x],1,m+q,postmp,-1,num[tmp]);
	last[x]++;
	add(root[x],1,m+q,last[x],1,val[t]);
	return num[tmp];
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("phalanx.in","r",stdin);
	freopen("phalanx.out","w",stdout);
	#endif
	read(n);
	read(m);
	read(q);
	build(1,1,n+q);
	lastv=n;
	for(rg i=1;i<=n;i++)
		last[i]=m-1;
	for(rg i=1;i<=q;i++)
	{
		rg a,b;
		read(a);
		read(b);
		printf("%lld\n",solve(a,b));
	}
	return 0;
}