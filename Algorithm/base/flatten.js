const uniqueArr = (arr) => {
    return arr.reduce((origin, item) => {
        if(origin.indexOf(item) === -1) {
            origin.push(item);
        }
        return origin;
    }, []);
}
console.log(uniqueArr([2,1,3,3,4,5]));

const flattenArr = (arr) => {
    const reducer = (origin, item) => {
        if(Array.isArray(item)) {
            // origin = origin.concat(flattenArr(item)); // concat 返回一个新数组
            origin = [...origin, ...flattenArr(item)];
        } else {
            origin.push(item);
        }
        return origin;
    }
    return arr.reduce(reducer, []);
}

const arr1 = [1, 2, 3, [4, 5], 6, [7, 8, [9, 10 , [11, 12, 13], 14]], 15];
console.log(flattenArr(arr1));

