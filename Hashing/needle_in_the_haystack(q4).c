#include <stdio.h>
#include <stdlib.h>
#include<string.h>


int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int flag=0;
        char pat[1001],text[100001];
        scanf("%s",pat);
        scanf("%s",text);

        int pat_freq[26]={0};
        int text_freq[26]={0};

        int pat_len=strlen(pat);
        int text_len=strlen(text);

        int i=0;
        while(i<pat_len)
            pat_freq[pat[i++]-'a']++;

        int j=0;
        while(j<pat_len)
            text_freq[text[j++]-'a']++;

        for(int i=pat_len;i<text_len;i++)
        {
            int bool=1;
            for(int j=0;j<26;j++)
            {
                if(pat_freq[j]!=text_freq[j])
                {
                    bool=0;
                    break;
                }
            }
            if(bool)
            {
                flag=1;
                break;
            }
            text_freq[text[i-pat_len]-'a']--;
            text_freq[text[i]-'a']++;
        }

        int bool=1;

        for(int i=0;i<26 && flag==0;i++)
        {
            if(pat_freq[i]!=text_freq[i])
            {
                bool=0;
                break;
            }
        }
        if(bool==1)
            flag=1;

        if(flag==1)
            printf("YES\n");
        else
            printf("NO\n");

    }
}
