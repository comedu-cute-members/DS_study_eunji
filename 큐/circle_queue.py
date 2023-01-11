class Queue():
    def __init__(self, max_size):
        self.value_list = [None for i in range(max_size+1)]
        self.size = max_size + 1
        self.front = 0
        self.rear = 0

    def enqueue(self, value):
        temp_rear = (self.rear + 1) % self.size
        if (temp_rear == self.front):
            return None  # 포화상태
        else:
            self.rear = temp_rear
            self.value_list[self.rear] = value

    def dequeue(self):
        if (self.front == self.rear):  # 공백상태
            return None
        else:
            self.front = (self.front + 1) % self.size
            return self.value_list[self.front]

    def is_empty(self):
        if (self.front == self.rear): return True
        else: return False

    def is_full(self):
        if ( (self.rear + 1) % self.size == self.front): return True
        else: return False

    def count(self):
        count = 0
        current = self.front

        while (current != self.rear):
            count += 1
            current = (current + 1) % self.size

        return count
        

queue = Queue(5)
queue.enqueue('a')
queue.enqueue('b')
print(queue.dequeue())
print(queue.is_empty())
print(queue.dequeue())
print(queue.is_empty())

queue.enqueue('a')
queue.enqueue('b')
queue.enqueue('c')
queue.enqueue('d')
queue.enqueue('e')
print(queue.is_full())

print(queue.count())
