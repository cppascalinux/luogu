#include<cstdio>
#include<ctime>
#include<cstring>
#include<random>
#include<cstdlib>
using namespace std;
int main()
{
	freopen("tree.in","w",stdout);
	random_device rnd;
	int a=rnd()%10000+1,b=rnd()%10000+1;
	if(a>b)
		swap(a,b);
	printf("%d %d",a,b);
	return 0;
}