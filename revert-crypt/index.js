import { clientId, responseData } from "./constance.js";
import { convertToHex } from "./utils.js";
import fs from "node:fs";

// Read the .wasm file
const wasmBuffer = fs.readFileSync("./crypt_bg.wasm");

let r;
function o(e) {
    let n = r.__externref_table_alloc();
    return r.__wbindgen_export_2.set(n, e), n;
}
function i(e, n) {
    try {
        return e.apply(this, n);
    } catch (n) {
        let e = o(n);
        r.__wbindgen_exn_store(e);
    }
}

let l =
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
"undefined" != typeof TextDecoder && l.decode();
let _ = null;
function a() {
    return (null === _ || 0 === _.byteLength) && (_ = new Uint8Array(r.memory.buffer)), _;
}
function c(e, n) {
    return (e >>>= 0), l.decode(a().subarray(e, e + n));
}
let s = 0,
    f =
        "undefined" != typeof TextEncoder
            ? new TextEncoder("utf-8")
            : {
                  encode: () => {
                      throw Error("TextEncoder not available");
                  },
              },
    u =
        "function" == typeof f.encodeInto
            ? function (e, n) {
                  return f.encodeInto(e, n);
              }
            : function (e, n) {
                  let t = f.encode(e);
                  return (
                      n.set(t),
                      {
                          read: e.length,
                          written: t.length,
                      }
                  );
              };
function b(e, n, t) {
    if (void 0 === t) {
        let t = f.encode(e),
            r = n(t.length, 1) >>> 0;
        return (
            a()
                .subarray(r, r + t.length)
                .set(t),
            (s = t.length),
            r
        );
    }
    let r = e.length,
        o = n(r, 1) >>> 0,
        i = a(),
        l = 0;
    for (; l < r; l++) {
        let n = e.charCodeAt(l);
        if (n > 127) break;
        i[o + l] = n;
    }
    if (l !== r) {
        0 !== l && (e = e.slice(l)), (o = t(o, r, (r = l + 3 * e.length), 1) >>> 0);
        let n = u(e, a().subarray(o + l, o + r));
        (l += n.written), (o = t(o, r, l, 1) >>> 0);
    }
    return (s = l), o;
}
let d = null;
function w() {
    return (null === d || !0 === d.buffer.detached || (void 0 === d.buffer.detached && d.buffer !== r.memory.buffer)) && (d = new DataView(r.memory.buffer)), d;
}
function g() {
    r.main_js();
}
function y() {
    let e, n;
    try {
        let t = r.get_host();
        return (e = t[0]), (n = t[1]), c(t[0], t[1]);
    } finally {
        r.__wbindgen_free(e, n, 1);
    }
}
function p(e, n) {
    let t = n(1 * e.length, 1) >>> 0;
    return a().set(e, t / 1), (s = e.length), t;
}
function m(e, n, t, o) {
    let i, l;
    try {
        let _ = b(e, r.__wbindgen_malloc, r.__wbindgen_realloc),
            a = s,
            f = b(n, r.__wbindgen_malloc, r.__wbindgen_realloc),
            u = s,
            d = p(t, r.__wbindgen_malloc),
            w = s,
            g = b(o, r.__wbindgen_malloc, r.__wbindgen_realloc),
            y = s,
            m = r.encrypt(_, a, f, u, d, w, g, y);
        return (i = m[0]), (l = m[1]), c(m[0], m[1]);
    } finally {
        r.__wbindgen_free(i, l, 1);
    }
}
function h(e, n, t, o) {
    let i, l;
    try {
        let _ = b(e, r.__wbindgen_malloc, r.__wbindgen_realloc),
            a = s,
            f = b(n, r.__wbindgen_malloc, r.__wbindgen_realloc),
            u = s,
            d = p(t, r.__wbindgen_malloc),
            w = s,
            g = b(o, r.__wbindgen_malloc, r.__wbindgen_realloc),
            y = s,
            m = r.decrypt(_, a, f, u, d, w, g, y);
        return (i = m[0]), (l = m[1]), c(m[0], m[1]);
    } finally {
        r.__wbindgen_free(i, l, 1);
    }
}
async function W(e, n) {
    if ("function" == typeof Response && e instanceof Response) {
        if ("function" == typeof WebAssembly.instantiateStreaming)
            try {
                return await WebAssembly.instantiateStreaming(e, n);
            } catch (n) {
                if ("application/wasm" != e.headers.get("Content-Type"))
                    console.warn(
                        "`WebAssembly.instantiateStreaming` failed because your server does not serve Wasm with `application/wasm` MIME type. Falling back to `WebAssembly.instantiate` which is slower. Original error:\n",
                        n
                    );
                else throw n;
            }
        let t = await e.arrayBuffer();
        return await WebAssembly.instantiate(t, n);
    }
    {
        let t = await WebAssembly.instantiate(e, n);
        return t instanceof WebAssembly.Instance
            ? {
                  instance: t,
                  module: e,
              }
            : t;
    }
}
function v() {
    let e = {};
    return (
        (e.wbg = {}),
        (e.wbg.__wbg_call_672a4d21634d4a24 = function () {
            return i(function (e, n) {
                return e.call(n);
            }, arguments);
        }),
        (e.wbg.__wbg_error_7534b8e9a36f1ab4 = function (e, n) {
            let t, o;
            try {
                (t = e), (o = n), console.error(c(e, n));
            } finally {
                r.__wbindgen_free(t, o, 1);
            }
        }),
        (e.wbg.__wbg_host_9bd7b5dc07c48606 = function () {
            return i(function (e, n) {
                let t = b(n.host, r.__wbindgen_malloc, r.__wbindgen_realloc),
                    o = s;
                w().setInt32(e + 4, o, !0), w().setInt32(e + 0, t, !0);
            }, arguments);
        }),
        (e.wbg.__wbg_instanceof_Window_def73ea0955fc569 = function (e) {
            let n;
            try {
                n = e instanceof Window;
            } catch (e) {
                n = !1;
            }
            return n;
        }),
        (e.wbg.__wbg_location_350d99456c2f3693 = function (e) {
            return e.location;
        }),
        (e.wbg.__wbg_new_8a6f238a6ece86ea = function () {
            return Error();
        }),
        (e.wbg.__wbg_newnoargs_105ed471475aaf50 = function (e, n) {
            return Function(c(e, n));
        }),
        (e.wbg.__wbg_stack_0ed75d68575b0f3c = function (e, n) {
            let t = b(n.stack, r.__wbindgen_malloc, r.__wbindgen_realloc),
                o = s;
            w().setInt32(e + 4, o, !0), w().setInt32(e + 0, t, !0);
        }),
        (e.wbg.__wbg_static_accessor_GLOBAL_88a902d13a557d07 = function () {
            let e = "undefined" == typeof global ? null : global;
            return null == e ? 0 : o(e);
        }),
        (e.wbg.__wbg_static_accessor_GLOBAL_THIS_56578be7e9f832b0 = function () {
            let e = "undefined" == typeof globalThis ? null : globalThis;
            return null == e ? 0 : o(e);
        }),
        (e.wbg.__wbg_static_accessor_SELF_37c5d418e4bf5819 = function () {
            let e = "undefined" == typeof self ? null : self;
            return null == e ? 0 : o(e);
        }),
        (e.wbg.__wbg_static_accessor_WINDOW_5de37043a91a9c40 = function () {
            // let e = window;
            return null == e ? 0 : o(e);
        }),
        (e.wbg.__wbindgen_init_externref_table = function () {
            let e = r.__wbindgen_export_2,
                n = e.grow(4);
            e.set(0, void 0), e.set(n + 0, void 0), e.set(n + 1, null), e.set(n + 2, !0), e.set(n + 3, !1);
        }),
        (e.wbg.__wbindgen_is_undefined = function (e) {
            return void 0 === e;
        }),
        (e.wbg.__wbindgen_throw = function (e, n) {
            throw Error(c(e, n));
        }),
        e
    );
}
function x(e, n) {
    return (r = e.exports), (E.__wbindgen_wasm_module = n), (d = null), (_ = null), r.__wbindgen_start(), r;
}
function A(e) {
    if (void 0 !== r) return r;
    void 0 !== e && (Object.getPrototypeOf(e) === Object.prototype ? ({ module: e } = e) : console.warn("using deprecated parameters for `initSync()`; pass a single object instead"));
    let n = v();
    return e instanceof WebAssembly.Module || (e = new WebAssembly.Module(e)), x(new WebAssembly.Instance(e, n), e);
}
async function E(e) {
    if (void 0 !== r) return r;
    void 0 !== e &&
        (Object.getPrototypeOf(e) === Object.prototype ? ({ module_or_path: e } = e) : console.warn("using deprecated parameters for the initialization function; pass a single object instead")),
        void 0 === e && (e = new t.U(t(54947)));
    let n = v();
    ("string" == typeof e || ("function" == typeof Request && e instanceof Request) || ("function" == typeof URL && e instanceof URL)) && (e = fetch(e));
    let { instance: o, module: i } = await W(await e, n);
    return x(o, i);
}
let I = E;

const iii = {
    decrypt: (e, n, t, o) => {
        let i, l;
        try {
            let _ = b(e, r.__wbindgen_malloc, r.__wbindgen_realloc),
                a = s,
                f = b(n, r.__wbindgen_malloc, r.__wbindgen_realloc),
                u = s,
                d = p(t, r.__wbindgen_malloc),
                w = s,
                g = b(o, r.__wbindgen_malloc, r.__wbindgen_realloc),
                y = s,
                m = r.decrypt(_, a, f, u, d, w, g, y);
            return (i = m[0]), (l = m[1]), c(m[0], m[1]);
        } finally {
            r.__wbindgen_free(i, l, 1);
        }
    },
};

async function revert() {
    E(new Uint8Array(wasmBuffer));
    A(new Uint8Array(wasmBuffer));
    console.log("rrrr", r);
    const [o, l] = clientId.split("_");
    const [iv, a] = responseData.split(":");
    const d = convertToHex(iv);

    c = JSON.parse(iii.decrypt(o, l, d, a));
    console.log(c);
}

revert();
