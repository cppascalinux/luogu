#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 19940417
#define li long long
using namespace std;
int main()
{
#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	freopen("bf.out","w",stdout);
#endif
	int n,m,sm1=0,sm2=0,sm3=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		sm1=(sm1+n%i)%mod;
	for(int i=1;i<=m;i++)
		sm2=(sm2+m%i)%mod;
	for(int i=1;i<=min(n,m);i++)
		sm3=(sm3+(li)(n%i)*(m%i))%mod;
	printf("sm1:%d sm2:%d sm3:%d\n",sm1,sm2,sm3);
	return 0;
}