// 构造二叉搜索树                     
class Node {
    constructor(val) {
        this.val = val;
        this.left = this.right = null;
    }
}

class BinaryTree {
    constructor(arr) {
        let root = new Node(arr.shift());
        arr.forEach( element => {
            this.createBinarySearchTree(root, element);
        });
        return root;
    }

    createBinarySearchTree(root, val) {
        if(!root) 
            return;
        let pNode = root;
        if(val < pNode.val) {
            if(!pNode.left) {
                pNode.left = new Node(val);
            } else {
                this.createBinarySearchTree(pNode.left, val);
            }
        } else {
            if(!pNode.right) {
                pNode.right = new Node(val);
            } else {
                this.createBinarySearchTree(pNode.right, val);
            }
        }
    } 
} 

// 中序遍历打印二叉树
const printBinaryByMiddle = (root) => {
    const printArr = [];
    const printBinary = (root) => {
        if(root) {
            if(!root.left && !root.right) {
                printArr.push(root.val);
                return;
            }
            root.left && printBinary(root.left);
            printArr.push(root.val);
            root.right && printBinary(root.right);
        }
    } 
    printBinary(root);
    return printArr;
}

// 前序打印二叉树
const printBinaryByBefore = (root) => {
    const printArr = [];
    const printBinary = (root) => {
        if(root) {
            if(!root.left && !root.right) {
                printArr.push(root.val);
                return;
            }
            printArr.push(root.val);
            root.left && printBinary(root.left);
            root.right && printBinary(root.right);
        }
    }
    printBinary(root);
    return printArr;  
}

// 后序打印二叉树
const printBinaryByAfter = (root) => {
    const printArr = [];
    const printBinary = (root) => {
        if(root) {
            if(!root.left && !root.right) {
                printArr.push(root.val);
                return;
            }
            root.left && printBinary(root.left);
            root.right && printBinary(root.right);
            printArr.push(root.val);
        }
    }
    printBinary(root);
    return printArr;
}

let binaryTree = new BinaryTree([8, 3, 10, 1, 6, 4, 7, 14, 13]);
// console.log(binaryTree);
console.log("before: " , printBinaryByBefore(binaryTree));
console.log("middle: ", printBinaryByMiddle(binaryTree));
console.log("after: ", printBinaryByAfter(binaryTree));

