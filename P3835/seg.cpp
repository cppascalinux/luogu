//2019.06.25
//luogu P3835 可持久化平衡树 直接拿可持久化线段树写写试试qwq
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define m 1000000001
#define inf 0x7FFFFFFF
using namespace std;
int n,cnt;
int rt[500009];
int lp[20000009],rp[20000009],sz[20000009];
int cln(int x)
{
	int y=++cnt;
	lp[y]=lp[x],rp[y]=rp[x],sz[y]=sz[x];
	return y;
}
void add(int lst,int &a,int l,int r,int pos,int val)
{
	if(a<=lst)
		a=cln(a);
	sz[a]+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		add(lst,lp[a],l,mid,pos,val);
	else
		add(lst,rp[a],mid+1,r,pos,val);
}
int fnd(int a,int l,int r,int pos)
{
	if(l==r)
		return sz[a]>0;
	int mid=(l+r)>>1;
	if(pos<=mid)
		return fnd(lp[a],l,mid,pos);
	return fnd(rp[a],mid+1,r,pos);
}
int rnk(int a,int l,int r,int val)
{
	if(l==r||!a)
		return 1;
	int mid=(l+r)>>1;
	if(val<=mid)
		return rnk(lp[a],l,mid,val);
	return rnk(rp[a],mid+1,r,val)+sz[lp[a]];
}
int kth(int a,int l,int r,int k)
{
	if(l==r)
		return l;
	int lsz=sz[lp[a]],mid=(l+r)>>1;
	if(k<=lsz)
		return kth(lp[a],l,mid,k);
	return kth(rp[a],mid+1,r,k-lsz);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("seg.in","r",stdin);
	freopen("seg.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1,a,b,c;i<=n;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		rt[i]=rt[a];
		if(b==1)
			add(cnt,rt[i],-m,m,c,1);
		else if(b==2)
		{
			if(fnd(rt[i],-m,m,c))
				add(cnt,rt[i],-m,m,c,-1);
		}
		else if(b==3)
			printf("%d\n",rnk(rt[i],-m,m,c));
		else if(b==4)
			printf("%d\n",kth(rt[i],-m,m,c));
		else if(b==5)
		{
			int v=kth(rt[i],-m,m,rnk(rt[i],-m,m,c)-1);
			printf("%d\n",v==-m?-inf:(v==m?inf:v));
		}
		else if(b==6)
		{
			int v=kth(rt[i],-m,m,rnk(rt[i],-m,m,c+1));
			printf("%d\n",v==-m?-inf:(v==m?inf:v));
		}
	}
	return 0;
}