const findM = (arr, m) => {
    arr.reduce((origin, item, index) => {
        console.log(item, index);
        if(origin.length === 0) {
            origin.push(index);
        } else if(origin.length === 1) {
            
        }
    }, [])
}

findM([2, 3, 4, 5, 1]);