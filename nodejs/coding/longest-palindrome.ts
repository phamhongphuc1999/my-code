/**
 * Solution - Books
 * We want to find longest contiguous segment of books that can be read within t minutes.
 * Note that the result must have total of reading as max as possible.
 */
export function twoPointerHandler(
  books: Array<number>,
  target: number,
): { begin: number; end: number; total: number } {
  const len = books.length;
  if (len == 0) return { begin: -1, end: -1, total: -1 };
  let begin = 0;
  let end = 0;
  let total = books[0];
  let bookLen = 1;
  let result = { begin: 0, end: 0, total: books[0] };
  for (let i = 1; i < len; i++) {
    end = i;
    total += books[i];
    while (total > target && begin <= end) {
      total -= books[begin++];
    }
    const tempBookLen = end - begin + 1;
    if (total <= target) {
      if (bookLen < tempBookLen || (bookLen == tempBookLen && total > result.total)) {
        result = { begin, end, total };
        bookLen = tempBookLen;
      }
    }
  }
  if (result.total > target) return { begin: -1, end: -1, total: -1 };
  return result;
}

/*https://leetcode.com/problems/longest-palindromic-substring/description/*/
export function expand(s: string, left: number, right: number) {
  while (left >= 0 && right < s.length && s[left] == s[right]) {
    left--;
    right++;
  }
  return s.slice(left + 1, right);
}

export function longestPalindrome(s: string): string {
  let maxLen = 0;
  let maxStr = '';
  for (let i = 0; i < s.length; i++) {
    const oddWords = expand(s, i, i);
    const evenWords = expand(s, i, i + 1);
    if (oddWords.length > maxLen) {
      maxStr = oddWords;
      maxLen = oddWords.length;
    }
    if (evenWords.length > maxLen) {
      maxStr = evenWords;
      maxLen = evenWords.length;
    }
  }
  return maxStr;
}
