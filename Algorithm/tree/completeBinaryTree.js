class Node {
    constructor(val) {
        this.val = val;
        this.left = this.right = null;
    }
}

// 构造完全二叉树，找到叶子节点的最上一层的最后一个父节点
class CompleteBinaryTree {
    constructor(data) {
        const nodeList = [];
        for(let i=0; i<data.length; i++) {
            const node = new Node(data[i]);
            nodeList.push(node);
            const father = Math.floor((i+1)/2) - 1;
            if(father >= 0) {
                if(!nodeList[father].left) {
                    nodeList[father].left = node;
                } else {
                    nodeList[father].right = node;
                }
            }
        }
        return nodeList[0];
    }
}

// 按层打印二叉树: 使用了多个队列空间
const printCompleteBinaryTree = (root) => {
    let queue = new Array();
    queue.push(root);
    while(queue.length > 0) {
        const dataList = [];
        queue.forEach( item => {
            dataList.push(item.val);
        })
        console.log(dataList);
        const queue2 = new Array();
        while(queue.length > 0) {
            const node = queue.shift();
            node.left && queue2.push(node.left);
            node.right && queue2.push(node.right);
        }  
        queue = queue2;
    }

}

//按层打印二叉树，增加一个lastNode标记位，只使用一个队列空间
const printCompleteBinaryTree2 = (root) => {
    let pLastNode = root;
    const queue = []; // 保存树队列
    let dataList = []; // 保存输出结果
    queue.push(root);
    while(queue.length > 0) {
        const node = queue.shift();
        dataList.push(node.val);
        node.left && queue.push(node.left);
        node.right && queue.push(node.right);
        if(node === pLastNode) {
            console.log(dataList);
            dataList = [];
            if(queue.length > 0) {
                pLastNode = queue[queue.length - 1];
            }
        }
    }
}

let tree1 = new CompleteBinaryTree([1,2,2,3,4,4,3]);
let tree2 = new CompleteBinaryTree([8, 6, 10, 5, 7, 9]);
printCompleteBinaryTree(tree2);
printCompleteBinaryTree2(tree2);