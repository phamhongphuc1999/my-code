import { expect, test } from 'vitest';
import { addTwoNumbers, convertArrayToList, convertListToArray } from '../coding/add-two-numbers';
import { expand, longestPalindrome, twoPointerHandler } from '../coding/longest-palindrome';
import { arrayCompare } from '../utils';

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

test('Add two numbers', () => {
  let _list = convertArrayToList([1, 2, 3, 4, 5]);
  if (_list) {
    expect(_list?.val).toBe(1);
    _list = _list?.next;
    expect(_list?.val).toBe(2);
  }
  const _arr = convertListToArray(_list);
  expect(arrayCompare(_arr, [1, 2, 3, 4, 5]));

  const result1 = convertListToArray(
    addTwoNumbers(convertArrayToList([2, 4, 3]), convertArrayToList([5, 6, 4])),
  );
  expect(arrayCompare(result1, [7, 0, 8])).toBe(true);
  const result2 = convertListToArray(
    addTwoNumbers(convertArrayToList([0]), convertArrayToList([0])),
  );
  expect(arrayCompare(result2, [0])).toBe(true);
  const result3 = convertListToArray(
    addTwoNumbers(convertArrayToList([9, 9, 9, 9, 9, 9, 9]), convertArrayToList([9, 9, 9, 9])),
  );
  expect(arrayCompare(result3, [8, 9, 9, 9, 0, 0, 0, 1])).toBe(true);
});
