use wasm_bindgen::prelude::*;
use aes::Aes256;
use cbc::{Encryptor, Decryptor};
use cipher::{
    block_padding::Pkcs7, BlockEncryptMut, BlockDecryptMut, KeyIvInit,
};
use sha2::{Sha256, Digest};
use base64::{engine::general_purpose, Engine as _};
use obfstr::obfstr;

mod domain;

pub use domain::*;

#[wasm_bindgen(start)]
pub fn main_js() {
    console_error_panic_hook::set_once();
}

fn derive_key(key: &str) -> [u8; 32] {
    let mut hasher = Sha256::new();
    hasher.update(key.as_bytes());
    let result = hasher.finalize();
    let mut key_bytes = [0u8; 32];
    key_bytes.copy_from_slice(&result);
    key_bytes
}

fn check_domain() {
    let _host = get_host();
    if _host != obfstr!("localhost:3011") && _host != obfstr!("experiment.peter-present.xyz") {
        panic!("{}", obfstr!("Something went wrong"));
    }
}

fn _encrypt(key: &str, iv: &[u8], plain: &str) -> String {
    check_domain();
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
pub fn encrypt(key: &str, iv: &[u8], plain: &str) -> String {
    _encrypt(key, iv, plain)
}

fn _decrypt(key: &str, iv: &[u8], cipher_b64: &str) -> String {
    check_domain();
    let key = derive_key(key);

    let mut buf = general_purpose::STANDARD.decode(cipher_b64).unwrap();
    let cipher = Decryptor::<Aes256>::new(&key.into(), iv.into());
    let decrypted = cipher.decrypt_padded_mut::<Pkcs7>(&mut buf).unwrap();

    String::from_utf8(decrypted.to_vec()).unwrap()
}

#[wasm_bindgen]
pub fn decrypt(key: &str, iv: &[u8], cipher_b64: &str) -> String {
    _decrypt(key, iv, cipher_b64)
}

fn _create_key(key: &str, iv: &[u8], timestamp: &str, uuid: &str) -> String {
    check_domain();
    let raw_result = format!("{}---{}", timestamp, uuid);
    encrypt(key, iv, &raw_result)
}

#[wasm_bindgen]
pub fn create_key(key: &str, iv: &[u8], timestamp: &str, uuid: &str) -> String {
    _create_key(key, iv, timestamp, uuid)
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

    #[test]
    fn test_create_key() {
        let key = "my secret key not 32 bytes"; // flexible size
        let iv = [0u8; 16];

        let str1 = "1234567";
        let str2 = "890";
        let result = create_key(key, &iv, str1, str2);
        let enc = encrypt(key, &iv, "1234567---890");

        assert_eq!(result, enc);
    }

    #[test]
    fn test_flow() {
        let key = "12345678";
        // let iv = [0u8; 16];
        let iv = [
        0x00, 0x11, 0x22, 0x33,
        0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xaa, 0xbb,
        0xcc, 0xdd, 0xee, 0xff,
    ];

        let str1 = "1755533523";
        let str2 = "ee05e338-5d0b-4bd6-99f6-41ab90eb1338";

        let password = create_key(key, &iv, str1, str2);
        println!("password: {}", password);

        let msg = "Hello, AES flexible size key!";
        let encrypted_msg = encrypt(&password, &iv, msg);
        let decrypted_msg = decrypt(&password, &iv, &encrypted_msg);
        
        assert_eq!(decrypted_msg, msg);
    }
}
