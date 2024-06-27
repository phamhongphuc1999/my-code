import { expect, test } from 'vitest';
import { arrayCompare, twoSum } from '../coding/two-sum';

test('Two sum', () => {
  expect(arrayCompare(twoSum([2, 7, 11, 15], 9), [0, 1])).toBe(true);
  expect(arrayCompare(twoSum([3, 2, 4], 6), [1, 2])).toBe(true);
  expect(arrayCompare(twoSum([3, 3], 6), [0, 1])).toBe(true);
});
