#include <stdio.h>
#include <string.h>

#define uint unsigned int
char flag[17];
int xor_num[16] = { 0x11, 0x45, 0x14, 0x19, 0x19, 0x81, 0x01, 0x14, 0x51, 0x41, 0x91, 0x91, 0x81, 0x00, 0x36, 0x33 };
int pow_num1[16] = { 'w', 'h', 'a', 't', ' ', 'd', 'o', ' ', 'u', ' ', 't', 'h', 'i', 'n', 'k', '?' };
int pow_num2[16] = { 'i', 's', 'n', 't', ' ', 't', 'h', 'i', 's', ' ', 'e', 'a', 's', 'y', '?', '!' };
int intended_result[16] = { 41, 204, 262, 413, 120, 355, 374, 487, 41, 576, 117, 414, 757, 492, 62, 6 };

uint naive_pow_mod(uint x, uint y, uint p) {
    uint res = 1;
    for (uint i = 1; i <= y; ++i) res = res * x % p;
    return res;
}

int check() {
    for (int i = 0; i < 16; ++i) {
        if ((naive_pow_mod(flag[i], pow_num1[i], 532) ^ naive_pow_mod(flag[i], pow_num2[i], 361) ^ xor_num[i]) != intended_result[i]) return 0;
    }
    return 1;
}

int main() {
    printf("Ah, give me your flag: ");
    scanf("%s", flag);
    if (strlen(flag) == 16 && check()) puts("Good job, you got the flag!");
    else puts("Nope, try again.");
}
