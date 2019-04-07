#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
char ss[20];
char s1[20],s2[20],s3[20],s4[20];
int used[1010];
int top,dep[1010],num[1010];
void read(char *s,int &x)
{
	int i=0;
	x=0;
	while(s[i]<'0'||s[i]>'9')
		i++;
	while(s[i]>='0'&&s[i]<='9')
		x=(x*10)+(s[i]&15),i++;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("complexity.in","r",stdin);
	freopen("complexity.out","w",stdout);
	#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int maxx=0,err=0,p=0;
		scanf("%d%s",&n,ss);
		if(ss[2]=='1')
			p=0;
		else
			read(ss,p);
		// printf("p:%d\n",p);
		for(int i=1;i<=n;i++)
		{
			scanf("%s",s1);
			if(s1[0]=='E')
			{
				if(top<=0)
					err=1;
				else
				{
					used[num[top]]=0;
					top--;
				}
			}
			else
			{
				scanf("%s%s%s",s2,s3,s4);
				if(used[s2[0]])
					err=1;
				else
				{
					used[s2[0]]=1;
					num[++top]=s2[0];
					if(s3[0]=='n')
					{
						if(s4[0]=='n')
							dep[top]=dep[top-1];
						else
							dep[top]=-10000000;
					}
					else
					{
						if(s4[0]=='n')
							dep[top]=dep[top-1]+1;
						else
						{
							int fa,fb;
							read(s3,fa);
							read(s4,fb);
							if(fa<=fb)
								dep[top]=dep[top-1];
							else
								dep[top]=-10000000;
						}
					}
					maxx=max(maxx,dep[top]);
				}
			}
		}
		if(top>0)
			err=1;
		if(err)
			printf("ERR\n");
		else if(p==maxx)
			printf("Yes\n");
		else
			printf("No\n");
		top=0;
		memset(used,0,sizeof(used));
		memset(dep,0,sizeof(dep));
		memset(num,0,sizeof(num));
	}
	return 0;
}