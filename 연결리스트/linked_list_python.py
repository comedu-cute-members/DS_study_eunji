class LinkedNode():
    def __init__(self, value):
        self.value = value
        self.next = None

class LinkedList():
    def __init__(self):
        self.head = None

    def add_tail(self, value):
        new_node = LinkedNode(value)
        if (self.head == None):
            self.head = new_node
        else:
            current_node = self.head
            while(current_node.next != None): # move to tail
                current_node = current_node.next

            current_node.next = new_node

    def print_list(self):
        current_node = self.head
        while(current_node.next != None): # move to tail
            print(current_node.value)
            current_node = current_node.next
        print(current_node.value) # print tail

    def get_data(self, index):
        current_node = self.head
        for i in range(index): # move to index
            if (current_node.next == None):
                print("index out of range")
                return False
            current_node = current_node.next

        return current_node.value

    def delete(self, index):
        if (index == 0):
            self.head = self.head.next
        else:
            current_node = self.head
            for i in range(index - 1): # move to index - 1
                if (current_node.next == None):
                    print("index out of range")
                current_node = current_node.next
                
            current_node.next = current_node.next.next

    def list_count(self):
        count = 1
        current_node = self.head
        while(current_node.next != None): # move to tail
            count += 1
            print(current_node.value)
            current_node = current_node.next
        return count

my_list = LinkedList()
my_list.add_tail('a')
my_list.add_tail('b')
my_list.add_tail('c')

my_list.print_list()
print(my_list.get_data(3)) # out of range

my_list.delete(1)
my_list.print_list()

print(my_list.list_count())
            
