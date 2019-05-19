//2019.05.19
//luoguP1654 OSU! 维护每个位置为结尾时连续段长度的期望,平方和的期望,立方和的期望
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define db double
using namespace std;
int n;
db p[100009],f[100009],g[100009],h[100009];
int main()
{
#ifndef ONLINE_JUDGE
	freopen("osu.in","r",stdin);
	freopen("osu.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf",p+i);
	db ans=0;
	for(int i=1;i<=n;i++)
	{
		f[i]=(f[i-1]+1)*p[i];
		g[i]=(g[i-1]+2*f[i-1]+1)*p[i];
		h[i]=(h[i-1]+3*g[i-1]+3*f[i-1]+1)*p[i];
		ans+=h[i]*(1-p[i+1]);
	}
	printf("%.1lf",ans);
	return 0;
}