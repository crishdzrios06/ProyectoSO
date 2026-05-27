#include "seguridad.h"

#include <openssl/sha.h>

#include <stdio.h>
#include <string.h>

void hash_password(const char* password, char* output) {

    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(
        (unsigned char*)password,
        strlen(password),
        hash
    );

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {

        sprintf(
            output + (i * 2),
            "%02x",
            hash[i]
        );
    }

    output[64] = 0;
}