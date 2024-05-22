def is_palindromic(num):
    num_str = str(num)
    if len(num_str) <= 1:
        return True
    elif num_str[0] != num_str[-1]:
        return False
    else:
        return is_palindromic(num_str[1:-1])

# Test the function
for number in range(10000):  # Change this number to test different cases
    if is_palindromic(number):
        print(f"{number} is palindromic.")
