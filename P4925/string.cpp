//2020.08.30
//休闲小水题..一个字符串中不含回文子串当且仅当对于任意的i,有s[i]!=s[i-1]且s[i]!=s[i-2]
//从前往后确定每个位置的字符,答案就是k*(k-1)*(k-2)^(l-2),有限制的话稍加讨论即可
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
using namespace std;
int mod;
LL n,m,s,w;
int qpow(LL a,LL b)
{
	a%=mod;
	int ans=1;
	for(;b;b>>=1)
	{
		if(b&1)
			ans=ans*a%mod;
		a=a*a%mod;
	}
	return ans;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
#endif
	scanf("%lld%lld%d%lld%lld",&m,&n,&mod,&s,&w);
	int ans=0;
	if(s==0)
	{
		ans=m%mod*((m-1)%mod)%mod;
		ans=(LL)ans*qpow(m-2,n-2)%mod;
	}
	else
		ans=(m-1)%mod*qpow(m-2,n-2)%mod;
	printf("%d",ans);
	return 0;
}