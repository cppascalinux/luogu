//2019.02.06
//luogu4332 [SHOI2014]三叉神经树 LCT
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define nrt(x) x==lc(f[x])||x==rc(f[x])
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m;
int f[1500009],ch[500009][2],cl[1500009],c1[500009],c2[500009],lz[500009],st[500009];
int deg[500009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void update(int x)
{
	int lx=lc(x),rx=rc(x);
	c1[x]=c1[lx]|c1[rx]|(cl[x]!=1);
	c2[x]=c2[lx]|c2[rx]|(cl[x]!=2);
}
void down(int x)
{
	int lx=lc(x),rx=rc(x);
	if(lz[x]!=-1)
	{
		if(lx)
		{
			cl[lx]=lz[lx]=lz[x];
			c1[lx]=c2[lx]=1;
			if(lz[x]==1)
				c1[lx]=0;
			if(lz[x]==2)
				c2[lx]=0;
		}
		if(rx)
		{
			cl[rx]=lz[rx]=lz[x];
			c1[rx]=c2[rx]=1;
			if(lz[x]==1)
				c1[rx]=0;
			if(lz[x]==2)
				c2[rx]=0;
		}
		lz[x]=-1;
	}
}
void rotate(int x)
{
	int y=f[x],z=f[y],dx=x==rc(y),dy=y==rc(z);
	if(ch[x][dx^1])
		f[ch[x][dx^1]]=y;
	if(nrt(y))
		ch[z][dy]=x;
	f[x]=z;
	f[y]=x;
	ch[y][dx]=ch[x][dx^1];
	ch[x][dx^1]=y;
	update(y);
	update(x);
}
void splay(int x)
{
	int y,z,tp=0;
	for(y=x;nrt(y);y=f[y])
		st[++tp]=y;
	st[++tp]=y;
	for(int i=tp;i>=1;i--)
		down(st[i]);
	while(nrt(x))
	{
		y=f[x],z=f[y];
		if(nrt(y))
			rotate((x==rc(y))^(y==rc(z))?x:y);
		rotate(x);
	}
}
void access(int x)
{
	for(int y=0;x;y=x,x=f[x])
	{
		splay(x);
		rc(x)=y;
		update(x);
	}
}
int findrt(int x)
{
	access(x);
	splay(x);
	while(1)
	{
		down(x);
		if(!lc(x))
			break;
		x=lc(x);
	}
	splay(x);
	return x;
}
void bin(int &p,int *c,int s)
{
	while(1)
	{
		down(p);
		if(rc(p)&&c[rc(p)])
			p=rc(p);
		else if(cl[p]!=s)
			break;
		else if(lc(p)&&c[lc(p)])
			p=lc(p);
		else
			break;
	}
	splay(p);
}
void topo()
{
	queue<int> q;
	for(int i=1;i<=n;i++)
		if(!deg[i])
			q.push(i);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		cl[f[x]]+=cl[x]>=2;
		deg[f[x]]--;
		if(!deg[f[x]])
			q.push(f[x]);
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("nerve.in","r",stdin);
	freopen("nerve.out","w",stdout);
#endif
	rd(n);
	for(int i=1,a,b,c;i<=n;i++)
	{
		rd(a),rd(b),rd(c);
		f[a]=f[b]=f[c]=i;
		deg[i]=3;
	}
	for(int i=n+1,a;i<=3*n+1;i++)
	{
		rd(a);
		cl[i]=a;
		cl[f[i]]+=a;
		deg[f[i]]--;
	}
	topo();
	rd(m);
	for(int i=1,a;i<=m;i++)
	{
		rd(a);
		if(cl[a])
		{
			cl[a]=0;
			int p=findrt(f[a]);
			bin(p,c2,2);
			cl[p]--;
			if(rc(p))
			{
				cl[rc(p)]=lz[rc(p)]=1;
				c1[rc(p)]=0;
				c2[rc(p)]=1;
			}
			update(p);
		}
		else
		{
			cl[a]=1;
			int p=findrt(f[a]);
			bin(p,c1,1);
			cl[p]++;
			if(rc(p))
			{
				cl[rc(p)]=lz[rc(p)]=2;
				c1[rc(p)]=1;
				c2[rc(p)]=0;
			}
			update(p);
		}
		splay(1);
		printf("%d\n",cl[1]>=2);
		// printf("0:%d cl:%d c1:%d c2:%d\n",0,cl[0],c1[0],c2[0]);
	}
	return 0;
}