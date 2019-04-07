#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;
const int inf=0x7FFFFFFF,ninf=0x80000000;
int n,tot,root;
int l[100010],r[100010],num[100010],rd[100010],s[100010],rep[100010];
void mt(int p)
{
	s[p]=s[l[p]]+s[r[p]]+rep[p];
}
void lt(int &p)
{
	int t=r[p];
	r[p]=l[t];
	l[t]=p;
	mt(p);
	mt(t);
	p=t;
}
void rt(int &p)
{
	int t=l[p];
	l[p]=r[t];
	r[t]=p;
	mt(p);
	mt(t);
	p=t;
}
void add(int &p,int x)
{
	if(!p)
	{
		p=++tot;
		num[p]=x;
		rd[p]=rand();
		s[p]=1;
		rep[p]=1;
		return;
	}
	s[p]++;
	if(x==num[p])
		rep[p]++;
	else if(x>num[p])
	{
		add(r[p],x);
		if(rd[r[p]]>rd[p])
			lt(p);
	}
	else if(x<num[p])
	{
		add(l[p],x);
		if(rd[l[p]]>rd[p])
			rt(p);
	}
}
void del(int &p,int x)
{
	if(!p)
		return;
	s[p]--;
	if(num[p]==x)
	{
		if(rep[p]>1)
			rep[p]--;
		else if(l[p]*r[p]==0)
			p=l[p]|r[p];
		else if(rd[l[p]]>rd[r[p]])
		{
			rt(p);
			del(p,x);
		}
		else if(rd[l[p]]<=rd[r[p]])
		{
			lt(p);
			del(p,x);
		}
	}
	else if(x<num[p])
		del(l[p],x);
	else if(x>num[p])
		del(r[p],x);
	mt(p);
}
int getrk(int x)
{
	int now=s[l[root]]+1,p=root;
	while(x!=num[p])
	{
		if(x>num[p])
		{
			now+=rep[p];
			p=r[p];
			now+=s[l[p]];
		}
		else if(x<num[p])
		{
			p=l[p];
			now-=rep[p];
			now-=s[r[p]];
		}
	}
	return now;
}
int rank(int p,int x)
{
	if(x==num[p]||!p)
		return s[l[p]]+1;
	if(x<num[p])
		return rank(l[p],x);
	return s[l[p]]+rep[p]+rank(r[p],x);
}
int kth(int p,int x)
{
	int t=s[l[p]];
	if(x>=t+1&&x<=t+rep[p])
		return num[p];
	if(x<=t)
		return kth(l[p],x);
	return kth(r[p],x-t-rep[p]);
}
int getx(int x)
{
	int now=s[l[root]]+1,p=root;
	while(x<now||x>now+rep[p]-1)
	{
		if(x>now+rep[p]-1)
		{
			now+=rep[p];
			p=r[p];
			now+=s[l[p]];
		}
		else if(x<now)
		{
			p=l[p];
			now-=rep[p];
			now-=s[r[p]];
		}
	}
	return num[p];
}
int fpre(int x)
{
	int p=root,ans=ninf;
	while(p)
	{
		if(x>num[p])
		{
			ans=max(num[p],ans);
			p=r[p];
		}
		else if(x<=num[p])
			p=l[p];
	}
	return ans;
}
int fnex(int x)
{
	int p=root,ans=inf;
	while(p)
	{
		if(x<num[p])
		{
			ans=min(num[p],ans);
			p=l[p];
		}
		else if(x>=num[p])
			p=r[p];
	}
	return ans;
}
void debug()
{
	printf("root:%d\n",root);
	for(int i=1;i<=tot;i++)
		printf("i:%d l:%d r:%d num:%d rep:%d s:%d\n",i,l[i],r[i],num[i],rep[i],s[i]);
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("treap.in","r",stdin);
	freopen("treap.out","w",stdout);
	#endif
	srand(time(0));
	scanf("%d",&n);
	int a,b;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a,&b);
		if(a==1)
			add(root,b);
		else if(a==2)
			del(root,b);
		else if(a==3)
			printf("%d\n",rank(root,b));
		else if(a==4)
			printf("%d\n",kth(root,b));
		else if(a==5)
		{
			int t=rank(root,b);
			printf("%d\n",kth(root,t-1));
		}
		else if(a==6)
		{
			int t=rank(root,b+1);
			printf("%d\n",kth(root,t));
		}
	}
//	debug();
	return 0;
}