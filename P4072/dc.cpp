//2020.08.20
//luoguP4072 [SDOI2016]征途 写个dp决策单调性分治试试qwq...O(nmlogn)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
#define INF 0x7F7F7F7F
using namespace std;
int n,m;
int s[3009],sm[3009];
int f[3009][3009];
void solve(int d,int ls,int rs,int lv,int rv)
{
	if(ls>rs)
		return;
	int mid=(ls+rs)>>1;
	int mn=INF,mp=0;
	for(int i=lv;i<=min(mid,rv);i++)
		if(f[d-1][i]<INF)
		{
			if(mn>f[d-1][i]+(sm[mid]-sm[i])*(sm[mid]-sm[i]))
				mn=f[d-1][i]+(sm[mid]-sm[i])*(sm[mid]-sm[i]),mp=i;
		}
	f[d][mid]=mn;
	solve(d,ls,mid-1,lv,mp);
	solve(d,mid+1,rs,mp,rv);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("march.in","r",stdin);
	freopen("dc.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",s+i),sm[i]=sm[i-1]+s[i];
	memset(f,0x7F,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=m;i++)
		solve(i,1,n,0,n);
	// for(int i=1;i<=m;i++)
	// {
	// 	for(int j=1;j<=n;j++)
	// 		printf("%d ",f[i][j]);
	// 	printf("\n");
	// }
	LL ans=(LL)f[m][n]*m-(LL)sm[n]*sm[n];
	printf("%lld",ans);
	return 0;
}