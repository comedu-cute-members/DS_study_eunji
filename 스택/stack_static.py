class Stack():
    def __init__(self, max_size): # create
        self.max_size = max_size
        self.value_list = [None for i in range(max_size)]
        self.top = -1

    def push(self, value):
        if (self.top+1 == self.max_size):
            print("overflow!!!")
            # overflow
        else:
            self.value_list[self.top+1] = value
            self.top += 1

    def pop(self):
        if (self.top == -1): # underflow
            return False
        value = self.value_list[self.top]
        self.value_list[self.top] = None
        self.top -= 1
        return value

    def is_full(self):
        return self.max_size == self.top+1

    def print_stack(self):
        temp_stack = Stack(self.max_size)
        for i in range(self.top + 1):
            value = self.pop()
            temp_stack.push(value)
            print(f"{self.top + 1}: {value}")
        for i in range(temp_stack.top + 1):
            self.push(temp_stack.pop())

    def is_member(self, value):
        temp_stack = Stack(self.max_size)
        is_in = False
        for i in range(self.top+1):
            temp = self.pop()
            temp_stack.push(temp)
            if (value == temp):
                is_in = True
                break
        for i in range(temp_stack.top + 1):
            self.push(temp_stack.pop())

        return is_in

### main ###
stack = Stack(5)

stack.push('a')
stack.push('b')
stack.push('c')
stack.push('d')

print(stack.pop())
print(stack.is_full())
stack.print_stack()
print(stack.is_member('b'))
