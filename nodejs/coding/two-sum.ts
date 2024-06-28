/*https://leetcode.com/problems/two-sum/*/
/**
 * Solution for this problem is hash table. Using a key-value structure to storing all indexes that have same value, this way can reduce the complex when query value.
 * @param nums
 * @param target
 * @returns
 */
export function twoSum(nums: Array<number>, target: number): Array<number> {
  const keys: { [key: number]: Array<number> } = {};
  let counter = 0;
  for (const num of nums) {
    if (!keys[num]) keys[num] = [counter];
    else keys[num].push(counter);
    counter++;
  }
  for (const _key of Object.keys(keys)) {
    const _revertKey = target - Number(_key);
    const _numKey = Number(_key);
    const _value = keys[_numKey];
    if (_numKey == _revertKey && _value.length > 1) return [_value[0], _value[1]];
    if (_numKey != _revertKey && keys[_revertKey]) return [_value[0], keys[_revertKey][0]];
  }
  return [-1, -1];
}
