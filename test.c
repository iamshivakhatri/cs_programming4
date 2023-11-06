#include <stdio.h>

int main(){
    char a = 'a';
    char b = 'b';

    int num = a - b;
    printf("Hello World!\n");

    char board[100]="  mHk tH l B He Flq p H  hByHlho H B  jr HFB ir j H FF ku gd  H pjB mH x  BF i H Bm oB HlHFBhoH BB ";

    char* player1 = board; // Initialize player 1 pointer


    printf("This is the address %p\n", player1);
    printf("This is the address %p\n", board);

    for(int i = 0; i < 100; i++){
        printf("This is %d and character %c\n",i, *(player1+i));
    }

    return 0;
}