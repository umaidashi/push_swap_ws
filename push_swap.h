#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_node
{
    int             value;
    struct s_node   *next;
    struct s_node   *prev;
} t_node;

typedef struct s_stack
{
    t_node  *head;
    int     size;
} t_stack;

// スタック操作
void    sa(t_stack *stack_a, int print);
void    sb(t_stack *stack_b, int print);
void    ss(t_stack *stack_a, t_stack *stack_b, int print);
void    pa(t_stack *stack_a, t_stack *stack_b, int print);
void    pb(t_stack *stack_a, t_stack *stack_b, int print);
void    ra(t_stack *stack_a, int print);
void    rb(t_stack *stack_b, int print);
void    rr(t_stack *stack_a, t_stack *stack_b, int print);
void    rra(t_stack *stack_a, int print);
void    rrb(t_stack *stack_b, int print);
void    rrr(t_stack *stack_a, t_stack *stack_b, int print);

// スタック管理
t_stack *init_stack(void);
void    free_stack(t_stack *stack);
void    add_node(t_stack *stack, int value);
int     is_sorted(t_stack *stack);

// ソート関数
void    sort_three(t_stack *stack);
void    sort_five_or_less(t_stack *stack_a, t_stack *stack_b);
void    sort_stack(t_stack *stack_a, t_stack *stack_b);
void    quick_sort_stacks(t_stack *stack_a, t_stack *stack_b, int len);
int     get_stack_min(t_stack *stack);
int     get_stack_max(t_stack *stack);
int     get_median(t_stack *stack, int len);
int     is_sorted_range(t_stack *stack, int len);
int     find_min_pos(t_stack *stack);

// インデックス変換
void    convert_to_indices(t_stack *stack);
int     *get_sorted_array(t_stack *stack);

// 改善されたソート関数
void    chunk_sort(t_stack *stack_a, t_stack *stack_b);
void    sort_medium(t_stack *stack_a, t_stack *stack_b);
void    sort_large(t_stack *stack_a, t_stack *stack_b);
void    smart_rotate_a(t_stack *stack_a, t_stack *stack_b, int target_pos);
void    smart_rotate_b(t_stack *stack_a, t_stack *stack_b, int target_pos);
int     get_target_position(t_stack *stack, int value);
int     get_cost(int pos, int size);
void    optimize_merge(t_stack *stack_a, t_stack *stack_b);
int     get_stack_min(t_stack *stack);
int     get_stack_max(t_stack *stack);
int     get_next_max(t_stack *stack, int current_max);
void    optimize_stack_b(t_stack *stack_b);

// エラーハンドリング
void    error_exit(void);
int     check_duplicate(t_stack *stack);
int     is_valid_number(char *str);
int     has_duplicates(t_stack *stack);

// ユーティリティ関数
long    ft_atol(const char *str);

#endif
