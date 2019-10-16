/*
 * @lc app=leetcode.cn id=148 lang=javascript
 *
 * [148] 排序链表
 *
 * https://leetcode-cn.com/problems/sort-list/description/
 *
 * algorithms
 * Medium (61.71%)
 * Likes:    292
 * Dislikes: 0
 * Total Accepted:    24.9K
 * Total Submissions: 40.2K
 * Testcase Example:  '[4,2,1,3]'
 *
 * 在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。
 * 
 * 示例 1:
 * 
 * 输入: 4->2->1->3
 * 输出: 1->2->3->4
 * 
 * 
 * 示例 2:
 * 
 * 输入: -1->5->3->4->0
 * 输出: -1->0->3->4->5
 * 
 */
/**
 * Definition for singly-linked list.
 * function ListNode(val) {
 *     this.val = val;
 *     this.next = null;
 * }
 */

class ListNode {
    constructor(val) {
        this.val = val;
        this.next = null;
    }
}

class LinkList {
    constructor(arr) {
        let head = new ListNode(arr.shift());
        let next = head;
        arr.forEach( element => {
            next.next = new ListNode(element);
            next = next.next;
        });
        return head;
    }
}

const swap = (p, q) => {
    const temp = p.val;
    p.val = q.val;
    q.val = temp;
}

const partition = (head, end) => {
    let p = head, q = head.next;
    const baseLine = head.val; 
    while(q !== end) {
        if(q.val < baseLine) { // 放到baseLine左边
            p = p.next;
            swap(p, q);
        } 
        q = q.next;
    }
    swap(head, p);
    return p;
}

/**
 * @param {ListNode} head
 * @return {ListNode}
 */
var sortList = function(head) {
    const sort = (begin, end) => {
        if(begin !== end) {
            let part = partition(begin, end);
            // console.log(part);
            sort(head, part);
            sort(part.next, end);
        }
    }

    sort(head, null);
    return head;
};

var printLinkList = (linkList) => {
    let next = linkList;
    const result = [];
    while(next) {
        result.push(next.val);
        next = next.next;
    }
    console.log(result);
};


// console.log(new LinkList([4, 2, 1, 3]))
const singleLinkList = new LinkList([4, 1, 3, 2, 7, 9, 10, 12, 6]);
// sortList(new LinkList([-84,142,41,-17,-71,170,186,183,-21,-76,76,10,29,81,112,-39,-6,-43,58,41,111,33,69,97,-38,82,-44,-7,99,135,42,150,149,-21,-30,164,153,92,180,-61,99,-81,147,109,34,98,14,178,105,5,43,46,40,-37,23,16,123,-53,34,192,-73,94,39,96,115,88,-31,-96,106,131,64,189,-91,-34,-56,-22,105,104,22,-31,-43,90,96,65,-85,184,85,90,118,152,-31,161,22,104,-85,160,120,-31,144,115]));
sortList(singleLinkList);
printLinkList(singleLinkList);

