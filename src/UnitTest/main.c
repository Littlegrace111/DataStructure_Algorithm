#include <stdio.h>
#include <stdlib.h>

#include "SList.h"
#include "DList.h"

//function declaration
int alloc_frame(SList *pFrames);

int main()
{
    printf("Hello world!\n");
    return 0;
}

int alloc_frame(SList *pFrames)
{
    int iFrame_num = 0, *piData;

    if(list_size(pFrames) == 0)
    {
        return -1;
    }else{
        if(list_rem_next(pFrames, NULL, (void **)&piData) != 0)
            return -1;
        else{
            iFrame_num = *piData;
            free(*piData);
        }
    }
    return iFrame_num;
}


int free_frame(SList *pFrames, int iFrame_number)
{
    int *piData;

    if(piData == (int *)malloc(sizeof(int)) == NULL)
        return -1;

    *piData = iFrame_number;

    if(list_ins_next(pFrames, NULL, piData) != 0)
        return -1;

    return 0;
}
