//2019.06.25
//luogu P3391 文艺平衡树 fhq treap
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,m,rt;
int ch[100009][2],sz[100009],lz[100009];
void update(int x)
{
	sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
}
void down(int x)
{
	if(lz[x])
	{
		int &lx=ch[x][0],&rx=ch[x][1];
		swap(lx,rx),lz[lx]^=1,lz[rx]^=1,lz[x]=0;
	}
}
pii split(int x,int k)
{
	if(!x)
		return pii(0,0);
	down(x);
	int lsz=sz[ch[x][0]];
	if(k<=lsz)
	{
		pii t=split(ch[x][0],k);
		ch[x][0]=t.se;
		update(x);
		return pii(t.fi,x);
	}
	else
	{
		pii t=split(ch[x][1],k-lsz-1);
		ch[x][1]=t.fi;
		update(x);
		return pii(x,t.se);
	}
}
int mrg(int x,int y)
{
	if(!x||!y)
		return x+y;
	down(x),down(y);
	if(rand()%(sz[x]+sz[y])<sz[x])
	{
		ch[x][1]=mrg(ch[x][1],y);
		update(x);
		return x;
	}
	else
	{
		ch[y][0]=mrg(x,ch[y][0]);
		update(y);
		return y;
	}
}
int build(int l,int r)
{
	if(l>r)
		return 0;
	int mid=(l+r)>>1;
	ch[mid][0]=build(l,mid-1);
	ch[mid][1]=build(mid+1,r);
	sz[mid]=1;
	update(mid);
	return mid;
}
void dfs(int x)
{
	if(!x)
		return;
	down(x);
	dfs(ch[x][0]);
	printf("%d ",x);
	dfs(ch[x][1]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("splay.in","r",stdin);
	freopen("treap.out","w",stdout);
#endif
	srand(20020618);
	scanf("%d%d",&n,&m);
	rt=build(1,n);
	// dfs(rt);
	// printf("\n");
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		pii t1=split(rt,a-1);
		pii t2=split(t1.se,b-a+1);
		// dfs(t2.fi);
		// printf("\n");
		lz[t2.fi]^=1;
		rt=mrg(t1.fi,t2.fi);
		rt=mrg(rt,t2.se);
	}
	dfs(rt);
	return 0;
}