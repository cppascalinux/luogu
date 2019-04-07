#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long n;
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("water.in","r",stdin);
	freopen("water.out","w",stdout);
	#endif
	scanf("%lld",&n);
	double cost=420000.0L/n,ans=0.0;
	for(long long i=1;i<=n;i++)
	{
		ans+=cost;
		cost*=((2.0*i-1.0)/(2.0*i));
	}
	printf("%.2lf",ans);
	return 0;
}