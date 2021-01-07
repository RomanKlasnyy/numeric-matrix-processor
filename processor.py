import numpy as np


def zeros_matrix(rows, cols):
    m = []
    while len(m) < rows:
        m.append([])
        while len(m[-1]) < cols:
            m[-1].append(0.0)
    return m


def copy_matrix(m):
    rows = len(m)
    cols = len(m[0])
    mc = zeros_matrix(rows, cols)
    for i in range(rows):
        for j in range(cols):
            mc[i][j] = m[i][j]
    return mc


def determinant(a, total=0):
    indices = list(range(len(a)))
    if len(a) == 2 and len(a[0]) == 2:
        val = a[0][0] * a[1][1] - a[1][0] * a[0][1]
        return val
    for fc in indices:
        ac = copy_matrix(a)
        ac = ac[1:]
        height = len(ac)
        for i in range(height):
            ac[i] = ac[i][0:fc] + ac[i][fc+1:]
        sign = (-1) ** (fc % 2)
        sub_det = determinant(ac)
        total += sign * a[0][fc] * sub_det
    return total


def show_options():
    print()
    print('1. Add matrices')
    print('2. Multiply matrix by a constant')
    print('3. Multiply matrices')
    print('4. Transpose matrix')
    print('5. Calculate a determinant')
    print('6. Inverse matrix')
    print('0. Exit')


def add_matrices():
    try:
        raw1, col1 = input('Enter size of first matrix:').split()
        nums1 = []
        print('Enter first matrix:')
        for i in range(int(raw1)):
            nums1.extend(input().split())
        raw2, col2 = input('Enter size of second matrix:').split()
        nums2 = []
        print('Enter second matrix:')
        for i in range(int(raw2)):
            nums2.extend(input().split())
        nums1 = [int(x) if '.' not in x else float(x) for x in nums1]
        nums2 = [int(x) if '.' not in x else float(x) for x in nums2]

        if raw1 != raw2 or int(raw1) * int(col1) != len(nums1) or \
           col1 != col2 or int(raw2) * int(col2) != len(nums2):
            print('ERROR')
        else:
            print('The result is:')
            for i in range(len(nums1)):
                num_sum = nums1[i]+nums2[i]
                if i+1 == len(nums1):
                    print(num_sum, end='')
                elif (i+1) % int(col1) == 0:
                    print(num_sum)
                else:
                    print(num_sum, end=' ')
    except ValueError:
        print('The operation cannot be performed.')


def multiply_const():
    try:
        raw1, col1 = input('Enter size of matrix:').split()
        nums1 = []
        print('Enter matrix:')
        for i in range(int(raw1)):
            nums1.extend(input().split())
        const = int(input('Enter constant:'))
        nums1 = [int(x)*const if '.' not in x else float(x)*const for x in nums1]
        print('The result is:')
        for i in range(len(nums1)):
            if i+1 == len(nums1):
                print(nums1[i], end='')
            elif (i+1) % int(col1) == 0:
                print(nums1[i])
            else:
                print(nums1[i], end=' ')
    except ValueError:
        print('The operation cannot be performed.')


def multiply_matrices():
    try:
        raw1, col1 = input('Enter size of first matrix:').split()
        nums1 = []
        print('Enter first matrix:')
        for i in range(int(raw1)):
            nums1.extend(input().split())
        raw2, col2 = input('Enter size of second matrix:').split()
        nums2 = []
        print('Enter second matrix:')
        for i in range(int(raw2)):
            nums2.extend(input().split())
        nums1 = [int(x) if '.' not in x else float(x) for x in nums1]
        nums2 = [int(x) if '.' not in x else float(x) for x in nums2]
        if col1 != raw2:
            print('ERROR')
        else:
            print('The result is:')
            for i in range(int(raw1)):
                for k in range(int(col2)):
                    num_sum = 0
                    for f in range(int(raw2)):
                        num_sum += nums1[i*int(raw2)+f]*nums2[f*int(col2)+k]
                    print(num_sum, end=' ')
                print()
    except ValueError:
        print('The operation cannot be performed.')


def transpose_matrix():
    print('1. Main diagonal')
    print('2. Side diagonal')
    print('3. Vertical line')
    print('4. Horizontal line')
    choice4 = input('Your choice:')
    if choice4 == '1':
        try:
            raw1, col1 = input('Enter matrix size:').split()
            nums1 = []
            print('Enter matrix:')
            for i in range(int(raw1)):
                nums1.extend(input().split())
            print('The result is:')
            for i in range(int(raw1)):
                for k in range(int(col1)):
                    print(nums1[(k*int(raw1))+i], end=' ')
                print()
        except ValueError:
            print('The operation cannot be performed.')
    elif choice4 == '2':
        try:
            raw1, col1 = input('Enter matrix size:').split()
            nums1 = []
            print('Enter matrix:')
            for i in range(int(raw1)):
                nums1.extend(input().split())
            print('The result is:')
            for i in range(int(raw1)):
                for k in range(int(col1)):
                    print(nums1[len(nums1)-1-i-(k*int(raw1))], end=' ')
                print()
        except ValueError:
            print('The operation cannot be performed.')
    elif choice4 == '3':
        try:
            raw1, col1 = input('Enter matrix size:').split()
            nums1 = []
            print('Enter matrix:')
            for i in range(int(raw1)):
                nums1.extend(input().split())
            print('The result is:')
            for i in range(int(raw1)):
                for k in range(int(col1)):
                    print(nums1[(i*int(raw1))+(int(col1)-1-k)], end=' ')
                print()
        except ValueError:
            print('The operation cannot be performed.')
    elif choice4 == '4':
        try:
            raw1, col1 = input('Enter matrix size:').split()
            nums1 = []
            print('Enter matrix:')
            for i in range(int(raw1)):
                nums1.extend(input().split())
            print('The result is:')
            for i in range(int(raw1)):
                for k in range(int(col1)):
                    print(nums1[k+((int(raw1)-1-i)*int(col1))], end=' ')
                print()
        except ValueError:
            print('The operation cannot be performed.')


def calc_determinant():
    try:
        raw1, col1 = input('Enter size of matrix:').split()
        n = []
        print('Enter matrix:')
        for i in range(int(raw1)):
            n.append(input().split())
        int_matrix = []
        for mat in n:
            mat = [int(x) if '.' not in x else float(x) for x in mat]
            int_matrix.append(mat)
        if raw1 != col1:
            print('Error! Use square matrices only!')
        else:
            print('The result is:')
            if len(n) == 1:
                print(n[0][0])
            else:
                print(determinant(int_matrix))
    except ValueError:
        print('The operation cannot be performed.')


def inverse_matrix():
    try:
        raw1, col1 = input('Enter size of matrix:').split()
        n = []
        print('Enter matrix:')
        for i in range(int(raw1)):
            n.append(input().split())
        int_matrix = []
        for mat in n:
            mat = [int(x) if '.' not in x else float(x) for x in mat]
            int_matrix.append(mat)
        int_matrix = np.linalg.inv(int_matrix)
        if raw1 != col1:
            print('Error! Use square matrices only!')
        else:
            print('The result is:')
            for i in int_matrix:
                for j in i:
                    print(j, end=' ')
                print()
    except ValueError:
        print('The operation cannot be performed.')
    except np.linalg.LinAlgError:
        print("This matrix doesn't have an inverse.")


def main():
    while True:
        show_options()
        choice = input('Your choice:')
        if choice == '0':
            break
        elif choice == '1':
            add_matrices()
        elif choice == '2':
            multiply_const()
        elif choice == '3':
            multiply_matrices()
        elif choice == '4':
            transpose_matrix()
        elif choice == '5':
            calc_determinant()
        elif choice == '6':
            inverse_matrix()


if __name__ == "__main__":
    main()
