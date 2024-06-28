import { expect, test } from 'vitest';
import { findSubstring, findTail } from '../coding/longest-substring';

test('Longest substring without repeating', () => {
  expect(findTail('abcabcabc')).toBe(3);
  expect(findTail('1234567')).toBe(7);
  expect(findTail('1')).toBe(1);
  expect(findSubstring('abcabcbb')).toBe(3);
  expect(findSubstring('bbbbb')).toBe(1);
  expect(findSubstring('pwwkew')).toBe(3);
});
