//2020.08.01
//luoguP6139 【模板】广义后缀自动机（广义 SAM）拿后缀数组水一水...
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
using namespace std;
int n;
char s[2000009],ts[1000009];
int sa[2000009],ar1[2000009],ar2[2000009],buc[2000009],rnk[2000009];
int h[2000009],lm[2000009];
void getsa()
{
	int m=127,*x=ar1,*y=ar2;
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
		memset(buc,0,(m+1)<<2);
		for(int i=1;i<=n;i++) buc[x[i]]++;
		for(int i=1;i<=m;i++) buc[i]+=buc[i-1];
		for(int i=n;i>=1;i--) sa[buc[x[y[i]]]--]=y[i];
		p=0;
		swap(x,y);
		for(int i=1;i<=n;i++)
			x[sa[i]]=y[sa[i]]==y[sa[i-1]]&&y[sa[i]+d]==y[sa[i-1]+d]?p:++p;
		if((m=p)==n)
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
	for(int i=n;i>=1;i--)
		lm[i]=s[i]=='#'?i:lm[i+1];
	LL ans=0;
	for(int i=1;i<=n;i++)
	{
		int l=sa[i]+h[i];
		int r=lm[sa[i]]-1;
		ans+=max(0,r-l+1);
		// printf("%s ",s+sa[i]);
		// printf("h:%d l:%d r:%d\n",h[i],l,r);
	}
	printf("%lld",ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("sa.in","r",stdin);
	freopen("sa.out","w",stdout);
#endif
	scanf("%d",&n);
	int tn=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",ts+1);
		int l=strlen(ts+1);
		for(int j=1;j<=l;j++)
			s[++tn]=ts[j];
		s[++tn]='#';
	}
	n=tn;
	getsa(),geth();
	// printf("s:%s\n",s+1);
	solve();
	return 0;
}