#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,ans,tot;
int map[6][8];
int d[6][8];
int ans1[6],ans2[6],ans3[6];
int q[20];
int cnt[20];
int del()
{
	int ret=0;
	for(int i=1;i<=5;i++)
	{
		int l=1;
		for(int j=2;j<=7;j++)
		{
			if(map[i][j]!=map[i][j-1])
			{
				if(j-l>=3)
					for(int k=l;k<=j-1;k++)
						d[i][k]=1;
				l=j;
			}
		}
		if(8-l>=3)
			for(int k=l;k<=7;k++)
				d[i][k]=1;
	}
	for(int i=1;i<=7;i++)
	{
		int l=1;
		for(int j=2;j<=5;j++)
		{
			if(map[j][i]!=map[j-1][i])
			{
				if(j-l>=3)
					for(int k=l;k<=j-1;k++)
						d[k][i]=1;
				l=j;
			}
		}
		if(6-l>=3)
			for(int k=l;k<=5;k++)
				d[k][i]=1;
	}
	for(int i=1;i<=5;i++)
		for(int j=1;j<=7;j++)
			if(d[i][j])
			{
				if(map[i][j])
				{
					cnt[map[i][j]]--;
					map[i][j]=0;
					ret=1;
				}
				d[i][j]=0;
			}
	// printf("\n\ndel\n");
	// for(int i=1;i<=5;i++)
	// {
	// 	for(int j=1;j<=7;j++)
	// 		printf("%d ",map[i][j]);
	// 	printf("\n");
	// }
	return ret;
}
void drop()
{
	int l,r;
	for(int i=1;i<=5;i++)
	{
		l=1;
		r=0;
		for(int j=1;j<=7;j++)
			if(map[i][j])
			{
				if(l<=r)
				{
					map[i][q[l++]]=map[i][j];
					map[i][j]=0;
					q[++r]=j;
				}
			}
			else
				q[++r]=j;
	}
	// printf("\n\ndrop\n");
	// for(int i=1;i<=5;i++)
	// {
	// 	for(int j=1;j<=7;j++)
	// 		printf("%d ",map[i][j]);
	// 	printf("\n");
	// }
}
void dfs(int d)
{
	// printf("\n\ntot:%d d:%d\n",++tot,d);
	// for(int i=1;i<=5;i++)
	// {
	// 	for(int j=1;j<=7;j++)
	// 		printf("%d ",map[i][j]);
	// 	printf("\n");
	// }
	// fflush(stdout);
	if(d>n)
	{
		int sum=0;
		for(int i=1;i<=5;i++)
			for(int j=1;j<=7;j++)
				if(map[i][j])
					return;
		if(!sum&&!ans)
		{
			ans=1;
			for(int i=1;i<=n;i++)
				printf("%d %d %d\n",ans1[i]-1,ans2[i]-1,ans3[i]);
		}
		return;
	}
	for(int i=1;i<=10;i++)
		if(cnt[i]==1||cnt[i]==2)
			return;
	int map1[6][8],cnt1[20];
	memcpy(cnt1,cnt,sizeof(cnt));
	memcpy(map1,map,sizeof(map));
	for(int i=1;i<=5&&!ans;i++)
		for(int j=1;j<=7&&!ans;j++)
			if(map[i][j])
			{
				if(i<=4&&map[i][j]^map[i+1][j])
				{
					ans1[d]=i;
					ans2[d]=j;
					ans3[d]=1;
					swap(map[i][j],map[i+1][j]);
					drop();
					while(del())
						drop();
					dfs(d+1);
					memcpy(map,map1,sizeof(map));
					memcpy(cnt,cnt1,sizeof(cnt));
				}
				if(i>=2&&map[i][j]^map[i-1][j]&&!map[i-1][j])
				{
					ans1[d]=i;
					ans2[d]=j;
					ans3[d]=-1;
					swap(map[i][j],map[i-1][j]);
					drop();
					while(del())
						drop();
					dfs(d+1);
					memcpy(map,map1,sizeof(map));
					memcpy(cnt,cnt1,sizeof(cnt));
				}
			}
}
int main()
{
	#ifndef ONLINE_JUDGE
	char *p=(char*)malloc(256<<20)+(256<<20);
	__asm__("movl %0,%%esp"::"r"(p));
	freopen("mayan.in","r",stdin);
	freopen("mayan.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1;i<=5;i++)
	{
		int a=1,b;
		scanf("%d",&b);
		while(b)
		{
			cnt[b]++;
			map[i][a]=b;
			a++;
			scanf("%d",&b);
		}
	}
	// for(int i=1;i<=5;i++)
	// {
	// 	for(int j=1;j<=7;j++)
	// 		printf("%d ",map[i][j]);
	// 	printf("\n");
	// }
	dfs(1);
	if(!ans)
		printf("-1");
	return 0;
}