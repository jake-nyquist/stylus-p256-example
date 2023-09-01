// SPDX-License-Identifier: MIT 

pragma solidity 0.8.19;

// deployed here: https://stylus-testnet-explorer.arbitrum.io/address/0xfdECC62c5ed1158B75e02aD9f38da34BBE87572A/write-contract#address-tabs

contract VerifyP256 {
    address immutable verifier;
    constructor (address _verifier) {
        verifier = _verifier;
    }

    function ensureValidP256Signature(bytes calldata signature, bytes calldata publicKey, bytes calldata message) public {
        (bool success, ) = verifier.call(abi.encodePacked(signature, publicKey, message));
        if (!success) {
            revert("invalid signature");
        }
    }
}