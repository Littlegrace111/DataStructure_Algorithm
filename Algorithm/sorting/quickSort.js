/**
 * 1. 选择一个基准元素；
 * 2. 按照一定的策略做元素交换，把小于基准元素的元素放左边，大于的放右边；
 * 3. 按照前两个步骤依次拆解下去，直到子数组的长度<=1；
 */

// const arr = [30, 32, 6, 24, 37, 32, 45, 21, 38, 23, 47];
const arr = [3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48];

const quickSort = (arr) => {
    if(arr.length <= 1) {
        return arr;
    }
    let privot = arr[0];
    let left = [], right = [];
    for(let i=1; i<arr.length; i++) {
        if(arr[i] < privot) {
            left.push(arr[i])
        } else {
            right.push(arr[i])
        }
    }
    console.log(left, right)
    return quickSort(left).concat(privot, quickSort(right));
}

const quick2Sort = (arr, left=0, right=arr.length-1) => {
    if(left >= right)
        return;
    
    const baseLine = arr[left]; // 需要找一个基准
    let lPos = left, rPos = right;
    while(lPos < rPos) {
        while((lPos<rPos) && arr[rPos] >= baseLine) {
            rPos--;
        }
        if(lPos < rPos) {
            arr[lPos] = arr[rPos];
        }

        while((lPos<rPos) && arr[lPos] <= baseLine) {
            lPos++;
        }
        if(lPos < rPos) {
            arr[rPos] = arr[lPos];
        }
    }
    // console.log(lPos);
    arr[lPos] = baseLine;
    quick2Sort(arr, left, lPos-1);
    quick2Sort(arr, lPos+1, right);
}

console.log(arr);
quick2Sort(arr, 0, arr.length-1);
console.log(arr);
// quick2Sort(arr, 0, 4)
// console.log(arr);