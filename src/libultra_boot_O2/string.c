#include "global.h"

const char* strchr(const char* str, s32 ch) {
    u8 c = ch;

    while (*str != c) {
        if (*str == 0) {
            return NULL;
        }
        str++;
    }
    return str;
}

u32 strlen(const char* str) {
    const char* ptr = str;

    while (*ptr) {
        ptr++;
    }
    return ptr - str;
}

void* memcpy(void* dst, const void* src, u32 size) {
    u8* _dst = dst;
    const u8* _src = src;

    while (size > 0) {
        *_dst++ = *_src++;
        size--;
    }
    return dst;
}

char* reverseItoa(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
     return s;
 }

char* itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     return reverseItoa(s);
 }

char *strcpy(char *dest, const char *src)
{
   char *save = dest;
   while(*dest++ = *src++);
   return save;
}

char* strcat(char *dest, const char *src){
    strcpy(dest + strlen(dest), src);
    return dest;
}