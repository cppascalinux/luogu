//2020.08.11
//luoguP1712 [NOI2016]区间 把所有区间排序,然后双指针扫描,用线段树维护区间max(不难证明合法性关于左右端点的位置单调)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 0x7F7F7F7F
using namespace std;
int sv[1000009];
struct seg
{
	int l,r;
	bool operator<(const seg &p)const{return sv[r]-sv[l]<sv[p.r]-sv[p.l];}
};
int n,m,tot,d;
seg s[500009];
int mx[4000009],lz[4000009];
void lsh()
{
	int tp=0;
	for(int i=1;i<=n;i++)
		sv[++tp]=s[i].l,sv[++tp]=s[i].r+1;
	sort(sv+1,sv+tp+1);
	d=unique(sv+1,sv+tp+1)-sv-1;
	for(int i=1;i<=n;i++)
	{
		s[i].l=lower_bound(sv+1,sv+d+1,s[i].l)-sv;
		s[i].r=lower_bound(sv+1,sv+d+1,s[i].r+1)-sv;
	}
	// for(int i=1;i<=d;i++)
	// 	printf("i:%d sv:%d\n",i,sv[i]);
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d sl:%d sr:%d\n",i,sv[s[i].l],sv[s[i].r]);
}
void dn(int a)
{
	int la=a<<1,ra=a<<1|1,&v=lz[a];
	if(!v)
		return;
	lz[la]+=v,lz[ra]+=v;
	mx[la]+=v,mx[ra]+=v;
	v=0;
}
void add(int a,int l,int r,int ll,int rr,int val)
{
	if(l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
		return lz[a]+=val,mx[a]+=val,void();
	dn(a);
	int mid=(l+r)>>1;
	add(a<<1,l,mid,ll,rr,val);
	add(a<<1|1,mid+1,r,ll,rr,val);
	mx[a]=max(mx[a<<1],mx[a<<1|1]);
}
void solve()
{
	sort(s+1,s+n+1);
	int ans=INF;
	for(int i=1,lp=1;i<=n;i++)
	{
		add(1,1,d,s[i].l,s[i].r-1,1);
		while(lp<=i&&mx[1]>=m)
		{
			ans=min(ans,(sv[s[i].r]-sv[s[i].l])-(sv[s[lp].r]-sv[s[lp].l]));
			add(1,1,d,s[lp].l,s[lp].r-1,-1);
			lp++;
		}
	}
	printf("%d",ans==INF?-1:ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("seg.in","r",stdin);
	freopen("seg.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&s[i].l,&s[i].r);
	lsh();
	solve();
	return 0;
}