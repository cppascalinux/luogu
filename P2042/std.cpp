#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 0x7F7F7F7F
using namespace std;
int n,m;
int num[500010],tmp[500010],sum[500010];
char s[100];
void insert()
{
	int pos,tot,l,r;
	scanf("%d%d",&pos,&tot);
	for(int i=n;i>=pos+1;i--)
		num[i+tot]=num[i];
	for(int i=1;i<=tot;i++)
		scanf("%d",tmp+i);
	for(int i=pos+1;i<=pos+tot;i++)
		num[i]=tmp[i-pos];
	n+=tot;
}
void del()
{
	int pos,tot,l,r;
	scanf("%d%d",&pos,&tot);
	for(int i=pos;i<=n;i++)
		num[i]=num[i+tot];
	n-=tot;
}
void set()
{
	int pos,tot,val;
	scanf("%d%d%d",&pos,&tot,&val);
	for(int i=pos;i<=pos+tot-1;i++)
		num[i]=val;
}
void reverse()
{
	int pos,tot,l,r;
	scanf("%d%d",&pos,&tot);
	l=pos;
	r=pos+tot-1;
	for(int i=l;i<=r;i++)
		tmp[i]=num[l+r-i];
	for(int i=l;i<=r;i++)
		num[i]=tmp[i];
}
int getsum()
{
	int pos,tot,l,r,ans=0;
	scanf("%d%d",&pos,&tot);
	l=pos;
	r=pos+tot-1;
	for(int i=l;i<=r;i++)
		ans+=num[i];
	return ans;
}
int getmax()
{
	int ans=0,minn=0;
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+num[i];
	for(int i=1;i<=n;i++)
	{
//		printf("sum:%d min:%d\n",sum[i],minn);
		ans=max(ans,sum[i]-minn);
		minn=min(minn,sum[i]);
//		printf("i:%d ans:%d\n",i,ans);
	}
	return ans;
}
int main()
{
	freopen("splay.in","r",stdin);
	freopen("std.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",num+i);
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s);
		if(s[0]=='I')
			insert();
		else if(s[0]=='D')
			del();
		else if(s[0]=='M'&&s[2]=='K')
			set();
		else if(s[0]=='R')
			reverse();
		else if(s[0]=='G')
			printf("i:%d %d\n",i,getsum());
		else
			printf("i:%d %d\n",i,getmax());
//		printf("i:%d n:%d\n",i,n);
//		for(int i=1;i<=n;i++)
//			printf("%d ",num[i]);
//		printf("\n");
	}
	return 0;
}