import ast
import functools

def less(left, right):
    left_is_list = isinstance(left, list)
    right_is_list = isinstance(right, list)

    if not left_is_list and not right_is_list:
        if left == right:
            return None
        return left < right

    if not left_is_list:
        return less([left], right)

    if not right_is_list:
        return less(left, [right])

    for i in range(len(left)):
        if i >= len(right):
            return False

        is_less = less(left[i], right[i])

        if (is_less == True):
            return True
        if (is_less == False):
            return False
    
    return None if len(left) == len(right) else True

def cmp_less(left, right):
    if less(left, right):
        return -1
    return 1

with open('input.txt') as f:
    lists = [ast.literal_eval(x) for x in f.readlines() if x.strip() != '']

    total = 0
    for i in range(0, len(lists), 2):
        left = lists[i]
        right = lists[i + 1]
        res = less(left, right)
        if res:
            total = total + (i // 2) + 1

    print(total)

    lists.append([[2]])
    lists.append([[6]])
    
    ordered_list = sorted(lists, key=functools.cmp_to_key(cmp_less))
    ind1 = ordered_list.index([[2]]) + 1
    ind2 = ordered_list.index([[6]]) + 1
    print(ind1 * ind2)
