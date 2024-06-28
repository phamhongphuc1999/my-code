import { expect, test } from 'vitest';
import { isPalindrome } from '../coding/palindrome-number';

test('Palindrome', () => {
  expect(isPalindrome(121)).toBe(true);
  expect(isPalindrome(-121)).toBe(false);
  expect(isPalindrome(10)).toBe(false);
});
