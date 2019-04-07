#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
using namespace std;
int n,m,ans;
int f[5010];
struct node
{
	int x,y,len;
	bool operator < (const node &o) const
	{
		return len<o.len;
	}
}v[200010];
int find(int x)
{
	if(x==f[x])
		return x;
	return f[x]=find(f[x]);
}
void kruskal()
{
	sort(v+1,v+m+1);
	rg fx,fy;
	for(rg i=1;i<=m;i++)
	{
		fx=find(v[i].x);
		fy=find(v[i].y);
		if(fx^fy)
		{
			f[fx]=fy;
			ans+=v[i].len;
		}
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("bor.in","r",stdin);
	freopen("kruskal.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(rg i=1;i<=n;i++)
		f[i]=i;
	for(rg i=1;i<=m;i++)
		scanf("%d%d%d",&v[i].x,&v[i].y,&v[i].len);
	kruskal();
	for(int i=2;i<=n;i++)
		if(find(i)^find(i-1))
		{
			printf("orz");
			return 0;
		}
	printf("%d",ans);
	return 0;
}