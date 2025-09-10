import { decrypt, ivDecode } from "./crypt.js";
import { initWasm } from "./wasm.js";

const e = {
    data: "e3rc6+F7vuHtDcrFDfANsMbx65we9rt5OCKfaZXr2yQXipJ1G721y6pw6AxB5uN9ikI9CnvJd7JA6ngdb3pFNMf5/fHZofFgcpa+ZfiV3Q3nA9iGwKjnfv1RsigdDWXni+8f1nkgh2NdpWzPwwP6CQVlCIjV/NXGd3+qqYApixJPYzJvvzEycvNxWgrgOjvtKTnq30kCr4IyBqbJrZKRktD/QeklL9lqypC+QnJqQovgw/NG1N321Ht/JO+FBGicqD5yaC8ISty85+UKU38Kg8g8fE6T6GTozPwineVJUEpfL0401WUbm2RZmY3ns8BdBnGihZROMhj/N4UWzqssC73L4alPZezB0IM4k6JIziJIgfjB56LyUwf/nHt7HjS2zpBo5IormdcOw0biAzHaP3Cdg+TgdPWsBex+k9LXlTce3UniMCXW3J7zD/tAtdKmxZHO1Noe4DG/WAAqvhianWKZflOdb5uxNcmAO7ldU5THESyEujOJ7pXSsjscZ1xUGT925qQ4tcNPCg+67J4XSEZLbqD29lEUaBaoMTs3+kkV1cIoHU9nIavN/c8w1YGKbybcmvWitYL0VMor+HTtsGaR2abMESpU34TSnENY5EJuJspF0uuTt9KG2KMi3LvtKe63SRN5glH0/4g9zvWwyEudmqDlRQ3Z/ITY1kpHp/SSKyGFscMfF07M4uU/PWDVjX5VhzDb9c+ye0SCLHEU+6T2SP4+jjdB3otdgT8ahwRjyLdmPdkKG4wZmgKA/qFIj4IvB8RSceAGRvSiPN+HntorDD8rFlRpZpVIzQHg+KnZ9vTsan2oACST1//A/VuF9IsIbM9qForlMDOTqjbRmfBsH2lAXelV2CI9rEgoSvZ81a1+GHlYTaxUTTJp+MtEIT2q7BSwWx3ig6qRJKRjcXRybXh7+MxxfomG3jU4jFk9J952vzXL4EQZc2rMbDYlgxl9y3UupG6qIgQBviYL+fMzkWvPUZ2oMY/SB6tYuFen5ye6h2xWIer3T6GtAUO2FMSLqwY3pJwDebTTekDokI+XnMOiEUEuk5cb1eSiwJaCXbnIf2NW5ni4S5gsOd7FIe7aw+fn/tZIhiLMAthA0peZfc+30euwsgh3rK9TwJOjDymKbED0S995PzDYrDF8R9TD7rHnkUmtfv19uvBjnZYWtAxeDh27iRJbgI1Hgad2ZkiV3/s4QouRCi1egM1h8aM38Lia92VJ5fbadCOF7M+JztEO5M1+Dlb2xgkowfnC+gnNho/Dg8A4BqkyzJYGuqeQ2LOfebxQLQCEvOHEdZZyzhPdhF8yBoWI/W5p2L7Wg89fblQbVZ1wF0NkCQxUw/EjwhmLkVZB+XMD5TNbBcOIGDfS2YeAxoRVMjJKHhK+1VKMG+aSPWRzdtEc5ryYhghzi00KJDDqv8trRduq9nCbx1HM3ygxl8IJhYLj1AUKfC+UC+31/EEhsNx7msdMnK1n2/Idhk7T+HFu5kQc6ofnXtToX5FPlJf9hyLaj2ckA2LV8gU+OuvRTDVD9hZUc3fJki1NjbPGD92o7jaxzOXaTneElL75aT4xXfyom14=",
    iv: "bed14c57ae795dd51e0a329c3cda96b5",
    status: true,
};

async function _run(mode) {
    let t = "1757403076_810b0d0b-e3eb-4e40-a688-b0f7e17395c5";
    let [n, d] = t.toString().split("_");
    let a = ivDecode(e.iv);
    if (mode == "mode1") return JSON.parse(await decrypt(n, d, a, e.data));
    else {
        const _func = await initWasm();
        return JSON.parse(_func.decrypt(n, d, a, e.data));
    }
}

_run("mode1").then((a) => {
    console.log("result", a);
});
