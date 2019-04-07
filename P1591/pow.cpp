#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int ans[1010][20];
int a[1000010],len;
void mul(int x)
{
	int now=0,next=0;
	for(int i=1;i<=len;i++)
	{
		now=a[i]*x+next;
		a[i]=now%10;
		next=now/10;
	}
	while(next)
	{
		len++;
		a[len]=next%10;
		next/=10;
	}
}
void init()
{
	a[1]=1;
	len=1;
	for(int i=1;i<=1000;i++)
	{
		mul(i);
		for(int j=1;j<=len;j++)
			ans[i][a[j]]++;
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("pow.in","r",stdin);
	freopen("pow.out","w",stdout);
	#endif
	init();
	int t,n,a;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&a);
		printf("%d\n",ans[n][a]);
	}
	return 0;
}