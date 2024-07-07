import { expect, test } from 'vitest';
import { analysisNumber, romanToInt } from '../coding/roman-and-int';
import { arrayCompare } from '../utils';

test('Roman to int', () => {
  expect(romanToInt('III')).toBe(3);
  expect(romanToInt('LVIII')).toBe(58);
  expect(romanToInt('MCMXCIV')).toBe(1994);
});

test('Int to roman', function () {
  expect(arrayCompare(analysisNumber(1234), [4, 3, 2, 1])).toBe(true);
  expect(arrayCompare(analysisNumber(343434), [4, 3, 4, 3, 4, 3])).toBe(true);
});
