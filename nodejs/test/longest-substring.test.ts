import { expect, test } from 'vitest';
import {
  findSubstring,
  findTail,
  longestCommonSubstring,
  slideIndices,
} from '../coding/longest-substring';
import { arrayCompare } from '../utils';

test('Longest substring without repeating', () => {
  expect(findTail('abcabcabc')).toBe(3);
  expect(findTail('1234567')).toBe(7);
  expect(findTail('1')).toBe(1);
  expect(findSubstring('abcabcbb')).toBe(3);
  expect(findSubstring('bbbbb')).toBe(1);
  expect(findSubstring('pwwkew')).toBe(3);
});

test('Longest common substring', function () {
  expect(longestCommonSubstring('GeeksforGeeks', 'GeeksQuiz')).toBe('Geeks');
  expect(longestCommonSubstring('123456789', 'abc')).toBe('');
  expect(longestCommonSubstring('123456789', '12341212345673456')).toBe('1234567');
});

test('Substring with concatenation of all words', function () {
  expect(arrayCompare(slideIndices('abababab', 'ab'), [0, 2, 4, 6]));
  expect(arrayCompare(slideIndices('abccad123abc4abc', 'abc'), [0, 9, 13]));
});
