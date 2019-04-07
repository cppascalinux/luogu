#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define rg register int
#define rc register char
#define lowbit(x) (x&-x)
#define update(x) s[x]=s[ch[x][0]]+s[ch[x][1]]+cnt[x]
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000010];
int n,k,tot;
int c[200010];
int ch[2000010][2],s[2000010],cnt[2000010],val[2000010],rnd[2000010];
int ans[100010],sum[100010];
struct node
{
	int a,b,c,id;
	bool operator < (const node &o) const
	{
		return a<o.a||(a==o.a&&b<o.b)||(a==o.a&&b==o.b&&c<o.c);
	}
	bool operator == (const node &o) const
	{
		return a==o.a&&b==o.b&&c==o.c;
	}
}p[100010];
void read(int &x)
{
	rc ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=(x<<3)+(x<<1)+(ch&15),ch=gc();
}
void rotate(int &x,int k)
{
	int y=ch[x][k];
	ch[x][k]=ch[y][k^1];
	ch[y][k^1]=x;
	update(x);
	update(y);
	x=y;
}
void insert(int &p,int x)
{
	if(!p)
	{
		p=++tot;
		val[p]=x;
		rnd[p]=rand();
		s[p]=cnt[p]=1;
		return;
	}
	s[p]++;
	if(x==val[p])
		cnt[p]++;
	else
	{
		int d=x>val[p];
		insert(ch[p][d],x);
		if(rnd[ch[p][d]]>rnd[p])
			rotate(p,d);
	}
}
int rnk(int p,int x)
{
	int ls=s[ch[p][0]];
	if(x==val[p]||!p)
		return ls;
	if(x<val[p])
		return rnk(ch[p][0],x);
	return ls+cnt[p]+rnk(ch[p][1],x);
}
void add(int x,int val)
{
	for(rg i=x;i<=k;i+=lowbit(i))
		insert(c[i],val);
}
int ask(int x,int val)
{
	rg ans=0;
	for(rg i=x;i;i-=lowbit(i))
		ans+=rnk(c[i],val+1);
	return ans;
}
void solve()
{
	for(int i=1;i<=n;i++)
	{
		ans[p[i].id]+=ask(p[i].b,p[i].c);
		add(p[i].b,p[i].c);
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("treap.out","w",stdout);
	#endif
	read(n);
	read(k);
	for(rg i=1;i<=n;i++)
	{
		read(p[i].a);
		read(p[i].b);
		read(p[i].c);
		p[i].id=i;
	}
	sort(p+1,p+n+1);
	solve();
	rg l=n;
	for(rg i=n-1;i>=1;i--)
	{
		if(p[i]==p[i+1])
			ans[p[i].id]+=l-i;
		else
			l=i;
	}
	for(rg i=1;i<=n;i++)
		sum[ans[i]]++;
	for(rg i=0;i<=n-1;i++)
		printf("%d\n",sum[i]);
	return 0;
}