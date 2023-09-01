# stylus-c-examples
examples of c code compiled to stylus

## Building.
this library requires the stdlib, so we need to use wasi-sdk.

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

install the dependency for cargo-stylus, which is the deployer
``` cargo install cargo-stylus```

```cargo stylus deploy --wasm-file-path=out/p256.wasm``````

this version is deployed at: 0xff92a41a7edb4af7862868031121dbdba3319270385ed3b8b49544c118757fa7
