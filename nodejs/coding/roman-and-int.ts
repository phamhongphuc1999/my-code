const romanToIntMapping: { [roman: string]: number } = {
  I: 1,
  V: 5,
  X: 10,
  L: 50,
  C: 100,
  D: 500,
  M: 1000,
};

const intToRomanMapping: { [int: number]: string } = {
  1: 'I',
  5: 'V',
  10: 'X',
  50: 'L',
  100: 'C',
  500: 'D',
  1000: 'M',
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

// export function intToRoman(num: number): string {
//   const _arr = analysisNumber(num).slice(0, 3);
//   const _len = _arr.length;
//   let result = '';
//   for (let i = _len - 1; i >= 0; i--) {
//     const element = _arr[i];

//   }
// }
