#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int n,m;
int gcd(int a,int b)
{
	if(!b)
		return a;
	return gcd(b,a%b);
}
int main()
{
	#ifndef ONLINE_JUDGE
	//freopen("b.in","r",stdin);
	//freopen("b.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	m=abs(m);
	int a,b;
	scanf("%d",&b);
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&a);
		b=gcd(a,b);
	}
	if(m%b==0)
		puts("YES");
	else
		puts("NO");
	return 0;
}