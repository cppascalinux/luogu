//2019.05.20
//P3772 [CTSC2017]游戏 期望dp转矩阵乘法,线段树维护区间乘积+前缀乘积区间和
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define db double
using namespace std;
struct mat
{
	db v[2][2];
	mat(){memset(v,0,sizeof(v));}
	mat(db a,db b,db c,db d){v[0][0]=a,v[0][1]=b,v[1][0]=c,v[1][1]=d;}
	mat operator +(mat p){return mat(v[0][0]+p.v[0][0],v[0][1]+p.v[0][1],v[1][0]+p.v[1][0],v[1][1]+p.v[1][1]);}
	mat operator -(mat p){return mat(v[0][0]-p.v[0][0],v[0][1]-p.v[0][1],v[1][0]-p.v[1][0],v[1][1]-p.v[1][1]);}
	mat operator *(mat p)
	{
		mat ans;
		for(int i=0;i<=1;i++)
			for(int j=0;j<=1;j++)
				for(int k=0;k<=1;k++)
					ans.v[i][j]+=v[i][k]*p.v[k][j];
		return ans;
	}
};
int n,m;
mat org[200009];
int l[800009],r[800009];
mat msm[800009],adm[800009];
void update(int a)
{
	int la=a<<1,ra=a<<1|1;
	msm[a]=msm[ra]*msm[la];
	adm[a]=adm[la]+adm[ra]*msm[la];
}
void build(int a,int ll,int rr)
{
	l[a]=ll;
	r[a]=rr;
	if(ll==rr)
	{
		msm[a]=adm[a]=org[ll];
		return;
	}
	int mid=(ll+rr)>>1;
	build(a<<1,ll,mid);
	build(a<<1|1,mid+1,rr);
	update(a);
}
void setm(int a,int pos,mat val)
{
	if(l[a]==r[a])
	{
		msm[a]=adm[a]=val;
		return;
	}
	if(pos<=r[a<<1])
		setm(a<<1,pos,val);
	else
		setm(a<<1|1,pos,val);
	update(a);
}
void dbg()
{
	mat ans=org[1];
	for(int i=2;i<=n;i++)
		ans=org[i]*ans;
	for(int i=0;i<=1;i++)
		for(int j=0;j<=1;j++)
			printf("i:%d j:%d v:%lf\n",i,j,ans.v[i][j]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	char s[10];
	scanf("%d%d%s",&n,&m,s);
	db p,q;
	scanf("%lf",&q);
	org[1]=mat(0,q,0,1);
	for(int i=2;i<=n;i++)
	{
		scanf("%lf%lf",&p,&q);
		org[i]=mat(p-q,q,0,1);
	}
	// dbg();
	build(1,1,n);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%s%d",s,&a);
		if(s[0]=='a')
		{
			scanf("%d",&b);
			printf("a:%d b:%d\n",a,b);
			if(b==1)
				setm(1,a,mat(0,1,0,1));
			else
				setm(1,a,mat(0,0,0,1));
		}
		else
			setm(1,a,org[a]);
		printf("%.6lf\n",adm[1].v[0][1]);
	}
	return 0;
}