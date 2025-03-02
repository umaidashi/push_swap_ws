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
    int i, j, median;
    t_node *current;

    if (!stack || stack->size < len || len <= 0)
        return (0);

    arr = (int *)malloc(sizeof(int) * len);
    if (!arr)
        return (0);

    current = stack->head;
    for (i = 0; i < len && current; i++)
    {
        arr[i] = current->value;
        current = current->next;
    }

    // 挿入ソートで配列をソート
    for (i = 1; i < len; i++)
    {
        int key = arr[i];
        j = i - 1;
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

// スタック内の最小値の位置を見つける
int find_min_pos(t_stack *stack)
{
    t_node *current;
    int min;
    int min_pos;
    int pos;

    if (!stack || !stack->head)
        return (0);
    current = stack->head;
    min = current->value;
    min_pos = 0;
    pos = 0;
    while (current)
    {
        if (current->value < min)
        {
            min = current->value;
            min_pos = pos;
        }
        pos++;
        current = current->next;
    }
    return (min_pos);
}

void sort_five_or_less(t_stack *stack_a, t_stack *stack_b)
{
    int size;
    int min_pos;

    size = stack_a->size;
    if (size <= 1 || is_sorted_range(stack_a, size))
        return;
    if (size == 2)
    {
        if (stack_a->head->value > stack_a->head->next->value)
            sa(stack_a, 1);
        return;
    }
    if (size == 3)
    {
        sort_three(stack_a);
        return;
    }

    // 4または5要素の場合は、最小値をスタックBに移動して、残りをソート
    while (size > 3)
    {
        // 最小値の位置を見つける
        min_pos = find_min_pos(stack_a);
        
        // 最小値をスタックの先頭に移動
        if (min_pos <= size / 2)
        {
            while (min_pos-- > 0)
                ra(stack_a, 1);
        }
        else
        {
            while (min_pos++ < size)
                rra(stack_a, 1);
        }
        
        // 最小値をスタックBに移動
        pb(stack_a, stack_b, 1);
        size--;
    }

    // 残りの3要素をソート
    sort_three(stack_a);

    // スタックBの要素を戻す
    while (stack_b->size > 0)
        pa(stack_a, stack_b, 1);
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
        int min;
        get_min_max(stack_b, len_b, &min, NULL);
        int mid = (min + get_stack_max(stack_b)) / 2;
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

void sort_stack(t_stack *stack_a, t_stack *stack_b)
{
    if (!stack_a || !stack_a->head)
        return;
    if (is_sorted_range(stack_a, stack_a->size))
        return;
    
    // サイズに応じて適切なアルゴリズムを選択
    if (stack_a->size <= 5)
        sort_five_or_less(stack_a, stack_b);
    else
        chunk_sort(stack_a, stack_b);
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
