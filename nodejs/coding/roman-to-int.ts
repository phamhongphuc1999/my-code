/*https://leetcode.com/problems/roman-to-integer/*/
const mapping: { [roman: string]: number } = { I: 1, V: 5, X: 10, L: 50, C: 100, D: 500, M: 1000 };

export function romanToInt(romanNumber: string) {
  const _len = romanNumber.length;
  let result = mapping[romanNumber[_len - 1]];
  if (_len == 1) return result;
  for (let i = _len - 2; i >= 0; i--) {
    const atom = mapping[romanNumber[i]];
    const nextAtom = mapping[romanNumber[i + 1]];
    if ((nextAtom == 5 || nextAtom == 10) && atom == 1) result -= 1;
    else if ((nextAtom == 50 || nextAtom == 100) && atom == 10) result -= 10;
    else if ((nextAtom == 500 || nextAtom == 1000) && atom == 100) result -= 100;
    else result += atom;
  }
  return result;
}
