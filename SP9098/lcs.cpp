//2020.08.03
//SPOJ LCS3 就一dp乱搞..时间复杂度O(n+qm^3logn)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define INF 0x7F7F7F7F
#define PII pair<int,int>
#define FI first
#define SE second
using namespace std;
int n,q;
int s[1000009];
vector<int> ps[100009];
int t[6],f[7][7];
PII sb[6];
void solve()
{
	int m;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
		scanf("%d",t+i),sb[i]=PII(t[i],i);
	memset(f,0,sizeof(f));
	f[m+1][0]=n+1;
	for(int i=m;i>=1;i--)
		for(int j=1;j<=m-i+1;j++)
		{
			for(int k=i+1;k<=m+1;k++)
			{
				int lp=f[k][j-1],v=t[i];
				auto p=lower_bound(ps[v].begin(),ps[v].end(),lp);
				if(p==ps[v].begin()||ps[v].size()==0)
					continue;
				p--;
				// printf("i:%d j:%d k:%d lp:%d p:%d v:%d\n",i,j,k,lp,*p,v);
				f[i][j]=max(f[i][j],*p);
			}
			// printf("i:%d j:%d f:%d\n",i,j,f[i][j]);
		}
	sort(sb+1,sb+m+1);
	int vi=0,vj=0;
	for(int j=m;j>=1;j--)
	{
		int bk=0;
		for(int i=1;i<=m;i++)
			if(f[sb[i].SE][j])
			{
				vi=sb[i].SE,vj=j,bk=1;
				break;
			}
		if(bk)
			break;
	}
	int lp=0;
	printf("%d ",vj);
	for(int i=vj;i>=1;i--)
	{
		int v=t[vi];
		printf("%d ",v);
		if(i>1)
		{
			lp=*upper_bound(ps[v].begin(),ps[v].end(),lp);
			// printf("vi:%d lp:%d\n",vi,lp);
			for(int j=1;j<=m;j++)
				if(sb[j].SE>vi&&f[sb[j].SE][i-1]>lp)
				{
					vi=sb[j].SE;
					break;
				}
		}
	}
	printf("\n");
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("lcs.in","r",stdin);
	freopen("lcs.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",s+i),ps[s[i]].push_back(i);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
		solve();
	return 0;
}