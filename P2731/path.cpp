#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define rg register int
using namespace std;
int m;
int mat[509][509];
int in[509];
int ans[2009],top;
void dfs(int x)
{
	for(int i=1;i<=500;i++)
		if(mat[x][i])
		{
			mat[x][i]--;
			mat[i][x]--;
			dfs(i);
		}
	ans[++top]=x;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
	#endif
	scanf("%d",&m);
	int a,b;
	for(rg i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		mat[a][b]++;
		mat[b][a]++;
		in[a]++;
		in[b]++;
	}
	int s=1;
	for(rg i=1;i<=500;i++)
		if(in[i]&1)
		{
			s=i;
			break;
		}
	dfs(s);
	for(rg i=top;i>=1;i--)
		printf("%d\n",ans[i]);
	return 0;
}