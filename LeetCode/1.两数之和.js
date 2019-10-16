/*
 * @lc app=leetcode.cn id=1 lang=javascript
 *
 * [1] 两数之和
 *
 * https://leetcode-cn.com/problems/two-sum/description/
 *
 * algorithms
 * Easy (46.53%)
 * Likes:    6086
 * Dislikes: 0
 * Total Accepted:    519.1K
 * Total Submissions: 1.1M
 * Testcase Example:  '[2,7,11,15]\n9'
 *
 * 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
 * 
 * 你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
 * 
 * 示例:
 * 
 * 给定 nums = [2, 7, 11, 15], target = 9
 * 
 * 因为 nums[0] + nums[1] = 2 + 7 = 9
 * 所以返回 [0, 1]
 * 
 * 
 */

// @lc code=start
/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
var twoSum = function(nums, target) {
    let result = null;
    // 把数组flattern成一个hashmap
    const map = nums.reduce((origin, item, index) => {
        if(!origin.hasOwnProperty(item)) {
            origin[item] = []
        }
        origin[item].push(index);
        return origin;
    }, {});
    console.log(map);

    nums.forEach( item => {
        const first = map[item].shift();
        if(map.hasOwnProperty(target - item) && map[target - item].length > 0) {
            result = [first, map[target-item][0]];
        }
    });
    return result;
};

console.log(twoSum([2, 3, 7, 1, 2], 9));

// @lc code=end

