#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define inf 0x7F7F7F7F
#define rg register int
#define lb(x) (x&-x)
using namespace std;
int n,m;
int a[19][19],b[19][19];
int bel[1050001],f[1050001];
void init()
{
	rg t,sum;
	for(rg i=0;i<=(1<<(n+m))-1;i++)
	{
		sum=0;
		t=i;
		while(t)
		{
			t-=lb(t);
			++sum;
		}
		if(sum==m)
		{
			t=sum=0;
			for(rg j=n+m;j>=1;j--)
				if(i&(1<<(j-1)))
					t++;
				else
					sum+=t;
			if(sum&1)
			{
				bel[i]=2;
				f[i]=inf;
			}
			else
			{
				bel[i]=1;
				f[i]=-inf;
			}
		}
	}
}
int dp()
{
	int tmp=((1<<m)-1)<<n;
	f[tmp]=0;
	// printf("tmp:%d ",bel[tmp]);
	// for(rg j=n+m;j>=1;j--)
	// 	if(tmp&(1<<(j-1)))
	// 		printf("1");
	// 	else
	// 		printf("0");
	// printf("\n");
	for(rg i=(1<<(n+m))-1;i>=0;i--)
		if(bel[i])
		{
			int x=n+1,y=1;
			for(rg j=n+m;j>=2;j--)
			{
				if(i&(1<<(j-1)))
					y++;
				else
					x--;
				if((!(i&(1<<(j-1))))&&(i&(1<<(j-2))))
				{
					int t=i^(3<<(j-2));
					// printf("t:%d x:%d y:%d  ",bel[t],x,y);
					// for(rg k=n+m;k>=1;k--)
					// 	if(t&(1<<(k-1)))
					// 		printf("1");
					// 	else
					// 		printf("0");
					// printf("\n");
					if(bel[i]==1)
						f[i]=max(f[i],f[t]+a[x][y]);
					else
						f[i]=min(f[i],f[t]-b[x][y]);
				}
			}
		}
	int t=(1<<m)-1;
	// printf("t:%d ",bel[t]);
	// for(rg j=n+m;j>=1;j--)
	// 	if(t&(1<<(j-1)))
	// 		printf("1");
	// 	else
	// 		printf("0");
	// printf("\n");
	return f[t];
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("chess.in","r",stdin);
	freopen("chess.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(rg i=1;i<=n;i++)
		for(rg j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for(rg i=1;i<=n;i++)
		for(rg j=1;j<=m;j++)
			scanf("%d",&b[i][j]);
	init();
	// for(rg i=1;i<=(1<<(n+m))-1;i++)
	// 	if(bel[i])
	// 	{
	// 		printf("bel:%d ",bel[i]);
	// 		for(rg j=n+m;j>=1;j--)
	// 			if(i&(1<<(j-1)))
	// 				printf("1");
	// 			else
	// 				printf("0");
	// 		printf("\n");
	// 	}
	printf("%d",dp());
	return 0;
}