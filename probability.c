#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define true 1
#define false 0

typedef int bool;
int N, M;

void draw(int position)
{
    switch(position)
    {
        case 1:
        {
            system("CLS");
            printf("########################## Toto Simulation ##########################\n# (Use arrow keys to navigate and press ENTER or press ESC to exit) #\n");
            printf("#                          ->1. 6/49                                #\n");
            printf("#                          2. 6/42                                  #\n");
            printf("#                          3. 5/35                                  #\n");
            printf("#####################################################################\n");
        }break;
        case 2:
        {
            system("CLS");
            printf("########################## Toto Simulation ##########################\n# (Use arrow keys to navigate and press ENTER or press ESC to exit) #\n");
            printf("#                          1. 6/49                                  #\n");
            printf("#                          ->2. 6/42                                #\n");
            printf("#                          3. 5/35                                  #\n");
            printf("#####################################################################\n");
        }break;
        case 3:
        {
            system("CLS");
            printf("########################## Toto Simulation ##########################\n# (Use arrow keys to navigate and press ENTER or press ESC to exit) #\n");
            printf("#                          1. 6/49                                  #\n");
            printf("#                          2. 6/42                                  #\n");
            printf("#                          ->3. 5/35                                #\n");
            printf("#####################################################################\n");
        }break;
    }
}

int* sort(int* arr, int cnt) {
    int* sorted = malloc(6 * sizeof(int));
    int min = arr[0];
    sorted[0] = arr[0];

    for(int i = 0; i < cnt; ++i) {
        if(arr[i] > sorted[0]) sorted[0] = arr[i];
    }
    for(int i = 0; i < cnt; ++i) {
        if(arr[i] < min) min = arr[i];
    }
    sorted[1] = min;
    sorted[2] = min;
    sorted[3] = min;
    sorted[4] = min;
    sorted[5] = min;
    for(int i = 0; i < cnt; ++i) {
        if(arr[i] < sorted[0] && arr[i] > sorted[1]) sorted[1] = arr[i];
    }
    for(int i = 0; i < cnt; ++i) {
        if(arr[i] < sorted[1] && arr[i] > sorted[2]) sorted[2] = arr[i];
    }
    for(int i = 0; i < cnt; ++i) {
        if(arr[i] < sorted[2] && arr[i] > sorted[3]) sorted[3] = arr[i];
    }
    for(int i = 0; i < cnt; ++i) {
        if(arr[i] < sorted[3] && arr[i] > sorted[4]) sorted[4] = arr[i];
    }
    for(int i = 0; i < cnt; ++i) {
        if(arr[i] < sorted[4] && arr[i] > sorted[5]) sorted[5] = arr[i];
    }
	

    return sorted;
}

void* function(void* arg)
{
    int (*nums)[N] = malloc(100000 * N * sizeof(int)), *p, cnt[M];
    memset(cnt, 0, sizeof(int) * M);
    srand(time(NULL));
    for(int i = 0; i < 100000; ++i) {
        for(int j = 0; j < N; ++j) {
            nums[i][j] = rand() % (M + 1 - 1) + 1;
        }
    }

    for(int i = 0; i < 100000; ++i) {
        for(int j = 0; j < N; ++j) {
            switch(nums[i][j]) {
                case 1: cnt[0]++; break;
                case 2: cnt[1]++; break;
                case 3: cnt[2]++; break;
                case 4: cnt[3]++; break;
                case 5: cnt[4]++; break;
                case 6: cnt[5]++; break;
                case 7: cnt[6]++; break;
                case 8: cnt[7]++; break;
                case 9: cnt[8]++; break;
                case 10: cnt[9]++; break;
                case 11: cnt[10]++; break;
                case 12: cnt[11]++; break;
                case 13: cnt[12]++; break;
                case 14: cnt[13]++; break;
                case 15: cnt[14]++; break;
                case 16: cnt[15]++; break;
                case 17: cnt[16]++; break;
                case 18: cnt[17]++; break;
                case 19: cnt[18]++; break;
                case 20: cnt[19]++; break;
                case 21: cnt[20]++; break;
                case 22: cnt[21]++; break;
                case 23: cnt[22]++; break;
                case 24: cnt[23]++; break;
                case 25: cnt[24]++; break;
                case 26: cnt[25]++; break;
                case 27: cnt[26]++; break;
                case 28: cnt[27]++; break;
                case 29: cnt[28]++; break;
                case 30: cnt[29]++; break;
                case 31: cnt[30]++; break;
                case 32: cnt[31]++; break;
                case 33: cnt[32]++; break;
                case 34: cnt[33]++; break;
                case 35: cnt[34]++; break;
                case 36: cnt[35]++; break;
                case 37: cnt[36]++; break;
                case 38: cnt[37]++; break;
                case 39: cnt[38]++; break;
                case 40: cnt[39]++; break;
                case 41: cnt[40]++; break;
                case 42: cnt[41]++; break;
                case 43: cnt[42]++; break;
                case 44: cnt[43]++; break;
                case 45: cnt[44]++; break;
                case 46: cnt[45]++; break;
                case 47: cnt[46]++; break;
                case 48: cnt[47]++; break;
                case 49: cnt[48]++; break;
            }
        }
    }

    p = sort(cnt, M);
    printf("------Most common numbers in 100000 iterations(%d/%d)------\n", N, M);
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < M; ++j) {
            if(p[i] == cnt[j]) {
                printf("%d  (%d times out of 100000)\n", j+1, p[i]);
            }
        }
    }
    free(p);
    free(nums);
    system("pause");
    return NULL;
}

int main(void) {
    bool finished = false;
    int ch, pos = 1;
    pthread_t thread_id;
    while(!finished)
    {
        draw(pos);
        ch = getch();
        if(ch == 0 || ch == 224)
        {
            switch(ch = getch())
            {
                case 72:  pos--; break;
                case 80: pos++; break;
            }
            if(pos < 1) pos = 3;
            else if(pos > 3) pos = 1;
        }
        switch(ch)
        {
            case 27: finished = true; break;
            case 13:
            {
                switch(pos)
                {
                    case 1: {N = 6; M = 49; pthread_create(&thread_id, NULL, function, NULL); pthread_join(thread_id, NULL);} break;
                    case 2: {N = 6; M = 42; pthread_create(&thread_id, NULL, function, NULL); pthread_join(thread_id, NULL);} break;
                    case 3: {N = 5; M = 35; pthread_create(&thread_id, NULL, function, NULL); pthread_join(thread_id, NULL);} break;
                }
            }
        }
    }

    return 0;
}
