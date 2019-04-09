#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char s[20][100010];
int l[20];
int n,tot,lst;
int lnk[200010],len[200010],a[200010][30],ans[20][200010];
void solve(int x)
{
    char *ss=s[x];
    int p=0,ll=0,m=l[x];
    for(int i=1;i<=m;i++)
    {
        if(a[p][ss[i]])
        {
            p=a[p][ss[i]];
            ll++;
        }
        else
        {
            while(~p&&!a[p][ss[i]])
                p=lnk[p];
            if(~p)
            {
                ll=len[p]+1;
                p=a[p][ss[i]];
            }
            else
                ll=p=0;
        }
        for(int k=p;k&&ans[x][k]<len[k];k=lnk[k])
            ans[x][k]=max(ans[x][k],min(ll,len[k]));
    }
}
void add(int x)
{
    int cur=++tot,p;
    len[cur]=len[lst]+1;
    for(p=lst;~p&&!a[p][x];p=lnk[p])
        a[p][x]=cur;
    if(~p)
    {
        int q=a[p][x];
        if(len[q]==len[p]+1)
            lnk[cur]=q;
        else
        {
            int c=++tot;
            len[c]=len[p]+1;
            lnk[c]=lnk[q];
            memcpy(a[c],a[q],sizeof(a[c]));
            for(;~p&&a[p][x]==q;p=lnk[p])
                a[p][x]=c;
            lnk[q]=lnk[cur]=c;
        }
    }
    lst=cur;
}
void read()
{
    n=1;
    while(~scanf("%s",s[n]))
        n++;
    n--;
    for(int i=1;i<=n;i++)
    {
        l[i]=strlen(s[i]);
        for(int j=l[i];j>=1;j--)
            s[i][j]=s[i][j-1]-'a'+1;
    }
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("sam.in","r",stdin);
    freopen("std.out","w",stdout);
    #endif
    read();
    lnk[0]=-1;
    for(int i=1;i<=l[1];i++)
        add(s[1][i]);
//	for(int i=0;i<=tot;i++)
//		printf("i:%d len:%d lnk:%d\n",i,len[i],lnk[i]);
    for(int i=2;i<=n;i++)
        solve(i);
/*	for(int i=2;i<=n;i++)
    {
        for(int j=1;j<=tot;j++)
            printf("%d ",ans[i][j]);
        printf("\n");
    }
*/	for(int i=3;i<=n;i++)
        for(int j=1;j<=tot;j++)
            ans[2][j]=min(ans[2][j],ans[i][j]);
    int out=0;
    for(int i=1;i<=tot;i++)
        out=max(out,ans[2][i]);
    if(n==1)
        out=l[1];
    printf("%d",out);
    return 0;
}