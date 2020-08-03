//2020.08.03
//luoguP2852 [USACO06DEC]Milk Patterns G 后缀数组+单调栈水过..
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k;
int s[20009];
int sa[20009],h[20009],rnk[20009];
void lsh()
{
	static int ss[20009];
	memcpy(ss,s,(n+1)*4);
	sort(ss+1,ss+n+1);
	int d=unique(ss+1,ss+n+1)-ss-1;
	for(int i=1;i<=n;i++)
		s[i]=lower_bound(ss+1,ss+d+1,s[i])-ss;
}
void getsa()
{
	static int buc[20009],p1[20009],p2[20009];
	int m=n,*x=p1,*y=p2;
	for(int i=1;i<=n;i++) buc[x[i]=s[i]]++;
	for(int i=1;i<=m;i++) buc[i]+=buc[i-1];
	for(int i=1;i<=n;i++) sa[buc[x[i]]--]=i;
	for(int d=1;d<=n;d<<=1)
	{
		int p=0;
		for(int i=n-d+1;i<=n;i++) y[++p]=i;
		for(int i=1;i<=n;i++)
			if(sa[i]>=d+1)
				y[++p]=sa[i]-d;
		memset(buc,0,(m+1)*4);
		for(int i=1;i<=n;i++) buc[x[i]]++;
		for(int i=1;i<=m;i++) buc[i]+=buc[i-1];
		for(int i=n;i>=1;i--) sa[buc[x[y[i]]]--]=y[i];
		p=0;
		swap(x,y);
		for(int i=1;i<=n;i++)
			x[sa[i]]=y[sa[i]]==y[sa[i-1]]&&y[sa[i]+d]==y[sa[i-1]+d]?p:++p;
		if((m=p)>=n)
			break;
	}
}
void geth()
{
	for(int i=1;i<=n;i++)
		rnk[sa[i]]=i;
	int p=0;
	for(int i=1;i<=n;i++)
	{
		if(p)
			p--;
		int j=sa[rnk[i]-1];
		while(s[i+p]==s[j+p])
			p++;
		h[rnk[i]]=p;
	}
}
void solve()
{
	static int st[20009],d[20009];
	int tp=0,ans=0;
	for(int i=1;i<=n;i++)
	{
		int sm=0;
		for(;tp&&h[st[tp]]>=h[i];tp--)
		{
			sm+=d[st[tp]];
			if(sm+1>=k)
				ans=max(ans,h[st[tp]]);
		}
		d[i]=sm+1,st[++tp]=i;
	}
	int sm=0;
	for(;tp;tp--)
	{
		sm+=d[st[tp]];
		if(sm+1>=k)
			ans=max(ans,h[st[tp]]);
	}
	printf("%d",ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("sam.in","r",stdin);
	freopen("sa.out","w",stdout);
#endif
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",s+i);
	lsh();
	getsa();
	geth();
	solve();
	return 0;
}