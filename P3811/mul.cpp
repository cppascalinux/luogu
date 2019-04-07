#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,p,x,y;
void exgcd(int a,int b)
{
	if(b==0)
	{
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b);
	int t=x;
	x=y;
	y=t-a/b*y;
}
int get(int xx)
{
	exgcd(xx,p);
	x=(x%p+p)%p;
	return x;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("mul.in","r",stdin);
	freopen("mul.out","w",stdout);
	#endif
	scanf("%d%d",&n,&p);
	for(register int i=1;i<=n;++i)
		printf("%d\n",get(i));
	return 0;
}