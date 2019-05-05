//2019.05.05
//luoguP2260 [清华集训2012]模积和 整除分块
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
#define mod 19940417
#define phi 17091780
using namespace std;
int n,m;
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
int cal1(int x)
{
	li ans=(li)x*x;
	for(int l=1,r;l<=x;l=r+1)
	{
		r=x/(x/l);
		li tmp=(li)(l+r)*(r-l+1)/2*(x/l);
		ans-=tmp;
	}
	return ans%mod;
}
int cal2(int x,int y)
{
	if(x>y)
		swap(x,y);
	int ans=(li)x*x%mod*y%mod;
	int inv2=qpow(2,phi-1);
	int inv6=qpow(6,phi-1);
	// printf("inv2:%d inv6:%d\n",inv2,inv6);
	for(int l=1,r;l<=x;l=r+1)
	{
		r=min(x/(x/l),y/(y/l));
		int k1=x/l%mod,k2=y/l%mod;
		int tmp1=(li)(l+r)*(r-l+1)/2%mod;
		tmp1=(li)tmp1*(((li)k1*y+(li)k2*x)%mod)%mod;
		int tmp2=(li)r*(r+1)%mod*(2*r+1)%mod*inv6%mod;
		int tmp3=(li)(l-1)*l%mod*(2*l-1)%mod*inv6%mod;
		int tmp4=(li)k1*k2%mod*(tmp2-tmp3+mod)%mod;
		ans=((li)ans+tmp4-tmp1+mod)%mod;
	}
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	int sm1=cal1(n),sm2=cal1(m),sm3=cal2(n,m);
	// printf("sm1:%d sm2:%d sm3:%d\n",sm1,sm2,sm3);
	int ans=((li)sm1*sm2%mod-sm3+mod)%mod;
	printf("%d",ans);
	return 0;
}