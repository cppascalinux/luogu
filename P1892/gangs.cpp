#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rg register int
using namespace std;
int n,m;
int f[1009],enm[1009];
char s[10];
int find(int x)
{
    return x==f[x]?x:f[x]=find(f[x]);
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("gangs.in","r",stdin);
    freopen("gangs.out","w",stdout);
    #endif
    scanf("%d%d",&n,&m);
    for(rg i=1;i<=n;i++)
        f[i]=i;
    int a,b,fa,fb;
    for(rg i=1;i<=m;i++)
    {
        scanf("%s%d%d",s,&a,&b);
        if(s[0]=='E')
        {
            if(enm[a])
            {
                fa=find(enm[a]);
                f[find(b)]=fa;
            }
            if(enm[b])
            {
                fb=find(enm[b]);
                f[find(a)]=fb;
            }
            enm[a]=b;
            enm[b]=a;
        }
        else
            f[find(a)]=find(b);
    }
    int ans=0;
    for(rg i=1;i<=n;i++)
        if(find(i)==i)
            ans++;
    printf("%d",ans);
    return 0;
}