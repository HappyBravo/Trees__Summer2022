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

class NullNode:
    def __init__(self) :
        self.data = None
        self.left = None
        self.right = None
        self.parent = None
        self.color = 0

class rb_Node:
    def __init__(self, data):
        self.data = data
        self.left = NullNode()
        self.right = NullNode()
        self.parent = None
        self.color = 1
    
    def is_red(self):
        if self:
            return (self.color == 1)
        return False

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

    def _print_tree(self, node, is_left, offset, depth, s, rbt_nil=False):
        b = ""
        width = 5
        if node is None:
            return 0
        
        if hasattr(node, 'height'): # FOR AVL TREES
            width = 8
            b = f"({node.data:03d},{node.height:02d})"
        elif hasattr(node, 'color'): # FOR RB TREES
            width = 7
            if node.data is None:
                if rbt_nil:
                    b = f"(NIL,{node.color})" # RED = 1, BLACK = 0
                else:
                    return 0
            else:
                b = f"({node.data:03d},{node.color})" # RED = 1, BLACK = 0
        else:
            b = f"({node.data:03d})"
        
        b = list(b)
        # print(len(b))
        left  = self._print_tree(node.left,  1, offset,            depth+1, s, rbt_nil)
        right = self._print_tree(node.right, 0, offset+left+width, depth+1, s, rbt_nil)


        for i in range(width):
            s[2 * depth][offset + left + i] = b[i]
        
        if depth and is_left:
            for i in range(width+right):
                s[2 * depth -1][offset + left+width//2 +i] = "-"

            s[2 * depth -1][offset + left + width//2] = "+"
            s[2 * depth -1][offset + left + width + right + width//2] = "+"

        elif depth and not is_left:
            for i in range(left+width):
                s[2 * depth - 1][offset - width//2 + i] = "-"

            s[2 * depth -1][offset + left + width//2] = "+"
            s[2 * depth -1][offset -width//2 - 1] = "+"

        return left+right+width
    
    def print_tree_main(self, node, rbt_nil=False):
        h = self.height()
        # print(h)
        s = [[" " for i in range(255)] for j in range(2*h)] # BUFFER STRING
        # print(s)

        self._print_tree(node, 0, 0, 0, s, rbt_nil)

        for i in range(2*h):
            print("".join(s[i]))

    def print_tree(self, rbt_nil=False):
        self.print_tree_main(self.root, rbt_nil)
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
                        # print("Inserted in left branch")
                        break
                elif data > temp.data:
                    if temp.right:
                        temp = temp.right
                    else:
                        temp.right = bt_Node(data)
                        # print("Inserted in right branch")
                        break
                else:
                    # print(f"{data} VALUE AREADY PRESENT!!!") #ERROR MESSAGE, BST DO NOT TAKE DUPLICATES
                    break
        else:
            self.root = bt_Node(data)
            # print("new node as ROOT created")

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
            # print(f"{data} ALREADY EXIST !!!")
            return node

        
        balance_fact = self.balance_factor(node)
        # print(f"Balance factor at {node.data} = {balance_fact}")
         
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

    def remove_main(self, node, data):
        if node is None:
            return node
        
        # SEARCHING FOR THE DATA TO BE DELETED
        if data < node.data:
            node.left = self.remove_main(node.left, data)
        elif data > node.data:
            node.right = self.remove_main(node.right, data)
        else:
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            else:
                temp = self.minValueNode(node.right)
                node.data = temp.data
                node.right = self.remove_main(node.right, temp.data)
        
        # BALANCING THE TREE AFTER DELETION
        if node is None:
            return node
        
        node.height = max(self.avl_height(node.right), self.avl_height(node.left)) + 1

        balance_fact = self.balance_factor(node)
        print(f"Balance factor at {node.data} = {balance_fact}")
        
        if balance_fact > 1 and self.balance_factor(node.left) >= 0:
            return self.rotate_right(node)
        
        if balance_fact < -1 and self.balance_factor(node.right) <= 0:
            return self.rotate_left(node)

        if balance_fact > 1 and self.balance_factor(node.left) < 0:
            node.left = self.rotate_left(node.left)
            return self.rotate_right(node)
        
        if balance_fact < -1 and self.balance_factor(node.right) > 0:
            node.right = self.rotate_right(node.right)
            return self.rotate_left(node)
        
         
        # if balance_fact > 1:                  # LEFT TREE IS HEAVY
        #     if data < node.left.data:          # LEFT LEFT
        #         return self.rotate_right(node)
        #     else:                             # LEFT RIGHT
        #         node.left = self.rotate_left(node.left)
        #         return self.rotate_right(node)
        # elif balance_fact < -1 :               # RIGHT TREE IS HEAVY
        #     if data > node.right.data:          # RIGHT RIGHT
        #         return self.rotate_left(node)
        #     else:                              # RIGHT LEFT
        #         node.right = self.rotate_right(node.right)
        #         return self.rotate_left(node)
        
        # node.height = max(self.avl_height(node.right), self.avl_height(node.left)) + 1

        return node
    
    def remove(self, data):
        self.root = self.remove_main(self.root, data)

class RBT(Tree):
    def __init__(self):
        self.root = None
        # self.nil = None

    def sibling(self, node):
        if node.parent is None:
            return None
        if node is node.parent.right:
            return node.parent.left
        else:
            return node.parent.right

    def uncle(self, node):
        if node.parent == None:
            return None
        return self.sibling(node.parent)

    def has_children(self, node):
        if node.left or node.right:
            return True
        return False

    def is_red_light_zone(self, node):
        if node == None:
            return False
        elif node.left and node.right:
            if node.left.color and node.right.color:
                return True # DANGER AHEAD
        
        return False # SAFE
    
    # def is_black_light_zone(self, node):
    #     if node == None:
    #         return False
    #     elif node.left and node.right:
    #         if not (node.left.color or node.right.color):
    #             return True # DANGER AHEAD
        
    #     return False # SAFE

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

        parent = node.parent
        temp1 = node.left
        temp2 = temp1.right

        temp1.right = node
        node.left = temp2

        temp1.parent = parent
        node.parent = temp1
        if temp2.data is not None:
            temp2.parent = node

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

        parent = node.parent
        temp1 = node.right
        temp2 = temp1.left

        temp1.left = node
        node.right = temp2

        temp1.parent = parent
        node.parent = temp1
        if temp2.data is not None:
            temp2.parent = node

        return temp1

    # problem was ... the older rotate_left/right was not changing parent.left/right
    # changing older function can cause error in insert_fixup, so simply made new rotation function for removing node
    # 
    def rotate_left_2(self, node):
        temp = node.right

        node.right = temp.left
        if temp.left is not None:
            temp.left.parent = node
        
        temp.parent = node.parent
        if node.parent is None:
            self.root = temp
        elif node == node.parent.left:
            node.parent.left = temp
        else:
            node.parent.right = temp

        temp.left = node
        node.parent = temp
        
    def rotate_right_2(self, node):
        temp = node.left

        node.left = temp.right
        if temp.right is not None:
            temp.right.parent = node
        
        temp.parent = node.parent
        if node.parent is None:
            self.root = temp
        elif node == node.parent.left:
            node.parent.left = temp
        else:
            node.parent.right = temp

        temp.right = node
        node.parent = temp


    def cmp(self, data1, data2) -> int:
        # print(f"{data1}, {data2}")
        if data1 is None and data2 is None:
            print("BOTH ARE NONE")
            return 0
        elif data2 is None and data1 is not None:
            return -1
        elif data1 is None and data2 is not None:
            return 1
        elif data1 < data2 :
            return 1
        elif data1 > data2:
            return -1
        elif data1 == data2:
            return 0


    def insert_main(self, node, data):
        if node is not None:
            comp = self.cmp(node.data, data)

        if node == None:
            node = rb_Node(data)
            node.parent = None
            node.color = 0 # FOR ROOT.
            return node
        # elif data == node.data:
        elif comp == 0:
            # print(f"{data} already exist.")
            return node
        elif comp == -1:
            if node.left.data == None:
                node.left = rb_Node(data)
                # node.left.data = data
                node.left.parent = node

            elif self.is_red_light_zone(node):
                node.left.color = 0
                node.right.color = 0
                node.color = 1
            
            # if node.left is not None and node.left.data is not None:
            node.left = self.insert_main(node.left, data)
            node.left.parent = node

            if node.left.data: # IF NODE.LEFT IS NULL NODE IS NONE i.e. IF ITS EMPTY, IT WILL NOT GO INTO THE IF BLOCK
                if node.left.color == 1:
                    
                    if node.left.left.data: # LEFT GRANDCHILD
                        if node.left.left.color == 1:
                            node.left.color = 0
                            node.color = 1
                            node = self.rotate_right(node)
                            # self.rotate_right_2(node)
                    else :
                        if node.left.right.data: # RIGHT GRANDCHILD
                            if node.left.right.color == 1:
                                node.left = self.rotate_left(node.left)
                                # self.rotate_left_2(node.left)
                            node.left.color = 0
                            node.color = 1
                            node = self.rotate_right(node)
                            # self.rotate_right_2(node)


        elif comp == 1:
            if node.right.data == None:
                node.right = rb_Node(data)
                # node.right.data = data
                node.right.parent = node
            
            elif self.is_red_light_zone(node):
                node.right.color = 0
                node.left.color = 0
                node.color = 1

            # if node.right is not None and node.right.data is not None:
            node.right = self.insert_main(node.right, data)
            node.right.parent = node

            if node.right.data:
                if node.right.color == 1:
                    if node.right.right.data:
                        if node.right.right.color == 1:
                            node.right.color = 0
                            node.color = 1
                            node = self.rotate_left(node)
                            # self.rotate_left_2(node)
                    else:
                        if node.right.left.data:
                            if node.right.left.color == 1:
                                node.right = self.rotate_right(node.right)
                                # self.rotate_right_2(node.right)
                            node.right.color = 0
                            node.color = 1
                            node = self.rotate_left(node)
                            # self.rotate_left_2(node)
            
        
        if node is self.root:
            node.color = 0
        return node
    
    def insert(self, data):
        self.root = self.insert_main(self.root, data)
        self.root.color = 0

    # <---------------------------------------->
    def rbt_minValueNode(self, root):
        temp = root
        while temp.left is not None and temp.left.data is not None:
            temp = temp.left
        return temp

    def transplant(self, node1, node2):
        print(f"Transplanting ({node1, node2})")
        if node1.parent is None:
            self.root = node2
        elif node1 == node1.parent.left:
            node1.parent.left = node2
        else:
            node1.parent.right = node2
        if node2 is not None:
            node2.parent = node1.parent 

    def remove_fixup(self, node):
        # print(f"--- FIXING {node.data, node.color}")

        while node != self.root and node.color == 0:
            print("loop starts")
            if node == node.parent.left: # IF THE NODE IS IN THE LEFT
                sibling = node.parent.right
                
                if sibling.color == 1: # CASE 1
                    sibling.color = 0
                    node.parent.color = 1
        
                    # print(f"left rotating {node.parent.data}")
                    # node.parent = self.rotate_left(node.parent) 
                    self.rotate_left_2(node.parent)
                    # print("left rotation done")
        
                    sibling = node.parent.right # <---- CAUTION
                
                if sibling.left.color == 0 and sibling.right.color == 0: # CASE 2
                    sibling.color = 1
                    node = node.parent

                else: # CASE 3
                    if sibling.right.color == 0:
                        sibling.left.color = 0
                        sibling.color = 1
        
                        # print(f"right rotating {sibling.data}")
                        # sibling = self.rotate_right(sibling)
                        self.rotate_right_2(sibling)
                        # print("right rotation done")
        
                        sibling = node.parent.right # <---- CAUTION
                    
                    # CASE 4
                    sibling.color = node.parent.color
                    node.parent.color = 0
                    sibling.right.color = 0
        
                    # print(f"left rotating {node.parent.data}")
                    # node.parent = self.rotate_left(node.parent)
                    self.rotate_left_2(node.parent)
                    # print("left rotation done")
        
                    node = self.root

            else: # IF THE NODE IS ON THE RIGHT
                sibling = node.parent.left
                
                if sibling.color == 1: #CASE 1
                    sibling.color = 0
                    node.parent.color = 1
        
                    # print(f"rightt rotating {node.parent.data}")
                    # node.parent = self.rotate_right(node.parent)
                    self.rotate_right_2(node.parent)
                    # print("right rotation done")
        
                    sibling = node.parent.left # <---- CAUTION

                if  sibling.right.color == 0 and sibling.left.color == 0 : # CASE 2
                    sibling.color = 1
                    node = node.parent
                else:
                    if sibling.left.color == 0:
                        sibling.right.color = 0
                        sibling.color = 1
        
                        # print(f"left rotating {sibling.data}")
                        # sibling = self.rotate_left(sibling)
                        self.rotate_left_2(sibling)
                        # print("left rotation done")
        
                        sibling = node.parent.left # <---- CAUTION
                    sibling.color = node.parent.color
                    node.parent.color = 0
                    sibling.left.color = 0
        
                    # print(f"right rotating {node.parent.data}")
                    # node.parent = self.rotate_right(node.parent)
                    self.rotate_right_2(node.parent)
                    # print("right rotation done")
        
                    node = self.root
            print("loop ends")
        print("Out of loop")
        node.color = 0

    def remove_main(self, node):
        print(f"Removing {node.data, node.color}")
        original_color = node.color
        if node.left.data is None:
            temp = node.right
            self.transplant(node, node.right)
        elif node.right.data is None:
            temp = node.left
            self.transplant(node, node.left)
        
        else:
            inorder_Successor = self.rbt_minValueNode(node.right)
            original_color = inorder_Successor.color

            temp = inorder_Successor.right
            # if temp is None
            if inorder_Successor.parent == node:
                if temp is not None:
                    temp.parent = node.right
            else:
                self.transplant(inorder_Successor, inorder_Successor.right)
                inorder_Successor.right = node.right
                inorder_Successor.right.parent = inorder_Successor
            self.transplant(node, inorder_Successor)
            inorder_Successor.left = node.left
            inorder_Successor.left.parent = inorder_Successor
            inorder_Successor.color = node.color

        if original_color == 0:
            print("TRYING TO FIX TREE")
            # if temp is not None:
            self.remove_fixup(temp)
            print("TREE FIXING DONE")

    def remove(self, data):
        if self.root:
            node_to_delete = self.search(data)
            if node_to_delete.data is not None:
                self.remove_main(node_to_delete)
        else:
            print("TREE DOES NOT EXIST!!!")
            return None
    # < ------------------------------------------ >

