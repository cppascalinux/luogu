#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;
int main()
{
	freopen("splay.in","w",stdout);
	srand(time(0));
	int n=100,m=100;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
		printf("%d ",rand()%2001-1000);
	printf("\n");
	for(int i=1;i<=m;i++)
	{
		int t=rand()%6;
		if(t!=3&&!n)
			i--;
		else if(t==0)
		{
			printf("GET-SUM ");
			int l=rand()%n+1,r=rand()%n+1;
			if(l>r)
				swap(l,r);
			printf("%d %d\n",l,r-l+1);
		}
		else if(t==1)
		{
			printf("REVERSE ");
			int l=rand()%n+1,r=rand()%n+1;
			if(l>r)
				swap(l,r);
			printf("%d %d\n",l,r-l+1);
		}
		else if(t==2)
			printf("MAX-SUM\n");
		else if(t==3)
		{
			printf("INSERT ");
			int l=rand()%(n+1),r=rand()%10+1;
			if(l>r)
				swap(l,r);
			printf("%d %d ",l,r-l+1);
			for(int i=1;i<=r-l+1;i++)
				printf("%d ",rand()%2001-1000);
			printf("\n");
			n+=r-l+1;
		}
		else if(t==4)
		{
			printf("DELETE ");
			int l=rand()%n+1,r=rand()%n+1;
			if(l>r)
				swap(l,r);
			printf("%d %d\n",l,r-l+1);
			n-=r-l+1;
		}
		else if(t==5)
		{
			printf("MAKE-SAME ");
			int l=rand()%n+1,r=rand()%n+1;
			if(l>r)
				swap(l,r);
			printf("%d %d %d\n",l,r-l+1,rand()%2001-1000);
		}
	}
	return 0;
}