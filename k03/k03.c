#include <stdio.h>

#define DEBUG

#define ALPHABET_LEN    255

char StrOriginal[] = "On a dark deseart highway, cool wind in my hair.";
char StrKey[] = "wind";

char* ForceSearch(char text[], char key[])
{
    //  ここを実装する
    int start, pos, count=0, key_len;

    for(key_len=0 ; key[key_len] != '\0' ; key_len++);

    for(start=0 ; text[start] != '\0' ; start++){
        for(pos=0 ; key[pos] != '\0' ; pos++){
            if(text[start+pos] == key[pos]){
                count += 1;
                if(count == key_len){
                    return &text[start];
                }
            }
            else{
                break;
            }
        }
    }
    return NULL;
}

char* BMSearch(char text[], char key[])
{
    //  ここを実装する
    int index, key_index, newindex;
    int text_len, key_len;
    int table[256];
    int i, j;
    int count=0;

    for(text_len=0 ; text[text_len] != '\0'; text_len++);
    for(key_len=0 ; key[key_len] != '\0' ; key_len++);
    
    for(i=0 ; i<=ALPHABET_LEN ; i++){
        table[i] = key_len;
        for(j=0 ; j<key_len ; j++){
            if(i == key[j]){
                table[i] = key_len-j-1;
            }
        }
    }

    index = key_len-1;
    while(index < text_len){
        for(key_index=key_len-1 ; key_index>=0 ; key_index--){
            if(text[index] == key[key_index]){
                index -= 1;
                count += 1;
                if(count == key_len){
                    return &text[index+1];
                }
            }
            else{
                newindex = index + table[text[index]];
                if(newindex <= index){
                    index += 1;
                }
                else{
                    index = newindex;
                }
                break;
            }
        }
    }
    return NULL;
}

int main(void)
{
    char*   str;
    str = ForceSearch(StrOriginal, StrKey);
    printf("Force Search. Find keyword at:%s\n", str);

    str = BMSearch(StrOriginal, StrKey);
    printf("BM Search. Find keyword at:%s\n", str);

    return 0;
}