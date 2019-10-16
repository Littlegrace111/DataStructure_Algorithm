/*
 * @lc app=leetcode.cn id=922 lang=javascript
 *
 * [922] 按奇偶排序数组 II
 *
 * https://leetcode-cn.com/problems/sort-array-by-parity-ii/description/
 *
 * algorithms
 * Easy (64.93%)
 * Likes:    56
 * Dislikes: 0
 * Total Accepted:    15.4K
 * Total Submissions: 23.7K
 * Testcase Example:  '[4,2,5,7]'
 *
 * 给定一个非负整数数组 A， A 中一半整数是奇数，一半整数是偶数。
 * 
 * 对数组进行排序，以便当 A[i] 为奇数时，i 也是奇数；当 A[i] 为偶数时， i 也是偶数。
 * 
 * 你可以返回任何满足上述条件的数组作为答案。
 * 
 * 
 * 
 * 示例：
 * 
 * 输入：[4,2,5,7]
 * 输出：[4,5,2,7]
 * 解释：[4,7,2,5]，[2,5,4,7]，[2,7,4,5] 也会被接受。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 2 <= A.length <= 20000
 * A.length % 2 == 0
 * 0 <= A[i] <= 1000
 * 
 * 
 * 
 * 
 */

const swap = function(array, i, j) {
    let temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}
/**
 * 先对数组进行奇偶归类
 * @param {number[]} A
 * @return {number[]}
 */
var sortArrayByParityI = function(array) {
    //对数组进行奇偶归类：前面是偶数，后面是奇数
    const len = array.length;
    for(let i=0; i<len/2; i++) {
        if(array[i] % 2 === 0) // 如果是偶数跳过
            continue;
        else { // 奇数
            for(let j=i+1; j<len; j++) {
                if(array[j] % 2 === 0 ) {
                    swap(array, i, j)
                    break;
                }
            }
        }
    }

    // console.log(array)
    if((len / 2) % 2 === 1) {
        for(let i=1; i<len/2; i=i+2) {
            swap(array, i, i+(len/2))
        }
    } else {
        for(let i=1; i<len/2; i=i+2) {
            swap(array, i, i+(len/2)-1)
        }
    }
    // console.log(array);
    return array;
};

const array = [4, 2, 1, 3, 5, 6]; // 4 1 2 3 5 6
//sortArrayByParityI(array)

const sortArrayByParityII = function(array) {
    const len = array.length;
    for(let i=0; i<len-1; i++) {
        if(i%2 !== array[i]%2) {
            for(let j=i+1; j<len; j++) {
                if(array[j]%2 === i%2) {
                    swap(array, i, j);
                    break;
                }
            }
        }
    }
    // console.log(array)
    return array
}
sortArrayByParityII(array)
