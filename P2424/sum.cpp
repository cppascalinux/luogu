#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
int x,y;
ll get(int n)
{
	ll l=1,r=1;
	ll ans=0;
	while(l<=n&&r<=n)
	{
		ans+=((l+r)*(r-l+1)>>1)*(n/l);
		l=r+1;
		if(l>n)
			break;
		r=n/(n/l);
	}
	return ans;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	#endif
	scanf("%d%d",&x,&y);
	printf("%lld",get(y)-get(x-1));
	return 0;
}