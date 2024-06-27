/*https://leetcode.com/problems/palindrome-number/*/
export function isPalindrome(x: number): boolean {
  if (x < 0) return false;
  let temp = 0;
  let xTemp = x;
  while (xTemp > 0) {
    const remain = xTemp % 10;
    xTemp = Math.floor(xTemp / 10);
    temp = temp * 10 + remain;
  }
  return temp == x;
}
