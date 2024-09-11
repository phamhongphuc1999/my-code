/*https://leetcode.com/problems/valid-sudoku/description/*/
type ValidType = { [order: number]: { [num: number]: boolean | undefined } };

export function isValidSudoku(board: Array<Array<string>>): boolean {
  const rowValidation: ValidType = {};
  const columnValidation: ValidType = {};
  const blockValidation: ValidType = {};
  for (let row = 0; row < 9; row++) {
    for (let column = 0; column < 9; column++) {
      const value = parseInt(board[row][column]);
      if (Number.isInteger(value)) {
        const blockIndex = Math.floor(row / 3) * 3 + Math.floor(column / 3);
        if (rowValidation[row]) {
          if (rowValidation[row][value]) return false;
          else rowValidation[row][value] = true;
        } else rowValidation[row] = { [value]: true };
        if (columnValidation[column]) {
          if (columnValidation[column][value]) return false;
          else columnValidation[column][value] = true;
        } else columnValidation[column] = { [value]: true };
        if (blockValidation[blockIndex]) {
          if (blockValidation[blockIndex][value]) return false;
          else blockValidation[blockIndex][value] = true;
        } else blockValidation[blockIndex] = { [value]: true };
      }
    }
  }
  return true;
}
