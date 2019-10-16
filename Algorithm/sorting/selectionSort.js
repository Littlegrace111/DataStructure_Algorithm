const swap = function(array, i, j) {
    let temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

// 选择排序是一个不算稳定的算法，每次交换后，它都改变了后续数组的顺序；
const array = [1, 20, 10, 30, 22, 11, 55, 24, 31, 88, 12, 100, 50];
const selectionSort = function(array) {
    for(let i=0; i<array.length-1; i++) {
        let minPos = i, isChange = false;
        for(let j=i+1; j<array.length-1; j++) {
            // console.log(array[j], array[minPos])
            if(array[j] < array[minPos]) {
                minPos = j;
                isChange = true;
            }
        }
        if(isChange) {
            swap(array, i, minPos);
        }
        console.log(array, minPos, isChange)
    }
}

selectionSort(array)