#include<cstdio>
#include<cstdlib>
using namespace std;
int main()
{
	char s[100];
	for(int i=1;i<=10;i++)
	{
		sprintf(s,"cp %d.in walk.in",i);
		system(s);
		system("./walk");
		sprintf(s,"diff %d.out walk.out -B -Z",i);
		system(s);
	}
	return 0;
}