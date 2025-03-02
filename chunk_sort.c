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
    int i;
    int size;
    int min_val, max_val, range;
    int current_pos;
    t_node *current;
    
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
    
    // 最小値から最大値まで順にスタックBに移動
    for (i = 0; i < chunk_count; i++)
    {
        // 現在のチャンクの範囲
        int chunk_min = min_val + i * chunk_size;
        int chunk_max = (i == chunk_count - 1) ? max_val : min_val + (i + 1) * chunk_size - 1;
        
        // チャンク内のすべての要素を処理するまで繰り返す
        while (1)
        {
            // チャンク内の要素を探す
            int target_pos = -1;
            current_pos = 0;
            current = stack_a->head;
            
            // スタックAの上半分を探索
            while (current && current_pos <= size / 2)
            {
                if (current->value >= chunk_min && current->value <= chunk_max)
                {
                    target_pos = current_pos;
                    break;
                }
                current = current->next;
                current_pos++;
            }
            
            // 上半分に見つからなければ下半分を探索
            if (target_pos == -1)
            {
                current = stack_a->head;
                current_pos = 0;
                
                while (current)
                {
                    if (current->value >= chunk_min && current->value <= chunk_max)
                    {
                        target_pos = current_pos;
                        break;
                    }
                    current = current->next;
                    current_pos++;
                }
            }
            
            // チャンク内の要素がもう見つからなければ次のチャンクへ
            if (target_pos == -1)
                break;
            
            // 最適な回転方向を選択して要素をスタックAの先頭に持ってくる
            if (target_pos <= stack_a->size / 2)
            {
                while (target_pos > 0)
                {
                    ra(stack_a, 1);
                    target_pos--;
                }
            }
            else
            {
                while (target_pos < stack_a->size)
                {
                    rra(stack_a, 1);
                    target_pos++;
                }
            }
            
            // スタックBに移動
            pb(stack_a, stack_b, 1);
            
            // スタックBでの位置を最適化（大きい値は上に、小さい値は下に）
            if (stack_b->size > 1)
            {
                // 中央値よりも大きい値は上に配置
                if (stack_b->head->value > chunk_min + (chunk_max - chunk_min) / 2)
                    rb(stack_b, 1);
            }
        }
    }
    
    // スタックBから最大値順にスタックAに戻す
    while (stack_b->size > 0)
    {
        // スタックBの最大値を見つける
        int max = get_stack_max(stack_b);
        int max_pos = get_target_position(stack_b, max);
        
        // 最適な回転方向を選択
        if (max_pos <= stack_b->size / 2)
        {
            while (max_pos > 0)
            {
                rb(stack_b, 1);
                max_pos--;
            }
        }
        else
        {
            while (max_pos < stack_b->size)
            {
                rrb(stack_b, 1);
                max_pos++;
            }
        }
        
        // スタックAに移動
        pa(stack_a, stack_b, 1);
    }
}

// 大規模サイズ（~500）のソート
void sort_large(t_stack *stack_a, t_stack *stack_b)
{
    int chunk_size;
    int chunk_count;
    int i;
    int size;
    int min_val, max_val, range;
    int current_pos;
    t_node *current;
    
    size = stack_a->size;
    
    // チャンク数を調整（最適な値を設定）
    if (size <= 100)
        chunk_count = 5;
    else if (size <= 300)
        chunk_count = 8;
    else if (size <= 400)
        chunk_count = 11;
    else
        chunk_count = 12;  // 500要素の場合はチャンク数を増やす
    
    // スタックの最小値と最大値を取得
    min_val = get_stack_min(stack_a);
    max_val = get_stack_max(stack_a);
    range = max_val - min_val + 1;
    
    chunk_size = range / chunk_count;
    if (chunk_size < 1)
        chunk_size = 1;
    
    // 最小値から最大値まで順にスタックBに移動
    for (i = 0; i < chunk_count; i++)
    {
        // 現在のチャンクの範囲
        int chunk_min = min_val + i * chunk_size;
        int chunk_max = (i == chunk_count - 1) ? max_val : min_val + (i + 1) * chunk_size - 1;
        
        // チャンク内のすべての要素を処理するまで繰り返す
        while (1)
        {
            // チャンク内の最も効率的に移動できる要素を探す
            int best_pos = -1;
            int best_cost = size;  // 初期コストを最大に設定
            
            current_pos = 0;
            current = stack_a->head;
            
            // スタック全体をスキャンして最も効率的に移動できる要素を見つける
            while (current)
            {
                if (current->value >= chunk_min && current->value <= chunk_max)
                {
                    // この要素を移動するコストを計算
                    int cost;
                    if (current_pos <= stack_a->size / 2)
                        cost = current_pos;  // 上からの回転コスト
                    else
                        cost = stack_a->size - current_pos;  // 下からの回転コスト
                    
                    // より良いコストが見つかれば更新
                    if (cost < best_cost)
                    {
                        best_cost = cost;
                        best_pos = current_pos;
                    }
                }
                current = current->next;
                current_pos++;
            }
            
            // チャンク内の要素がもう見つからなければ次のチャンクへ
            if (best_pos == -1)
                break;
            
            // 最適な回転方向を選択して要素をスタックAの先頭に持ってくる
            if (best_pos <= stack_a->size / 2)
            {
                while (best_pos > 0)
                {
                    ra(stack_a, 1);
                    best_pos--;
                }
            }
            else
            {
                while (best_pos < stack_a->size)
                {
                    rra(stack_a, 1);
                    best_pos++;
                }
            }
            
            // スタックBに移動
            pb(stack_a, stack_b, 1);
            
            // スタックBでの位置を最適化（大きい値は上に、小さい値は下に）
            if (stack_b->size > 1)
            {
                // 中央値よりも大きい値は上に配置
                if (stack_b->head->value > chunk_min + (chunk_max - chunk_min) / 2)
                    rb(stack_b, 1);
            }
        }
    }
    
    // スタックBから最大値順にスタックAに戻す
    while (stack_b->size > 0)
    {
        // スタックBの最大値を見つける
        int max = get_stack_max(stack_b);
        int max_pos = get_target_position(stack_b, max);
        
        // 最大値の次に大きい値とその位置を見つける
        int next_max = get_next_max(stack_b, max);
        int next_max_pos = -1;
        if (next_max != max)  // 次の最大値が存在する場合
            next_max_pos = get_target_position(stack_b, next_max);
        
        // 最適な回転方向を選択
        if (max_pos <= stack_b->size / 2)
        {
            while (max_pos > 0)
            {
                rb(stack_b, 1);
                max_pos--;
                
                // 次の最大値の位置も更新
                if (next_max_pos != -1)
                {
                    next_max_pos = (next_max_pos - 1 + stack_b->size) % stack_b->size;
                }
            }
        }
        else
        {
            while (max_pos < stack_b->size)
            {
                rrb(stack_b, 1);
                max_pos++;
                
                // 次の最大値の位置も更新
                if (next_max_pos != -1)
                {
                    next_max_pos = (next_max_pos + 1) % stack_b->size;
                }
            }
        }
        
        // スタックAに移動
        pa(stack_a, stack_b, 1);
        
        // 次の最大値が先頭に来るように最適化（先読み最適化）
        if (next_max_pos != -1 && stack_b->size > 1)
        {
            // 次の最大値を効率的に先頭に持ってくる準備
            if (next_max_pos == 1)
            {
                // 次の最大値が2番目にある場合は単純に回転
                rb(stack_b, 1);
            }
            else if (next_max_pos == stack_b->size - 1)
            {
                // 次の最大値が末尾にある場合は逆回転
                rrb(stack_b, 1);
            }
        }
    }
}

// スタックBを最適化する関数
void optimize_stack_b(t_stack *stack_b)
{
    // スタックBの最大値と最小値を取得
    int max = get_stack_max(stack_b);
    int min = get_stack_min(stack_b);
    
    // 先頭の値がスタックの最大値または最小値に近い場合、適切に回転
    if (stack_b->head->value == max)
    {
        // 最大値が先頭にある場合は何もしない
        return;
    }
    else if (stack_b->head->value == min)
    {
        // 最小値が先頭にある場合は回転して末尾に移動
        rb(stack_b, 1);
    }
    else
    {
        // 先頭の値が最大値と最小値の間にある場合
        int mid_value = (max + min) / 2;
        
        // 中央値よりも大きい値は上部に配置
        if (stack_b->head->value > mid_value)
        {
            // 上部に配置すべき値が先頭にある場合
            rb(stack_b, 1);
        }
    }
}

// スタック内で指定された値の次に大きい値を取得する関数
int get_next_max(t_stack *stack, int current_max)
{
    int next_max = INT_MIN;
    t_node *current = stack->head;
    
    // まず次の最大値の初期値を見つける
    while (current)
    {
        if (current->value < current_max && current->value > next_max)
            next_max = current->value;
        current = current->next;
    }
    
    // 次の最大値が見つからなかった場合は現在の最大値を返す
    if (next_max == INT_MIN)
        return current_max;
    
    return next_max;
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
