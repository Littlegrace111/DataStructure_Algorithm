/*
 * @lc app=leetcode.cn id=62 lang=javascript
 *
 * [62] 不同路径
 *
 * https://leetcode-cn.com/problems/unique-paths/description/
 *
 * algorithms
 * Medium (55.84%)
 * Likes:    334
 * Dislikes: 0
 * Total Accepted:    43K
 * Total Submissions: 76K
 * Testcase Example:  '3\n2'
 *
 * 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
 * 
 * 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
 * 
 * 问总共有多少条不同的路径？
 * 
 * 
 * 
 * 例如，上图是一个7 x 3 的网格。有多少可能的路径？
 * 
 * 说明：m 和 n 的值均不超过 100。
 * 
 * 示例 1:
 * 
 * 输入: m = 3, n = 2
 * 输出: 3
 * 解释:
 * 从左上角开始，总共有 3 条路径可以到达右下角。
 * 1. 向右 -> 向右 -> 向下
 * 2. 向右 -> 向下 -> 向右
 * 3. 向下 -> 向右 -> 向右
 * 
 * 
 * 示例 2:
 * 
 * 输入: m = 7, n = 3
 * 输出: 28
 * 
 */
/**
 * @param {number} m
 * @param {number} n
 * @return {number}
 */
// 解题思路使用递归，可以非常直观的求解出来，但是递归有很多重复计算是可以优化的
var uniquePaths2 = function(m, n) {
    let countPaths = 0; 
    const paths = (m, n) => {
        if(m <=1 && n <=1 ) {
            return 1;
        } else if(m === 1 || n === 1) {
            return 1;
        } else if(m === 2 && n === 2) {
            return 2;
        } else if( (m === 3 && n === 2) || (m===2 && n===3)) {
            return 3;
        }
        return paths(m-1, n) + paths(m, n-1);
    }
    countPaths = paths(m, n);
    return countPaths;
};

// 利用空间缓存来存储已经计算过的结果；
var uniquePaths = function(m ,n) {
    let pathDimensions = new Array(101);
    for(let i=0; i<pathDimensions.length; i++) {
        pathDimensions[i] = new Array(101);
    }
    const paths = (m, n) => {
        if(m <=1 && n <=1 ) {
            return 1;
        } else if(m === 1 || n === 1) {
            return 1;
        } else if(m === 2 && n === 2) {
            return 2;
        } else if( (m === 3 && n === 2) || (m===2 && n===3)) {
            return 3;
        }
        if(pathDimensions[m][n]) {
            return pathDimensions[m][n];
        } 
        pathDimensions[m-1][n] = paths(m-1, n);
        pathDimensions[m][n-1] = paths(m, n-1);
        pathDimensions[m][n] = pathDimensions[m-1][n] + pathDimensions[m][n-1];
        return pathDimensions[m][n];
    }
    pathDimensions[m][n] = paths(m,n);
    return pathDimensions[m][n];
}

const uniquePaths3 = (m, n) => {
    
}


console.log(uniquePaths(100, 1));

