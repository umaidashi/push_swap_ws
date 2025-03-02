#include "push_swap.h"

long	ft_atol(const char *str)
{
    long	result;
    int		sign;
    int		i;

    result = 0;
    sign = 1;
    i = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result * sign);
}

int get_stack_min(t_stack *stack)
{
    t_node *current;
    int min;

    if (!stack || !stack->head)
        return (0);
    current = stack->head;
    min = current->value;
    while (current)
    {
        if (current->value < min)
            min = current->value;
        current = current->next;
    }
    return (min);
}

int get_stack_max(t_stack *stack)
{
    t_node *current;
    int max;

    if (!stack || !stack->head)
        return (0);
    current = stack->head;
    max = current->value;
    while (current)
    {
        if (current->value > max)
            max = current->value;
        current = current->next;
    }
    return (max);
}

// スタックの中央値を取得
int get_median(t_stack *stack, int len)
{
    int *arr;
    int i;
    t_node *current;
    int median;

    if (!stack || !stack->head || len <= 0)
        return (0);
    arr = (int *)malloc(sizeof(int) * len);
    if (!arr)
        return (0);
    
    current = stack->head;
    i = 0;
    while (i < len && current)
    {
        arr[i] = current->value;
        current = current->next;
        i++;
    }

    // 挿入ソートで配列をソート
    for (i = 1; i < len; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

    median = arr[len / 2];
    free(arr);
    return (median);
}

// 3要素以下のスタックをソート
void sort_three(t_stack *stack)
{
    int first, second, third;

    if (!stack || stack->size <= 1)
        return;
    if (stack->size == 2)
    {
        if (stack->head->value > stack->head->next->value)
            sa(stack, 1);
        return;
    }
    first = stack->head->value;
    second = stack->head->next->value;
    third = stack->head->next->next->value;
    if (first > second && second < third && first < third)
        sa(stack, 1);
    else if (first > second && second > third)
    {
        sa(stack, 1);
        rra(stack, 1);
    }
    else if (first > second && second < third && first > third)
        ra(stack, 1);
    else if (first < second && second > third && first < third)
    {
        sa(stack, 1);
        ra(stack, 1);
    }
    else if (first < second && second > third && first > third)
        rra(stack, 1);
}

void sort_five_or_less(t_stack *stack_a, t_stack *stack_b)
{
    if (stack_a->size <= 3)
    {
        sort_three(stack_a);
        return;
    }
    
    // 最小値を見つけてスタックBに移動
    while (stack_a->size > 3)
    {
        int min = get_stack_min(stack_a);
        while (stack_a->head->value != min)
            ra(stack_a, 1);
        pb(stack_a, stack_b, 1);
    }
    
    // 残りの3要素をソート
    sort_three(stack_a);
    
    // スタックBの要素を戻す
    while (stack_b->size > 0)
        pa(stack_a, stack_b, 1);
}

// スタックの最小値と最大値を取得
void get_min_max(t_stack *stack, int len, int *min, int *max)
{
    t_node *current;
    int i;

    *min = INT_MAX;
    *max = INT_MIN;
    current = stack->head;
    i = 0;
    while (i < len && current)
    {
        if (current->value < *min)
            *min = current->value;
        if (current->value > *max)
            *max = current->value;
        current = current->next;
        i++;
    }
}

// スタックの要素が昇順にソートされているかチェック
int is_sorted_range(t_stack *stack, int len)
{
    t_node *current;
    int i;

    if (!stack || !stack->head || len <= 1)
        return (1);
    
    current = stack->head;
    i = 1;
    while (i < len && current && current->next)
    {
        if (current->value > current->next->value)
            return (0);
        current = current->next;
        i++;
    }
    return (1);
}

// スタックの要素が降順にソートされているかチェック
int is_reverse_sorted_range(t_stack *stack, int len)
{
    t_node *current;
    int i;

    if (!stack || !stack->head || len <= 1)
        return (1);
    
    current = stack->head;
    i = 1;
    while (i < len && current && current->next)
    {
        if (current->value < current->next->value)
            return (0);
        current = current->next;
        i++;
    }
    return (1);
}

// 改善されたピボット選択
int get_better_pivot(t_stack *stack, int len)
{
    t_node *current;
    int *arr;
    int i;
    int pivot = 0;  // 初期化を追加

    arr = (int *)malloc(sizeof(int) * len);
    if (!arr)
        return (0);

    current = stack->head;
    i = 0;
    while (i < len && current)
    {
        arr[i] = current->value;
        current = current->next;
        i++;
    }

    // クイックセレクトで中央値を選択
    int left = 0;
    int right = len - 1;
    int k = len / 2;
    
    while (left < right)
    {
        int store_idx = left;
        
        for (i = left; i < right; i++)
        {
            if (arr[i] < arr[right])
            {
                int temp = arr[store_idx];
                arr[store_idx] = arr[i];
                arr[i] = temp;
                store_idx++;
            }
        }
        
        int temp = arr[store_idx];
        arr[store_idx] = arr[right];
        arr[right] = temp;
        
        if (store_idx == k)
        {
            pivot = arr[store_idx];
            break;
        }
        else if (store_idx < k)
            left = store_idx + 1;
        else
            right = store_idx - 1;
    }

    if (left == right)
        pivot = arr[left];  // エッジケースの処理を追加

    free(arr);
    return (pivot);
}

// スタックBをソートしながらスタックAに戻す
void merge_stacks(t_stack *stack_a, t_stack *stack_b, int len_b)
{
    if (len_b <= 0)
        return;

    // スタックBが降順にソートされているか確認
    if (!is_reverse_sorted_range(stack_b, len_b))
    {
        // スタックBをソート
        int min, max;
        get_min_max(stack_b, len_b, &min, &max);
        int mid = (min + max) / 2;
        int pushed = 0;

        // 大きい要素をスタックAに移動
        for (int i = 0; i < len_b; i++)
        {
            if (stack_b->head->value > mid)
            {
                pa(stack_a, stack_b, 1);
                ra(stack_a, 1);
                pushed++;
            }
            else
                rb(stack_b, 1);
        }

        // 残りの要素を処理
        merge_stacks(stack_a, stack_b, len_b - pushed);

        // 移動した要素を元に戻す
        while (pushed--)
            rra(stack_a, 1);
    }
    else
    {
        // すでにソートされている場合は直接移動
        while (len_b--)
            pa(stack_a, stack_b, 1);
    }
}

void improved_quick_sort(t_stack *stack_a, t_stack *stack_b, int len)
{
    if (len <= 5)
    {
        sort_five_or_less(stack_a, stack_b);
        return;
    }

    if (is_sorted_range(stack_a, len))
        return;

    int pivot = get_better_pivot(stack_a, len);
    int pushed = 0;

    // ピボットより小さい要素をスタックBに移動
    for (int i = 0; i < len; i++)
    {
        if (stack_a->head->value < pivot)
        {
            pb(stack_a, stack_b, 1);
            pushed++;
        }
        else
            ra(stack_a, 1);
    }

    // スタックAの要素を元の位置に戻す
    for (int i = 0; i < (len - pushed); i++)
        rra(stack_a, 1);

    // スタックAの残りの要素をソート
    improved_quick_sort(stack_a, stack_b, len - pushed);

    // スタックBの要素をソートしながらマージ
    merge_stacks(stack_a, stack_b, pushed);
}

void sort_stack(t_stack *stack_a, t_stack *stack_b)
{
    if (!stack_a || !stack_a->head)
        return;
    if (is_sorted_range(stack_a, stack_a->size))
        return;
    improved_quick_sort(stack_a, stack_b, stack_a->size);
}

#ifndef TESTING
int main(int argc, char **argv)
{
    t_stack *stack_a;
    t_stack *stack_b;
    int i;
    long num;

    if (argc < 2)
        return (0);
    stack_a = init_stack();
    stack_b = init_stack();
    if (!stack_a || !stack_b)
        error_exit();

    i = 1;
    while (i < argc)
    {
        if (!is_valid_number(argv[i]))
            error_exit();
        num = ft_atol(argv[i]);
        if (num > INT_MAX || num < INT_MIN)
            error_exit();
        add_node(stack_a, (int)num);
        i++;
    }

    if (has_duplicates(stack_a))
        error_exit();

    sort_stack(stack_a, stack_b);

    free_stack(stack_a);
    free_stack(stack_b);
    return (0);
}
#endif
