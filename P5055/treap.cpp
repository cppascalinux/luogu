//2019.06.25
//luogu P5055 可持久化文艺平衡树 fhq treap暴力维护,打懒标记,split和merge的时候新建节点,同时标记下传的时候也要新建节点
//因为一个儿子可能有很多个父亲,将这个父亲的标记下传的时候,其他父亲的标记没变,就会出错
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define pii pair<int,int>
#define fi first
#define se second
#define li long long
using namespace std;
int n,cnt,lst;
int rt[200009];
int v[10000009],ch[10000009][2],sz[10000009],lz[10000009];
li sm[10000009];
int cln(int x)
{
	int y=++cnt;
	v[y]=v[x];
	sm[y]=sm[x];
	sz[y]=sz[x];
	lz[y]=lz[x];
	ch[y][0]=ch[x][0];
	ch[y][1]=ch[x][1];
	return y;
}
int newnode(int val)
{
	int x=++cnt;
	return sm[x]=v[x]=val,sz[x]=1,x;
}
void update(int x)
{
	int lx=ch[x][0],rx=ch[x][1];
	sz[x]=sz[lx]+sz[rx]+1;
	sm[x]=sm[lx]+sm[rx]+v[x];
}
void down(int x)
{
	if(lz[x])
	{
		int &lx=ch[x][0],&rx=ch[x][1];
		if(lx&&lx<=lst)
			lx=cln(lx);
		if(rx&&rx<=lst)
			rx=cln(rx);
		swap(lx,rx),lz[lx]^=1,lz[rx]^=1,lz[x]=0;
	}
}
pii split(int x,int k)
{
	if(!x)
		return pii(0,0);
	if(x<=lst)
		x=cln(x);
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
		return cln(x+y);
	if(rand()%(sz[x]+sz[y])<sz[x])
	{
		if(x<=lst)
			x=cln(x);
		down(x);
		ch[x][1]=mrg(ch[x][1],y);
		update(x);
		return x;
	}
	else
	{
		if(y<=lst)
			y=cln(y);
		down(y);
		ch[y][0]=mrg(x,ch[y][0]);
		update(y);
		return y;
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("treap.in","r",stdin);
	freopen("treap.out","w",stdout);
#endif
	srand(20020618);
	scanf("%d",&n);
	li lstans=0;
	for(int i=1,a,b;i<=n;i++)
	{
		li c,d;
		scanf("%d%d%lld",&a,&b,&c);
		c^=lstans;
		rt[i]=rt[a];
		lst=cnt;
		if(b==1)
		{
			scanf("%lld",&d);
			d^=lstans;
			pii t=split(rt[i],c);
			int x=newnode(d);
			rt[i]=mrg(t.fi,x);
			rt[i]=mrg(rt[i],t.se);
		}
		else if(b==2)
		{
			pii t1=split(rt[i],c-1);
			pii t2=split(t1.se,1);
			rt[i]=mrg(t1.fi,t2.se);
		}
		else if(b==3)
		{
			scanf("%lld",&d);
			d^=lstans;
			pii t1=split(rt[i],c-1);
			pii t2=split(t1.se,d-c+1);
			lz[t2.fi]^=1;
			rt[i]=mrg(t1.fi,t2.fi);
			rt[i]=mrg(rt[i],t2.se);
		}
		else
		{
			scanf("%lld",&d);
			d^=lstans;
			pii t1=split(rt[i],c-1);
			pii t2=split(t1.se,d-c+1);
			printf("%lld\n",lstans=sm[t2.fi]);
			rt[i]=mrg(t1.fi,t2.fi);
			rt[i]=mrg(rt[i],t2.se);
		}
	}
	return 0;
}