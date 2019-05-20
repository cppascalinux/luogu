//2019.05.20
//luoguP3750 [六省联考2017]分手是祝愿 求出最优解,然后递推期望
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define li long long
#define mod 100003
using namespace std;
int n,k;
int q[100009],f[100009];
vector<int> v[100009];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
void init()
{
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j+=i)
			v[j].push_back(i);
}
int getw()
{
	int ans=0;
	for(int i=n;i>=1;i--)
		if(q[i])
		{
			ans++;
			for(int j=0;j<(int)v[i].size();j++)
				q[v[i][j]]^=1;
		}
	return ans;
}
void solve(int w)
{
	f[n]=1;
	for(int i=n-1;i>=1;i--)
		f[i]=((li)qpow(i,mod-2)*n%mod*(f[i+1]+1)%mod+mod-f[i+1])%mod;
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d f:%d\n",i,f[i]),fflush(stdout);
	int ans=min(w,k);
	for(int i=w;i>=k+1;i--)
		ans=(ans+f[i])%mod;
	for(int i=1;i<=n;i++)
		ans=(li)ans*i%mod;
	printf("%d",ans);
}
int main()
{
#ifdef HJQ
	freopen("bless.in","r",stdin);
	freopen("bless.out","w",stdout);
#endif
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",q+i);
	init();
	int w=getw();
	// printf("w:%d\n",w),fflush(stdout);
	solve(w);
	return 0;
}