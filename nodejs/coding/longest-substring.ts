/**
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/
 */
export function findTail(s: string): number {
  let counter = 0;
  const _len = s.length - 1;
  const temp: { [key: string]: boolean } = {};
  while (counter <= _len) {
    const _index = _len - counter;
    if (!temp[s[_index]]) {
      counter++;
      temp[s[_index]] = true;
    } else return counter;
  }
  return counter;
}

export function findSubstring(s: string): number {
  const _len = s.length;
  if (_len <= 1) return _len;
  let result = 1;
  for (let i = 1; i < _len; i++) {
    const tempMax = findTail(s.slice(0, i));
    if (result < tempMax) result = tempMax;
  }
  return result;
}

/**
 * Longest common substring
 * Given two strings X and Y, find the length of the longest common substring
 * For example:
 * - Input:  = GeeksforGeeks, y = GeeksQuiz
 * Output: 5 => the longest common substring is "Geeks" and is of length 5.
 * L(i, j) = L(i - 1, j - 1) + 1 if s1(i) == s2(j)
 * L(i, j) = max(L(i - 1, j), L(i, j - 1)) if s1(i) != s2(j)
 */
export function longestCommonSubstring(s1: string, s2: string): string {
  const preResult: { [key: string]: { value: string; len: number } } = {};
  const len1 = s1.length;
  const len2 = s2.length;
  preResult['0-0'] = s1[0] == s2[0] ? { value: s1[0], len: 1 } : { value: '', len: 0 };
  for (let i = 1; i < len1; i++) {
    const preValue = preResult[`${i - 1}-0`];
    const isCheck = s1[i] == s2[0];
    if (preValue.len == 1) preResult[`${i}-0`] = preValue;
    else if (isCheck) preResult[`${i}-0`] = { value: s2[0], len: 1 };
    else preResult[`${i}-0`] = { value: '', len: 0 };
  }
  for (let j = 1; j < len2; j++) {
    const preValue = preResult[`0-${j - 1}`];
    const isCheck = s1[0] == s2[j];
    if (preValue.len == 1) preResult[`0-${j}`] = preValue;
    else if (isCheck) preResult[`0-${j}`] = { value: s1[0], len: 1 };
    else preResult[`0-${j}`] = { value: '', len: 0 };
  }
  for (let i = 1; i < len1; i++) {
    for (let j = 1; j < len2; j++) {
      if (s1[i] == s2[j]) {
        const preValue = preResult[`${i - 1}-${j - 1}`];
        preResult[`${i}-${j}`] = { value: `${preValue.value}${s1[i]}`, len: preValue.len + 1 };
      } else {
        const preValue1 = preResult[`${i}-${j - 1}`];
        const preValue2 = preResult[`${i - 1}-${j}`];
        const maxValue = preValue1.len > preValue2.len ? preValue1 : preValue2;
        preResult[`${i}-${j}`] = maxValue;
      }
    }
  }
  return preResult[`${len1 - 1}-${len2 - 1}`].value;
}

/**
 * https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/
 */
export function slideIndices(s: string, e: string): Array<number> {
  const result: Array<number> = [];
  const sLen = s.length;
  const eLen = e.length;
  for (let i = 0; i < sLen - eLen; i++) {
    if (s.slice(i, i + eLen - 1) == e) result.push(i);
  }
  return result;
}
function slideGroup(s: string, e: Array<string>): { [key: string]: Array<number> } {
  const result: { [key: string]: Array<number> } = {};
  for (const element of e) result[element] = slideIndices(s, element);
  return result;
}
export function findSubstringWithConcatenation(s: string, words: Array<string>) {
  const indices = slideGroup(s, words);
}
