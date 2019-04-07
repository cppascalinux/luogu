#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
#define rc register char
#define lb(x) (x&-x)
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000010];
int n,k,tot;
int ans[100010],sum[100010];
int c[200010];
struct node
{
	int x,y,z,id;
	bool operator == (const node &o) const
	{
		return x==o.x&&y==o.y&&z==o.z;
	}
}p[100010],tmp[100010];
void read(int &x)
{
	rc ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch&15),ch=gc();
}
bool cmp1(const node &a,const node &b)
{
	return a.x<b.x||(a.x==b.x&&a.y<b.y)||(a.x==b.x&&a.y==b.y&&a.z<b.z);
}
void add(int x,int val)
{
	for(rg i=x;i<=k;i+=lb(i))
		c[i]+=val;
}
int ask(int x)
{
	rg val=0;
	for(rg i=x;i;i-=lb(i))
		val+=c[i];
	return val;
}
void solve(int l,int r)
{
	if(l==r)
		return;
	rg mid=(l+r)>>1;
	solve(l,mid);
	solve(mid+1,r);
	rg j=l-1,pt=l-1;
	for(rg i=mid+1;i<=r;i++)
	{
		while(j+1<=mid&&p[j+1].y<=p[i].y)
		{
			tmp[++pt]=p[++j];
			add(p[j].z,1);
		}
		tmp[++pt]=p[i];
		ans[p[i].id]+=ask(p[i].z);
	}
	for(rg i=l;i<=j;i++)
		add(p[i].z,-1);
	while(j+1<=mid)
		tmp[++pt]=p[++j];
	for(rg i=l;i<=r;i++)
		p[i]=tmp[i];
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("cdq.out","w",stdout);
	#endif
	read(n);
	read(k);
	for(rg i=1;i<=n;i++)
	{
		read(p[i].x);
		read(p[i].y);
		read(p[i].z);
		p[i].id=i;
	}
	sort(p+1,p+n+1,cmp1);
	int l=n;
	for(rg i=n;i>=1;i--)
	{
		if(p[i]==p[i+1])
		{
			ans[p[i].id]+=l-i;
		}
		else
			l=i;
	}
	solve(1,n);
	for(rg i=1;i<=n;i++)
		sum[ans[i]]++;
	for(rg i=0;i<=n-1;i++)
		printf("%d\n",sum[i]);
	return 0;
}