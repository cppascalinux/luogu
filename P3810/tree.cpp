#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k,tot;
int root[800010];
int lp[31010010],rp[31010010],sum[31010010];
int ans[100010],out[100010];
int st[100010],top;
struct node
{
	int x,y,z;
	bool operator < (const node &o) const
	{
		return x<o.x||(x==o.x&&y<o.y)||(x==o.x&&y==o.y&&z<o.z);
	}
	bool operator == (const node &o) const
	{
		return x==o.x&&y==o.y&&z==o.z;
	}
}q[100010];
void insert(int a,int l,int r,int x,int val)
{
	sum[a]+=val;
	if(l^r)
	{
		int mid=(l+r)>>1;
		if(x<=mid)
		{
			if(!lp[a])
				lp[a]=++tot;
			insert(lp[a],l,mid,x,val);
		}
		else
		{
			if(!rp[a])
				rp[a]=++tot;
			insert(rp[a],mid+1,r,x,val);
		}
	}
}
void add(int a,int l,int r,int x,int y,int val)
{
	if(!root[a])
		root[a]=++tot;
	insert(root[a],0,k,y,val);
	if(l^r)
	{
		int mid=(l+r)>>1;
		if(x<=mid)
			add(a<<1,l,mid,x,y,val);
		else
			add(a<<1|1,mid+1,r,x,y,val);
	}
}
int ask(int a,int l,int r,int x)
{
	if(l==r||!a)
		return 0;
	int mid=(l+r)>>1;
	if(x<=mid)
		return ask(lp[a],l,mid,x);
	return sum[lp[a]]+ask(rp[a],mid+1,r,x);
}
int get(int a,int l,int r,int x,int y)
{
	if(l==r)
		return 0;
	int mid=(l+r)>>1;
	if(x<=mid)
		return get(a<<1,l,mid,x,y);
	return ask(root[a<<1],0,k,y)+get(a<<1|1,mid+1,r,x,y);
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	#endif
	scanf("%d%d",&n,&k);
	k++;
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&q[i].x,&q[i].y,&q[i].z);
	sort(q+1,q+n+1);
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d x:%d y:%d z:%d\n",i,q[i].x,q[i].y,q[i].z);
	int l=0;
	for(int i=1;i<=n;i++)
	{
		if(!(q[i]==q[l]))
		{
			for(int j=l;j<=i-1;j++)
			{
				int t=get(1,0,k,q[j].y+1,q[j].z+1);
				ans[t]++;
			}
			l=i;
		}
		add(1,0,k,q[i].y,q[i].z,1);
	}
	for(int i=l;i<=n;i++)
	{
		int t=get(1,0,k,q[i].y+1,q[i].z+1);
		ans[t]++;
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}