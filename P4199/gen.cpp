#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
using namespace std;
int main()
{
	freopen("fft.in","w",stdout);
	random_device rnd;
	int n=100000;
	for(int i=1;i<=n;i++)
		printf("%c",'a'+rnd()%2);
	return 0;
}