#include "./p256/p256.c"
#include "./stylus-lib/stylus.h"

ArbResult user_main(uint8_t * args, size_t args_len) {
    const uint8_t * sig = args; // 64 byte sig
    const uint8_t * pk = args + 64; // 65 byte key 
    const uint8_t * input = args + 129; // variable length key
    const uint64_t length = args_len - 129; // length of the key

    // call p256_verify on the results
    p256_ret_t res = p256_verify(input, length, sig, pk);

    if (res == P256_INVALID_SIGNATURE) {

        // simply return a failure here 
        return (ArbResult) {
            .status = Failure,
            .output = args,
            .output_len = 0,
        };
    }

    return (ArbResult) {
        .status = Success,
        .output = args,
        .output_len = 0,
    };
}


// sets user_main as the entrypoint
ENTRYPOINT(user_main);


// define these two curves as a hack -- doesn't like the reactor exec model without them
// DO NOT USE
const br_ec_curve_def br_secp521r1 = {
	BR_EC_secp256r1,
	P256_N, sizeof P256_N,
	P256_G, sizeof P256_G
};

const br_ec_curve_def br_secp384r1 = {
	BR_EC_secp256r1,
	P256_N, sizeof P256_N,
	P256_G, sizeof P256_G
};