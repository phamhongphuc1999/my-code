import fs from "node:fs";

// const _____URL = "crypt_bg.final.wasm";
const _____URL = "pkg/crypt_bg.wasm";

const wasmBuffer = fs.readFileSync(_____URL);

let r;
let f = 0;
let wasm;
let cachedDataViewMemory0 = null;
let cachedUint8ArrayMemory0 = null;
let WASM_VECTOR_LEN = 0;

function getDataViewMemory0() {
    if (
        cachedDataViewMemory0 === null ||
        cachedDataViewMemory0.buffer.detached === true ||
        (cachedDataViewMemory0.buffer.detached === undefined && cachedDataViewMemory0.buffer !== wasm.memory.buffer)
    ) {
        cachedDataViewMemory0 = new DataView(wasm.memory.buffer);
    }
    return cachedDataViewMemory0;
}

function passStringToWasm0(arg, malloc, realloc) {
    if (realloc === undefined) {
        const buf = cachedTextEncoder.encode(arg);
        const ptr = malloc(buf.length, 1) >>> 0;
        getUint8ArrayMemory0()
            .subarray(ptr, ptr + buf.length)
            .set(buf);
        WASM_VECTOR_LEN = buf.length;
        return ptr;
    }

    let len = arg.length;
    let ptr = malloc(len, 1) >>> 0;

    const mem = getUint8ArrayMemory0();

    let offset = 0;

    for (; offset < len; offset++) {
        const code = arg.charCodeAt(offset);
        if (code > 0x7f) break;
        mem[ptr + offset] = code;
    }

    if (offset !== len) {
        if (offset !== 0) {
            arg = arg.slice(offset);
        }
        ptr = realloc(ptr, len, (len = offset + arg.length * 3), 1) >>> 0;
        const view = getUint8ArrayMemory0().subarray(ptr + offset, ptr + len);
        const ret = encodeString(arg, view);

        offset += ret.written;
        ptr = realloc(ptr, len, offset, 1) >>> 0;
    }

    WASM_VECTOR_LEN = offset;
    return ptr;
}

function getUint8ArrayMemory0() {
    if (cachedUint8ArrayMemory0 === null || cachedUint8ArrayMemory0.byteLength === 0) {
        cachedUint8ArrayMemory0 = new Uint8Array(wasm.memory.buffer);
    }
    return cachedUint8ArrayMemory0;
}

function getStringFromWasm0(ptr, len) {
    ptr = ptr >>> 0;
    return cachedTextDecoder.decode(getUint8ArrayMemory0().subarray(ptr, ptr + len));
}

function __wbg_finalize_init(instance, module) {
    wasm = instance.exports;
    __wbg_init.__wbindgen_wasm_module = module;
    cachedDataViewMemory0 = null;
    cachedUint8ArrayMemory0 = null;

    wasm.__wbindgen_start();
    return wasm;
}

function __wbg_init_memory(imports, memory) {}

async function __wbg_load(module, imports) {
    if (typeof Response === "function" && module instanceof Response) {
        if (typeof WebAssembly.instantiateStreaming === "function") {
            try {
                return await WebAssembly.instantiateStreaming(module, imports);
            } catch (e) {
                if (module.headers.get("Content-Type") != "application/wasm") {
                    console.warn(
                        "`WebAssembly.instantiateStreaming` failed because your server does not serve Wasm with `application/wasm` MIME type. Falling back to `WebAssembly.instantiate` which is slower. Original error:\n",
                        e
                    );
                } else {
                    throw e;
                }
            }
        }

        const bytes = await module.arrayBuffer();
        return await WebAssembly.instantiate(bytes, imports);
    } else {
        const instance = await WebAssembly.instantiate(module, imports);

        if (instance instanceof WebAssembly.Instance) {
            return { instance, module };
        } else {
            return instance;
        }
    }
}

async function __wbg_init(module_or_path) {
    if (wasm !== undefined) return wasm;

    if (typeof module_or_path !== "undefined") {
        if (Object.getPrototypeOf(module_or_path) === Object.prototype) {
            ({ module_or_path } = module_or_path);
        } else {
            console.warn("using deprecated parameters for the initialization function; pass a single object instead");
        }
    }

    if (typeof module_or_path === "undefined") {
        module_or_path = new URL(_____URL, import.meta.url);
    }
    const imports = __wbg_get_imports();

    // if (typeof module_or_path === "string" || (typeof Request === "function" && module_or_path instanceof Request) || (typeof URL === "function" && module_or_path instanceof URL)) {
    //     module_or_path = fetch(module_or_path);
    // }

    __wbg_init_memory(imports);

    // console.log("12345", module_or_path);

    // const { instance, module } = await __wbg_load(await module_or_path, imports);

    const { instance, exports: module } = await WebAssembly.instantiate(new Uint8Array(wasmBuffer), imports);

    return __wbg_finalize_init(instance, module);
}

let o =
    "undefined" != typeof TextDecoder
        ? new TextDecoder("utf-8", {
              ignoreBOM: !0,
              fatal: !0,
          })
        : {
              decode: () => {
                  throw Error("TextDecoder not available");
              },
          };

function c(e, n) {
    return (e >>>= 0), o.decode(a().subarray(e, e + n));
}

function isLikeNone(x) {
    return x === undefined || x === null;
}

function addToExternrefTable0(obj) {
    const idx = wasm.__externref_table_alloc();
    wasm.__wbindgen_export_2.set(idx, obj);
    return idx;
}

function __wbg_get_imports() {
    const imports = {};
    imports.wbg = {};
    imports.wbg.__wbg_call_672a4d21634d4a24 = function () {
        return handleError(function (arg0, arg1) {
            const ret = arg0.call(arg1);
            return ret;
        }, arguments);
    };
    imports.wbg.__wbg_error_7534b8e9a36f1ab4 = function (arg0, arg1) {
        let deferred0_0;
        let deferred0_1;
        try {
            deferred0_0 = arg0;
            deferred0_1 = arg1;
            console.error(getStringFromWasm0(arg0, arg1));
        } finally {
            wasm.__wbindgen_free(deferred0_0, deferred0_1, 1);
        }
    };
    imports.wbg.__wbg_host_9bd7b5dc07c48606 = function () {
        return handleError(function (arg0, arg1) {
            const ret = arg1.host;
            const ptr1 = passStringToWasm0(ret, wasm.__wbindgen_malloc, wasm.__wbindgen_realloc);
            const len1 = WASM_VECTOR_LEN;
            getDataViewMemory0().setInt32(arg0 + 4 * 1, len1, true);
            getDataViewMemory0().setInt32(arg0 + 4 * 0, ptr1, true);
        }, arguments);
    };
    imports.wbg.__wbg_hostname_8d7204884eb7378b = function () {
        return handleError(function (arg0, arg1) {
            const ret = arg1.hostname;
            const ptr1 = passStringToWasm0(ret, wasm.__wbindgen_malloc, wasm.__wbindgen_realloc);
            const len1 = WASM_VECTOR_LEN;
            getDataViewMemory0().setInt32(arg0 + 4 * 1, len1, true);
            getDataViewMemory0().setInt32(arg0 + 4 * 0, ptr1, true);
        }, arguments);
    };
    imports.wbg.__wbg_href_87d60a783a012377 = function () {
        return handleError(function (arg0, arg1) {
            const ret = arg1.href;
            const ptr1 = passStringToWasm0(ret, wasm.__wbindgen_malloc, wasm.__wbindgen_realloc);
            const len1 = WASM_VECTOR_LEN;
            getDataViewMemory0().setInt32(arg0 + 4 * 1, len1, true);
            getDataViewMemory0().setInt32(arg0 + 4 * 0, ptr1, true);
        }, arguments);
    };
    imports.wbg.__wbg_instanceof_Window_def73ea0955fc569 = function (arg0) {
        let result;
        try {
            result = arg0 instanceof Window;
        } catch (_) {
            result = false;
        }
        const ret = result;
        return ret;
    };
    imports.wbg.__wbg_location_350d99456c2f3693 = function (arg0) {
        const ret = arg0.location;
        return ret;
    };
    imports.wbg.__wbg_new_8a6f238a6ece86ea = function () {
        const ret = new Error();
        return ret;
    };
    imports.wbg.__wbg_newnoargs_105ed471475aaf50 = function (arg0, arg1) {
        const ret = new Function(getStringFromWasm0(arg0, arg1));
        return ret;
    };
    imports.wbg.__wbg_origin_7c5d649acdace3ea = function () {
        return handleError(function (arg0, arg1) {
            const ret = arg1.origin;
            const ptr1 = passStringToWasm0(ret, wasm.__wbindgen_malloc, wasm.__wbindgen_realloc);
            const len1 = WASM_VECTOR_LEN;
            getDataViewMemory0().setInt32(arg0 + 4 * 1, len1, true);
            getDataViewMemory0().setInt32(arg0 + 4 * 0, ptr1, true);
        }, arguments);
    };
    imports.wbg.__wbg_stack_0ed75d68575b0f3c = function (arg0, arg1) {
        const ret = arg1.stack;
        const ptr1 = passStringToWasm0(ret, wasm.__wbindgen_malloc, wasm.__wbindgen_realloc);
        const len1 = WASM_VECTOR_LEN;
        getDataViewMemory0().setInt32(arg0 + 4 * 1, len1, true);
        getDataViewMemory0().setInt32(arg0 + 4 * 0, ptr1, true);
    };
    imports.wbg.__wbg_static_accessor_GLOBAL_88a902d13a557d07 = function () {
        const ret = typeof global === "undefined" ? null : global;
        return isLikeNone(ret) ? 0 : addToExternrefTable0(ret);
    };
    imports.wbg.__wbg_static_accessor_GLOBAL_THIS_56578be7e9f832b0 = function () {
        const ret = typeof globalThis === "undefined" ? null : globalThis;
        return isLikeNone(ret) ? 0 : addToExternrefTable0(ret);
    };
    imports.wbg.__wbg_static_accessor_SELF_37c5d418e4bf5819 = function () {
        const ret = typeof self === "undefined" ? null : self;
        return isLikeNone(ret) ? 0 : addToExternrefTable0(ret);
    };
    imports.wbg.__wbg_static_accessor_WINDOW_5de37043a91a9c40 = function () {
        const ret = typeof window === "undefined" ? null : window;
        return isLikeNone(ret) ? 0 : addToExternrefTable0(ret);
    };
    imports.wbg.__wbindgen_init_externref_table = function () {
        // const table = wasm.__wbindgen_export_2;
        // const offset = table.grow(4);
        // table.set(0, undefined);
        // table.set(offset + 0, undefined);
        // table.set(offset + 1, null);
        // table.set(offset + 2, true);
        // table.set(offset + 3, false);
    };
    imports.wbg.__wbindgen_is_undefined = function (arg0) {
        const ret = arg0 === undefined;
        return ret;
    };
    imports.wbg.__wbindgen_throw = function (arg0, arg1) {
        throw new Error(getStringFromWasm0(arg0, arg1));
    };

    return imports;
}

function loadWasmModule() {
    if (r) return r;
    const imports = __wbg_get_imports();
    return WebAssembly.instantiate(new Uint8Array(wasmBuffer), imports).then((wasmModule) => {
        const instance = wasmModule.instance;
        const exports = instance.exports;

        r = exports;

        if (typeof exports.__wbindgen_start === "function") {
            exports.__wbindgen_start();
            console.log("__wbindgen_start called for WASM initialization.");
        } else {
            console.warn("__wbindgen_start not found in WASM exports.");
        }

        return exports;
    });
}

let l = null;
function a() {
    return (null === l || 0 === l.byteLength) && (l = new Uint8Array(r.memory.buffer)), l;
}

function b(e, n, t) {
    if (void 0 === t) {
        let t = u.encode(e),
            r = n(t.length, 1) >>> 0;
        return (
            a()
                .subarray(r, r + t.length)
                .set(t),
            (f = t.length),
            r
        );
    }
    let r = e.length,
        i = n(r, 1) >>> 0,
        _ = a(),
        o = 0;
    for (; o < r; o++) {
        let n = e.charCodeAt(o);
        if (n > 127) break;
        _[i + o] = n;
    }
    if (o !== r) {
        0 !== o && (e = e.slice(o)), (i = t(i, r, (r = o + 3 * e.length), 1) >>> 0);
        let n = s(e, a().subarray(i + o, i + r));
        (o += n.written), (i = t(i, r, o, 1) >>> 0);
    }
    return (f = o), i;
}

function y(e, n) {
    let t = n(+e.length, 1) >>> 0;
    return a().set(e, t / 1), (f = e.length), t;
}

export async function decrypt(e, n, t, i) {
    await __wbg_init();
    let r = await loadWasmModule();
    let _, o;
    try {
        let l = b(e, r.__wbindgen_malloc, r.__wbindgen_realloc),
            a = f,
            u = b(n, r.__wbindgen_malloc, r.__wbindgen_realloc),
            s = f,
            d = y(t, r.__wbindgen_malloc),
            g = f,
            w = b(i, r.__wbindgen_malloc, r.__wbindgen_realloc),
            m = f;

        let p = r.decrypt(l, a, u, s, d, g, w, m);
        return (_ = p[0]), (o = p[1]), c(p[0], p[1]);
    } finally {
        r.__wbindgen_free(_, o, 1);
    }
}

export function ivDecode(e) {
    if (e.length % 2 != 0) throw Error("Invalid hex string");
    let i = new Uint8Array(e.length / 2);
    for (let t = 0; t < e.length; t += 2) i[t / 2] = parseInt(e.substr(t, 2), 16);
    return i;
}
