#include<cstdio>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int main()
{
	freopen("tree.in","w",stdout);
	srand(time(0));
	rand();
	int n=10000,m=100;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n-1;i++)
		printf("%d %d %d\n",i,i+1,2*(rand()%500+1));
	for(int i=1;i<=m;i++)
		printf("%d\n",rand()%1000+1);
	return 0;
}