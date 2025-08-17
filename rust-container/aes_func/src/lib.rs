use wasm_bindgen::prelude::*;
use aes::Aes256;
use cbc::{Encryptor, Decryptor};
use cipher::{
    block_padding::Pkcs7, BlockEncryptMut, BlockDecryptMut, KeyIvInit,
};
use sha2::{Sha256, Digest};
use base64::{engine::general_purpose, Engine as _};

fn derive_key(key: &str) -> [u8; 32] {
    let mut hasher = Sha256::new();
    hasher.update(key.as_bytes());
    let result = hasher.finalize();
    let mut key_bytes = [0u8; 32];
    key_bytes.copy_from_slice(&result);
    key_bytes
}

#[wasm_bindgen]
pub fn encrypt(key: &str, iv: &[u8], plain: &str) -> String {
    let key = derive_key(key);

    let mut buf = plain.as_bytes().to_vec();
    // add capacity for padding up to next multiple of block size
    let bs = 16;
    let pad_len = bs - (buf.len() % bs);
    buf.extend(std::iter::repeat(0u8).take(pad_len));

    let cipher = Encryptor::<Aes256>::new(&key.into(), iv.into());
    let pos = plain.len();
    let ciphertext = cipher.encrypt_padded_mut::<Pkcs7>(&mut buf, pos).unwrap();

    general_purpose::STANDARD.encode(ciphertext)
}

#[wasm_bindgen]
pub fn decrypt(key: &str, iv: &[u8], cipher_b64: &str) -> String {
    let key = derive_key(key);

    let mut buf = general_purpose::STANDARD.decode(cipher_b64).unwrap();
    let cipher = Decryptor::<Aes256>::new(&key.into(), iv.into());
    let decrypted = cipher.decrypt_padded_mut::<Pkcs7>(&mut buf).unwrap();

    String::from_utf8(decrypted.to_vec()).unwrap()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_encrypt_decrypt() {
        let key = "my secret key not 32 bytes"; // flexible size
        let iv = [0u8; 16];
        let msg = "Hello, AES flexible size key!";

        let enc = encrypt(key, &iv, msg);
        println!("cipher: {}", enc);

        let dec = decrypt(key, &iv, &enc);
        assert_eq!(msg, dec);
    }
}
