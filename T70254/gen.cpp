#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
#include<ctime>
using namespace std;
mt19937 rnd(time(0));
int main()
{
	for(int t=1;t<=20;t++)
	{
		char s[20];
		sprintf(s,"sqrt%d.in",t);
		freopen(s,"w",stdout);
		int n=100000,m=100000;
		printf("%d %d\n",n,m);
		for(int i=1;i<=n;i++)
			printf("%d ",rnd()%100000+1);
		for(int i=1;i<=m;i++)
		{
			int k=rnd()%100000+1;
			int l=rnd()%n+1;
			int r=rnd()%(n-l+1)+l;
			printf("\n%d %d %d",l,r,k);
		}
	}
	return 0;
}
