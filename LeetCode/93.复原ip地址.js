/*
 * @lc app=leetcode.cn id=93 lang=javascript
 *
 * [93] 复原IP地址
 *
 * https://leetcode-cn.com/problems/restore-ip-addresses/description/
 *
 * algorithms
 * Medium (45.20%)
 * Likes:    133
 * Dislikes: 0
 * Total Accepted:    14.6K
 * Total Submissions: 32.2K
 * Testcase Example:  '"25525511135"'
 *
 * 给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。
 * 
 * 示例:
 * 
 * 输入: "25525511135"
 * 输出: ["255.255.11.135", "255.255.111.35"]
 * 
 */
/**
 * @param {string} s
 * @return {string[]}
 */
var restoreIpAddresses = function (s) {
    const resultIp = [];
    const findIp = (arr, index = 0, result = []) => {
        if (result.length >= 4) {
            return;
        } else if (result.length >= 3) {
            const target = parseInt(arr.slice(index));
            console.log("target", target);
            if (target >= 0 && target <= 255) {
                result.push(target);
                if (result.join('').length === arr.length) {
                    // const resultStr = result.map(item => item + '').join('.');
                    resultIp.push(result.map(item => item + '').join('.'));
                }
            }
            return;
        } else {
            for (let i = 1; i <= 3; i++) {
                const target = parseInt(arr.slice(index, index + i));
                console.log(target)
                if (target >= 0 && target <= 255) {
                    // result.push(target)
                    // console.log(result)
                    // findIp(arr, index+i, result.concat(target))
                    findIp(arr, index + i, [...result, target])
                } else {
                    return;
                }
            }
        }
    }
    findIp(s)
    console.log(resultIp)
    return (resultIp)
};

// restoreIpAddresses("25525511135")
restoreIpAddresses('010010')
