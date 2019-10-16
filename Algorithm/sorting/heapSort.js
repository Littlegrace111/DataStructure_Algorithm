class Heap {
    constructor(arr) {
        this.data = arr;
    }

    sort() {
        let iArr = this.data;
        let n = iArr.length;
        if(n <= 1) {
            return iArr;
        } else {
            for(let size = iArr.length - 1; size >= 1; size--) {
                // console.log(size);
                // 找到完全二叉树的最后一个父节点的位置：(size-1)/2
                for(let i = Math.floor((size-1)/2); i >= 0; i--) {
                    Heap.maxHeapify(iArr, i, size);
                }
                // console.log(iArr);
                // 一次最大堆构建完成，把第一个元素与最后一个元素交换
                Heap.swap(iArr, 0, size);
            }
            /**
             * 一次最大堆排序，把最大元素冒泡到顶层节点
             */
            // for(let i = Math.floor((n-2)/2); i >= 0; i--) {
            //     Heap.maxHeapify(iArr, i, n - 1);
            // }
            /**
             * 一次最大堆构建完成，把第一个元素与最后一个元素交换
             */
            // Heap.swap(iArr, 0, n-1);

            return iArr;
        }
    }

    toString() {
        return iArr;
    }

    static swap(Arr, p, q) {
        if(p === q) {
            return;
        }
        let temp = Arr[p];
        Arr[p] = Arr[q];
        Arr[q] = temp;
    }

    // 每一次构建最大堆的过程，都能把最大元素冒泡到顶层元素
    static maxHeapify(Arr, i, size) {
        let l = 2 * i + 1; // 左子节点索引
        let r = 2 * i + 2; // 右子节点索引
        let largest = i;
        if(l <= size && Arr[l] > Arr[largest]) {
            largest = l;
        } 
        if(r <= size && Arr[r] > Arr[largest]) {
            largest = r;
        }
        if(largest !== i) {
            Heap.swap(Arr, i, largest);
            Heap.maxHeapify(Arr, largest, size);
        }
    }
}

// export default Heap;

const heap = new Heap([1, 10, 9, 5, 3, 11]);
console.log(heap.sort());

