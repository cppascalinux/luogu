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
int dp()
{
	memset(f,0x7F,sizeof(f));
	for(int i=0;i<=m;i++)
		f[0][i]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=0;k<=i-1;k++)
				if(f[k][j-1]<INF)
					f[i][j]=min(f[i][j],f[k][j-1]+(sm[k]-sm[i])*(sm[k]-sm[i]));
	return f[n][m];
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("march.in","r",stdin);
	freopen("bf.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",s+i),sm[i]=sm[i-1]+s[i];
	LL ans=dp()*m-(LL)sm[n]*sm[n];
	printf("%lld",ans);
	return 0;
}