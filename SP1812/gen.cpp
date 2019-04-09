#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
int main()
{
	freopen("sam.in","w",stdout);
	srand(time(0));
	for(int i=1;i<=10;i++)
	{
		for(int j=1;j<=100;j++)
			printf("%c",rand()%2+'a');
		printf("\n");
	}
	return 0;
}