#include<cstdlib>
#include<cstdio>
using namespace std;
int main()
{
	int t=0;
	while(1)
	{
		printf("%d\n",++t);
		system("./gen;./wqs;./march");
		if(system("diff wqs.out march.out"))
			break;
	}
	return 0;
}