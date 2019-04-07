#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int mod=1000000007;
int n;
ll k;
int m[110][110];
int o[110][110];
int ans[110][110];
int p[110][110];
void mul(int a[110][110],int b[110][110])
{
	memset(p,0,sizeof(p));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				p[i][j]=(p[i][j]+(ll)a[i][k]*b[k][j])%mod;
}
void pow()
{
	while(k)
	{
		if(k&1)
		{
			mul(m,ans);
			memcpy(ans,p,sizeof(p));
		}
		mul(m,m);
		memcpy(m,p,sizeof(p));
		k>>=1;
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
	#endif
	scanf("%d%lld",&n,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&m[i][j]);
	for(int i=1;i<=n;i++)
		ans[i][i]=1;
	pow();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%d ",ans[i][j]);
		printf("\n");
	}
	return 0;
}