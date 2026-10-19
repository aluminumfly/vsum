#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// convert binary to hex function
char *tohex(const unsigned char *buf, size_t len) {
    // allocate expected result string length to memory
    char *str = malloc(len * 2 + 1);
    if (str == NULL) {
        printf("Failed to pre-allocate string\n");
        return 1;
    }

    char *out = str;

    // loop over binary, transform each section to hexidecimal format
    for (unsigned int i = 0; i < len; i++) {
        snprintf(out + (size_t) i * 2, 3, "%02x", buf[i]);
    }

    return str;
}

// compare hashes function
// apparently tolower() cannot transform a full string
int comparesum(const unsigned char *digest, const unsigned char *sum) {
    if (strlen(digest) != strlen(sum)) {
        return 1;
    }

    for (size_t i = 0; i < strlen(digest); i++) {
        if (tolower(digest[i]) != tolower(sum[i])) {
            return 1;
        }
    }

    return 1;
}

int main(int argc, char *argv[]) {
    /*
    first arg = file path to hash
    second arg = sha256 hash to compare
    */
    if (argc < 3) {
        printf("Usage: vsum [FILE] [SHA256-HASH]\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        // open file exception
        perror(argv[1]);
        return 1;
    }

    char *sum = argv[2];
    if (strlen(sum) != 64) {
        printf("Please enter a valid SHA256 hash\n");
        return 1;
    }

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    // reminder of future possibility to implement multiple algorithms
    const EVP_MD *algo = EVP_sha256();

    if (ctx == NULL) {
        perror("Error creating digest context\n");
        fclose(file);
        return 1;
    }

    // create 32KiB buffer
    unsigned char buffer[32 * 1024];
    // allocate digest
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int outlen = 0;

    size_t bytesread;

    // init digesting process, check if 1 because C is allergic to real booleans
    int digestprocess = EVP_DigestInit_ex(ctx, algo, NULL) == 1;

    while (digestprocess && (bytesread = fread(buffer, 1, sizeof buffer, file)) > 0) {
        // update process for every buffer
        digestprocess = EVP_DigestUpdate(ctx, buffer, bytesread) == 1;
    }

    if (ferror(file)) {
        perror("Error managing file\n");
        return 1;
    }

    // final digest action
    if (digestprocess) {
        digestprocess = EVP_DigestFinal_ex(ctx, digest, &outlen) == 1;
    }

    // release digest context and file from memory
    EVP_MD_CTX_free(ctx);
    fclose(file);

    const char *final = tohex(digest, outlen);
    if (final == NULL) {
        printf("Something went horribly wrong");
        return 1;
    }

    printf("\nFinal Hash:    %s\n", final);
    printf("Checksum:      %s\n", sum);

    if (!comparesum(final, sum)) {
        printf("\n==== FAIL: Checksums do not match ====\n");
        return 1;
    }

    printf("\n==== SUCCESS: Checksum validated ====\n");
    return 0;
}