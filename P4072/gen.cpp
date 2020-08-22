#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
using namespace std;
int n=3000,m=1000;
int main()
{
	freopen("march.in","w",stdout);
	random_device rnd;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
		printf("%d ",rnd()%10+1);
	return 0;
}