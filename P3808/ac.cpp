#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define tr(x) (x-'a'+1)
using namespace std;
int n,ans,tot;
char ss[1000010],s[1000010];
int f[1000010],last[1000010],vist[1000010];
int a[1000010][30];
int q[1000010],l,r=-1;
void add()
{
    int now=0,len=strlen(ss);
    for(int i=len;i>=1;i--)
        ss[i]=tr(ss[i-1]);
    for(int i=1;i<=len;i++)
    {
        if(!a[now][ss[i]])
            a[now][ss[i]]=++tot;
        now=a[now][ss[i]];
    }
    last[now]++;
}
void get()
{
    int x;
    q[++r]=0;
    while(l<=r)
    {
        x=q[l++];
        for(int i=1;i<=26;i++)
            if(a[x][i])
            {
                int j=f[x];
                while(j&&!a[j][i])
                    j=f[j];
                if(x)
                    f[a[x][i]]=a[j][i];
                q[++r]=a[x][i];
            }
			else
				a[x][i]=a[f[x]][i];
    }
}
void solve()
{
    int j=0,len=strlen(s);
    for(int i=len;i>=1;i--)
        s[i]=tr(s[i-1]);
    for(int i=1;i<=len;i++)
    {
        j=a[j][s[i]];
		for(int k=j;k&&!vist[k];k=f[k])
		{
			ans+=last[k];
			vist[k]=1;
		}
    }
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("ac.in","r",stdin);
    freopen("ac.out","w",stdout);
#endif
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ss);
        add();
    }
    scanf("%s",s);
    get();
    solve();
    printf("%d",ans);
    return 0;
}