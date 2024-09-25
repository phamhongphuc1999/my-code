import { expect, test } from 'vitest';
import { convertArrayToList, convertListToArray, mergeTwoLists } from '../coding/add-two-numbers';
import {
  findSubstring,
  findTail,
  longestCommonSubstring,
  slideIndices,
} from '../coding/longest-substring';
import { analytic, compare, minWindow } from '../coding/minimum-window-sliding';
import { isPalindrome } from '../coding/palindrome-number';
import { analysisNumber, intToRoman, romanToInt } from '../coding/roman-and-int';
import { reverse, twoSum } from '../coding/two-sum';
import { isValidSudoku } from '../coding/valid-sudoku';
import { arrayCompare } from '../utils';

const case1 = [
  ['5', '3', '.', '.', '7', '.', '.', '.', '.'],
  ['6', '.', '.', '1', '9', '5', '.', '.', '.'],
  ['.', '9', '8', '.', '.', '.', '.', '6', '.'],
  ['8', '.', '.', '.', '6', '.', '.', '.', '3'],
  ['4', '.', '.', '8', '.', '3', '.', '.', '1'],
  ['7', '.', '.', '.', '2', '.', '.', '.', '6'],
  ['.', '6', '.', '.', '.', '.', '2', '8', '.'],
  ['.', '.', '.', '4', '1', '9', '.', '.', '5'],
  ['.', '.', '.', '.', '8', '.', '.', '7', '9'],
];

const case2 = [
  ['8', '3', '.', '.', '7', '.', '.', '.', '.'],
  ['6', '.', '.', '1', '9', '5', '.', '.', '.'],
  ['.', '9', '8', '.', '.', '.', '.', '6', '.'],
  ['8', '.', '.', '.', '6', '.', '.', '.', '3'],
  ['4', '.', '.', '8', '.', '3', '.', '.', '1'],
  ['7', '.', '.', '.', '2', '.', '.', '.', '6'],
  ['.', '6', '.', '.', '.', '.', '2', '8', '.'],
  ['.', '.', '.', '4', '1', '9', '.', '.', '5'],
  ['.', '.', '.', '.', '8', '.', '.', '7', '9'],
];

const case3 = [
  ['.', '.', '5', '.', '.', '.', '.', '.', '.'],
  ['1', '.', '.', '2', '.', '.', '.', '.', '.'],
  ['.', '.', '6', '.', '.', '3', '.', '.', '.'],
  ['8', '.', '.', '.', '.', '.', '.', '.', '.'],
  ['3', '.', '1', '5', '2', '.', '.', '.', '.'],
  ['.', '.', '.', '.', '.', '.', '.', '4', '.'],
  ['.', '.', '6', '.', '.', '.', '.', '.', '.'],
  ['.', '.', '.', '.', '.', '.', '.', '9', '.'],
  ['.', '.', '.', '.', '.', '.', '.', '.', '.'],
];

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

test('Two sum', () => {
  expect(arrayCompare(twoSum([2, 7, 11, 15], 9), [0, 1])).toBe(true);
  expect(arrayCompare(twoSum([3, 2, 4], 6), [1, 2])).toBe(true);
  expect(arrayCompare(twoSum([3, 3], 6), [0, 1])).toBe(true);
});

test('valid soduku', () => {
  expect(isValidSudoku(case1)).toBe(true);
  expect(isValidSudoku(case2)).toBe(false);
  expect(isValidSudoku(case3)).toBe(false);
});

test('minimum window sliding', () => {
  const result1 = analytic('abcabccca');
  expect(result1['a']).toBe(3);
  expect(result1['c']).toBe(4);
  expect(result1['e']).toBeUndefined();

  expect(compare({ a: 1, b: 2, c: 3, d: 10 }, { a: 1, b: 1, c: 2 })).toBe(true);
  expect(compare({ a: 1, b: 2, c: 3 }, { a: 1, b: 1, c: 10 })).toBe(false);

  expect(minWindow('ADOBECODEBANC', 'ABC')).toBe('BANC');
});

test('Palindrome', () => {
  expect(isPalindrome(121)).toBe(true);
  expect(isPalindrome(-121)).toBe(false);
  expect(isPalindrome(10)).toBe(false);
});

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

test('Merge sorted arrays', () => {
  const result2 = convertListToArray(
    mergeTwoLists(convertArrayToList([]), convertArrayToList([0])),
  );
  expect(arrayCompare(result2, [0])).toBe(true);
});

test('reverse integer', () => {
  const result1 = reverse(123);
  expect(result1 == 321).toBe(true);
  const result2 = reverse(-123);
  expect(result2 == -321).toBe(true);
  const result3 = reverse(120);
  expect(result3 == 21).toBe(true);
  const result4 = reverse(2147483647);
  expect(result4 == 0).toBe(true);
  const result5 = reverse(-1147483647);
  expect(result5 == 0).toBe(true);
});
