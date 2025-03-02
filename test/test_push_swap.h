#ifndef TEST_PUSH_SWAP_H
# define TEST_PUSH_SWAP_H

#include "../push_swap.h"
#include <stdio.h>

// テスト関数のプロトタイプ
void    test_stack_operations(void);
void    test_input_validation(void);
void    test_sort_small_stack(void);
void    test_error_handling(void);
void    test_edge_cases(void);
void    test_sort_medium_stack(void);  // 4-5要素のスタック用
void    test_sort_large_stack(void);   // 100要素以上のスタック用
void    test_sort_performance(void);   // ソートの性能テスト

// ユーティリティ関数
void    print_stack(t_stack *stack);
void    print_test_result(const char *test_name, int result);
int     compare_stack_with_array(t_stack *stack, int *array, int size);
int     count_operations(void);
void    reset_operation_count(void);

#endif
