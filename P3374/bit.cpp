#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
#define rc register char
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define lb(x) (x&-x)
using namespace std;
char *p1,*p2,buffer[10000010];
int n,m;
int c[500010];
int sum[500010];
void read(int &x)
{
	rc ch=0,inv=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc(),ch=='-'&&(inv=1);
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch&15),ch=gc();
	inv&&(x=-x);
}
void add(int x,int val)
{
	for(rg i=x;i<=n;i+=lb(i))
		c[i]+=val;
}
int ask(int x)
{
	rg val=0;
	for(rg i=x;i;i-=lb(i))
		val+=c[i];
	return val;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("cdq.in","r",stdin);
	freopen("bit.out","w",stdout);
	#endif
	read(n);
	read(m);
	for(rg i=1;i<=n;++i)
	{
		read(sum[i]);
		sum[i]+=sum[i-1];
		c[i]=sum[i]-sum[i-lb(i)];
	}
	int a,b,c;
	for(rg i=1;i<=m;++i)
	{
		read(a);
		read(b);
		read(c);
		if(a==1)
			add(b,c);
		else
			printf("%d\n",ask(c)-ask(b-1));
	}
	return 0;
}