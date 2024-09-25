/*https://leetcode.com/problems/add-two-numbers/*/
class ListNode {
  val: number;
  next: ListNode | null;

  constructor(val?: number, next?: ListNode | null) {
    this.val = val == undefined ? 0 : val;
    this.next = next == undefined ? null : next;
  }
}

export function convertArrayToList(arr: Array<number>): ListNode | null {
  const len = arr.length;
  if (len == 0) return null;
  const result: ListNode = new ListNode(arr[0], null);
  let temp = result;
  for (let i = 1; i < len; i++) {
    const _next = new ListNode(arr[i], null);
    temp.next = _next;
    temp = _next;
  }
  return result;
}

export function convertListToArray(_list: ListNode | null): Array<number> {
  if (_list == null) return [];
  let temp: ListNode | null = _list;
  const result: Array<number> = [];
  while (temp != null) {
    result.push(temp.val);
    temp = temp.next;
  }
  return result;
}

export function addTwoNumbers(l1: ListNode | null, l2: ListNode | null): ListNode | null {
  let temp1: ListNode | null = l1;
  let temp2: ListNode | null = l2;
  const rootResult: ListNode = new ListNode(0, null);
  let tempResult = rootResult;
  let remain = 0;
  while (temp1 != null && temp2 != null) {
    const _total = temp1.val + temp2.val + remain;
    if (_total >= 10) {
      tempResult.val = _total - 10;
      remain = 1;
    } else {
      tempResult.val = _total;
      remain = 0;
    }
    temp1 = temp1.next;
    temp2 = temp2.next;
    if (temp1 != null && temp2 != null) {
      const _next = new ListNode(0, null);
      tempResult.next = _next;
      tempResult = _next;
    }
  }
  while (temp1 != null) {
    const _next = new ListNode(0, null);
    tempResult.next = _next;
    tempResult = _next;
    const _total = temp1.val + remain;
    if (_total >= 10) {
      tempResult.val = _total - 10;
      remain = 1;
    } else {
      tempResult.val = _total;
      remain = 0;
    }
    temp1 = temp1.next;
  }
  while (temp2 != null) {
    const _next = new ListNode(0, null);
    tempResult.next = _next;
    tempResult = _next;
    const _total = temp2.val + remain;
    if (_total >= 10) {
      tempResult.val = _total - 10;
      remain = 1;
    } else {
      tempResult.val = _total;
      remain = 0;
    }
    temp2 = temp2.next;
  }
  if (remain == 1) tempResult.next = new ListNode(1, null);
  return rootResult;
}

/*https://leetcode.com/problems/merge-two-sorted-lists/*/
export function mergeTwoLists(list1: ListNode | null, list2: ListNode | null): ListNode | null {
  if (list1 == null && list2 == null) return null;
  else if (list1 == null && list2 != null) return list2;
  else if (list1 != null && list2 == null) return list1;
  const result: ListNode = new ListNode(0, null);
  let temp = result;
  let node1 = list1;
  let node2 = list2;
  while (node1 != null && node2 != null) {
    const val1 = node1.val;
    const val2 = node2.val;
    if (val1 > val2) {
      temp.val = val2;
      node2 = node2.next;
    } else {
      temp.val = val1;
      node1 = node1.next;
    }
    if (node1 != null && node2 != null) {
      temp.next = new ListNode(0, null);
      temp = temp.next;
    }
  }
  if (node1 != null) temp.next = node1;
  else if (node2 != null) temp.next = node2;
  return result;
}
