use wasm_bindgen::prelude::*;
use web_sys::window;

#[wasm_bindgen]
pub fn get_hostname() -> String {
    window()
        .and_then(|w| w.location().hostname().ok())
        .unwrap_or_default()
}

#[wasm_bindgen]
pub fn get_host() -> String {
    window()
        .and_then(|w| w.location().host().ok())
        .unwrap_or_default()
}

#[wasm_bindgen]
pub fn get_origin() -> String {
    if let Some(win) = window() {
        if let Ok(origin) = win.location().origin() {
            return origin;
        }
        if let Ok(href) = win.location().href() {
            return href;
        }
    }
    String::new()
}

#[wasm_bindgen]
pub fn get_href() -> String {
    window()
        .and_then(|w| w.location().href().ok())
        .unwrap_or_default()
}
