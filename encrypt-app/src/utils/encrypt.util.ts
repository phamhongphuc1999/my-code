import CryptoJS from "crypto-js";

export interface EncodeType {
    cipherText: ArrayBuffer;
    iv: Uint8Array;
}

export default class Encrypt {
    private static async deriveKey(publicKey: string) {
        const algo = {
            name: "PBKDF2",
            hash: "SHA-256",
            salt: new TextEncoder().encode("a-unique-salt"),
            iterations: 1000,
        };
        const _key = await crypto.subtle.importKey("raw", new TextEncoder().encode(publicKey), { name: algo.name }, false, ["deriveKey"]);
        return crypto.subtle.deriveKey(algo, _key, { name: "AES-GCM", length: 256 }, false, ["encrypt", "decrypt"]);
    }

    static async encrypt(text: string, password: string): Promise<EncodeType> {
        const algo = { name: "AES-GCM", length: 256, iv: crypto.getRandomValues(new Uint8Array(12)) };
        const cipherText = await crypto.subtle.encrypt(algo, await this.deriveKey(password), new TextEncoder().encode(text));
        return { cipherText, iv: algo.iv };
    }

    static async decrypt(encrypted: EncodeType, password: string) {
        const algo = { name: "AES-GCM", length: 256, iv: encrypted.iv };
        const decode = await crypto.subtle.decrypt(algo, await this.deriveKey(password), encrypted.cipherText);
        return new TextDecoder().decode(decode);
    }
}

export function uintArrayToString(data: Uint8Array) {
    return Buffer.from(data.buffer).toString("base64");
}

export function stringToUintArray(data: string) {
    return new Uint8Array(Buffer.from(data, "base64"));
}

export function arrayBufferToString(data: ArrayBuffer) {
    return Buffer.from(data).toString("hex");
}

export function stringToArrayBuffer(data: string) {
    const _arr: Array<number> = [];
    const _len = data.length;
    let counter = 0;
    while (counter < _len) {
        const _hex = data.slice(counter, counter + 2);
        _arr.push(parseInt(_hex, 16));
        counter += 2;
    }
    const temp = new Uint8Array(_arr);
    return temp;
}

export async function encode(text: string, password: string) {
    const encode = await Encrypt.encrypt(text, password);
    const _data = {
        cipherText: arrayBufferToString(encode.cipherText),
        iv: uintArrayToString(encode.iv),
    };
    return JSON.stringify(_data);
}

export async function decode(text: string, password: string) {
    const _data: { cipherText: string; iv: string } = JSON.parse(text);
    const data = await Encrypt.decrypt(
        {
            cipherText: stringToArrayBuffer(_data.cipherText).buffer,
            iv: stringToUintArray(_data.iv),
        },
        password
    );
    return data;
}

export function encryptText(text: string, password: string): string {
    const ciphertext = CryptoJS.AES.encrypt(text, password).toString();
    return ciphertext;
}

export function decryptText(ciphertext: string, password: string): string {
    const bytes = CryptoJS.AES.decrypt(ciphertext, password);
    const decrypted = bytes.toString(CryptoJS.enc.Utf8);
    return decrypted;
}
