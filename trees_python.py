
class bt_Node():
    def __init__(self, data): # CONSTRUCTOR
        self.data = data
        self.left = None
        self.right = None
        # self.level = None # 0

    def __str__(self): # WE CAN DIRECTLY PRINT WITH THIS METHOD
        return str(self.data)

class avl_Node():
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.height = 1

class Tree:
    travel_inorder = "INORDER"
    travel_preorder = "PREORDER"
    travel_postorder = "POSTORDER"

    def inorder(self, node):
        # LEFT - DATA - RIGHT
        if node:
            self.inorder(node.left)
            print(node.data, end = ", ")
            self.inorder(node.right)
    
    def preorder(self, node):
        # DATA - LEFT - RIGHT
        if node:
            print(node.data, end = ", ")
            self.preorder(node.left)
            self.preorder(node.right)
        
    def postorder(self, node):
        # LEFT - RIGHT - DATA
        if node:
            self.postorder(node.left)
            self.postorder(node.right)
            print(node.data, end = ", ")
    
    def print(self, traversal_type = 'INORDER'):
        if traversal_type.upper() == self.travel_inorder:
            print(">>> INORDER TRAVERSAL : ")
            self.inorder(self.root)
        elif traversal_type.upper() == self.travel_postorder:
            print(">>> POST-ORDER TRAVERSAL : ")
            self.postorder(self.root)
        elif traversal_type.upper() == self.travel_preorder:
            print(">>> PRE-ORDER TRAVERSAL : ")
            self.preorder(self.root)

    def height_main(self, node):
        left = 1
        right = 1
        if node is None:
            return 0
        if node.left is not None:
            left = 1+ self.height_main(node.left)
        if node.right is not None:
            right = 1 + self.height_main(node.right)
        return max(left, right)

    def height(self):
        return self.height_main(self.root)

    def _print_tree(self, node, is_left, offset, depth, s):
        b = "" #[" " for i in range(20)]
        width = 5
        if node is None:
            return 0
        b = f"({node.data:03d})"
        b = list(b)
        # print(len(b))

        left  = self._print_tree(node.left,  1, offset,            depth+1, s)
        right = self._print_tree(node.right, 0, offset+left+width, depth+1, s)


        for i in range(width):
            s[2*depth][offset + left + i] = b[i]
        
        if depth and is_left:
            for i in range(width+right):
                s[2*depth -1][offset + left+width//2 +i] = "-"

            s[2*depth -1][offset + left + width//2] = "+"
            s[2*depth -1][offset + left + width + right + width//2] = "+"

        elif depth and not is_left:
            for i in range(left+width):
                s[2*depth - 1][offset - width//2 + i] = "-"

            s[2*depth -1][offset + left + width//2] = "+"
            s[2*depth -1][offset -width//2 - 1] = "+"

        return left+right+width
    
    def print_tree_main(self, node):
        h = self.height()
        # print(h)
        s = [[" " for i in range(255)] for j in range(2*h)] # BUFFER STRING
        # print(s)

        self._print_tree(node, 0, 0, 0, s)

        for i in range(2*h):
            print("".join(s[i]))

    def print_tree(self):
        self.print_tree_main(self.root)
        print()



class BST(Tree):
    def __init__(self):
        self.root = None

    def insert(self, data):
        if self.root:
            temp = self.root
            while 1:
                if data < temp.data:
                    if temp.left:
                        temp = temp.left
                    else:
                        temp.left = bt_Node(data)
                        print("Inserted in left branch")
                        break
                elif data > temp.data:
                    if temp.right:
                        temp = temp.right
                    else:
                        temp.right = bt_Node(data)
                        print("Inserted in right branch")
                        break
                else:
                    print(f"{data} VALUE AREADY PRESENT!!!") #ERROR MESSAGE, BST DO NOT TAKE DUPLICATES
                    break
        else:
            self.root = bt_Node(data)
            print("new node as ROOT created")

    def minValueNode(self, root):
        temp = root
        while temp.left is not None:
            temp = temp.left
        return temp
    
    def maxValueNode(self, root):
        temp = root
        while temp.right is not None:
            temp = temp.right
        return temp

    def remove_main(self, node, data):
        if node is None: # IF DATA IS NOT PRESENT
            print(f"{data} IS NOT PRESENT !!!")
            return node
        
        # SEARCHING FOR THE VALUE
        if data < node.data:
            node.left = self.remove_main(node.left, data)
        
        elif data > node.data:
            node.right = self.remove_main(node.right, data)
        
        else: # DATA FOUND
            if node.left is None and node.right is None: # LEAF NODE
                node = None
                return node
            elif node.left and node.right: # TWO CHILDREN
                successor = self.minValueNode(node.right)
                node.data = successor.data

                node.right = self.remove_main(node.right, successor.data)
            
            else: # ONE CHILD
                child = node.left if node.left else node.right
                node = child
        return node

    def remove(self, data):
        self.root = self.remove_main(self.root, data)
        # return self
    
    def search(self, data):
        # temp = None
        node = self.root
        
        if node is None:
            return None
        
        while node and node.data != data:
            # temp = node
            if data < node.data:
                node = node.left
            else:
                node = node.right
        if node == None:
            print("NOT FOUND!!!")
            return node
        else :
            return node

class AVL(Tree):
    def __init__(self):
        self.root = None
    
    def avl_height(self, node):
        if node is not None:
            return node.height
        else :
            return 0
    
    def balance_factor(self, node):
        # RETURNS
        #  1 : LEFT SIDE IS HEAVY
        # -1 : RIGHT SIDE IS HEAVY
        #  0 : EQUAL
        if node is None:
            return 0
        
        return self.avl_height(node.left) - self.avl_height(node.right)

    def rotate_right(self, node):
        # INITIALLY
        #          NODE
        #         /     \
        #     TEMP1     [SUB]
        #     /   \
        #  [SUB]  TEMP2

        # AFTER ROTATION 
        #         TEMP1
        #         /     \
        #     [SUB]     NODE
        #              /   \
        #           TEMP2   [SUB]

        temp1 = node.left
        temp2 = temp1.right

        temp1.right = node
        node.left = temp2

        node.height = max(self.avl_height(node.left), self.avl_height(node.right)) + 1
        temp1.height = max(self.avl_height(temp1.left), self.avl_height(temp1.right)) + 1
        
        return temp1
  

    def rotate_left(self, node):
        # INITIALLY
        #          NODE
        #         /    \
        #     [SUB]    TEMP1
        #              /   \
        #           TEMP2   [SUB]

        # AFTER ROTATION 
        #         TEMP1
        #         /   \
        #     NODE     [SUB]
        #    /    \     
        # [SUB]   TEMP2

        temp1 = node.right
        temp2 = temp1.left

        temp1.left = node
        node.right = temp2
        
        node.height = max(self.avl_height(node.left), self.avl_height(node.right)) + 1
        temp1.height = max(self.avl_height(temp1.left), self.avl_height(temp1.right)) + 1

        return temp1
    
    def insert_main(self, node, data):
        if node is None:
            node = avl_Node(data)
            return node
        if data < node.data:
            node.left = self.insert_main(node.left, data)
        
            
        elif data > node.data:
            node.right = self.insert_main(node.right, data)
         
        else:
            print(f"{data} ALREADY EXIST !!!")
            return node

        
        balance_fact = self.balance_factor(node)
        print(f"Balance factor at {node.data} = {balance_fact}")
         
        if balance_fact > 1:                  # LEFT TREE IS HEAVY
            if data < node.left.data:          # LEFT LEFT
                return self.rotate_right(node)
            else:                             # LEFT RIGHT
                node.left = self.rotate_left(node.left)
                return self.rotate_right(node)
        elif balance_fact < -1 :               # RIGHT TREE IS HEAVY
            if data > node.right.data:          # RIGHT RIGHT
                return self.rotate_left(node)
            else:                              # RIGHT LEFT
                node.right = self.rotate_right(node.right)
                return self.rotate_left(node)
        # else:
        #     print('Balanced')

        node.height = max(self.avl_height(node.left), self.avl_height(node.right))+1
        
        return node
    
    def insert(self, data):
        self.root = self.insert_main(self.root, data)
        # return self

