#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define update(x) cnt[x]=cnt[lp[x]]+cnt[rp[x]];
#define inf 10000000
using namespace std;
int n,tot=1;
int cnt[3000010],lp[3000010],rp[3000010];
void add(int a,int l,int r,int x,int val)
{
	cnt[a]+=val;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(x<=mid)
	{
		if(!lp[a])
			lp[a]=++tot;
		add(lp[a],l,mid,x,val);
	}
	else
	{
		if(!rp[a])
			rp[a]=++tot;
		add(rp[a],mid+1,r,x,val);
	}
}
int rank(int a,int l,int r,int x)
{
	if(l==r||!a)
		return 1;
	int mid=(l+r)>>1;
	if(x<=mid)
		return rank(lp[a],l,mid,x);
	else
		return cnt[lp[a]]+rank(rp[a],mid+1,r,x);
}
int kth(int a,int l,int r,int x)
{
	if(l==r)
		return l;
	int suml=cnt[lp[a]];
	int mid=(l+r)>>1;
	if(x<=suml)
		return kth(lp[a],l,mid,x);
	else
		return kth(rp[a],mid+1,r,x-suml);
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("treap.in","r",stdin);
	freopen("seg.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		if(a==1)
			add(1,-inf,inf,b,1);
		else if(a==2)
			add(1,-inf,inf,b,-1);
		else if(a==3)
			printf("%d\n",rank(1,-inf,inf,b));
		else if(a==4)
			printf("%d\n",kth(1,-inf,inf,b));
		else if(a==5)
		{
			int t=rank(1,-inf,inf,b);
			printf("%d\n",kth(1,-inf,inf,t-1));
		}
		else if(a==6)
		{
			int t=rank(1,-inf,inf,b+1);
			printf("%d\n",kth(1,-inf,inf,t));
		}
	}
	return 0;
}