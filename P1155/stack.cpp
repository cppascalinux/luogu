#include<bits/stdc++.h>
using namespace std;
int n;
int edg[1009][1009];
int cl[1009];
int s[1009],mn[1009];
int st1[1009],st2[1009];
int dfs(int x,int c)
{
	if(cl[x]>=0)
	{
		if(cl[x]!=c)
			return 0;
		return 1;
	}
	cl[x]=c;
	int ans=1;
	for(int i=1;i<=n;i++)
		if(edg[x][i])
			ans&=dfs(i,c^1);
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",s+i);
	mn[n+1]=1e9;
	for(int i=n;i>=1;i--)
		mn[i]=min(mn[i+1],s[i]);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(s[i]<s[j]&&mn[j+1]<s[i])
				edg[i][j]=edg[j][i]=1;
	memset(cl,-1,sizeof(cl));
	for(int i=1;i<=n;i++)
		if(cl[i]==-1)
			if(!dfs(i,0))
				return printf("0"),0;
	memset(cl,-1,sizeof(cl));
	int cur=1,p=1,tp1=0,tp2=0;
	st1[0]=st2[0]=1e9;
	for(int i=1;i<=2*n;i++)
	{
		if(p<=n&&(cl[p]==-1||cl[p]==0)&&s[p]<st1[tp1])
		{
			st1[++tp1]=s[p];
			dfs(p,0);
			p++;
			printf("a ");
		}
		else if(tp1&&st1[tp1]==cur)
		{
			tp1--;
			cur++;
			printf("b ");
		}
		else if(p<=n&&cl[p]==1&&s[p]<st2[tp2])
		{
			st2[++tp2]=s[p];
			p++;
			printf("c ");
		}
		else if(tp2&&st2[tp2]==cur)
		{
			tp2--;
			cur++;
			printf("d ");
		}
		else
			assert(0);
	}
	return 0;
}