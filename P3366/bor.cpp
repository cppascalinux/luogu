#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
#define inf 0x7F7F7F7F
using namespace std;
int n,m,tot,ans;
int f[5010];
int x[200010],y[200010],len[200010];
int mn[5010],mx[5010];
int	find(int x)
{
	if(x==f[x])
		return x;
	return f[x]=find(f[x]);
}
void bov()
{
	int fx,fy,flag=1;
	len[0]=inf;
	while(flag)
	{
		flag=0;
		memset(mn,inf,sizeof(mn));
		memset(mx,0,sizeof(mx));
		for(rg i=1;i<=m;i++)
		{
			fx=find(x[i]);
			fy=find(y[i]);
			if(fx^fy)
			{
				if(len[i]<mn[fx])
				{
					mn[fx]=len[i];
					mx[fx]=fy;
				}
				if(len[i]<mn[fy])
				{
					mn[fy]=len[i];
					mx[fy]=fx;
				}
			}	
		}
		for(rg i=1;i<=n;i++)
			if(mx[i])
			{
				fx=find(i);
				fy=find(mx[i]);
				if(fx^fy)
				{
					f[fx]=fy;
					ans+=mn[i];
					flag=1;
				}
			}
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("bor.in","r",stdin);
	freopen("bor.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(rg i=1;i<=n;i++)
		f[i]=i;
	for(rg i=1;i<=m;i++)
		scanf("%d%d%d",x+i,y+i,len+i);
	bov();
	int f1=find(1);
	for(rg i=1;i<=n;i++)
		if(find(i)^f1)
		{
			printf("orz");
			return 0;
		}
	printf("%d",ans);
	return 0;
}