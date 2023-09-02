## P256 verification using Arbitrum stylus

Examples of c code compiled to stylus to verify a ECDSA signature using a standard P256 Curve.

This is useful for many use cases because P.256/secp256r1/prime256v1 is much more common than the curve built into the EVM.

As an example, Apple Face ID and webauthn signatures must be verified using this curve.

This repo also includes a sample solidity contract to call the stylus contract.

**IMPORTANT: this is not tested / audited, and likely has significant bugs**

## Building.
The P256 library requires the C stdlib, so we need to use wasi-sdk.

to get it, run the following
```bash
export WASI_VERSION=20
export WASI_VERSION_FULL=${WASI_VERSION}.0
wget https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-${WASI_VERSION}/wasi-sdk-${WASI_VERSION_FULL}-linux.tar.gz
tar xvf wasi-sdk-${WASI_VERSION_FULL}-linux.tar.gz

/// then, once installed, build with this:

export WASI_SDK_PATH=`pwd`/wasi-sdk-${WASI_VERSION_FULL}
CC="${WASI_SDK_PATH}/bin/clang --sysroot=${WASI_SDK_PATH}/share/wasi-sysroot"
$CC *.c -o out/p256.wasm -mbulk-memory -Wl,--no-entry -mexec-model=reactor -O3
```
The wasisdk compiler seems to ignore the --no-entry flag, unless we use the `-mexec-model=reactor`

## deploying

install the dependency for cargo-stylus, which is the deployer library.

```$ cargo install cargo-stylus```

```$ cargo stylus deploy --wasm-file-path=out/p256.wasm```

this version is deployed at: 0xff92a41a7edb4af7862868031121dbdba3319270385ed3b8b49544c118757fa7

## Usage
I included a simply econtract (caller.sol) to demonstrate how to call the deployed stylus contract. It also can be verified on their block explorer this way.

Try using this on the sepolia stylus testnet, using a sample deploy of this contract.
[View the contract in the block explorer](https://stylus-testnet-explorer.arbitrum.io/address/0xfdECC62c5ed1158B75e02aD9f38da34BBE87572A/write-contract#address-tabs)

Valid inputs:
```
sig:        0x6c98b6809f6e2c7395c6c9f18a302821c5f60369d3abd192e9e5c4f607d518d34a9d74a0f44c61031330a7e3f27908f5c589fe6427db7c3f3f7409559e500c3c
pubkey:     0x045616ab0df85ac89cc853b84e53cab535224a7dbc39270276dda800853ee8ae9b68b95359704f87e023424d5d842f0821d88ce01fb6a81a6a1c878a81130c6168
message:    0x68690a
```

Using these inputs, [the call](https://stylus-testnet-explorer.arbitrum.io/tx/0x262d63de85365cad7bbd34e07640542430bf09be7748ab2070a5bc706db85c83) does NOT revert.

If you change the message, it correctly reverts [see here](https://stylus-testnet-explorer.arbitrum.io/tx/0xf4bda5bb1b48fa7cbe3eb8063848f58bb9e211f664e4b5ff2d0b6a046bc5be96/logs)!