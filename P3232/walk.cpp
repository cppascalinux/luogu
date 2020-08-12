//2020.08.12
//luoguP3232 [HNOI2013]游走 设出每个点的期望经过次数,然后高斯消元..显然就能求出经过每条边的期望次数..然后套一个排序不等式就行
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
#define PB push_back
#define DB double
#define EPS 1e-8
using namespace std;
int n,m;
int deg[509];
vector<int> g[509],id[509];
DB mt[509][509];
DB f[509],fe[125009];
void buildmt()
{
	for(int i=1;i<=n-1;i++)
	{
		mt[i][i]=i==n?0:-1;
		mt[i][n+1]=i==1?-1:0;
		for(int t:g[i])
			if(t!=n)
				mt[i][t]=(DB)1/deg[t];
	}
	mt[n][n]=mt[n][n+1]=1;
	// for(int i=1;i<=n;i++)
	// {
	// 	for(int j=1;j<=n+1;j++)
	// 		printf("%.1lf ",mt[i][j]);
	// 	printf("\n");
	// }
}
void solve()
{
	for(int i=1;i<=n;i++)
	{
		int t=i;
		for(int j=i;j<=n;j++)
			if(fabs(mt[j][i])>EPS)
			{
				t=j;
				break;
			}
		if(t!=i)
			for(int k=1;k<=n+1;k++)
				swap(mt[i][k],mt[t][k]);
		for(int k=n+1;k>=i;k--)
			mt[i][k]/=mt[i][i];
		for(int j=i+1;j<=n;j++)
			for(int k=n+1;k>=i;k--)
				mt[j][k]-=mt[i][k]*mt[j][i];
	// for(int i=1;i<=n;i++)
	// {
	// 	for(int j=1;j<=n+1;j++)
	// 		printf("%.1lf ",mt[i][j]);
	// 	printf("\n");
	// }
	}
	for(int i=n;i>=1;i--)
		for(int j=i-1;j>=1;j--)
			mt[j][n+1]-=mt[i][n+1]*mt[j][i];
}
void getans()
{
	for(int i=1;i<=n;i++)
		f[i]=mt[i][n+1];
	for(int i=1;i<=n-1;i++)
		for(int j:id[i])
			fe[j]+=f[i]/deg[i];
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d f:%lf\n",i,f[i]);
	sort(fe+1,fe+m+1);
	DB ans=0;
	for(int i=1;i<=m;i++)
		ans+=(m-i+1)*fe[i];
	printf("%.3lf",ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("walk.in","r",stdin);
	freopen("walk.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		deg[a]++,deg[b]++;
		g[a].PB(b),g[b].PB(a);
		id[a].PB(i),id[b].PB(i);
	}
	buildmt();
	solve();
	getans();
	return 0;
}