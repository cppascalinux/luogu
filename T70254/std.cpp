#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define inf 0x7FFFFFFF
using namespace std;
int n,m,cnt,len;
int v[100009];
int l[1009],r[1009],bel[100009];
int pos[100009],fst[100009];
int f[1009][100009];
void clr()
{
	cnt=0;
	memset(pos,0,sizeof(pos));
}
void init()
{
	len=sqrt(10*n);
	for(int i=1;i<=n;i++)
	{
		if(i>r[cnt])
		{
			cnt++;
			l[cnt]=r[cnt-1]+1;
			r[cnt]=min(n,l[cnt]+len-1);
		}
		bel[i]=cnt;
	}
}
void getf()
{
	for(int i=1;i<=cnt;i++)
	{
		for(int j=l[i];j<=r[i];j++)
			pos[v[j]]=j;
		fst[100001]=inf;
		for(int j=100000;j>=0;j--)
			fst[j]=pos[j]>=l[i]?j:fst[j+1];
		for(int j=1;j<=100000;j++)
		{
			f[i][j]=inf;
			for(int k=0;k<=100000;k+=j)
				if(fst[k]<inf)
					f[i][j]=min(f[i][j],fst[k]%j);
		//	printf("i:%d j:%d f:%d\n",i,j,f[i][j]);
		}
	}
}
int solve(int ll,int rr,int mod)
{
	int tl=bel[ll],tr=bel[rr];
	int ans=inf;
	if(tl==tr)
	{
		for(int i=ll;i<=rr;i++)
			ans=min(ans,v[i]%mod);
		return ans;
	}
	for(int i=tl+1;i<=tr-1;i++)
		ans=min(ans,f[i][mod]);
	for(int i=ll;i<=r[tl];i++)
		ans=min(ans,v[i]%mod);
	for(int i=l[tr];i<=rr;i++)
		ans=min(ans,v[i]%mod);
	return ans;
}
int main()
{
	for(int ttt=1;ttt<=20;ttt++)
	{
		char sin[20],sout[20];
		sprintf(sin,"sqrt%d.in",ttt);
		sprintf(sout,"sqrt%d.out",ttt);
		freopen(sin,"r",stdin);
		freopen(sout,"w",stdout);
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			scanf("%d",v+i);
		init();
		getf();
		for(int i=1,a,b,c;i<=m;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			printf("%d\n",solve(a,b,c));
		}
		clr();
	}
	return 0;
}
