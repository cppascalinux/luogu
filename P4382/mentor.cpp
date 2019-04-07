//2019.04.07
//luoguP4382 [八省联考2018]劈配 dfs+增广路
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n,m;//number of students,number of teachers
int br[209],dr[209];//max students,dream level
vector<int> v[209][209],g[209],s[209];//levels,teachers of current level,students of a teacher
int vx[209],vy[209],mat[209];//vis during dfs,match of x
int ans1[209],ans2[209];//answer for question1&2
void clr()
{
	memset(mat,0,sizeof(mat));
	memset(ans1,0,sizeof(ans1));
	memset(ans2,0,sizeof(ans2));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			v[i][j].clear();
	for(int i=1;i<=n;i++)
		g[i].clear();
	for(int i=1;i<=m;i++)
		s[i].clear();
}
int dfs(int x,int l,int st)
{
	if(vx[x])
		return 0;
	vx[x]=1;
	if(x!=st&&l<=dr[st])
		ans2[st]=max(ans2[st],x);
	for(int i=0;i<(int)g[x].size();i++)
		if(g[x][i]!=mat[x]&&!vy[g[x][i]])
		{
			int p=g[x][i];
			vy[p]=1;
			if((int)s[p].size()<br[p])
			{
				s[p].push_back(x);
				mat[x]=p;
				return 1;
			}
			for(int j=0;j<(int)s[p].size();j++)
			{
				int u=s[p][j];
				if(dfs(u,l,st))
				{
					mat[x]=p;
					s[p][j]=x;
					return 1;
				}
			}
		}
	return 0;
}
void solve(int x)
{
	ans1[x]=m+1;
	for(int i=1;i<=m;i++)
	{
		for(int j=0;j<(int)v[x][i].size();j++)
			g[x].push_back(v[x][i][j]);
		memset(vx,0,sizeof(vx));
		memset(vy,0,sizeof(vy));
		if(!dfs(x,i,x))
			g[x].clear();
		else
		{
			ans1[x]=i;
			break;
		}
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("mentor.in","r",stdin);
	freopen("mentor.out","w",stdout);
#endif
	int t,c;
	scanf("%d%d",&t,&c);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
			scanf("%d",br+i);
		for(int i=1;i<=n;i++)
			for(int j=1,a;j<=m;j++)
			{
				scanf("%d",&a);
				if(a)
					v[i][a].push_back(j);
			}
		for(int i=1;i<=n;i++)
			scanf("%d",dr+i);
		for(int i=1;i<=n;i++)
			solve(i);
		for(int i=1;i<=n;i++)
			printf("%d ",ans1[i]);
		printf("\n");
		for(int i=1;i<=n;i++)
			printf("%d ",ans1[i]<=dr[i]?0:i-ans2[i]);
		printf("\n");
		clr();
	}
	return 0;
}