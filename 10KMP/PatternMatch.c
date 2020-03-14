#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*C语言string.h库函数strstr即可实现PatternMatch
char strstr(char *string, char *pattern)
*/
#define NotFound -1
typedef int Position;

void BuildMatch(char *pattern, int *match)
{
    int i, j, m;
    m = strlen(pattern); //O(m)

    match[0] = -1;
    for (j = 1; j < m; j++)
    { //O(m)
        i = match[j - 1];
        while (i > 0 && pattern[j] != match[i] + 1)
            i = match[i] + 1;
        if (pattern[j] == match[i] + 1)
            match[j] = i + 1;
        else
            match[j] = -1;
    }
}

Position KMP(char *string, char *pattern){  //O(n + m)
    int s, p;                               //s和p分别是string和pattern的指针
    int n = strlen(string);                 //string的长度，扫描的时间复杂度是O(n)
    int m = strlen(pattern);                //pattern的长度，扫描的时间复杂度是O(m)
    if(n < m) return NotFound;
    int *match =(int*)malloc(sizeof(int)*m);
    BuildMatch(pattern, match);
    s = p = 0;
    while(s < n && p < m){                  //O(n)
        if(string[s] == pattern[p]){
            s++;
            p++;
        }
        else if(p>0){
            p = match[p-1] + 1;             //p和s不相等时，找到p的前一个位置的匹配位置，然后从后一个位置开始再继续比较，即p的指针位置
        }
        else s++;                           //p=0,说明第一个字符开始就不相等，所以只移动s指针即可
    }
    return p == m ? (s-m):NotFound; 
}

int main(){
    char string[] = "This is a simple sentnece";
    char pattern[] = "simple";
    Position P = KMP(string, pattern);
    if(P == NotFound) printf("Not Found.\n");
    else printf("%s\n", string+P);
}
