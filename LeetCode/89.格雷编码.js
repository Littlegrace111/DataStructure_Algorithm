/*
 * @lc app=leetcode.cn id=89 lang=javascript
 *
 * [89] 格雷编码
 *
 * https://leetcode-cn.com/problems/gray-code/description/
 *
 * algorithms
 * Medium (65.79%)
 * Likes:    80
 * Dislikes: 0
 * Total Accepted:    10.4K
 * Total Submissions: 15.9K
 * Testcase Example:  '2'
 *
 * 格雷编码是一个二进制数字系统，在该系统中，两个连续的数值仅有一个位数的差异。
 * 
 * 给定一个代表编码总位数的非负整数 n，打印其格雷编码序列。格雷编码序列必须以 0 开头。
 * 
 * 示例 1:
 * 
 * 输入: 2
 * 输出: [0,1,3,2]
 * 解释:
 * 00 - 0
 * 01 - 1
 * 11 - 3
 * 10 - 2
 * 
 * 对于给定的 n，其格雷编码序列并不唯一。
 * 例如，[0,2,3,1] 也是一个有效的格雷编码序列。
 * 
 * 00 - 0
 * 10 - 2
 * 11 - 3
 * 01 - 1
 * 
 * 示例 2:
 * 
 * 输入: 0
 * 输出: [0]
 * 解释: 我们定义格雷编码序列必须以 0 开头。
 * 给定编码总位数为 n 的格雷编码序列，其长度为 2^n。当 n = 0 时，长度为 2^0 = 1。
 * 因此，当 n = 0 时，其格雷编码序列为 [0]。
 * 
 * 
 */
/**
 * @param {number} n
 * @return {number[]}
 */
var grayCode = function(n) {
    if(n === 0) {
        return [0]
    } else if (n === 1) {
        return [0, 1]
    } else {
        const lastGrayCode = grayCode(n-1)
        const result = []
        for(let i=0; i<lastGrayCode.length; i++) {
            result.push((lastGrayCode[i]<<1) + i%2)
            result.push((lastGrayCode[i]<<1) + ((i%2)^1))
        }
        return result
    }

    // 采用循环的方式： 虽然graycode的思想查了资料，凡是递归，都可以解析成树的结构
    // if(n === 0) return [0]
    // let result = [0, 1]
    // for(let i=1; i<n; i++) {
    //     let temp = []
    //     for(let j=0; j<result.length; j++) {
    //         const temp1 = (result[j]<<1) + j%2
    //         const temp2 = (result[j]<<1) + ((j%2)^1)
            
    //         temp.push(temp1)
    //         temp.push(temp2)
    //     }
    //     result = [...temp];
    // }
    
    // return result
};
console.log(grayCode(3))
