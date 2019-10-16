const array = [1, 20, 10, 30, 22, 11, 55, 24, 31, 88, 12, 100, 50];
const bubbleSort = function(array) { 
    // 升序
    for(let i=0; i<array.length-1; i++) {
        for(let j=0; j<array.length-1-i; j++) {
            if(array[j] > array[j+1]) {
                // swap
                const temp = array[j+1]
                array[j+1] = array[j]
                array[j] = temp;
            } 
        }
        console.log(array)
    }
}

// 冒泡优化：如果某一次子循环没有进行交换，则说明已经排好序了
// 加一个标志位，如果没有进行交换，将标志位置为false, 表示排序完成；
const improveBubbleSort = function(array) {
    // 升序
    for(let i=0; i<array.length-1; i++) {
        let isSwap = false;
        for(let j=0; j<array.length-1-i; j++) {
            if(array[j] > array[j+1]) {
                // swap
                const temp = array[j+1]
                array[j+1] = array[j]
                array[j] = temp;
                isSwap = true;
            } 
        }
        if(!isSwap) {
            break;
        }
        console.log(array, i)
    }
}


//  排序优化2： 记录子循环最后一次交换的位置，下一次遍历的数据长度就是这次交换的位置
// 与上一个优化结合：记录最后一次交换的位置pos，下一次遍历数组的长度就是pos+1; 能优化程度很大
const improveBubbleSortV2 = function(array) {
    let pos = array.length;
    for(let i=pos; i>0; i--) { // 表示数组遍历的长度
        let isSwap = false
        for(let j=0; j<i-1; j++) {
            if(array[j] > array[j+1]) {
                // swap
                const temp = array[j+1]
                array[j+1] = array[j]
                array[j] = temp;
                pos = j + 1;
                isSwap = true
            }
        } 
        console.log(array, pos)
        if(!isSwap)
            break
    }
}

// bubbleSort(array)
improveBubbleSort(array)
// improveBubbleSortV2(array)