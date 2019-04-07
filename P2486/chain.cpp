#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
#define rgc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define read(x) \
{ \
	rgc ch=0; \
	x=0; \
	while(ch<'0'||ch>'9') \
		ch=gc(); \
	while(ch>='0'&&ch<='9') \
		x=(x<<1)+(x<<3)+(ch&15),ch=gc(); \
}
#define readc(x) \
{ \
	x=0; \
	while(x<'A'||x>'Z') \
		x=gc(); \
}
#define ins(a,b) \
{ \
	edge[++tot]=b; \
	nxt[tot]=head[a]; \
	head[a]=tot; \
}
#define update(x) \
{ \
	sum[x]=sum[x<<1]+sum[x<<1|1]-(rc[x<<1]==lc[x<<1|1]); \
	lc[x]=lc[x<<1]; \
	rc[x]=rc[x<<1|1]; \
}
#define down(x) \
{ \
	if(~lazy[x]) \
	{ \
		int lx=x<<1,rx=x<<1|1,t=lazy[x]; \
		lazy[x]=-1; \
		lazy[lx]=lazy[rx]=t; \
		sum[lx]=sum[rx]=1; \
		lc[lx]=rc[lx]=lc[rx]=rc[rx]=t; \
	} \
}
char *p1,*p2,buffer[10000010];
int n,m,tot,tot1;
int num[100010];
int head[100010],edge[200010],nxt[200010];
int s[100010],son[100010],d[100010],f[100010];
int id[100010],top[100010],pos[100010];
int sum[400010],l[400010],r[400010],lc[400010],rc[400010],lazy[400010];
int ltx[200010],rtx[200010],lty[100010],rty[100010],topx,topy;
int ml,mr;
void dfs1(int x,int fa)
{
	f[x]=fa;
	d[x]=d[fa]+1;
	s[x]=1;
	for(int i=head[x];i;i=nxt[i])
		if(edge[i]^fa)
		{
			dfs1(edge[i],x);
			s[x]+=s[edge[i]];
			s[edge[i]]>s[son[x]]&&(son[x]=edge[i]);
		}
}
void dfs2(int x,int t)
{
	top[x]=t;
	id[x]=++tot1;
	pos[tot1]=x;
	if(son[x])
		dfs2(son[x],t);
	for(int i=head[x];i;i=nxt[i])
		if(edge[i]^son[x]&&edge[i]^f[x])
			dfs2(edge[i],edge[i]);
}
void build(int a,int ll,int rr)
{
	l[a]=ll;
	r[a]=rr;
	lazy[a]=-1;
	if(ll==rr)
	{
		sum[a]=1;
		lc[a]=rc[a]=num[pos[ll]];
	}
	else
	{
		int mid=(ll+rr)>>1;
		build(a<<1,ll,mid);
		build(a<<1|1,mid+1,rr);
		update(a);
	}
}
void set(int a,int ll,int rr,int val)
{
	if(l[a]>rr||r[a]<ll)
		return;
	if(l[a]>=ll&&r[a]<=rr)
	{
		sum[a]=1;
		lc[a]=rc[a]=lazy[a]=val;
		return;
	}
	down(a);
	set(a<<1,ll,rr,val);
	set(a<<1|1,ll,rr,val);
	update(a);
}
int ask(int a,int ll,int rr)
{
	if(l[a]>rr||r[a]<ll)
		return 0;
	if(l[a]>=ll&&r[a]<=rr)
	{
		if(l[a]==ll)
			ml=lc[a];
		if(r[a]==rr)
			mr=rc[a];
		return sum[a];
	}
	down(a);
	int lans=ask(a<<1,ll,rr);
	int rans=ask(a<<1|1,ll,rr);
	// printf("lans:%d rans:%d\n",lans,rans);
	if(lans&&rans)
		return lans+rans-(rc[a<<1]==lc[a<<1|1]);
	return lans+rans;
}
void modify(int x,int y,int val)
{
	int fx=top[x],fy=top[y];
	while(fx^fy)
		if(d[fx]>=d[fy])
		{
			set(1,id[fx],id[x],val);
			x=f[fx];
			fx=top[x];
		}
		else
		{
			set(1,id[fy],id[y],val);
			y=f[fy];
			fy=top[y];
		}
	if(id[x]<=id[y])
		set(1,id[x],id[y],val);
	else
		set(1,id[y],id[x],val);
}
int query(int x,int y)
{
	topx=topy=0;
	int fx=top[x],fy=top[y],ans=0;
	while(fx^fy)
		if(d[fx]>=d[fy])
		{
			ans+=ask(1,id[fx],id[x]);
			ltx[++topx]=mr;
			rtx[topx]=ml;
			x=f[fx];
			fx=top[x];
		}
		else
		{
			ans+=ask(1,id[fy],id[y]);
			lty[++topy]=ml;
			rty[topy]=mr;
			y=f[fy];
			fy=top[y];
		}
	if(id[x]<=id[y])
	{
		ans+=ask(1,id[x],id[y]);
		ltx[++topx]=ml;
		rtx[topx]=mr;
	}
	else
	{
		ans+=ask(1,id[y],id[x]);
		lty[++topy]=mr;
		rty[topy]=ml;
	}
	for(rg i=topy;i>=1;i--)
	{
		ltx[++topx]=lty[i];
		rtx[topx]=rty[i];
	}
	for(rg i=2;i<=topx;i++)
		if(ltx[i]==rtx[i-1])
			ans--;
	return ans;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("chain.in","r",stdin);
	freopen("chain.out","w",stdout);
	#endif
	read(n);
	read(m);
	for(rg i=1;i<=n;i++)
		read(num[i]);
	for(rg i=1;i<=n-1;i++)
	{
		rg a,b;
		read(a);
		read(b);
		ins(a,b);
		ins(b,a);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d lc:%d rc:%d sum:%d\n",i,lc[i],rc[i],sum[i]);
	// for(rg i=1;i<=n;i++)
	// 	printf("i:%d top:%d f:%d s:%d son:%d id:%d pos:%d\n",i,top[i],f[i],s[i],son[i],id[i],pos[i]);
	while(m--)
	{
		rgc ch;
		readc(ch);
		if(ch=='C')
		{
			rg a,b,c;
			read(a);
			read(b);
			read(c);
			modify(a,b,c);
		}
		else
		{
			rg a,b;
			read(a);
			read(b);
			printf("%d\n",query(a,b));
		}
	}
	return 0;
}