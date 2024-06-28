/*https://leetcode.com/problems/longest-substring-without-repeating-characters/*/
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
