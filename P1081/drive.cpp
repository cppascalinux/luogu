#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
using namespace std;
typedef long long ll;
const int inf=0x7FFFFFFF;
int n,x0,m;
int h[100010];
int m1[100010],m2[100010],l1[100010],l2[100010];
int fx[100010][20];
ll fl[100010][20],fl1[100010][20],fl2[100010][20];
ll ans1,ans2;
struct node
{
	int num,h0,h1;
	node(){}
	node(int a,int b,int c)
	{
		num=a;
		h0=b;
		h1=c;
	}
	void clr()
	{
		num=0;
		h0=h1=inf;
	}
	bool operator < (const node &o) const
	{
		return h1<o.h1||(h1==o.h1&&h0<o.h0);
	}
};
set<node> s;
set<node>::iterator it1,it2;
node t[10];
void getm()
{
	for(int i=n;i>=1;i--)
	{
		int tot=0;
		for(int j=0;j<=9;j++)
			t[j].clr();
		it1=it2=s.insert(node(i,h[i],h[i])).first;
		it1++;
		for(int j=1;j<=2&&it1!=s.end();j++,it1++)
			t[++tot]=node(it1->num,it1->h0,abs(it1->h1-h[i]));
		if(it2!=s.begin())
		{
			it2--;
			for(int j=1;j<=2;j++,it2--)
			{
				t[++tot]=node(it2->num,it2->h0,abs(it2->h1-h[i]));
				if(it2==s.begin())
					break;
			}
		}
		if(tot>0)
		sort(t+1,t+tot+1);
		m1[i]=t[1].num;
		l1[i]=t[1].h1;
		m2[i]=t[2].num;
		l2[i]=t[2].h1;
	}
}
void getk()
{
	for(int i=1;i<=n;i++)
	{
		fx[i][0]=m1[m2[i]];
		fl1[i][0]=l2[i];
		fl2[i][0]=l1[m2[i]];
		//printf("i:%d l1[m2[i]]:%d\n",i,l1[m2[i]]);
		fl[i][0]=fl1[i][0]+fl2[i][0];
	}
	for(int k=1;(1<<k)<=n;k++)
		for(int i=1;i<=n;i++)
		{
			fx[i][k]=fx[fx[i][k-1]][k-1];
			fl1[i][k]=fl1[i][k-1]+fl1[fx[i][k-1]][k-1];
			fl2[i][k]=fl2[i][k-1]+fl2[fx[i][k-1]][k-1];
			fl[i][k]=fl[i][k-1]+fl[fx[i][k-1]][k-1];
		}
}
void ask(int a,int b)
{
	ans1=ans2=0;
	ll ans=0;
	for(int i=18;i>=0;i--)
		if(fx[a][i]&&ans+fl[a][i]<=b)
		{
			ans1+=fl1[a][i];
			ans2+=fl2[a][i];
			ans+=fl[a][i];
			a=fx[a][i];
		}
	if(ans+l2[a]<=b&&m2[a])
		ans1+=l2[a];
}
void solve1()
{
	int ret=0;
	double out,lout=1e30;
	for(int i=1;i<=n;i++)
	{
		ask(i,x0);
		if(ans2==0)
			out=1e30;
		else
			out=ans1*1.0/ans2;
		if(out==lout)
		{
			if(h[i]>h[ret])
				ret=i;
		}
		else if(out<lout)
			ret=i;
		lout=min(out,lout);
	}
	printf("%d\n",ret);
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("drive.in","r",stdin);
	freopen("drive.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",h+i);
	getm();
	//getk();
	//for(int i=1;i<=n;i++)
	//	printf("i:%d m1:%d l1:%d m2:%d l2:%d fx:%d fl1:%lld fl2:%lld fl:%lld\n",i,m1[i],l1[i],m2[i],l2[i],fx[i][0],fl1[i][0],fl2[i][0],fl[i][0]);
	scanf("%d%d",&x0,&m);
	solve1();
	int a,b;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		ask(a,b);
		printf("%lld %lld\n",ans1,ans2);
	}
	return 0;
}