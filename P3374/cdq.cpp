#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rc register char
#define rg register int
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000010];
int n,m,tot,totq;
int ans[500010],vist[500010];
struct node
{
	int o,p,x;
	bool operator < (const node &ot) const
	{
		return p<ot.p;
	}
}s[2000010],t[2000010];
void read(int &x)
{
	rc ch=0,inv=0;
	x=0;
	while(ch<'0'||ch>'9')
	{
		ch=gc();
		ch=='-'&&(inv=1);
	}
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch&15),ch=gc();
	inv==1&&(x=-x);
}
void solve(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	solve(l,mid);
	solve(mid+1,r);
	for(rg i=l;i<=r;++i)
		t[i]=s[i];
	rg sum=0,i=l-1,k=l-1;
	for(rg j=mid+1;j<=r;++j)
	{
		while(i+1<=mid&&t[i+1].p<=t[j].p)
		{
			s[++k]=t[++i];
			if(t[i].o==0)
				sum+=t[i].x;
		}
		s[++k]=t[j];
		if(t[j].o==1)
			ans[t[j].x]-=sum;
		else if(t[j].o==2)
			ans[t[j].x]+=sum;
	}
	while(i+1<=mid)
		s[++k]=t[++i];
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("cdq.in","r",stdin);
	freopen("cdq.out","w",stdout);
	#endif
	read(n);
	read(m);
	// printf("n:%d m:%d\n",n,m);
	for(rg i=1;i<=n;i++)
	{
		read(s[i].x);
		s[i].o=0;
		s[i].p=i;
	}
	tot=n;
	int a,b,c;
	for(rg i=1;i<=m;i++)
	{
		read(a);
		read(b);
		read(c);
		// printf("a:%d b:%d c:%d\n",a,b,c);
		if(a==1)
		{
			s[++tot].o=0;
			s[tot].p=b;
			s[tot].x=c;
		}
		else
		{
			vist[i]=1;
			s[++tot].o=1;
			s[tot].p=b-1;
			s[tot].x=++totq;
			s[++tot].o=2;
			s[tot].p=c;
			s[tot].x=totq;
		}
	}
	// for(rg i=1;i<=tot;i++)
	// 	printf("i:%d o:%d p:%d x:%d\n",i,s[i].o,s[i].p,s[i].x);
	solve(1,tot);
	// printf("\nafter\n\n");
	// for(rg i=1;i<=tot;i++)
	// 	printf("i:%d o:%d p:%d x:%d\n",i,s[i].o,s[i].p,s[i].x);
	for(rg i=1;i<=totq;i++)
			printf("%d\n",ans[i]);
	return 0;
}