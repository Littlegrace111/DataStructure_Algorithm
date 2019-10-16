/*
 * @lc app=leetcode.cn id=451 lang=javascript
 *
 * [451] 根据字符出现频率排序
 *
 * https://leetcode-cn.com/problems/sort-characters-by-frequency/description/
 *
 * algorithms
 * Medium (59.96%)
 * Likes:    64
 * Dislikes: 0
 * Total Accepted:    8K
 * Total Submissions: 13.4K
 * Testcase Example:  '"tree"'
 *
 * 给定一个字符串，请将字符串里的字符按照出现的频率降序排列。
 * 
 * 示例 1:
 * 
 * 
 * 输入:
 * "tree"
 * 
 * 输出:
 * "eert"
 * 
 * 解释:
 * 'e'出现两次，'r'和't'都只出现一次。
 * 因此'e'必须出现在'r'和't'之前。此外，"eetr"也是一个有效的答案。
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入:
 * "cccaaa"
 * 
 * 输出:
 * "cccaaa"
 * 
 * 解释:
 * 'c'和'a'都出现三次。此外，"aaaccc"也是有效的答案。
 * 注意"cacaca"是不正确的，因为相同的字母必须放在一起。
 * 
 * 
 * 示例 3:
 * 
 * 
 * 输入:
 * "Aabb"
 * 
 * 输出:
 * "bbAa"
 * 
 * 解释:
 * 此外，"bbaA"也是一个有效的答案，但"Aabb"是不正确的。
 * 注意'A'和'a'被认为是两种不同的字符。
 * 
 * 
 */
/**
 * @param {string} s
 * @return {string}
 * 
 * 解题思路：
 * 1. 做数据预处理：统计
 * 2. 给预处理结果排序
 * 3. 输出
 */

class Heap {
    constructor(arr) {
        this.data = arr;
    }

    sort(desc=false) {
        let iArr = this.data;
        let n = iArr.length;
        if(n <= 1) {
            return iArr;
        } else {
            for(let size = iArr.length - 1; size >= 1; size--) {
                // console.log(size)
                // 找到完全二叉树的最后一个父节点的位置：(size-1)/2
                for(let i = Math.floor((size-1)/2); i >= 0; i--) {
                    !desc && Heap.maxHeapify(iArr, i, size);
                    desc && Heap.minHeapify(iArr, i, size);
                }
                // console.log(iArr);
                // 一次最大堆构建完成，把第一个元素与最后一个元素交换
                Heap.swap(iArr, 0, size);
            }
            /**
             * 一次最大堆排序，把最大元素冒泡到顶层节点
             */
            // for(let i = Math.floor((n-2)/2); i >= 0; i--) {
            //     Heap.maxHeapify(iArr, i, n - 1);
            // }
            /**
             * 一次最大堆构建完成，把第一个元素与最后一个元素交换
             */
            // Heap.swap(iArr, 0, n-1);
            
            return iArr;
        }
    }

    toString() {
        return iArr;
    }

    static swap(Arr, p, q) {
        if(p === q) {
            return;
        }
        let temp = Arr[p];
        Arr[p] = Arr[q];
        Arr[q] = temp;
    }

    // 每一次构建最大堆的过程，都能把最大元素冒泡到顶层
    static maxHeapify(Arr, i, size) {
        let l = 2 * i + 1; // 左子节点索引
        let r = 2 * i + 2; // 右子节点索引
        let largest = i;
        if(l <= size && Arr[l][1] > Arr[largest][1]) {
            largest = l;
        } 
        if(r <= size && Arr[r][1] > Arr[largest][1]) {
            largest = r;
        }
        if(largest !== i) {
            Heap.swap(Arr, i, largest);
            Heap.maxHeapify(Arr, largest, size);
        }
    }

    // 每一个构建最小堆的过程，都能把最小元素冒泡到顶层
    static minHeapify(Arr, i, size) {
        let l = 2 * i + 1;
        let r = 2 * i + 2;
        let smallest = i;
        if(l <= size && Arr[l][1] < Arr[smallest][1]) {
            smallest = l;
        } 
        if(r <= size && Arr[r][1] < Arr[smallest][1]) {
            smallest = r;
        }
        if(smallest !== i) {
            Heap.swap(Arr, i, smallest);
            Heap.minHeapify(Arr, smallest, size);
        }
    }
}

var frequencySort = function(s) {
    // 1. 数据预处理：统计
    let frequencyList = new Map();
    s.split('').forEach( char => {
        if(!frequencyList.has(char)) {
            frequencyList.set(char, 1);
        } else {
            frequencyList.set(char, frequencyList.get(char)+1);
        }
    });
    // console.log(frequencyList);

    let resultArr = Array.from(frequencyList);
    console.log(resultArr);

    // 2. 排序
    const heap = new Heap(resultArr);
    console.log(heap.sort(true));

    // retuleArr = resultArr.map( item => item[0].repeat(item[1]))
    console.log(resultArr.map( item => item[0].repeat(item[1])).join(''));
    return resultArr.map( item => item[0].repeat(item[1])).join('');
};

frequencySort('helloworld');

