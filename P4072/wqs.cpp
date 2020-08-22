//2020.08.20
//luoguP4072 [SDOI2016]征途 斜率优化+wqs二分
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x7F7F7F7F7F7F7F7FLL;
#define LL long long
using namespace std;
struct node
{
	int x,v;
	LL y;
};
int n,m;
int s[3009],sm[3009];
node q[3009];
LL mul(node a,node b,node c)
{
	return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
node solve(int adv)
{
	int tp=1,cur=1;
	q[1]=node{0,0,0};
	for(int i=1;i<=n;i++)
	{
		while(cur<tp&&2LL*sm[i]*(q[cur+1].x-q[cur].x)>=q[cur+1].y-q[cur].y)
			cur++;
		LL cf=q[cur].y-2LL*sm[i]*q[cur].x+(LL)sm[i]*sm[i]+adv;
		int cg=q[cur].v+1;
		if(i==n)
			return node{sm[i],cg,cf};
		node nq{sm[i],cg,cf+(LL)sm[i]*sm[i]};
		while(tp>1&&mul(q[tp-1],q[tp],nq)<=0)
			tp--;
		q[++tp]=nq;
		cur=min(cur,tp);
	}
}
LL bin()
{
	int l=0,r=1000000000;
	LL ans=0;
	while(l<r)
	{
		int mid=(l+r)>>1;
		node t=solve(mid);
		// printf("l:%d r:%d mid:%d t.v:%d t.x:%d t.y:%lld\n",l,r,mid,t.v,t.x,t.y);
		ans=max(ans,t.y-(LL)mid*m);
		if(t.v<=m)
			r=mid;
		else
			l=mid+1;
	}
	// printf("l:%d\n",l);
	node t=solve(l);
	ans=max(ans,t.y-(LL)l*m);
	// printf("t.v:%d t.y:%lld\n",t.v,t.y);
	return ans;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("march.in","r",stdin);
	freopen("wqs.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",s+i),sm[i]=sm[i-1]+s[i];
	LL ans=m*bin()-(LL)sm[n]*sm[n];
	printf("%lld",ans);
	return 0;
}