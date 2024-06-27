import { expect, test } from 'vitest';
import { addTwoNumbers, convertArrayToList, convertListToArray } from '../coding/add-two-numbers';
import { arrayCompare } from '../coding/two-sum';

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
  expect(arrayCompare(result1, [7, 0, 8]));
  const result2 = convertListToArray(
    addTwoNumbers(convertArrayToList([0]), convertArrayToList([0])),
  );
  expect(arrayCompare(result2, [0]));
  const result3 = convertListToArray(
    addTwoNumbers(convertArrayToList([9, 9, 9, 9, 9, 9, 9]), convertArrayToList([9, 9, 9, 9])),
  );
  expect(arrayCompare(result3, [8, 9, 9, 9, 0, 0, 0, 1]));
});
