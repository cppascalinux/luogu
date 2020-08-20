#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
using namespace std;
LL gcd(LL a,LL b)
{
	if(!a||!b)
		return a+b;
	return gcd(b,a%b);
}
int main()
{
	int n;
	scanf("%d",&n);
	LL lst=1;
	for(int i=1,a;i<=n;i++)
	{
		scanf("%d",&a);
		lst=lst*a/gcd(a,lst);
	}
	printf("%lld",lst);
	return 0;
}