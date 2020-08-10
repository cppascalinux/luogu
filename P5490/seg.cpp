//2020.08.07
//luoguP5490 【模板】扫描线 扫描线+线段树..
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
using namespace std;
struct node
{
	int typ,x,y1,y2;
	bool operator<(const node &p)const{return x<p.x||(x==p.x&&typ<p.typ);}
};
node q[200009];
int n,d,tot;
int sv[200009];
int mn[800009],sm[800009],tl[800009],lz[800009];
void lsh()
{
	sort(sv+1,sv+n+1);
	d=unique(sv+1,sv+n+1)-sv-1;
	for(int i=1;i<=n;i++)
	{
		q[i].y1=lower_bound(sv+1,sv+d+1,q[i].y1)-sv;
		q[i].y2=lower_bound(sv+1,sv+d+1,q[i].y2)-sv;
	}
	tot=sv[d]-sv[1];
	// for(int i=1;i<=d;i++)
	// 	printf("i:%d sv:%d\n",i,sv[i]);
}
void upd(int a)
{
	int la=a<<1,ra=a<<1|1;
	mn[a]=min(mn[la],mn[ra]);
	sm[a]=0;
	if(mn[a]==mn[la])
		sm[a]+=sm[la];
	if(mn[a]==mn[ra])
		sm[a]+=sm[ra];
}
void dn(int a)
{
	int la=a<<1,ra=a<<1|1,&tv=lz[a];
	if(!tv)
		return;
	lz[la]+=tv,lz[ra]+=tv;
	mn[la]+=tv,mn[ra]+=tv;
	tv=0;
}
void build(int a,int l,int r)
{
	if(l==r)
		return sm[a]=tl[a]=sv[l+1]-sv[l],void();
	int mid=(l+r)>>1;
	build(a<<1,l,mid);
	build(a<<1|1,mid+1,r);
	upd(a);
}
void add(int a,int l,int r,int ll,int rr,int val)
{
	if(l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
		return mn[a]+=val,lz[a]+=val,void();
	dn(a);
	int mid=(l+r)>>1;
	add(a<<1,l,mid,ll,rr,val);
	add(a<<1|1,mid+1,r,ll,rr,val);
	upd(a);
}
void solve()
{
	sort(q+1,q+n+1);
	LL ans=0;
	for(int i=1;i<=n;i++)
	{
		int tp=q[i].typ,ql=q[i].y1,qr=q[i].y2;
		// printf("i:%d typ:%d y1:%d y2:%d\n",i,q[i].typ,q[i].y1,q[i].y2);
		// for(int i=1;i<=5;i++)
		// 	printf("a:%d mn:%d sm:%d tl:%d lz:%d\n",i,mn[i],sm[i],tl[i],lz[i]);
		int yl=tot;
		if(mn[1]==0)
			yl-=sm[1];
		// printf("tot:%d sm1:%d yl:%d\n",tot,sm[1],yl);
		ans+=(LL)(q[i].x-q[i-1].x)*yl;
		add(1,1,d-1,ql,qr-1,tp*2-1);
	}
	printf("%lld",ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("seg.in","r",stdin);
	freopen("seg.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1,x1,y1,x2,y2;i<=n;i++)
	{
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		sv[i*2-1]=y1,sv[i*2]=y2;
		q[i*2-1]=node{1,x1,y1,y2};
		q[i*2]=node{0,x2,y1,y2};
	}
	n<<=1;
	lsh();
	build(1,1,d-1);
	solve();
	return 0;
}