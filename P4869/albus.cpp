//luogu4869 albus就是要第一个出场 线性基+贪心
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 10086
using namespace std;
int n,q;
int bs[39],used[39];
void ins(int x)
{
	for(int i=30;i>=0;i--)
		if(x&(1<<i))
		{
			if(bs[i])
				x^=bs[i];
			else
			{
				for(int j=0;j<i;j++)
					if(x&(1<<j))
						x^=bs[j];
				for(int j=i+1;j<=30;j++)
					if(bs[j]&(1<<i))
						bs[j]^=x;
				bs[i]=x;
				break;
			}
		}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("albus.in","r",stdin);
	freopen("albus.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1,a;i<=n;i++)
	{
		scanf("%d",&a);
		ins(a);
	}
	scanf("%d",&q);
	for(int i=30;i>=0;i--)
		if(q&(1<<i))
		{
			used[i]=1;
			q^=bs[i];
		}
	int ans=0;
	for(int i=30;i>=0;i--)
		if(bs[i])
		{
			ans<<=1;
			if(used[i])
				ans++;
		}
	ans%=mod;
	int sm=0;
	for(int i=0;i<=30;i++)
		sm+=(bs[i]>0);
	for(int i=1;i<=n-sm;i++)
		ans=ans*2%mod;
	printf("%d",(ans+1)%mod);
	return 0;
}