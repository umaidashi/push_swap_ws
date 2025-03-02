#include "push_swap.h"

void    error_exit(void)
{
    write(2, "Error\n", 6);
    exit(1);
}

int is_valid_number(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int has_duplicates(t_stack *stack)
{
    t_node *current;
    t_node *check;

    if (!stack || !stack->head)
        return (0);
    current = stack->head;
    while (current)
    {
        check = current->next;
        while (check)
        {
            if (current->value == check->value)
                return (1);
            check = check->next;
        }
        current = current->next;
    }
    return (0);
}
