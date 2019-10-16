/*
 * @lc app=leetcode.cn id=860 lang=javascript
 *
 * [860] 柠檬水找零
 *
 * https://leetcode-cn.com/problems/lemonade-change/description/
 *
 * algorithms
 * Easy (51.68%)
 * Likes:    78
 * Dislikes: 0
 * Total Accepted:    10.3K
 * Total Submissions: 19.8K
 * Testcase Example:  '[5,5,5,10,20]'
 *
 * 在柠檬水摊上，每一杯柠檬水的售价为 5 美元。
 * 
 * 顾客排队购买你的产品，（按账单 bills 支付的顺序）一次购买一杯。
 * 
 * 每位顾客只买一杯柠檬水，然后向你付 5 美元、10 美元或 20 美元。你必须给每个顾客正确找零，也就是说净交易是每位顾客向你支付 5 美元。
 * 
 * 注意，一开始你手头没有任何零钱。
 * 
 * 如果你能给每位顾客正确找零，返回 true ，否则返回 false 。
 * 
 * 示例 1：
 * 
 * 输入：[5,5,5,10,20]
 * 输出：true
 * 解释：
 * 前 3 位顾客那里，我们按顺序收取 3 张 5 美元的钞票。
 * 第 4 位顾客那里，我们收取一张 10 美元的钞票，并返还 5 美元。
 * 第 5 位顾客那里，我们找还一张 10 美元的钞票和一张 5 美元的钞票。
 * 由于所有客户都得到了正确的找零，所以我们输出 true。
 * 
 * 
 * 示例 2：
 * 
 * 输入：[5,5,10]
 * 输出：true
 * 
 * 
 * 示例 3：
 * 
 * 输入：[10,10]
 * 输出：false
 * 
 * 
 * 示例 4：
 * 
 * 输入：[5,5,10,10,20]
 * 输出：false
 * 解释：
 * 前 2 位顾客那里，我们按顺序收取 2 张 5 美元的钞票。
 * 对于接下来的 2 位顾客，我们收取一张 10 美元的钞票，然后返还 5 美元。
 * 对于最后一位顾客，我们无法退回 15 美元，因为我们现在只有两张 10 美元的钞票。
 * 由于不是每位顾客都得到了正确的找零，所以答案是 false。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 <= bills.length <= 10000
 * bills[i] 不是 5 就是 10 或是 20 
 * 
 * 
 */
/**
 * @param {number[]} bills
 * @return {boolean}
 */

const findSubArr = (arr, subArr) => {
    let posArr = [];
    for(let i=0; i<subArr.length; i++) {
        const pos = arr.indexOf(subArr[i]);
        if(pos > -1) {
            posArr.push(pos);
            arr.splice(pos, 1);
        } else {
            return false;
        }
    }
    return true;
}

const removeItems = (arr, target) => {
    target.forEach( item => {
        const pos = arr.indexOf(item);
        if(pos > -1) {
            arr.splice(pos, 1);
        }
    });
}

// var lemonadeChange = function(bills) {
//     if(bills[0] !== 5) {
//         return false;
//     }
//     const countList = []; // 手里的零钱
//     let target = []; // 需要找给顾客的零钱
//     for(let i=0; i<bills.length; i++) {
//         if(i === 0) {
//             countList[0] = bills[0];
//         } else {
//             if(bills[i]/5 === 1) {
//                 countList.push(bills[i]);
//             } else if(bills[i] / 5 === 2) {
//                 target = [5];
//                 let result = findSubArr(countList.slice(0), [5]);
//                 if(!result) {
//                     return false;
//                 } else {
//                     removeItems(countList, target);
//                 }
//                 countList.push(bills[i]);
//             } else if(bills[i] / 5 === 4) {
//                 target = [10, 5];
//                 let result = findSubArr(countList.slice(0), [10, 5]); // 优先给金额大的零钱,贪心算法
//                 if(!result) {
//                     target = [5, 5, 5];
//                     result = findSubArr(countList.slice(0), [5, 5, 5]);
//                 }
//                 // console.log(target);
//                 if(!result) {
//                     return false;
//                 } else {
//                     removeItems(countList, target);
//                 }
//                 countList.push(bills[i]);
//             }
//         }
//     }
//     return true;
// };

const isChangeOver = (handList, change) => {

};

//给手里的钱降序排列
var lemonadeChange = function(bills) {
    if(bills[0] !== 5) { // 第一个人的钱不是5的话则整个数组找不开
        return false;
    }
    const handList = []; // 手里的钱
    let change = 0; // 需要找的零钱
    for(let i=0; i<bills.length; i++) {
        change = bills[i] - 5;
        if(change === 0) {
            handList.push(bills[i]);
        } else if(change >= 5) {
            // 贪心算法：尽量先把大额的钱找给客户，所以给其零钱降序排列
            handList.sort( (a, b) => b-a ); // 降序排列
            for(let j=0; j<handList.length; j++) {
                if(handList[j] <= change) {
                    change -= handList[j];
                    handList.splice(j, 1);
                    j--; // 零钱数组的长度发生了变化，必须让指针归位
                }
                if(change === 0) {
                    break;
                }
            }
            // console.log(change);
            if(change > 0) {
                return false;
            } else {
                handList.push(bills[i]); // 把客户的钱存起来
            }
        }
    }
    return true;
};

console.log(lemonadeChange([5,5,5,10,20]));

