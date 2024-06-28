export function arrayCompare(arr1: Array<number>, arr2: Array<number>) {
  if (arr1.length != arr2.length) return false;
  let counter = 0;
  for (const item of arr1) {
    if (item != arr2[counter]) return false;
    counter++;
  }
  return true;
}
