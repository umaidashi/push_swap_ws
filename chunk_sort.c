#include "push_swap.h"

// スタックの指定位置に最適な回転方法を選択
void smart_rotate_a(t_stack *stack_a, t_stack *stack_b, int target_pos)
{
    int size = stack_a->size;
    
    (void)stack_b; // 未使用パラメータの警告を抑制
    
    if (target_pos <= size / 2)
    {
        // 上から回転
        while (target_pos > 0)
        {
            ra(stack_a, 1);
            target_pos--;
        }
    }
    else
    {
        // 下から回転
        while (target_pos < size)
        {
            rra(stack_a, 1);
            target_pos++;
        }
    }
}

// スタックBの指定位置に最適な回転方法を選択
void smart_rotate_b(t_stack *stack_a, t_stack *stack_b, int target_pos)
{
    int size = stack_b->size;
    
    (void)stack_a; // 未使用パラメータの警告を抑制
    
    if (target_pos <= size / 2)
    {
        // 上から回転
        while (target_pos > 0)
        {
            rb(stack_b, 1);
            target_pos--;
        }
    }
    else
    {
        // 下から回転
        while (target_pos < size)
        {
            rrb(stack_b, 1);
            target_pos++;
        }
    }
}

// 指定した値の位置を取得
int get_target_position(t_stack *stack, int value)
{
    t_node *current;
    int pos;

    if (!stack || !stack->head)
        return (0);
    
    current = stack->head;
    pos = 0;
    while (current)
    {
        if (current->value == value)
            return (pos);
        pos++;
        current = current->next;
    }
    return (0);
}

// 回転コストを計算
int get_cost(int pos, int size)
{
    if (pos <= size / 2)
        return (pos);
    else
        return (size - pos);
}

// 中規模サイズ（~100）のソート
void sort_medium(t_stack *stack_a, t_stack *stack_b)
{
    int chunk_size;
    int chunk_count;
    int i, j;
    int size;
    int pushed;
    
    size = stack_a->size;
    // 適切なチャンク数を決定（サイズに応じて調整）
    chunk_count = 5;
    chunk_size = size / chunk_count;
    
    // チャンクごとにスタックBに移動
    for (i = 0; i < chunk_count; i++)
    {
        pushed = 0;
        j = 0;
        while (j < size && pushed < chunk_size)
        {
            if (stack_a->head->value < (i + 1) * chunk_size && 
                stack_a->head->value >= i * chunk_size)
            {
                pb(stack_a, stack_b, 1);
                pushed++;
            }
            else
            {
                ra(stack_a, 1);
            }
            j++;
        }
    }
    
    // 残りの要素をスタックBに移動
    while (stack_a->size > 0)
        pb(stack_a, stack_b, 1);
    
    // スタックBから最大値順にスタックAに戻す
    while (stack_b->size > 0)
    {
        // スタックBの最大値を見つける
        int max = get_stack_max(stack_b);
        int max_pos = get_target_position(stack_b, max);
        
        // 最適な回転方向を選択
        smart_rotate_b(stack_a, stack_b, max_pos);
        
        // スタックAに移動
        pa(stack_a, stack_b, 1);
    }
}

// 大規模サイズ（~500）のソート
void sort_large(t_stack *stack_a, t_stack *stack_b)
{
    int chunk_size;
    int chunk_count;
    int i, j;
    int size;
    int pushed;
    
    size = stack_a->size;
    // 適切なチャンク数を決定（サイズに応じて調整）
    chunk_count = 11;
    chunk_size = size / chunk_count;
    
    // チャンクごとにスタックBに移動
    for (i = 0; i < chunk_count; i++)
    {
        pushed = 0;
        j = 0;
        while (j < size && pushed < chunk_size)
        {
            if (stack_a->head->value < (i + 1) * chunk_size && 
                stack_a->head->value >= i * chunk_size)
            {
                pb(stack_a, stack_b, 1);
                
                // 小さい値は下に、大きい値は上に配置
                if (stack_b->head->value < i * chunk_size + chunk_size / 2)
                    rb(stack_b, 1);
                
                pushed++;
            }
            else
            {
                ra(stack_a, 1);
            }
            j++;
        }
    }
    
    // 残りの要素をスタックBに移動
    while (stack_a->size > 0)
        pb(stack_a, stack_b, 1);
    
    // スタックBから最大値順にスタックAに戻す
    while (stack_b->size > 0)
    {
        // スタックBの最大値を見つける
        int max = get_stack_max(stack_b);
        int max_pos = get_target_position(stack_b, max);
        
        // 最適な回転方向を選択
        smart_rotate_b(stack_a, stack_b, max_pos);
        
        // スタックAに移動
        pa(stack_a, stack_b, 1);
    }
}

// サイズに応じて適切なソートアルゴリズムを選択
void chunk_sort(t_stack *stack_a, t_stack *stack_b)
{
    int size = stack_a->size;
    
    // ソート済みかどうかを再確認
    if (is_sorted_range(stack_a, size))
        return;
    
    // インデックスに変換
    convert_to_indices(stack_a);
    
    if (size <= 5)
        sort_five_or_less(stack_a, stack_b);
    else if (size <= 100)
        sort_medium(stack_a, stack_b);
    else
        sort_large(stack_a, stack_b);
}
