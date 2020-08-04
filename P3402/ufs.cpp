//2020.08.04
//luoguP3402 可持久化并查集 就用主席树维护可持久化数组然后按秩合并就行..O(nlog^2n)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define FL() fflush(stdout)
#define PII pair<int,int>
#define FI first
#define SE second
using namespace std;
int n,m,tot,lst;
int rt[200009],lp[8000009],rp[8000009],f[8000009],h[8000009];
void build(int &a,int l,int r)
{
	a=++tot;
	if(l==r)
		return f[a]=l,h[a]=1,void();
	int mid=(l+r)>>1;
	build(lp[a],l,mid);
	build(rp[a],mid+1,r);
}
void add(int &a,int l,int r,int p,int vf,int vh)
{
	if(a<=lst)
	{
		int b=++tot;
		lp[b]=lp[a],rp[b]=rp[a],f[b]=f[a],h[b]=h[a];
		a=b;
	}
	if(l==r)
		return (vf&&(f[a]=vf)),(h[a]+=vh),void();
	int mid=(l+r)>>1;
	if(p<=mid)
		add(lp[a],l,mid,p,vf,vh);
	else
		add(rp[a],mid+1,r,p,vf,vh);
}
PII ask(int a,int l,int r,int p)
{
	if(l==r)
		return PII(f[a],h[a]);
	int mid=(l+r)>>1;
	if(p<=mid)
		return ask(lp[a],l,mid,p);
	else
		return ask(rp[a],mid+1,r,p);
}
PII fnd(int num,int x)
{
	PII t=ask(rt[num],1,n,x);
	// printf("x:%d t:%d\n",x,t.FI),FL();
	if(x==t.FI)
		return t;
	return fnd(num,t.FI);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("ufs.in","r",stdin);
	freopen("ufs.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	build(rt[0],1,n);
	for(int i=1,a,b,c;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		rt[i]=rt[i-1],lst=tot;
		// printf("i:%d\n",i);
		// fflush(stdout);
		if(a==1)
		{
			scanf("%d",&c);
			PII fb=fnd(i,b),fc=fnd(i,c);
			if(fb.FI==fc.FI)
				continue;
			if(fb.SE<fc.SE)
				swap(fb,fc);
			add(rt[i],1,n,fc.FI,fb.FI,0);
			if(fb.SE==fc.SE)
				add(rt[i],1,n,fb.FI,0,1);
		}
		else if(a==2)
			rt[i]=rt[b];
		else
		{
			scanf("%d",&c);
			PII fb=fnd(i,b),fc=fnd(i,c);
			printf("%d\n",fb.FI==fc.FI);
		}
	}
	return 0;
}