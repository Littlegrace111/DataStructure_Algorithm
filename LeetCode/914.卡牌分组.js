/*
 * @lc app=leetcode.cn id=914 lang=javascript
 *
 * [914] 卡牌分组
 *
 * https://leetcode-cn.com/problems/x-of-a-kind-in-a-deck-of-cards/description/
 *
 * algorithms
 * Easy (31.18%)
 * Likes:    56
 * Dislikes: 0
 * Total Accepted:    5.2K
 * Total Submissions: 16.5K
 * Testcase Example:  '[1,2,3,4,4,3,2,1]'
 *
 * 给定一副牌，每张牌上都写着一个整数。
 * 
 * 此时，你需要选定一个数字 X，使我们可以将整副牌按下述规则分成 1 组或更多组：
 * 
 * 
 * 每组都有 X 张牌。
 * 组内所有的牌上都写着相同的整数。
 * 
 * 
 * 仅当你可选的 X >= 2 时返回 true。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：[1,2,3,4,4,3,2,1]
 * 输出：true
 * 解释：可行的分组是 [1,1]，[2,2]，[3,3]，[4,4]
 * 
 * 
 * 示例 2：
 * 
 * 输入：[1,1,1,2,2,2,3,3]
 * 输出：false
 * 解释：没有满足要求的分组。
 * 
 * 
 * 示例 3：
 * 
 * 输入：[1]
 * 输出：false
 * 解释：没有满足要求的分组。
 * 
 * 
 * 示例 4：
 * 
 * 输入：[1,1]
 * 输出：true
 * 解释：可行的分组是 [1,1]
 * 
 * 
 * 示例 5：
 * 
 * 输入：[1,1,2,2,2,2]
 * 输出：true
 * 解释：可行的分组是 [1,1]，[2,2]，[2,2]
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= deck.length <= 10000
 * 0 <= deck[i] < 10000
 * 
 * 
 * 
 * 
 */
/**
 * 问题转化为求最大公约数问题 （最小公倍数 = a * b / 最大公约数）
    递归求两树最大公约数
 * @param {number[]} deck
 * @return {boolean}
 */
var hasGroupsSizeX = function(deck) {
    // 对入参进行数据处理
    const mapList = {}
    deck.forEach( index => {
        // console.log(index)
        if(mapList.hasOwnProperty(index)) {
            mapList[index].count++
        } else {
            const temp = { count: 1}
            mapList[index] = temp
        }
    })
    console.log(mapList)
    const countArray = []
    Object.keys(mapList).forEach( key => {
        countArray.push(mapList[key].count)
    })
    console.log(countArray)
    // 数据处理end

    if(countArray.length === 1) {
        if(countArray[0] > 1) {
            return true  
        } else {
            return false
        }
    } 

    // 使得问题转化为求countArray中元素的最大公约数，如果公约数是偶数，则返回true；奇数返回false

    //循环求两数的最大公约数
    const findGreatestDivisor = (numberFirst, numberLast) => {
        const min = Math.min(numberFirst, numberLast)
        // 循环求最大公约数
        for(var i=min; i>=1; i--) {
            if(numberFirst%i === 0 && numberLast%i === 0) {
                break;
            }
        }
        console.log(i)
        return i
    }

    //辗转相除法
    const findGreatestDivisorV2 = (a, b) => {
        // let min = Math.min(numberFirst, numberLast)
        // let max = Math.max(numberFirst, numberLast)

        while(a % b !== 0) {
            let c = a % b
            a = b
            b = c
        }
        return b
    }

    // 辗转相除法的递归表示
    const findGreatestDivisorV3 = (first, last) => {
        if(first === 0) {
            return last
        } else {
            return findGreatestDivisorV3(last, first % last)
        }
    }

    // 循环写法
    while(countArray.length > 1) {
        countArray.splice(0, 2, findGreatestDivisorV2(countArray[0], countArray[1]))
    }
    
    console.log(countArray)
    if(countArray[0] > 1)
        return true
    else 
        return false
};
console.log(hasGroupsSizeX([1,1,2,2,2,2]))
