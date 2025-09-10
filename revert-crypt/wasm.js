let wasm;

export async function initWasm() {
    if (!wasm) {
        wasm = await import("./pkg/crypt.js");
        await wasm.default();
    }
    return wasm;
}
