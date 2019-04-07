#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define inf 0x3F3F3F3F
#define rg register int
#define lowbit(x) (x&-x)
using namespace std;
int n,m;
int dist[19][19];
int f[19][5009],len[19][5009];
int dp()
{
	memset(f,inf,sizeof(f));
	memset(len,inf,sizeof(len));
	for(rg i=1;i<=n;++i)
		f[1][1<<(i-1)]=0;
	for(rg i=1;i<=n;++i)
		for(rg j=1;j<=n;++j)
			len[i][1<<(j-1)]=dist[i][j];
	for(rg i=1;i<=n;++i)
		for(rg s=1;s<=(1<<n)-1;++s)
			len[i][s]=min(len[i][s],min(len[i][s^lowbit(s)],len[i][lowbit(s)]));
	for(rg d=1;d<=n-1;++d)
	{
		for(rg s=1;s<=(1<<n)-1;++s)
		{
			int k=((1<<n)-1)^s;
			for(rg p=k;p;p=(p-1)&k)
			{
				int tmp=0;
				for(rg i=1;i<=n;i++)
					if(p&(1<<(i-1)))
						tmp+=len[i][s]*d;
				f[d+1][p|s]=min(f[d+1][p|s],f[d][s]+tmp);
			}
		}
	}
	int ans=inf;
	for(rg d=1;d<=n;++d)
		ans=min(ans,f[d][(1<<n)-1]);
	return ans;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("treasure.in","r",stdin);
	freopen("treasure.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(rg i=1;i<=n;i++)
		for(rg j=1;j<=n;j++)
			if(i^j)
				dist[i][j]=600000;
	int a,b,c;
	for(rg i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		dist[a][b]=dist[b][a]=min(dist[a][b],c);
	}
	printf("%d",dp());
	return 0;
}