#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000000];
int n,q,tot,tot1;
int head[100010],edge[100010],next[100010];
int f[100010],d[100010],son[100010],s[100010];
int id[100010],pos[100010],top[100010],last[100010];
int sum[400010],lazy[400010],l[400010],r[400010];
char ss[20];
void read(int &x)
{
	rc ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch&15),ch=gc();
}
void reads(char *p)
{
	rg tot=-1;
	rc ch=0;
	while(ch<'a'||ch>'z')
		ch=gc();
	while(ch>='a'&&ch<='z')
		p[++tot]=ch,ch=gc();
}
void ins(rg a,rg b)
{
	edge[++tot]=b;
	next[tot]=head[a];
	head[a]=tot;
}
void build(int a,int ll,int rr)
{
	l[a]=ll;
	r[a]=rr;
	lazy[a]=-1;
	if(ll^rr)
	{
		int mid=(ll+rr)>>1;
		build(a<<1,ll,mid);
		build(a<<1|1,mid+1,rr);
	}
}
void down(int a)
{
	if(~lazy[a])
	{
		int t=lazy[a],la=a<<1,ra=a<<1|1;
		lazy[a]=-1;
		lazy[la]=lazy[ra]=t;
		sum[la]=(r[la]-l[la]+1)*t;
		sum[ra]=(r[ra]-l[ra]+1)*t;
	}
}
void set(int a,int ll,int rr,int val)
{
	if(l[a]>rr||r[a]<ll)
		return;
	if(l[a]>=ll&&r[a]<=rr)
	{
		lazy[a]=val;
		sum[a]=(r[a]-l[a]+1)*val;
		return;
	}
	down(a);
	set(a<<1,ll,rr,val);
	set(a<<1|1,ll,rr,val);
	sum[a]=sum[a<<1]+sum[a<<1|1];
}
int ask(int a,int ll,int rr)
{
	if(l[a]>rr||r[a]<ll)
		return 0;
	if(l[a]>=ll&&r[a]<=rr)
		return sum[a];
	down(a);
	return ask(a<<1,ll,rr)+ask(a<<1|1,ll,rr);
}
void dfs1(int x,int fa)
{
	f[x]=fa;
	d[x]=d[fa]+1;
	s[x]=1;
	for(int i=head[x];i;i=next[i])
	{
		dfs1(edge[i],x);
		s[x]+=s[edge[i]];
		if(s[edge[i]]>s[son[x]])
			son[x]=edge[i];
	}
}
void dfs2(int x,int t)
{
	top[x]=t;
	id[x]=++tot1;
	last[x]=pos[tot]=x;
	if(son[x])
	{
		dfs2(son[x],t);
		last[x]=last[son[x]];
	}
	for(int i=head[x];i;i=next[i])
		if(edge[i]^son[x])
		{
			dfs2(edge[i],edge[i]);
			last[x]=last[edge[i]];
		}
}
int query(rg x)
{
	int fx,ans=0;
	while(x)
	{
		fx=top[x];
		ans+=ask(1,id[fx],id[x]);
		x=f[fx];
	}
	return ans;
}
void modify(rg x,rg val)
{
	int fx;
	while(x)
	{
		fx=top[x];
		set(1,id[fx],id[x],val);
		x=f[fx];
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("chain.in","r",stdin);
	freopen("chain.out","w",stdout);
	#endif
	read(n);
	for(rg i=2;i<=n;i++)
	{
		rg a;
		read(a);
		ins(a+1,i);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d f:%d son:%d top:%d s:%d id:%d\n",i,f[i],son[i],top[i],s[i],id[i]);
	read(q);
	for(rg i=1;i<=q;i++)
	{
		rg a;
		reads(ss);
		read(a);
		a++;
		if(ss[0]=='i')
		{
			printf("%d\n",d[a]-query(a));
			modify(a,1);
		}
		else
		{
			printf("%d\n",ask(1,id[a],id[last[a]]));
			set(1,id[a],id[last[a]],0);
		}
	}
	return 0;
}