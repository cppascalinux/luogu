#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const ll inf=0x7FFFFFFFFFFFFFFF;
int n;
struct node
{
	ll x,y;
}p[200010],p1[200010];
bool cmp1(node a,node b)
{
	return a.x<b.x;
}
bool cmp2(node a,node b)
{
	return a.y<b.y;
}
ll getl(node a,node b)
{
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
ll solve(int l,int r)
{
	if(l==r)
		return inf;
	int m=(l+r)>>1,tot=0;
	ll lm,rm,d,minn;
	lm=solve(l,m);
	rm=solve(m+1,r);
	d=min(lm,rm);
	minn=d;
	for(int i=l;i<=r;i++)
		if((p[i].x-p[m].x)*(p[i].x-p[m].x)<=d)
			p1[++tot]=p[i];
	sort(p1+1,p1+tot+1,cmp2);
	for(int i=1;i<tot;i++)
		for(int j=i+1;j<=tot&&(p1[i].y-p1[j].y)*(p1[i].y-p1[j].y)<=d;j++)
			minn=min(minn,getl(p1[i],p1[j]));
	return minn;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("points.in","r",stdin);
	freopen("points.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&p[i].x,&p[i].y);
	sort(p+1,p+n+1,cmp1);
	printf("%.4lf",sqrt(solve(1,n)));
	return 0;
}