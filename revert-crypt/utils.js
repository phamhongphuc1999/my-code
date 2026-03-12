export function convertToHex(e) {
    if (e.length % 2 != 0) throw Error("Invalid hex string");
    let t = new Uint8Array(e.length / 2);
    for (let r = 0; r < e.length; r += 2) t[r / 2] = parseInt(e.substr(r, 2), 16);
    return t;
}
