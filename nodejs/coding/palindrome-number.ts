/*https://leetcode.com/problems/palindrome-number/*/
export function isPalindrome(x: number): boolean {
  const sX = x.toString();
  let start = 0;
  let end = sX.length - 1;
  while (start <= end) {
    if (sX[start] != sX[end]) return false;
    start++;
    end--;
  }
  return true;
}
