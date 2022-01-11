#include<bits/stdc++.h>
#define ll long long
#define mod 1000000007
using namespace std;
int n,m;
int sz[100009];
int f[100001][2][2][101];//deployed or not, monitored or not
int sa[101],sb[101];
vector<int> g[100009];
void dfs(int x,int fa)
{
	sz[x]=1;
	for(int v:g[x])
		if(v!=fa)
			dfs(v,x),sz[x]+=sz[v];
	// printf("x:%d az:%d\n",x,sz[x]);
	memset(sa,0,sizeof(sa));
	memset(sb,0,sizeof(sb));
	sa[0]=1;
	int sm=0;
	for(int v:g[x])
		if(v!=fa)
		{
			for(int i=0;i<=sm+sz[v]&&i<=m;i++)
				sb[i]=0;
			for(int i=0;i<=sm&&i<=m;i++)
				for(int j=0;j<=sz[v]&&i+j<=m;j++)
					sb[i+j]=(sb[i+j]+(ll)f[v][0][1][j]*sa[i])%mod;
			sm+=sz[v];
			for(int i=0;i<=sm&&i<=m;i++)
				sa[i]=sb[i];
		}
	for(int i=0;i<=sz[x]&&i<=m;i++)
		f[x][0][0][i]=sa[i];
	
	memset(sa,0,sizeof(sa));
	memset(sb,0,sizeof(sb));
	sa[0]=1;
	sm=0;
	for(int v:g[x])
		if(v!=fa)
		{
			for(int i=0;i<=sm+sz[v]&&i<=m;i++)
				sb[i]=0;
			for(int i=0;i<=sm&&i<=m;i++)
				for(int j=0;j<=sz[v]&&i+j<=m;j++)
					sb[i+j]=(sb[i+j]+(ll)(f[v][0][1][j]+f[v][1][1][j])*sa[i])%mod;
			sm+=sz[v];
			for(int i=0;i<=sm&&i<=m;i++)
				sa[i]=sb[i];
		}
	for(int i=0;i<=sz[x]&&i<=m;i++)
		f[x][0][1][i]=(sa[i]-f[x][0][0][i]+mod)%mod;
	
	memset(sa,0,sizeof(sa));
	memset(sb,0,sizeof(sb));
	sa[1]=1;
	sm=1;
	for(int v:g[x])
		if(v!=fa)
		{
			for(int i=0;i<=sm+sz[v]&&i<=m;i++)
				sb[i]=0;
			for(int i=0;i<=sm&&i<=m;i++)
				for(int j=0;j<=sz[v]&&i+j<=m;j++)
					sb[i+j]=(sb[i+j]+(ll)(f[v][0][0][j]+f[v][0][1][j])*sa[i])%mod;
			sm+=sz[v];
			for(int i=0;i<=sm&&i<=m;i++)
				sa[i]=sb[i];
		}
	for(int i=0;i<=sz[x]&&i<=m;i++)
		f[x][1][0][i]=sa[i];
	
	memset(sa,0,sizeof(sa));
	memset(sb,0,sizeof(sb));
	sa[1]=1;
	sm=1;
	for(int v:g[x])
		if(v!=fa)
		{
			for(int i=0;i<=sm+sz[v]&&i<=m;i++)
				sb[i]=0;
			for(int i=0;i<=sm&&i<=m;i++)
				for(int j=0;j<=sz[v]&&i+j<=m;j++)
					sb[i+j]=(sb[i+j]+((ll)f[v][0][0][j]+f[v][0][1][j]+f[v][1][0][j]+f[v][1][1][j])*sa[i])%mod;
			sm+=sz[v];
			for(int i=0;i<=sm&&i<=m;i++)
				sa[i]=sb[i];
		}
	for(int i=0;i<=sz[x]&&i<=m;i++)
		f[x][1][1][i]=(sa[i]-f[x][1][0][i]+mod)%mod;
	// for(int i=0;i<=1;i++)
	// 	for(int j=0;j<=1;j++)
	// 		for(int k=0;k<=m;k++)
	// 			printf("x:%d i:%d j:%d k:%d f:%d\n",x,i,j,k,f[x][i][j][k]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n-1;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1,0);
	printf("%d",(f[1][0][1][m]+f[1][1][1][m])%mod);
	return 0;
}