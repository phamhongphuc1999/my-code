const romanToIntMapping: { [roman: string]: number } = {
  I: 1,
  V: 5,
  X: 10,
  L: 50,
  C: 100,
  D: 500,
  M: 1000,
};

const intToRomanMapping: { [position: number]: { [int: number]: string } } = {
  0: { 1: 'I', 2: 'II', 3: 'III', 4: 'IV', 5: 'V', 6: 'VI', 7: 'VII', 8: 'VIII', 9: 'IX' },
  1: { 1: 'X', 2: 'XX', 3: 'XXX', 4: 'XL', 5: 'L', 6: 'LX', 7: 'LXX', 8: 'LXXX', 9: 'XC' },
  2: { 1: 'C', 2: 'CC', 3: 'CCC', 4: 'CD', 5: 'D', 6: 'DC', 7: 'DCC', 8: 'DCCC', 9: 'CM' },
  3: { 1: 'M', 2: 'MM', 3: 'MMM' },
};

/*https://leetcode.com/problems/roman-to-integer/*/
export function romanToInt(romanNumber: string) {
  const _len = romanNumber.length;
  let result = romanToIntMapping[romanNumber[_len - 1]];
  if (_len == 1) return result;
  for (let i = _len - 2; i >= 0; i--) {
    const atom = romanToIntMapping[romanNumber[i]];
    const nextAtom = romanToIntMapping[romanNumber[i + 1]];
    if ((nextAtom == 5 || nextAtom == 10) && atom == 1) result -= 1;
    else if ((nextAtom == 50 || nextAtom == 100) && atom == 10) result -= 10;
    else if ((nextAtom == 500 || nextAtom == 1000) && atom == 100) result -= 100;
    else result += atom;
  }
  return result;
}

/*https://leetcode.com/problems/integer-to-roman/description/*/
export function analysisNumber(num: number): Array<number> {
  const result: Array<number> = [];
  let _num = num;
  while (_num > 0) {
    const _temp = _num % 10;
    _num = Math.floor(_num / 10);
    result.push(_temp);
  }
  return result;
}

export function intToRoman(num: number): string {
  const _arr = analysisNumber(num).slice(0, 4);
  let result = '';
  _arr.forEach((item, index) => {
    const _int = intToRomanMapping[index][item];
    if (_int) result = `${_int}${result}`;
  });
  return result;
}
