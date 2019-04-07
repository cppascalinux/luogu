#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
using namespace std;
int n,m;
int mn[100009],dist[100009];
int f[100009],rt[100009];
int del[100009];
int lp[100009],rp[100009];
int find(int x)
{
	return x==f[x]?x:f[x]=find(f[x]);
}
int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(mn[x]>mn[y]||(mn[x]==mn[y]&&x>y))
		swap(x,y);
	rp[x]=merge(rp[x],y);
	if(dist[lp[x]]<dist[rp[x]])
		swap(lp[x],rp[x]);
	dist[x]=dist[rp[x]]+1;
	return x;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	dist[0]=-1;
	for(rg i=1;i<=n;i++)
	{
		scanf("%d",mn+i);
		f[i]=rt[i]=i;
	}
	int c,a,b,fa,fb,ra,rb;
	for(rg i=1;i<=m;i++)
	{
		scanf("%d",&c);
		if(c==1)
		{
			scanf("%d%d",&a,&b);
			if(del[a]||del[b])
				continue;
			fa=find(a);
			fb=find(b);
			if(fa==fb)
				continue;
			f[fa]=fb;
			ra=rt[fa];
			rb=rt[fb];
			rt[fb]=merge(ra,rb);
		}
		else
		{
			scanf("%d",&a);
			if(del[a])
			{
				printf("-1\n");
				continue;
			}
			fa=find(a);
			ra=rt[fa];
			del[ra]=1;
			printf("%d\n",mn[ra]);
			rt[fa]=merge(lp[ra],rp[ra]);
		}
	}
	return 0;
}