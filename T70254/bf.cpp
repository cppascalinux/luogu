#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 0x7FFFFFFF
using namespace std;
int n,m;
int s[100009];
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sqrt.in","r",stdin);
	freopen("bf.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",s+i);
	for(int i=1,a,b,c;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		int ans=inf;
		for(int j=a;j<=b;j++)
		{
			ans=min(ans,s[j]%c);
			if(!ans)
				break;
		}
		printf("%d\n",ans);
	}
	return 0;
}
