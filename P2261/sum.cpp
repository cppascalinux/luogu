//2019.05.05
//luoguP2261 [CQOI2007]余数求和 整除分块
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
using namespace std;
int n,k;
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
#endif
	scanf("%d%d",&n,&k);
	li ans=(li)n*k;
	for(int l=1,r=1;l<=min(n,k);l=r+1)
	{
		r=min(n,k/(k/l));
		// r=k/(k/l);
		// printf("l:%d r:%d\n",l,r);
		li tmp=(li)(r-l+1)*(l+r)/2;
		ans-=tmp*(k/l);
	}
	printf("%lld",ans);
	return 0;
}