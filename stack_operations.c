#include "push_swap.h"

t_stack *init_stack(void)
{
    t_stack *stack;

    stack = (t_stack *)malloc(sizeof(t_stack));
    if (!stack)
        return (NULL);
    stack->head = NULL;
    stack->size = 0;
    return (stack);
}

void    add_node(t_stack *stack, int value)
{
    t_node *new;
    t_node *last;

    new = (t_node *)malloc(sizeof(t_node));
    if (!new)
        error_exit();
    new->value = value;
    new->next = NULL;
    new->prev = NULL;

    if (!stack->head)
    {
        stack->head = new;
    }
    else
    {
        last = stack->head;
        while (last->next)
            last = last->next;
        last->next = new;
        new->prev = last;
    }
    stack->size++;
}

void    free_stack(t_stack *stack)
{
    t_node *current;
    t_node *next;

    if (!stack)
        return;
    current = stack->head;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(stack);
}

void sa(t_stack *stack_a, int print)
{
    t_node *first;
    t_node *second;

    if (!stack_a || !stack_a->head || !stack_a->head->next)
        return;
    first = stack_a->head;
    second = first->next;
    first->next = second->next;
    second->next = first;
    stack_a->head = second;
    if (print)
        write(1, "sa\n", 3);
}

void sb(t_stack *stack_b, int print)
{
    t_node *first;
    t_node *second;

    if (!stack_b || !stack_b->head || !stack_b->head->next)
        return;
    first = stack_b->head;
    second = first->next;
    first->next = second->next;
    second->next = first;
    stack_b->head = second;
    if (print)
        write(1, "sb\n", 3);
}

void ss(t_stack *stack_a, t_stack *stack_b, int print)
{
    sa(stack_a, 0);
    sb(stack_b, 0);
    if (print)
        write(1, "ss\n", 3);
}

void pa(t_stack *stack_a, t_stack *stack_b, int print)
{
    t_node *temp;

    if (!stack_b || !stack_b->head)
        return;
    temp = stack_b->head;
    stack_b->head = stack_b->head->next;
    temp->next = stack_a->head;
    stack_a->head = temp;
    stack_a->size++;
    stack_b->size--;
    if (print)
        write(1, "pa\n", 3);
}

void pb(t_stack *stack_a, t_stack *stack_b, int print)
{
    t_node *temp;

    if (!stack_a || !stack_a->head)
        return;
    temp = stack_a->head;
    stack_a->head = stack_a->head->next;
    temp->next = stack_b->head;
    stack_b->head = temp;
    stack_b->size++;
    stack_a->size--;
    if (print)
        write(1, "pb\n", 3);
}

void ra(t_stack *stack_a, int print)
{
    t_node *first;
    t_node *last;

    if (!stack_a || !stack_a->head || !stack_a->head->next)
        return;
    first = stack_a->head;
    last = stack_a->head;
    while (last->next)
        last = last->next;
    stack_a->head = first->next;
    first->next = NULL;
    last->next = first;
    if (print)
        write(1, "ra\n", 3);
}

void rb(t_stack *stack_b, int print)
{
    t_node *first;
    t_node *last;

    if (!stack_b || !stack_b->head || !stack_b->head->next)
        return;
    first = stack_b->head;
    last = stack_b->head;
    while (last->next)
        last = last->next;
    stack_b->head = first->next;
    first->next = NULL;
    last->next = first;
    if (print)
        write(1, "rb\n", 3);
}

void rr(t_stack *stack_a, t_stack *stack_b, int print)
{
    ra(stack_a, 0);
    rb(stack_b, 0);
    if (print)
        write(1, "rr\n", 3);
}

void rra(t_stack *stack_a, int print)
{
    t_node *last;
    t_node *second_last;

    if (!stack_a || !stack_a->head || !stack_a->head->next)
        return;
    last = stack_a->head;
    second_last = NULL;
    while (last->next)
    {
        second_last = last;
        last = last->next;
    }
    second_last->next = NULL;
    last->next = stack_a->head;
    stack_a->head = last;
    if (print)
        write(1, "rra\n", 4);
}

void rrb(t_stack *stack_b, int print)
{
    t_node *last;
    t_node *second_last;

    if (!stack_b || !stack_b->head || !stack_b->head->next)
        return;
    last = stack_b->head;
    second_last = NULL;
    while (last->next)
    {
        second_last = last;
        last = last->next;
    }
    second_last->next = NULL;
    last->next = stack_b->head;
    stack_b->head = last;
    if (print)
        write(1, "rrb\n", 4);
}

void rrr(t_stack *stack_a, t_stack *stack_b, int print)
{
    rra(stack_a, 0);
    rrb(stack_b, 0);
    if (print)
        write(1, "rrr\n", 4);
}

int is_sorted(t_stack *stack)
{
    t_node *current;

    if (!stack || !stack->head)
        return (1);
    current = stack->head;
    while (current->next)
    {
        if (current->value > current->next->value)
            return (0);
        current = current->next;
    }
    return (1);
}
