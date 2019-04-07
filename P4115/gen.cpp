#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define rg register int
using namespace std;
int main()
{
	freopen("qtree.in","w",stdout);
	srand(time(0));
	rand();
	int n=100000;
	printf("%d\n",n);
	for(rg i=1;i<=n-1;i++)
		printf("%d %d %d\n",i,i+1,1);
	printf("0\n");
	return 0;
}