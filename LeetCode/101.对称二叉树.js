/*
 * @lc app=leetcode.cn id=101 lang=javascript
 *
 * [101] 对称二叉树
 *
 * https://leetcode-cn.com/problems/symmetric-tree/description/
 *
 * algorithms
 * Easy (48.30%)
 * Likes:    456
 * Dislikes: 0
 * Total Accepted:    57.8K
 * Total Submissions: 119.1K
 * Testcase Example:  '[1,2,2,3,4,4,3]'
 *
 * 给定一个二叉树，检查它是否是镜像对称的。
 * 
 * 例如，二叉树 [1,2,2,3,4,4,3] 是对称的。
 * 
 * ⁠   1
 * ⁠  / \
 * ⁠ 2   2
 * ⁠/ \ / \
 * 3  4 4  3
 * 
 * 
 * 但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:
 * 
 * ⁠   1
 * ⁠  / \
 * ⁠ 2   2
 * ⁠  \   \
 * ⁠  3    3
 * 
 * 
 * 说明:
 * 
 * 如果你可以运用递归和迭代两种方法解决这个问题，会很加分。
 * 
 */
/**
 * Definition for a binary tree node.
 * function TreeNode(val) {
 *     this.val = val;
 *     this.left = this.right = null;
 * }
 */

class Node {
    constructor(val) {
        this.val = val;
        this.pos = null;
        this.leftChild = this.rightChild = null; 
    }
}

// 构造完全二叉树
class BinaryTree {
    constructor(dataArr) {
        let nodeList = [];
        for(let i = 0, len = dataArr.length; i<len; i++) {
            let node = new Node(dataArr[i]);
            nodeList.push(node);
            if(i > 0) {
                // 计算当前节点属于哪一层
                let n = Math.floor(Math.sqrt(i + 1));
                // 计算当前层数的起始节点
                let q = Math.pow(2, n) - 1;
                // 计算上一层的起始节点
                let p = Math.pow(2, n-1) - 1;
                // console.log(n, q, p);
                let parent = nodeList[p + Math.floor((i - q) / 2)];
                if(parent.leftChild) {
                    parent.rightChild = node;
                } else {
                    parent.leftChild = node;
                }
            }
        }
        const root = nodeList.shift();
        nodeList.length = 0; // 清空数组
        return root;
    }
}
/**
 * @param {TreeNode} root
 * @return {boolean}
 */
var isSymmetric = function(root) {
    const compare = (left, right) => {
        // console.log(left.val, right.val);
        if(!left && !right ) { // 叶子节点
            return true;
        } else if((!left && right) || (left && !right) || left.val !== right.val) {
            return false;
        } else {
            return compare(left.leftChild, right.rightChild) &&
            compare(left.rightChild, right.leftChild);
        }
    }

    if(!root) {
        return true;
    } else {
        return compare(root.leftChild, root.rightChild);
    }
};

const printBinaryTree = (root) => {
    const print = (left, right) => {
        if(!left && !right) {
            return;
        } else {
            console.log(left ? left.val : null, right ? right.val : null);
            print(left.leftChild, left.rightChild)
            print(right.leftChild, right.rightChild);
        }
    }
    if(root) {
        console.log(root.val);
        print(root.leftChild, root.rightChild);
    }
}

// const binaryTree = new BinaryTree([1,2,2,null,3,null,3]);
const binaryTree = new BinaryTree([1, 2]);
console.log(binaryTree);
// printBinaryTree(binaryTree);
// console.log(isSymmetric(binaryTree));


