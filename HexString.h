
#ifndef __HEXSTRING_HEADER__
#define __HEXSTRING_HEADER__

#ifdef  _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif//_WIN32

class CHex2String
{
public:
    // 
    // convert the hex to bytes.
    //
    void UChars2String(unsigned char *hex,long len, char *str)
    {
        int i;
        unsigned char  l4,h4;
        for(i=0; i<len; i++) {
            h4=(hex[i] & 0xf0)>>4;
            l4=hex[i] & 0x0f;
            if (h4<=9) 
                str[2*i] = h4 + ('0' -0);
            else
                str[2*i] = h4 + ('a'-10);

            if (l4<=9) 
                str[2*i+1] = l4 + ('0' -0);
            else
                str[2*i+1] = l4 + ('a'-10);
        }
        str[2*i]=0;
    }



    //
    // convert the string to hex string.
    //
    void String2UChars(const char *str, unsigned char  *hex, long *len=0)
    {
        unsigned char l4,h4;
        int i,lenstr;
        lenstr = (int)strlen(str);
        if(lenstr==0){
            if (len) *len = 0;
            return;
        }
        for(i=0; i<lenstr-(lenstr%2); i+=2){
            h4=asc2hex(str[i]);
            l4=asc2hex(str[i+1]);
            hex[i/2]=(h4<<4)+l4;
        }
        if(lenstr%2) {
            hex[(lenstr+1)/2-1]=asc2hex(str[lenstr-1]) << 4;
        }
        if (len) *len=(lenstr+1)/2;
    }


protected:
    unsigned char  asc2hex(char asccode)
    {
        unsigned char  ret;
        if('0'<=asccode && asccode<='9')
            ret=asccode-'0';
        else if('a'<=asccode && asccode<='f')
            ret=asccode-'a'+10;
        else if('A'<=asccode && asccode<='F')
            ret=asccode-'A'+10;
        else
            ret=0;
        return ret;
    }


    //
    // convert the ascii string to hex string.
    //
    void ascs2hex(unsigned char  *hex,unsigned char  *ascs,long srclen)
    {
        unsigned char  l4,h4;
        int i,lenstr;
        lenstr = srclen;
        if(lenstr==0){
            return;
        }
        if(lenstr%2)
            return;
        for(i=0; i<lenstr; i+=2){
            h4=asc2hex(ascs[i]);
            l4=asc2hex(ascs[i+1]);
            hex[i/2]=(h4<<4)+l4;
        }
    }
};

#endif//__HEXSTRING_HEADER__
