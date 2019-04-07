#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
int main()
{
	freopen("tree.in","w",stdout);
	int n=5,m=100;
	printf("%d %d\n",n,m);
	srand(time(0));
	for(int i=2;i<=n;i++)
	{
		int a=rand()*rand()%(i-1)+1;
		printf("%d %d %d\n",a,i,rand()%1000+1);
	}
	for(int i=n;i<=m;i++)
	{
		int a=rand()*rand()%(n-1)+2,b=rand()*rand()%(a-1)+1;
		printf("%d %d %d\n",a,b,rand()%1000+1);
	}
	return 0;
}