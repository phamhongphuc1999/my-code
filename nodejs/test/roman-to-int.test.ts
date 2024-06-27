import { expect, test } from 'vitest';
import { romanToInt } from '../coding/roman-to-int';

test('Roman to int', () => {
  expect(romanToInt('III')).toBe(3);
  expect(romanToInt('LVIII')).toBe(58);
  expect(romanToInt('MCMXCIV')).toBe(1994);
});
