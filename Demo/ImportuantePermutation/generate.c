#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a1, int* a2)
{
  int tmp = *a1;
  *a1 = *a2;
  *a2 = tmp;
}

void sub_11E9(int* a1, int* a2)
{
  while (1) {
    if (a1 >= a2) break;
    --a2;
    swap(a1, a2);
    ++a1;
  }
}

void sub_1231(int* a1, int* a2)
{
  int *i = a2 - 2, *j = a2 - 1;
  while (i >= a1 && *i >= *(i + 1)) --i;
  if (i < a1) {
    sub_11E9(a1, a2);
    return;
  }
  while (*i >= *j) --j;
  swap(i, j);
  sub_11E9(i + 1, a2);
}

int main()
{
    int G[100]; // [rsp+10h] [rbp-7E0h] BYREF
    int Alice[100]; // [rsp+1A0h] [rbp-650h] BYREF
    int Bob[100]; // [rsp+330h] [rbp-4C0h] BYREF
    int Shared1[100]; // [rsp+4C0h] [rbp-330h] BYREF
    int Shard2[100]; // [rsp+650h] [rbp-1A0h] BYREF
    int * endPointer; // [rsp+7E0h] [rbp-10h] BYREF

    srand(time(0));
    int val1 = rand() % 10000000;
    int val2 = rand() % 10000000;
    for (int i = 0; i <= 99; ++i) G[i] = i;
    for (int i = 0; i <= 99; ++i) {
        int pos = rand() % (i + 1);
        swap(&G[i], &G[pos]);
    }
    for (int i = 0; i <= 99; ++i) printf("%d ", G[i]);
    putchar('\n');
    for (int i = 0; i <= 99; ++i) Alice[i] = G[i];
    for (int i = 0; i < val1; ++i) sub_1231(Alice, Bob);
    for (int i = 0; i <= 99; ++i) printf("%d ", Alice[i]);
    putchar('\n');
    for (int i = 0; i <= 99; ++i) Bob[i] = G[i];
    for (int i = 0; i < val2; ++i) sub_1231(Bob, Shared1);
    for (int i = 0; i <= 99; ++i) printf("%d ", Bob[i]);
    putchar('\n');
    for (int i = 0; i <= 99; ++i) Shared1[i] = Alice[i];
    for (int i = 0; i < val2; ++i) sub_1231(Shared1, Shard2);
    for (int i = 0; i <= 99; ++i) Shard2[i] = Bob[i];
    for (int i = 0; i < val1; ++i) sub_1231(Shard2, endPointer);
    for (int i = 0; i <= 99; ++i) {
        if (Shared1[i] != Shard2[i]) exit(-1);
    }
    for (int i = 0; i <= 99; ++i) printf("%d ", Shared1[i]);
    putchar('\n');
}