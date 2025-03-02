#include "push_swap.h"
#include <stdlib.h>
#include <limits.h>

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
    int min_val, max_val, range;
    
    size = stack_a->size;
    
    // 適切なチャンク数を決定（サイズに応じて調整）
    if (size <= 20)
        chunk_count = 2;
    else if (size <= 50)
        chunk_count = 3;
    else
        chunk_count = 4;
    
    // スタックの最小値と最大値を取得
    min_val = get_stack_min(stack_a);
    max_val = get_stack_max(stack_a);
    range = max_val - min_val + 1;
    
    chunk_size = range / chunk_count;
    if (chunk_size < 1)
        chunk_size = 1;
    
    // チャンクごとにスタックBに移動（最小値から順に処理）
    for (i = 0; i < chunk_count; i++)
    {
        pushed = 0;
        j = 0;
        while (j < size * 2 && pushed < size / chunk_count + 1)
        {
            if (stack_a->head->value >= min_val + i * chunk_size && 
                stack_a->head->value < min_val + (i + 1) * chunk_size)
            {
                pb(stack_a, stack_b, 1);
                
                // 小さい値は下に、大きい値は上に配置
                if (stack_b->head->value < min_val + i * chunk_size + chunk_size / 2)
                    rb(stack_b, 1);
                
                pushed++;
            }
            else
            {
                ra(stack_a, 1);
            }
            j++;
            
            // 十分な数の要素が移動されたら次のチャンクへ
            if (pushed >= size / chunk_count + 1)
                break;
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
    int min_val, max_val, range;
    
    size = stack_a->size;
    
    // チャンク数を調整（最適な値を設定）
    if (size <= 100)
        chunk_count = 5;
    else if (size <= 300)
        chunk_count = 8;
    else
        chunk_count = 11;
    
    // スタックの最小値と最大値を取得
    min_val = get_stack_min(stack_a);
    max_val = get_stack_max(stack_a);
    range = max_val - min_val + 1;
    
    chunk_size = range / chunk_count;
    if (chunk_size < 1)
        chunk_size = 1;
    
    // チャンクごとにスタックBに移動（最適化）
    for (i = 0; i < chunk_count; i++)
    {
        pushed = 0;
        j = 0;
        // 各チャンクで効率的に要素を探す
        while (j < size * 3 && pushed < (size / chunk_count) + 2)
        {
            if (stack_a->head->value >= min_val + i * chunk_size && 
                stack_a->head->value < min_val + (i + 1) * chunk_size)
            {
                pb(stack_a, stack_b, 1);
                
                // スタックBでの位置を最適化
                if (stack_b->head->value < min_val + i * chunk_size + chunk_size / 2)
                    rb(stack_b, 1);
                
                pushed++;
            }
            else
            {
                // 効率的な回転方向を選択
                int target_pos = -1;
                t_node *current = stack_a->head;
                int pos = 0;
                
                // 現在のチャンク内の要素を探す
                while (current && pos < size / 2)
                {
                    if (current->value >= min_val + i * chunk_size && 
                        current->value < min_val + (i + 1) * chunk_size)
                    {
                        target_pos = pos;
                        break;
                    }
                    current = current->next;
                    pos++;
                }
                
                // 下半分も探す
                if (target_pos == -1)
                {
                    current = stack_a->head;
                    pos = 0;
                    while (current)
                    {
                        if (current->value >= min_val + i * chunk_size && 
                            current->value < min_val + (i + 1) * chunk_size)
                        {
                            target_pos = pos;
                            break;
                        }
                        current = current->next;
                        pos++;
                    }
                }
                
                // 最適な回転方向を選択
                if (target_pos != -1 && target_pos <= size / 2)
                    ra(stack_a, 1);
                else if (target_pos != -1)
                    rra(stack_a, 1);
                else
                    ra(stack_a, 1);
            }
            j++;
            
            // 十分な数の要素が移動されたら次のチャンクへ
            if (pushed >= (size / chunk_count) + 2)
                break;
        }
    }
    
    // 残りの要素をスタックBに移動
    while (stack_a->size > 0)
        pb(stack_a, stack_b, 1);
    
    // 最適化されたマージ戦略を使用
    optimize_merge(stack_a, stack_b);
}

// スタックBからスタックAに要素を最適に戻す
void optimize_merge(t_stack *stack_a, t_stack *stack_b)
{
    int max;
    int max_pos;
    int size_b;
    int next_max;
    int next_max_pos;
    int cost1, cost2, combined_cost;
    
    while (stack_b->size > 0)
    {
        size_b = stack_b->size;
        if (size_b <= 1)
        {
            pa(stack_a, stack_b, 1);
            continue;
        }
        
        // 現在の最大値と次の最大値を見つける
        max = get_stack_max(stack_b);
        max_pos = get_target_position(stack_b, max);
        
        // 次の最大値を見つける
        t_node *current = stack_b->head;
        next_max = INT_MIN;
        next_max_pos = 0;
        int pos = 0;
        
        while (current)
        {
            if (current->value < max && current->value > next_max)
            {
                next_max = current->value;
                next_max_pos = pos;
            }
            pos++;
            current = current->next;
        }
        
        // 各操作のコストを計算
        cost1 = get_cost(max_pos, size_b);
        cost2 = get_cost(next_max_pos, size_b);
        
        // 最大値と次の最大値を連続して処理するコスト
        if (max_pos <= size_b / 2 && next_max_pos <= size_b / 2)
            combined_cost = (max_pos > next_max_pos) ? max_pos : next_max_pos;
        else if (max_pos > size_b / 2 && next_max_pos > size_b / 2)
            combined_cost = (size_b - max_pos < size_b - next_max_pos) ? 
                            (size_b - max_pos) : (size_b - next_max_pos);
        else
            combined_cost = cost1 + cost2;
        
        // 最適な戦略を選択
        if (combined_cost < cost1 + cost2 - 1 && abs(max_pos - next_max_pos) <= 5)
        {
            // 両方を一緒に処理する方が効率的な場合
            if (max_pos <= size_b / 2 && next_max_pos <= size_b / 2)
            {
                // 両方が上半分にある場合
                if (max_pos < next_max_pos)
                {
                    // 最大値が先に来る場合
                    smart_rotate_b(stack_a, stack_b, max_pos);
                    pa(stack_a, stack_b, 1);
                    smart_rotate_b(stack_a, stack_b, get_target_position(stack_b, next_max));
                    pa(stack_a, stack_b, 1);
                }
                else
                {
                    // 次の最大値が先に来る場合
                    smart_rotate_b(stack_a, stack_b, next_max_pos);
                    pa(stack_a, stack_b, 1);
                    ra(stack_a, 1);
                    smart_rotate_b(stack_a, stack_b, get_target_position(stack_b, max));
                    pa(stack_a, stack_b, 1);
                    rra(stack_a, 1);
                }
            }
            else if (max_pos > size_b / 2 && next_max_pos > size_b / 2)
            {
                // 両方が下半分にある場合
                if (max_pos > next_max_pos)
                {
                    // 最大値が後に来る場合
                    smart_rotate_b(stack_a, stack_b, next_max_pos);
                    pa(stack_a, stack_b, 1);
                    ra(stack_a, 1);
                    smart_rotate_b(stack_a, stack_b, get_target_position(stack_b, max));
                    pa(stack_a, stack_b, 1);
                    rra(stack_a, 1);
                }
                else
                {
                    // 次の最大値が後に来る場合
                    smart_rotate_b(stack_a, stack_b, max_pos);
                    pa(stack_a, stack_b, 1);
                    smart_rotate_b(stack_a, stack_b, get_target_position(stack_b, next_max));
                    pa(stack_a, stack_b, 1);
                }
            }
            else
            {
                // 通常の処理
                smart_rotate_b(stack_a, stack_b, max_pos);
                pa(stack_a, stack_b, 1);
            }
        }
        else
        {
            // 通常の処理（最大値のみ処理）
            smart_rotate_b(stack_a, stack_b, max_pos);
            pa(stack_a, stack_b, 1);
        }
    }
}

// サイズに応じて適切なソートアルゴリズムを選択
void chunk_sort(t_stack *stack_a, t_stack *stack_b)
{
    int size = stack_a->size;
    
    // ソート済みかどうかを再確認
    if (is_sorted_range(stack_a, size))
        return;
    
    // 5以下のサイズは専用の関数で処理
    if (size <= 5)
    {
        sort_five_or_less(stack_a, stack_b);
        return;
    }
    
    // インデックスに変換
    convert_to_indices(stack_a);
    
    if (size <= 100)
        sort_medium(stack_a, stack_b);
    else
        sort_large(stack_a, stack_b);
}
