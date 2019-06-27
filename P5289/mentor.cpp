//2019.06.27
//luoguP5289 [十二省联考2019]皮配 首先考虑一个暴力:fijk表示前i个学校中,选了j个蓝阵营,k个鸭派系的方案,显然可以O(nm^2)dp
//然后考虑k=0的时候怎么做,发现阵营和派系相互独立,因此可以分别dp,最后直接乘起来
//考虑k>0的时候怎么做,可以先将所有的没有限制的城市和学校按k=0的做一遍,然后hijk表示前i个有限制的城市,城市内部所有学校有j学生个选择蓝阵营,
//有限制的学校中有k个选择鸭派系的方案数,这个可以枚举有限制的城市的阵营和有限制的学校的派系O(km^2)dp,最后再和k=0的合并,用前缀和优化,总复杂度O(nm+km^2)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define li long long
#define mod 998244353
#define pb push_back
using namespace std;
int n,m,q,c0,c1,d0,d1,mxm,sm,mx1,mx2;
int bl[1009],s[1009];
vector<int> ct[1009];
int smc[1009],smbn[1009];
int hts[1009],htc[1009];
int f[2509],g[2509];//zhenying, paixi
int h[2][2509][2509];
void clr()
{
	for(int i=1;i<=m;i++)
		ct[i].clear();
	memset(smc,0,sizeof(smc));
	memset(smbn,0,sizeof(smbn));
	memset(hts,0,sizeof(hts));
	memset(htc,0,sizeof(htc));
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	memset(h,0,sizeof(h));
	mxm=sm=mx1=mx2=0;
}
void init1()
{
	f[0]=1;
	int mx=0;
	for(int i=1;i<=m;i++)
		if(smc[i]&&!htc[i])
		{
			mx=min(mx+smc[i],mxm);
			for(int j=mx;j>=smc[i];j--)
				f[j]=(f[j]+f[j-smc[i]])%mod;
		}
	for(int i=1;i<=mxm;i++)
		f[i]=(f[i-1]+f[i])%mod;
	g[0]=1;
	mx=0;
	for(int i=1;i<=n;i++)
		if(!hts[i])
		{
			mx=min(mx+s[i],mxm);
			for(int j=mx;j>=s[i];j--)
				g[j]=(g[j]+g[j-s[i]])%mod;
		}
	for(int i=1;i<=mxm;i++)
		g[i]=(g[i-1]+g[i])%mod;
}
void init2()
{
	h[0][0][0]=1;
	for(int i=1;i<=m;i++)
		if(htc[i]&&smc[i])
		{
			mx1=min(mx1+smc[i],mxm);
			mx2=min(mx2+smbn[i],mxm);
			for(int j=0;j<=mx1;j++)
				for(int k=0;k<=mx2;k++)
					h[1][j][k]=h[0][j][k];
			for(int j=mx1;j>=0;j--)
				for(int k=0;k<=mx2;k++)
					h[0][j][k]=j>=smc[i]?h[0][j-smc[i]][k]:0;
			for(int j=0;j<(int)ct[i].size();j++)
			{
				int x=ct[i][j],cl=hts[x]-1,v=s[x];
				for(int k=0;k<=mx1;k++)
					for(int l=mx2;l>=0;l--)
					{
						h[0][k][l]=((cl!=1?h[0][k][l]:0)+(cl!=0&&l>=v?h[0][k][l-v]:0))%mod;
						h[1][k][l]=((cl!=3?h[1][k][l]:0)+(cl!=2&&l>=v?h[1][k][l-v]:0))%mod;
					}
			}
			for(int j=0;j<=mx1;j++)
				for(int k=0;k<=mx2;k++)
					h[0][j][k]=(h[0][j][k]+h[1][j][k])%mod;
		}
}
void solve()
{
	int ans=0;
	for(int i=0;i<=mx1;i++)
		for(int j=0;j<=mx2;j++)
		{
			int lp=max(sm-c1-i,0),rp=c0-i;
			if(lp>rp)
				continue;
			int sm1=f[rp];
			if(lp)
				sm1=(sm1+mod-f[lp-1])%mod;
			lp=max(sm-d1-j,0),rp=d0-j;
			if(lp>rp)
				continue;
			int sm2=g[rp];
			if(lp)
				sm2=(sm2+mod-g[lp-1])%mod;
			ans=(ans+(li)h[0][i][j]*sm1%mod*sm2)%mod;
		}
	// int lp=max(sm-c1,0),rp=c0;
	// int sm1=lp>rp?0:(f[rp]+mod-(lp>0?f[lp-1]:0))%mod;
	// lp=max(sm-d1,0),rp=d0;
	// int sm2=lp>rp?0:(g[rp]+mod-(lp>0?g[lp-1]:0))%mod;
	// ans=(li)sm1*sm2%mod;
	// for(int i=max(sm-c1,0);i<=c0;i++)
	// 	for(int j=max(sm-d1,0);j<=d0;j++)
	// 		ans=(ans+(li)f[i]*g[j])%mod;
	printf("%d\n",ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("mentor.in","r",stdin);
	freopen("mentor.out","w",stdout);
#endif
	int ptt=0;
	scanf("%d",&ptt);
	while(ptt--)
	{
		scanf("%d%d",&n,&m);
		scanf("%d%d%d%d",&c0,&c1,&d0,&d1);
		mxm=max(max(c0,c1),max(d0,d1));
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",bl+i,s+i);
			smc[bl[i]]+=s[i];
			sm+=s[i];
		}
		scanf("%d",&q);
		for(int i=1,a,b;i<=q;i++)
		{
			scanf("%d%d",&a,&b);
			hts[a]=b+1;
			ct[bl[a]].pb(a);
			smbn[bl[a]]+=s[a];
			htc[bl[a]]=1;
		}
		init1();
		init2();
		solve();
		clr();
	}
	return 0;
}