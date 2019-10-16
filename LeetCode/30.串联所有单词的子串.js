/*
 * @lc app=leetcode.cn id=30 lang=javascript
 *
 * [30] 串联所有单词的子串
 *
 * https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words/description/
 *
 * algorithms
 * Hard (27.69%)
 * Likes:    146
 * Dislikes: 0
 * Total Accepted:    13.1K
 * Total Submissions: 47.9K
 * Testcase Example:  '"barfoothefoobarman"\n["foo","bar"]'
 *
 * 给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。
 * 
 * 注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：
 * ⁠ s = "barfoothefoobarman",
 * ⁠ words = ["foo","bar"]
 * 输出：[0,9]
 * 解释：
 * 从索引 0 和 9 开始的子串分别是 "barfoor" 和 "foobar" 。
 * 输出的顺序不重要, [9,0] 也是有效答案。
 * 
 * 
 * 示例 2：
 * 
 * 输入：
 * ⁠ s = "wordgoodgoodgoodbestword",
 * ⁠ words = ["word","good","best","word"]
 * 输出：[]
 * 
 * 
 */
/**
 * @param {string} s
 * @param {string[]} words
 * @return {number[]}
 */
var findSubstring = function(s, words) {
    const resultIndex = [];
    const matchWords = (s, words, pattern='', index) => {
        if(words.length === 0) {
            resultIndex.push(index);
            return;
        } else if(words.length > 0){
            // console.log(words)
            words.forEach( (item, index) => {
                const position = s.indexOf(pattern + item);
                // console.log(position, pattern + item);
                if(position > -1) {
                    matchWords(s, words.filter((word, pos) => index !== pos ), pattern + item, position);
                } else {
                    return;
                }
            })
        }
    }
    // console.log(words)
    matchWords(s, words);
    console.log([...(new Set(resultIndex))])
    return [...(new Set(resultIndex))];
};

findSubstring("barfoothefoobarman", ["foo", "bar"]);
findSubstring("wordgoodgoodgoodbestword", ["word","good","best","word"]);
findSubstring("wordgoodgoodgoodbestword", ["word","good","best","good"]);
// console.log(['foo', 'bar'].filter( (item, index) => index !== 0));

