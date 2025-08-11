"use client";

import { encrypt_block, decrypt_block, initSync } from "../../public/pkg/aes";
import { globalQuery } from "@/utils/api.utils";
import { decode, decryptText } from "@/utils/encrypt.util";

export default function Home() {
    async function initWasm() {
        fetch("pkg/aes_bg.wasm")
            .then((res) => res.arrayBuffer())
            .then((bytes) => {
                initSync(bytes);
                const text = "Hello, AES in Rust";
                const padded = new TextEncoder().encode(text.padEnd(16, "\0")); // pad to 16 bytes

                const encrypted = encrypt_block(padded);
                console.log("Encrypted:", encrypted);

                const decrypted = decrypt_block(encrypted);
                console.log("Decrypted:", new TextDecoder().decode(decrypted));
            });
    }

    async function getNextJson() {
        const res = await fetch("/api/json");
        const stringJson = await res.json();
        console.log("🚀 ~ getNextJson ~ stringJson:", stringJson);
        console.log("stringJson", JSON.parse(decryptText(stringJson.message, "12345678")));
    }

    async function getJson() {
        const res = await globalQuery.getJson();
        console.log(res);
    }

    async function getWebApi() {
        const res = await globalQuery.getWebApi();
        console.log("res", res);
        const stringJson = await decode(res.data, "12345678");
        console.log("stringJson", JSON.parse(stringJson));
    }

    async function getCrypt() {
        const res = await globalQuery.getCrypt();
        console.log("res", res);
        const stringJson = decryptText(res.data, "12345678");
        console.log("stringJson", JSON.parse(stringJson));
    }

    return (
        <div className="inline-flex flex-col gap-2">
            <button className="border" onClick={getJson}>
                get json
            </button>
            <button className="border" onClick={getWebApi}>
                get web api
            </button>
            <button className="border" onClick={getCrypt}>
                crypt
            </button>
            <button className="border" onClick={getNextJson}>
                get next json
            </button>
            <button className="border" onClick={initWasm}>
                wasm
            </button>
        </div>
    );
}
