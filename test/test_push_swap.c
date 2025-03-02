#include "test_push_swap.h"
#include <stdlib.h>
#include <time.h>

// グローバル変数で操作回数を追跡
static int g_operation_count = 0;

void print_stack(t_stack *stack)
{
    t_node *current = stack->head;
    printf("Stack (size: %d): ", stack->size);
    while (current)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void print_test_result(const char *test_name, int result)
{
    printf("\nTest %s: %s\n", test_name, result ? "\033[32mOK\033[0m" : "\033[31mFAIL\033[0m");
}

int compare_stack_with_array(t_stack *stack, int *array, int size)
{
    t_node *current = stack->head;
    int i = 0;

    if (stack->size != size)
        return (0);
    while (current && i < size)
    {
        if (current->value != array[i])
            return (0);
        current = current->next;
        i++;
    }
    return (1);
}

int count_operations(void)
{
    return g_operation_count;
}

void reset_operation_count(void)
{
    g_operation_count = 0;
}

void test_stack_operations(void)
{
    t_stack *stack_a = init_stack();
    t_stack *stack_b = init_stack();
    int result = 1;

    printf("\n=== Testing Stack Operations ===\n");

    // スタックの初期化テスト
    printf("Testing stack initialization...\n");
    if (!stack_a || !stack_b)
    {
        printf("Failed to initialize stacks\n");
        return;
    }

    // ノード追加テスト
    printf("\nTesting node addition...\n");
    printf("Before: ");
    print_stack(stack_a);
    add_node(stack_a, 1);
    add_node(stack_a, 2);
    add_node(stack_a, 3);
    printf("After:  ");
    print_stack(stack_a);
    result &= (stack_a->size == 3);

    // スワップテスト
    printf("\nTesting swap operation...\n");
    printf("Before: ");
    print_stack(stack_a);
    sa(stack_a, 0);
    printf("After:  ");
    print_stack(stack_a);
    result &= (stack_a->head->value == 2);
    result &= (stack_a->head->next->value == 1);

    // プッシュテスト
    printf("\nTesting push operation...\n");
    printf("Stack A before: ");
    print_stack(stack_a);
    printf("Stack B before: ");
    print_stack(stack_b);
    pb(stack_a, stack_b);
    printf("Stack A after:  ");
    print_stack(stack_a);
    printf("Stack B after:  ");
    print_stack(stack_b);
    result &= (stack_a->size == 2);
    result &= (stack_b->size == 1);
    result &= (stack_b->head->value == 2);

    // 回転テスト
    printf("\nTesting rotation...\n");
    add_node(stack_a, 4);
    printf("Before ra: ");
    print_stack(stack_a);
    ra(stack_a, 0);
    printf("After ra:  ");
    print_stack(stack_a);

    // 逆回転テスト
    printf("\nTesting reverse rotation...\n");
    printf("Before rra: ");
    print_stack(stack_a);
    rra(stack_a, 0);
    printf("After rra:  ");
    print_stack(stack_a);

    print_test_result("Stack Operations", result);

    free_stack(stack_a);
    free_stack(stack_b);
}

void test_input_validation(void)
{
    int result = 1;
    printf("\n=== Testing Input Validation ===\n");

    // 数値チェック
    printf("Testing number validation:\n");
    printf("\"123\":   %s\n", is_valid_number("123") ? "Valid" : "Invalid");
    printf("\"-123\":  %s\n", is_valid_number("-123") ? "Valid" : "Invalid");
    printf("\"+123\":  %s\n", is_valid_number("+123") ? "Valid" : "Invalid");
    printf("\"12a3\":  %s\n", is_valid_number("12a3") ? "Valid" : "Invalid");
    printf("\"abc\":   %s\n", is_valid_number("abc") ? "Valid" : "Invalid");
    printf("\"\":      %s\n", is_valid_number("") ? "Valid" : "Invalid");

    result &= is_valid_number("123");
    result &= is_valid_number("-123");
    result &= is_valid_number("+123");
    result &= !is_valid_number("12a3");
    result &= !is_valid_number("abc");
    result &= !is_valid_number("");

    // 重複チェック
    printf("\nTesting duplicate check:\n");
    t_stack *stack = init_stack();
    add_node(stack, 1);
    add_node(stack, 2);
    add_node(stack, 1);
    print_stack(stack);
    printf("Has duplicates: %s\n", check_duplicate(stack) ? "Yes" : "No");
    result &= check_duplicate(stack);

    print_test_result("Input Validation", result);
    free_stack(stack);
}

void test_sort_small_stack(void)
{
    t_stack *stack_a;
    t_stack *stack_b;
    int result = 1;

    printf("\n=== Testing Small Stack Sorting ===\n");

    // 2つの要素のソート
    printf("\nTesting sort with 2 elements:\n");
    stack_a = init_stack();
    stack_b = init_stack();
    add_node(stack_a, 2);
    add_node(stack_a, 1);
    printf("Before: ");
    print_stack(stack_a);
    if (!is_sorted(stack_a))
        sa(stack_a, 0);
    printf("After:  ");
    print_stack(stack_a);
    result &= is_sorted(stack_a);
    free_stack(stack_a);
    free_stack(stack_b);

    // 3つの要素のソート - ケース1: [3,1,2]
    printf("\nTesting sort with 3 elements (case 1):\n");
    stack_a = init_stack();
    stack_b = init_stack();
    add_node(stack_a, 3);
    add_node(stack_a, 1);
    add_node(stack_a, 2);
    printf("Before: ");
    print_stack(stack_a);
    if (!is_sorted(stack_a))
        sort_three(stack_a);
    printf("After:  ");
    print_stack(stack_a);
    result &= is_sorted(stack_a);
    free_stack(stack_a);
    free_stack(stack_b);

    // 3つの要素のソート - ケース2: [2,3,1]
    printf("\nTesting sort with 3 elements (case 2):\n");
    stack_a = init_stack();
    stack_b = init_stack();
    add_node(stack_a, 2);
    add_node(stack_a, 3);
    add_node(stack_a, 1);
    printf("Before: ");
    print_stack(stack_a);
    if (!is_sorted(stack_a))
        sort_three(stack_a);
    printf("After:  ");
    print_stack(stack_a);
    result &= is_sorted(stack_a);
    free_stack(stack_a);
    free_stack(stack_b);

    // 3つの要素のソート - ケース3: [3,2,1]
    printf("\nTesting sort with 3 elements (case 3):\n");
    stack_a = init_stack();
    stack_b = init_stack();
    add_node(stack_a, 3);
    add_node(stack_a, 2);
    add_node(stack_a, 1);
    printf("Before: ");
    print_stack(stack_a);
    if (!is_sorted(stack_a))
        sort_three(stack_a);
    printf("After:  ");
    print_stack(stack_a);
    result &= is_sorted(stack_a);

    print_test_result("Sort Small Stack", result);
    free_stack(stack_a);
    free_stack(stack_b);
}

void test_error_handling(void)
{
    t_stack *stack = init_stack();
    int result = 1;

    printf("\n=== Testing Error Handling ===\n");

    // 空のスタックのテスト
    printf("\nTesting operations on empty stack:\n");
    printf("Empty stack: ");
    print_stack(stack);
    printf("Is sorted: %s\n", is_sorted(stack) ? "Yes" : "No");
    result &= is_sorted(stack);

    // 無効な操作のテスト
    printf("\nTesting invalid operations:\n");
    printf("Before sa on empty stack: ");
    print_stack(stack);
    sa(stack, 0);
    printf("After sa on empty stack:  ");
    print_stack(stack);
    result &= (stack->size == 0);

    // メモリ確保エラーのシミュレーション
    printf("\nTesting memory allocation:\n");
    t_stack *new_stack = init_stack();
    if (new_stack)
    {
        printf("Stack allocation: Success\n");
        free_stack(new_stack);
    }
    else
    {
        printf("Stack allocation: Failed\n");
        result = 0;
    }

    print_test_result("Error Handling", result);
    free_stack(stack);
}

void test_edge_cases(void)
{
    t_stack *stack_a = init_stack();
    t_stack *stack_b = init_stack();
    int result = 1;

    printf("\n=== Testing Edge Cases ===\n");

    // 同じ値が連続するケース
    printf("\nTesting consecutive identical values:\n");
    add_node(stack_a, 1);
    add_node(stack_a, 1);
    printf("Before: ");
    print_stack(stack_a);
    result &= check_duplicate(stack_a);
    printf("Duplicate check result: %s\n", check_duplicate(stack_a) ? "Detected" : "Not detected");

    // 最大値と最小値のケース
    printf("\nTesting max and min values:\n");
    free_stack(stack_a);
    stack_a = init_stack();
    add_node(stack_a, 2147483647);
    add_node(stack_a, -2147483648);
    printf("Stack with max/min values: ");
    print_stack(stack_a);
    if (!is_sorted(stack_a))
        sort_stack(stack_a, stack_b);
    printf("After sorting: ");
    print_stack(stack_a);
    result &= is_sorted(stack_a);

    print_test_result("Edge Cases", result);
    free_stack(stack_a);
    free_stack(stack_b);
}

void test_sort_medium_stack(void)
{
    t_stack *stack_a = init_stack();
    t_stack *stack_b = init_stack();
    int result = 1;

    printf("\n=== Testing Medium Stack Sorting (4-5 elements) ===\n");

    // テストケース1: 4要素 [4,2,1,3]
    printf("\nTesting sort with 4 elements:\n");
    add_node(stack_a, 4);
    add_node(stack_a, 2);
    add_node(stack_a, 1);
    add_node(stack_a, 3);
    printf("Before: ");
    print_stack(stack_a);
    reset_operation_count();
    if (!is_sorted(stack_a))
        sort_stack(stack_a, stack_b);
    printf("After:  ");
    print_stack(stack_a);
    printf("Operations used: %d\n", count_operations());
    result &= is_sorted(stack_a);
    free_stack(stack_a);
    free_stack(stack_b);

    // テストケース2: 5要素 [5,1,4,2,3]
    stack_a = init_stack();
    stack_b = init_stack();
    printf("\nTesting sort with 5 elements:\n");
    add_node(stack_a, 5);
    add_node(stack_a, 1);
    add_node(stack_a, 4);
    add_node(stack_a, 2);
    add_node(stack_a, 3);
    printf("Before: ");
    print_stack(stack_a);
    reset_operation_count();
    if (!is_sorted(stack_a))
        sort_stack(stack_a, stack_b);
    printf("After:  ");
    print_stack(stack_a);
    printf("Operations used: %d\n", count_operations());
    result &= is_sorted(stack_a);

    print_test_result("Sort Medium Stack", result);
    free_stack(stack_a);
    free_stack(stack_b);
}

void test_sort_large_stack(void)
{
    t_stack *stack_a = init_stack();
    t_stack *stack_b = init_stack();
    int result = 1;
    int size = 100;
    int *numbers = malloc(sizeof(int) * size);

    printf("\n=== Testing Large Stack Sorting (%d elements) ===\n", size);

    // 重複のない乱数を生成
    srand(time(NULL));
    for (int i = 0; i < size; i++)
        numbers[i] = i + 1;
    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    // スタックに追加
    printf("\nGenerating random stack with %d elements...\n", size);
    for (int i = 0; i < size; i++)
        add_node(stack_a, numbers[i]);

    printf("First 10 elements before sorting: ");
    t_node *current = stack_a->head;
    for (int i = 0; i < 10 && current; i++)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("...\n");

    reset_operation_count();
    if (!is_sorted(stack_a))
        sort_stack(stack_a, stack_b);

    printf("First 10 elements after sorting: ");
    current = stack_a->head;
    for (int i = 0; i < 10 && current; i++)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("...\n");

    printf("Operations used: %d\n", count_operations());
    result &= is_sorted(stack_a);

    print_test_result("Sort Large Stack", result);
    free(numbers);
    free_stack(stack_a);
    free_stack(stack_b);
}

void test_sort_performance(void)
{
    const int test_sizes[] = {10, 50, 100, 500};
    const int num_tests = sizeof(test_sizes) / sizeof(test_sizes[0]);

    printf("\n=== Testing Sort Performance ===\n");

    for (int i = 0; i < num_tests; i++)
    {
        t_stack *stack_a = init_stack();
        t_stack *stack_b = init_stack();
        int size = test_sizes[i];
        int *numbers = malloc(sizeof(int) * size);

        // 重複のない乱数を生成
        for (int j = 0; j < size; j++)
            numbers[j] = j + 1;
        for (int j = size - 1; j > 0; j--)
        {
            int k = rand() % (j + 1);
            int temp = numbers[j];
            numbers[j] = numbers[k];
            numbers[k] = temp;
        }

        // スタックに追加
        for (int j = 0; j < size; j++)
            add_node(stack_a, numbers[j]);

        printf("\nTesting with %d elements:\n", size);
        reset_operation_count();
        if (!is_sorted(stack_a))
            sort_stack(stack_a, stack_b);
        printf("Operations used: %d\n", count_operations());
        printf("Average operations per element: %.2f\n", 
               (float)count_operations() / size);

        free(numbers);
        free_stack(stack_a);
        free_stack(stack_b);
    }
}

int main(void)
{
    printf("\n=== Running Push_swap Tests ===\n");

    test_stack_operations();
    test_input_validation();
    test_sort_small_stack();
    test_error_handling();
    test_edge_cases();
    test_sort_medium_stack();
    test_sort_large_stack();
    test_sort_performance();

    printf("\n=== All tests completed ===\n\n");
    return (0);
}
