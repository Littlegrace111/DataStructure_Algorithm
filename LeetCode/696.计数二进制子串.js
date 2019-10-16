/*
 * @lc app=leetcode.cn id=696 lang=javascript
 *
 * [696] 计数二进制子串
 *
 * https://leetcode-cn.com/problems/count-binary-substrings/description/
 *
 * algorithms
 * Easy (46.24%)
 * Likes:    95
 * Dislikes: 0
 * Total Accepted:    4.3K
 * Total Submissions: 9.3K
 * Testcase Example:  '"00110"'
 *
 * 给定一个字符串 s，计算具有相同数量0和1的非空(连续)子字符串的数量，并且这些子字符串中的所有0和所有1都是组合在一起的。
 * 
 * 重复出现的子串要计算它们出现的次数。
 * 
 * 示例 1 :
 * 
 * 
 * 输入: "00110011"
 * 输出: 6
 * 解释: 有6个子串具有相同数量的连续1和0：“0011”，“01”，“1100”，“10”，“0011” 和 “01”。
 * 
 * 请注意，一些重复出现的子串要计算它们出现的次数。
 * 
 * 另外，“00110011”不是有效的子串，因为所有的0（和1）没有组合在一起。
 * 
 * 
 * 示例 2 :
 * 
 * 
 * 输入: "10101"
 * 输出: 4
 * 解释: 有4个子串：“10”，“01”，“10”，“01”，它们具有相同数量的连续1和0。
 * 
 * 
 * 注意：
 * 
 * 
 * s.length 在1到50,000之间。
 * s 只包含“0”或“1”字符。
 * 
 * 
 */
/**
 * @param {string} s
 * @return {number}
 */
// var countBinarySubstrings = function(s) {
//     let count = 0, arr = s.match(/(1+|0+)/g)
//     console.log(arr)
//     for(let i=0, len=arr.length; i < len - 1; i++) {
//         count += Math.min(arr[i].length, arr[i+1].length)
//     }
//     console.log(count)
//     return count
// };
// countBinarySubstrings('0100011')

var countBinarySubstrings = function(s) {
    const r = []
    const match = (str) => {
        // console.log(str.match(/^(0+|1+)/g))
        const j = str.match(/^(0+|1+)/g)[0]
        const o = (j[0]^1).toString().repeat(j.length)
        let reg = new RegExp(`^(${j}${o})`)
        // console.log(reg)
        if(reg.test(str)) {
            console.log(RegExp.$1)
            return RegExp.$1
        } else {
            return ''
        }
    }

    for(let i=0, len=s.length-1; i < len; i++) {
        let sub = match(s.slice(i))
        if(sub) {
            r.push(sub)
        }
    }
    console.log(r)
    return r.length
};
countBinarySubstrings('00000011')
