import { expect, test } from 'vitest';
import { analysisNumber, intToRoman, romanToInt } from '../coding/roman-and-int';
import { arrayCompare } from '../utils';

test('Roman to int', () => {
  expect(romanToInt('III')).toBe(3);
  expect(romanToInt('LVIII')).toBe(58);
  expect(romanToInt('MCMXCIV')).toBe(1994);
});

test('Int to roman', function () {
  expect(arrayCompare(analysisNumber(1234), [4, 3, 2, 1])).toBe(true);
  expect(arrayCompare(analysisNumber(343434), [4, 3, 4, 3, 4, 3])).toBe(true);
  expect(arrayCompare(analysisNumber(100140), [0, 4, 1, 0, 0, 1])).toBe(true);

  expect(intToRoman(3)).toBe('III');
  expect(intToRoman(58)).toBe('LVIII');
  expect(intToRoman(1994)).toBe('MCMXCIV');
});
