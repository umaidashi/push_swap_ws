#include "push_swap.h"

// 配列をソートする補助関数（挿入ソート）
static void insertion_sort(int *arr, int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// スタックの値をソートした配列として取得
int *get_sorted_array(t_stack *stack)
{
    int *arr;
    t_node *current;
    int i;

    if (!stack || !stack->head)
        return (NULL);
    
    arr = (int *)malloc(sizeof(int) * stack->size);
    if (!arr)
        return (NULL);
    
    current = stack->head;
    i = 0;
    while (current)
    {
        arr[i++] = current->value;
        current = current->next;
    }
    
    insertion_sort(arr, stack->size);
    return (arr);
}

// 値をインデックスに変換
void convert_to_indices(t_stack *stack)
{
    int *sorted;
    t_node *current;
    int i;

    if (!stack || !stack->head)
        return;
    
    sorted = get_sorted_array(stack);
    if (!sorted)
        return;
    
    current = stack->head;
    while (current)
    {
        // 元の値を対応するインデックスに置き換え
        for (i = 0; i < stack->size; i++)
        {
            if (current->value == sorted[i])
            {
                current->value = i;
                break;
            }
        }
        current = current->next;
    }
    
    free(sorted);
}
