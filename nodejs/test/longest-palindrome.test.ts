import { expect, test } from 'vitest';
import { expand, longestPalindrome, twoPointerHandler } from '../coding/longest-palindrome';

test('Two pointers', function () {
  const result1 = twoPointerHandler([1, 5, 6, 7, 2, 3, 1, 2, 1], 9);
  expect(result1.begin).toBe(4);
  expect(result1.end).toBe(8);
  expect(result1.total).toBe(9);
  const result2 = twoPointerHandler([10, 11, 12, 13, 14], 9);
  expect(result2.begin).toBe(-1);
  expect(result2.end).toBe(-1);
  expect(result2.total).toBe(-1);
});

test('Expand string', function () {
  expect(expand('babad', 1, 1)).toBe('bab');
});

test('Longest palindrome', function () {
  expect(longestPalindrome('babad')).toBe('bab');
  expect(longestPalindrome('cbbd')).toBe('bb');
});
