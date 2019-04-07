#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,ans,d;
int l[1200010],r[1200010],sum[1200010],lazy[1200010];
char s[10];
void build(int a,int ll,int rr)
{
	l[a]=ll;
	r[a]=rr;
	if(ll^rr)
	{
		int mid=(ll+rr)>>1;
		build(a<<1,ll,mid);
		build(a<<1|1,mid+1,rr);
	}
}
void down(int a)
{
	if(lazy[a])
	{
		lazy[a]=sum[a<<1]=sum[a<<1|1]=0;
		lazy[a<<1]=lazy[a<<1|1]=1;
	}
}
void add(int a,int x,int num)
{
	if(x>r[a]||x<l[a])
		return;
	sum[a]+=num;
	if(l[a]^r[a])
	{
		down(a);
		add(a<<1,x,num);
		add(a<<1|1,x,num);
	}
}
void set(int a,int ll,int rr)
{
	if(l[a]>rr||r[a]<ll)
		return;
	if(l[a]>=ll&&r[a]<=rr)
	{
		sum[a]=0;
		lazy[a]=1;
		return;
	}
	down(a);
	set(a<<1,ll,rr);
	set(a<<1|1,ll,rr);
	sum[a]=sum[a<<1]+sum[a<<1|1];
}
int ask(int a,int ll,int rr)
{
	if(l[a]>rr||r[a]<ll)
		return 0;
	if(l[a]>=ll&&r[a]<=rr)
		return sum[a];
	down(a);
	return ask(a<<1,ll,rr)+ask(a<<1|1,ll,rr);
}
int query(int x)
{
	int a=1;
	while(l[a]^r[a])
	{
		if(x>sum[a<<1])
		{
			x-=sum[a<<1];
			a=a<<1|1;
		}
		else
			a=a<<1;
	}
	return l[a];
}
void upd()
{
	ans+=ask(1,1,m-1);
	set(1,1,m-1);
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	int a;
	build(1,1,300001);
	d+=100001;
	m+=100001;
	for(int i=1;i<=n;i++)
	{
		scanf("%s%d",s,&a);
		if(s[0]=='I')
		{
			a+=d;
			if(a>=m)
				add(1,a,1);
		}
		else if(s[0]=='A')
		{
			m-=a;
			d-=a;
		}
		else if(s[0]=='S')
		{
			m+=a;
			d+=a;
			upd();
		}
		else if(s[0]=='F')
		{
			if(a>sum[1])
				printf("-1\n");
			else
				printf("%d\n",query(sum[1]-a+1)-d);
		}
	}
	printf("%d",ans);
	return 0;
}