#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll inf=0x7F7F7F7F7F7F7F7FLL;
int n,m;
int map[60][60][100];
ll len[60][60];
void solve()
{
	for(int d=1;d<=64;d++)
		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					if(map[i][k][d-1]&&map[k][j][d-1])
					{
						len[i][j]=1;
						map[i][j][d]=1;
					}
}
void floyd()
{
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(len[i][j]>len[i][k]+len[k][j])
					len[i][j]=len[i][k]+len[k][j];
}	
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("run.in","r",stdin);
	freopen("run.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	int a,b;
	memset(len,0x3F,sizeof(len));
	for(int i=1;i<=n;i++)
		len[i][i]=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		map[a][b][0]=1;
		len[a][b]=1;
	}
	solve();
	floyd();
	printf("%lld",len[1][n]);
	return 0;
}