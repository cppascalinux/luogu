#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,l;
int x[5010];
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("bridge.in","r",stdin);
	freopen("bridge.out","w",stdout);
	#endif
	scanf("%d%d",&l,&n);
	for(int i=1;i<=n;i++)
		scanf("%d",x+i);
	int minn=0,maxx=0;
	for(int i=1;i<=n;i++)
	{
		maxx=max(maxx,max(l-x[i]+1,x[i]));
		minn=max(minn,min(l-x[i]+1,x[i]));
	}
	printf("%d %d",minn,maxx);
	return 0;
}