use wasm_bindgen::prelude::*;
use aes::Aes128;
use cipher::{
    BlockEncrypt, BlockDecrypt, KeyInit,
    generic_array::GenericArray,
};

#[wasm_bindgen]
pub fn encrypt_block(input: &[u8]) -> Vec<u8> {
    // AES-128 key (16 bytes)
    let key = GenericArray::from_slice(b"examplekey123456");

    // IV (initialization vector) for AES in ECB here (block cipher demo)
    // In real usage, you should use AES-GCM or CBC with random IV.
    let cipher = Aes128::new(&key);

    // Ensure input is exactly 16 bytes for a single block
    let mut block = GenericArray::clone_from_slice(&input[0..16]);
    cipher.encrypt_block(&mut block);

    block.to_vec()
}

#[wasm_bindgen]
pub fn decrypt_block(input: &[u8]) -> Vec<u8> {
    let key = GenericArray::from_slice(b"examplekey123456");
    let cipher = Aes128::new(&key);

    let mut block = GenericArray::clone_from_slice(&input[0..16]);
    cipher.decrypt_block(&mut block);

    block.to_vec()
}
