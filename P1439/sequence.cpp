#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int inf=0x7F7F7F7F;
int n;
int s[100010],p[100010];
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	#endif
	scanf("%d",&n);
	int t;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&t);
		p[t]=i;
	}
	memset(s,0x7F,sizeof(s));
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&t);
		*lower_bound(s+1,s+n+1,p[t])=p[t];
	}
	printf("%d",lower_bound(s+1,s+n+1,inf)-s-1);
	return 0;
}