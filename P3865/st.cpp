#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m;
int a[100010];
int f[100010][20];
void init()
{
	for(int i=1;i<=n;i++)
		f[i][0]=a[i];
	int j,k;
	for(k=2,j=1;k<=n;k<<=1,j++)
		for(int i=1;i<=n-k+1;i++)
			f[i][j]=max(f[i][j-1],f[i+(k>>1)][j-1]);
}
int ask(int a,int b)
{
	int k=1,j=0;
	while(k<=b-a+1)
	{
		k<<=1;
		j++;
	}
	k>>=1;
	j--;
	return max(f[a][j],f[b-k+1][j]);
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("st.in","r",stdin);
	freopen("st.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	init();
	int x,y;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",ask(x,y));
	}
	return 0;
}