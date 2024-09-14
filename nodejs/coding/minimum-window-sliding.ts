/*https://leetcode.com/problems/minimum-window-substring/description/*/

type Json = { [key: string]: number };

export function analytic(s: string): Json {
  const result: Json = {};
  for (let i = 0; i < s.length; i++) {
    if (result[s[i]]) result[s[i]]++;
    else result[s[i]] = 1;
  }
  return result;
}

export function compare(source: Json, target: Json): boolean {
  for (const t of Object.keys(target)) {
    const sourceValue = source[t];
    if (sourceValue == undefined) return false;
    if (target[t] > sourceValue) return false;
  }
  return true;
}

export function minWindow(s: string, t: string): string {
  const sLen = s.length;
  const tLen = t.length;
  if (sLen < tLen || tLen == 0) return '';
  const tHashMap = analytic(t);
  const sHashMap: Json = { [s[0]]: 1 };
  let location: [number, number] = [0, 0];
  let resultLocation: [number, number] = [-1, -1];
  while (location[1] < sLen || location[0] < location[1]) {
    const isCheck = compare(sHashMap, tHashMap);
    if (isCheck) {
      if (location[0] == location[1]) return s.slice(location[0], location[1] + 1);
      if (
        resultLocation[1] < 0 ||
        resultLocation[0] < 0 ||
        resultLocation[1] - resultLocation[0] > location[1] - location[0]
      ) {
        resultLocation[0] = location[0];
        resultLocation[1] = location[1];
      }
      const cStart = s[location[0]];
      sHashMap[cStart]--;
      location[0]++;
    } else {
      location[1]++;
      if (location[1] >= sLen) break;
      else {
        const cEnd = s[location[1]];
        const currentValue = sHashMap[cEnd];
        if (currentValue == undefined) sHashMap[cEnd] = 1;
        else sHashMap[cEnd]++;
      }
    }
  }
  if (resultLocation[1] < 0 || resultLocation[0] < 0) return '';
  return s.slice(resultLocation[0], resultLocation[1] + 1);
}
