#include <stdio.h>
#include "AdptArray.h"
#include <stdlib.h>

typedef struct AdptArray_
{
    PElement* list;
    COPY_FUNC copy;
    DEL_FUNC del;
    PRINT_FUNC pri;
    int size;
}AdptArray_;

PAdptArray CreateAdptArray(COPY_FUNC copy_function, DEL_FUNC del_function ,PRINT_FUNC print_function) 
{

    PAdptArray arr = (PAdptArray)malloc(sizeof(AdptArray_));
    arr->list = NULL;
    arr->copy = copy_function;
    arr->del = del_function;
    arr->pri = print_function;
    arr->size= 0;
    return arr;
}

void DeleteAdptArray(PAdptArray arr) 
{
    if (!arr)
    {
        return;
    }

    for (int i = 0; i < arr->size; i++)
    {
        if (arr->list[i]) 
        {
            arr->del(arr->list[i]);
        }
    }
    free(arr->list);
    free(arr);
}

Result SetAdptArrayAt(PAdptArray arr, int index, PElement new_element) {
    if (!arr ||  index < 0 || !new_element)
    {
        return FAIL;
    }

    if (arr->size >= index) 
    {
        if (arr->list[index])
        {
            free(arr->list[index]);
        }
        arr->list[index] = arr->copy(new_element);
    }
    else 
    {
        PElement* new_arr = (PElement)calloc(index + 1, sizeof(PElement));
        for (int i = 0; i < arr->size; i++)
        {
            if (arr->list[i])
            {
                new_arr[i] = arr->list[i];
            }
            else 
            {
                new_arr[i] = NULL;
            }
        }
        free(arr->list); 
        arr->list = new_arr;
        arr->list[index] = arr->copy(new_element);
        arr->size = index + 1; 
    }
        return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray arr, int i) 
{
    if (!arr || arr->size < i || i < 0 || arr->list[i] == NULL)
    {
        return NULL; 
    }

    return arr->copy(arr->list[i]);
    
}

int GetAdptArraySize(PAdptArray arr) 
{
    if (!arr)
    {
        return -1;
    }

    return arr->size;   
}

void PrintDB(PAdptArray arr) 
{
    if (!arr)
    {
        return;
    }

    for (int i = 0; i < arr->size; i++)
    {
        if (arr->list[i])
        {
            arr->pri(arr->list[i]);
        }
    }
}