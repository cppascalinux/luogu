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
	for(int ttt=1;ttt<=10;ttt++)
	{
	char s[20];
	sprintf(s,"a%d.in",ttt);
	freopen(s,"w",stdout);
	int n=1000000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
	{
		if(rnd()%10000==0)
			printf("%d\n",rnd()%999999+1);
		else if(rnd()%1000==0)
			printf("%d\n",rnd()%700000+1);
		else if(rnd()%100==0)
			printf("%d\n",rnd()%500000+1);
		else if(rnd()%10==0)
			printf("%d\n",rnd()%300000+1);
		else
			printf("%d\n",rnd()%100000+1);
	}
	}
	return 0;
}
