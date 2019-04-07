#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,q,tot,t,tq;
int w[100009],c[100009];
int head[100009],edge[200009],nxt[200009];
int f[100009],top[100009],dep[100009],id[100009];
int pos[100009],son[100009],s[100009];
int ans[100009];
int sum[400009],mx[400009],l[400009],r[400009];
char ss[10];
struct node
{
	int typ,x,y,z;
	node(){}
	node(int a,int b,int c,int d)
	{
		typ=a;
		x=b;
		y=c;
		z=d;
	}
};
vector<node> mul[100009],inv[100009];
void read(int &x)
{
	rc ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void reads(char *ss)
{
	rc ch=0;
	rg p=0;
	while(ch<'A'||ch>'Z')
		ch=gc();
	while(ch>='A'&&ch<='Z')
		ss[++p]=ch,ch=gc();
}
void ins(int a,int b)
{
	edge[++tot]=b;
	nxt[tot]=head[a];
	head[a]=tot;
}
void dfs1(int x,int fa)
{
	f[x]=fa;
	dep[x]=dep[fa]+1;
	s[x]=1;
	for(int i=head[x];i;i=nxt[i])
		if(edge[i]^fa)
		{
			dfs1(edge[i],x);
			s[x]+=s[edge[i]];
			if(s[edge[i]]>s[son[x]])
				son[x]=edge[i];
		}
}
void dfs2(int x,int tp)
{
	top[x]=tp;
	id[x]=++t;
	pos[t]=x;
	if(son[x])
		dfs2(son[x],tp);
	for(int i=head[x];i;i=nxt[i])
		if(edge[i]^son[x]&&edge[i]^f[x])
			dfs2(edge[i],edge[i]);
}
void build(int a,int ll,int rr)
{
	l[a]=ll;
	r[a]=rr;
	if(ll^rr)
	{
		int mid=(ll+rr)>>1;
		build(a<<1,ll,mid);
		build(a<<1|1,mid+1,rr);
	}
}
void set(int a,int x,int val)
{
	if(l[a]==r[a])
	{
		mx[a]=sum[a]=val;
		return;
	}
	if(x<=r[a<<1])
		set(a<<1,x,val);
	else
		set(a<<1|1,x,val);
	mx[a]=max(mx[a<<1],mx[a<<1|1]);
	sum[a]=sum[a<<1]+sum[a<<1|1];
}
int askmax(int a,int ll,int rr)
{
	if(l[a]>rr||r[a]<ll)
		return 0;
	if(l[a]>=ll&&r[a]<=rr)
		return mx[a];
	return max(askmax(a<<1,ll,rr),askmax(a<<1|1,ll,rr));
}
int asksum(int a,int ll,int rr)
{
	if(l[a]>rr||r[a]<ll)
		return 0;
	if(l[a]>=ll&&r[a]<=rr)
		return sum[a];
	return asksum(a<<1,ll,rr)+asksum(a<<1|1,ll,rr);
}
int qmax(int a,int b)
{
	int fa=top[a],fb=top[b];
	int ans=0;
	while(fa^fb)
	{
		if(dep[fa]>dep[fb])
		{
			ans=max(ans,askmax(1,id[fa],id[a]));
			a=f[fa];
			fa=top[a];
		}
		else
		{
			ans=max(ans,askmax(1,id[fb],id[b]));
			b=f[fb];
			fb=top[b];
		}
	}
	if(id[a]<=id[b])
		ans=max(ans,askmax(1,id[a],id[b]));
	else
		ans=max(ans,askmax(1,id[b],id[a]));
	return ans;
}
int qsum(int a,int b)
{
	int fa=top[a],fb=top[b];
	int ans=0;
	while(fa^fb)
	{
		if(dep[fa]>dep[fb])
		{
			ans+=asksum(1,id[fa],id[a]);
			a=f[fa];
			fa=top[a];
		}
		else
		{
			ans+=asksum(1,id[fb],id[b]);
			b=f[fb];
			fb=top[b];
		}
	}
	if(id[a]<=id[b])
		ans+=asksum(1,id[a],id[b]);
	else
		ans+=asksum(1,id[b],id[a]);
	return ans;
}
void solve()
{
	node p;
	for(rg i=1;i<=100000;i++)
	{
		for(rg j=0;j<mul[i].size();j++)
		{
			p=mul[i][j];
			if(!p.typ)
				set(1,id[p.x],p.y);
			else if(p.typ==1)
				ans[p.z]=qsum(p.x,p.y);
			else
				ans[p.z]=qmax(p.x,p.y);
		}
		if(inv[i].size())
			for(rg j=inv[i].size()-1;j>=0;j--)
			{
				p=inv[i][j];
				set(1,id[p.x],p.y);
			}
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
	#endif
	read(n);
	read(q);
	for(rg i=1;i<=n;i++)
	{
		read(w[i]);
		read(c[i]);
	}
	int a,b;
	for(rg i=1;i<=n-1;i++)
	{
		read(a);
		read(b);
		ins(a,b);
		ins(b,a);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	for(rg i=1;i<=n;i++)
	{
		inv[c[i]].push_back(node(0,i,0,0));
		mul[c[i]].push_back(node(0,i,w[i],0));
	}
	for(rg i=1;i<=q;i++)
	{
		reads(ss);
		read(a);
		read(b);
		if(ss[2]=='C')
		{
			inv[c[a]].push_back(node(0,a,w[a],0));
			mul[c[a]].push_back(node(0,a,0,0));
			c[a]=b;
			inv[c[a]].push_back(node(0,a,0,0));
			mul[c[a]].push_back(node(0,a,w[a],0));
		}
		else if(ss[2]=='W')
		{
			inv[c[a]].push_back(node(0,a,w[a],0));
			w[a]=b;
			mul[c[a]].push_back(node(0,a,w[a],0));
		}
		else if(ss[2]=='S')
			mul[c[a]].push_back(node(1,a,b,++tq));
		else
			mul[c[a]].push_back(node(2,a,b,++tq));
	}
	solve();
	for(rg i=1;i<=tq;i++)
		printf("%d\n",ans[i]);
	return 0;
}