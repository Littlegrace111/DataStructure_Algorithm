const array = [1, 20, 10, 30, 22, 11, 55, 24, 31, 88, 12, 100, 50];

const swap = function(array, i, j) {
    let temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

const insertSort = function(array) {
    for(let i=1; i< array.length; i++) {
        for(let j=0; j<i; j++) {
            if(array[i] < array[j]) {
                // swap
                let temp = array[i]
                for(let n=i; n>j; n--) {
                    array[n] = array[n-1]
                } 
                array[j] = temp;
            }
        }
        console.log(array);
    }
}

const improvedInsertSort = function(array) {
    for(let i=1; i< array.length; i++) {
        let index = i;
        for(let j=i-1; j>=0; j--) {
            if(array[index] >= array[j]) {
                break;
            }
            if(array[index] < array[j]) {
                swap(array, index, j)
                index = j;
            }
        }
        console.log(array)
    }
}
// insertSort(array)
improvedInsertSort(array)

