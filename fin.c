#include<stdio.h>
#include<string.h>

#define MAX_LEN 100

typedef struct{
    char data[MAX_LEN];
} String;

String removespace(String s) {
    String result;
    int j = 0;

    for (int i = 0; s.data[i] != 0; i++){
        char c = s.data[i];

        if (!(c == ' ' || c == '\n' || c == '\t')){
            result.data[j++] = c;
        }
    }
    result.data[j] = '\0';

    return result;
}
int main(){
    String s = {"  Hello world\n"};
    String r = removespace(s);

    printf("%s", r.data);

    return 0;
}