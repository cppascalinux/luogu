//2019.04.16
//luoguP4094 [HEOI2016/TJOI2016]字符串 后缀数组+主席树+主席树上二分
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,tot;
char s[100009];
int sa[100009],c[100009],t1[100009],t2[100009],h[100009],rnk[100009];
int mn[19][100009],ln[100009];
int rt[100009],lp[2000009],rp[2000009],sm[2000009];
void getsa()
{
	int m=26,*x=t1,*y=t2;
	for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
	for(int i=1;i<=m;i++) c[i]+=c[i-1];
	for(int i=1;i<=n;i++) sa[c[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int p=0;
		for(int i=n-k+1;i<=n;i++)
			y[++p]=i;
		for(int i=1;i<=n;i++)
			if(sa[i]>k)
				y[++p]=sa[i]-k;
		memset(c+1,0,m<<2);
		for(int i=1;i<=n;i++) c[x[i]]++;
		for(int i=1;i<=m;i++) c[i]+=c[i-1];
		for(int i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i];
		p=0;
		for(int i=1;i<=n;i++)
			y[sa[i]]=x[sa[i]]==x[sa[i-1]]&&x[sa[i]+k]==x[sa[i-1]+k]?p:++p;
		swap(x,y);
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
		int np=sa[rnk[i]-1];
		while(s[i+p]==s[np+p])
			p++;
		h[rnk[i]]=p;
	}
}
void initlcp()
{
	for(int i=1;i<=n;i++)
		mn[0][i]=h[i];
	for(int k=1;k<=17;k++)
		for(int i=1;i<=n-(1<<k)+1;i++)
			mn[k][i]=min(mn[k-1][i],mn[k-1][i+(1<<k-1)]);
	for(int i=2;i<=n;i++)
		ln[i]=ln[i>>1]+1;
	// for(int k=0;k<=17;k++)
	// {
	// 	printf("k:%d-------------\n\t",k);
	// 	for(int i=1;i<=n;i++)
	// 		printf("%d ",mn[k][i]);
	// 	printf("\n");
	// }
}
int getlcp(int a,int b)
{
	// printf("sta:%d stb:%d\n",a,b);
	if(a>b)
		swap(a,b);
	if(a==b)
		return n-sa[a]+1;
	a++;
	int l=ln[b-a+1];
	// printf("eda:%d edb:%d l:%d ans:%d\n",a,b,l,min(mn[l][a],mn[l][b-(1<<l)+1]));
	return min(mn[l][a],mn[l][b-(1<<l)+1]);
}
void add(int &a,int l,int r,int pos)
{
	int p=a;
	a=++tot;
	sm[a]=sm[p]+1,lp[a]=lp[p],rp[a]=rp[p];
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		add(lp[a],l,mid,pos);
	else
		add(rp[a],mid+1,r,pos);
}
int getr(int al,int ar,int l,int r,int pos)
{
	if(l==r)
		return 1;
	int sml=sm[lp[ar]]-sm[lp[al]];
	// printf("sml:%d\n",sml);
	int mid=(l+r)>>1;
	if(pos<=mid)
		return getr(lp[al],lp[ar],l,mid,pos);
	return getr(rp[al],rp[ar],mid+1,r,pos)+sml;
}
int fndk(int al,int ar,int l,int r,int kth)
{
	if(l==r)
		return l;
	int sml=sm[lp[ar]]-sm[lp[al]];
	int mid=(l+r)>>1;
	if(kth<=sml)
		return fndk(lp[al],lp[ar],l,mid,kth);
	return fndk(rp[al],rp[ar],mid+1,r,kth-sml);
}
void build()
{
	for(int i=1;i<=n;i++)
	{
		rt[i]=rt[i-1];
		// printf("rnk:%d\n",rnk[i]);
		add(rt[i],0,n+1,rnk[i]);
	}
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d sm:%d\n",i,sm[rt[i]]);
}
int cal(int lp,int rp,int std)
{
	int ans=0;
	int rnk=getr(rt[lp-1],rt[rp],0,n+1,std);
	// printf("lp:%d rp:%d std:%d rnk1:%d ",lp,rp,std,rnk);
	if(rnk>1)
	{
		int pre=fndk(rt[lp-1],rt[rp],0,n+1,rnk-1);
		// printf("pre:%d ",pre);
		ans=max(ans,getlcp(std,pre));
	}
	// printf("rnk2:%d ",rnk);
	if(rnk<=rp-lp+1)
	{
		int nxt=fndk(rt[lp-1],rt[rp],0,n+1,rnk);
		// printf("nxt:%d ",nxt);
		ans=max(ans,getlcp(std,nxt));
	}
	// printf("\n");
	return ans;
}
int solve(int a,int b,int c,int d)
{
	int l=0,r=min(b-a+1,d-c+1);
	while(l<r)
	{
		int mid=(l+r+1)>>1;
		if(cal(a,b-mid+1,rnk[c])>=mid)
			l=mid;
		else
			r=mid-1;
	}
	return l;
}
void dbg()
{
	for(int i=1;i<=n;i++)
		printf("i:%d sa:%d h:%d\n",i,sa[i],h[i]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sa.in","r",stdin);
	freopen("sa.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
		s[i]-='a'-1;
	getsa();
	geth();
	// dbg();
	initlcp();
	build();
	for(int i=1,a,b,c,d;i<=m;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		printf("%d\n",solve(a,b,c,d));
	}
	return 0;
}