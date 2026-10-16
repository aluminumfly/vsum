#include <openssl/evp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    /*
    first arg = file path to hash
    second arg = sha256 hash to compare
    */

    if (argc != 2) {
        printf("Usage: %s [FILE] [SHA256-HASH]", argv[0]);
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        // open file exception
        perror(argv[1]);
        return 1;
    }

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    // reminder of future possibility to implement multiple algorithms
    const EVP_MD *algo = EVP_sha256();

    if (ctx == NULL) {
        // debugging is important
        fprintf(stderr, "Failed to create digest context\n");
        fclose(file);
        return 1;
    }

    // create 32KiB buffer
    unsigned char buffer[32 * 1024];
    // allocate digest
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int outlen = 0;

    // init digesting status, check if 1 because C is allergic to real booleans
    int status = EVP_DigestInit_ex(ctx, algo, NULL) == 1;

    // beej taught me that size_t should belong here (https://beej.us/guide/bgc/html/#variable-types)
    size_t read;

    return 0;
}