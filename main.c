#include <openssl/evp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    /*
    first arg = file path to hash
    second arg = sha256 hash to compare
    */
    if (argc < 3) {
        printf("Usage: %s [FILE] [SHA256-HASH]", argv[0]);
    }

    return 0;
}