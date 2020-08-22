//2020.08.19
//luoguP4072 [SDOI2016]征途 dp+斜率优化..O(nm)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
using namespace std;
struct pt
{
	int x,y;
};
int n,m;
int s[3009],sm[3009];
pt q0[3009][3009];
int tp0[3009],cur0[3009];
LL mul(pt a,pt b,pt c)
{
	return (LL)(b.x-a.x)*(c.y-a.y)-(LL)(c.x-a.x)*(b.y-a.y);
}
LL dp()
{
	for(int i=0;i<=m;i++)
	{
		tp0[i]=cur0[i]=1;
		q0[i][1]=pt{0,0};
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int &tp=tp0[j-1],&cur=cur0[j-1];
			pt *q=q0[j-1];
			while(cur<tp&&2LL*sm[i]*(q[cur+1].x-q[cur].x)>q[cur+1].y-q[cur].y)
				cur++;
			int nf=q[cur].y-2LL*sm[i]*q[cur].x+sm[i]*sm[i];
			if(i==n&&j==m)
				return nf;
			int &ntp=tp0[j],&ncr=cur0[j];
			pt *nq=q0[j];
			pt nx{sm[i],nf+sm[i]*sm[i]};
			while(ntp>1&&mul(nq[ntp-1],nq[ntp],nx)<=0)
				ntp--;
			nq[++ntp]=nx;
			ncr=min(ncr,ntp);
		}
	return 0;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("march.in","r",stdin);
	freopen("march.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",s+i),sm[i]=sm[i-1]+s[i];
	LL ans=m*dp()-(LL)sm[n]*sm[n];
	printf("%lld",ans);
	return 0;
}