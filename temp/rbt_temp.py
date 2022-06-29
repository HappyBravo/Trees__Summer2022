#  ----------
# ### RULES ###
#  ----------
# 1. A NODE ID EITHER RED OR BLACK
# 2. THE ROOT IS ALWAYS BLACK
# 3. A RED NODE ALWAYS HAS BLACK CHILDERN
# 4. BLACK NODE FROM ROOT HAS TO BE SAME IN EACH (SUB)TREE

class rb_Node:
    def __init__(self, data):
        self.data = data
        self.left = self.NIL()
        self.right = self.NIL()
        self.parent = self.NIL()
        self.color = 1

    def NIL(self):
        self.color = 0

class Tree:
    
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
        
        if hasattr(node, 'height'):
            width = 9
            b = f"({node.data:03d}, {node.height:02d})"
        elif hasattr(node, 'color'):
            width = 8
            b = f"({node.data:03d}, {node.color})" # RED = 1, BLACK = 0
        else:
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


class RBT(Tree):
    def __init__(self):
        self.root = None

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

    def is_red_light_zone(self, node):
        if node == None:
            return False
        elif node.left and node.right:
            if node.left.color and node.right.color:
                return True # DANGER AHEAD
        
        return False # SAFE

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
        print(temp1)
        temp2 = temp1.right
        
        # if temp1:
        #     temp2 = temp1.right
        #     temp1.right = node

        # else:
        #     temp2 = None


        temp1.right = node
        node.left = temp2

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
        print(temp1)
        temp2 = temp1.left
        
        # if temp1:
        #     temp2 = temp1.left
        #     temp1.left = node

        # else:
        #     temp2 = None

        temp1.left = node
        node.right = temp2

        return temp1


    def insert_main(self, node, data):
        if node == None:
            node = rb_Node(data)
            node.color = 0 # FOR ROOT.
            return node
        elif data == node.data:
            print(f"{data} already exist.")
            return node
        elif data < node.data:
            if node.left == None:
                node.left = rb_Node(data)

            elif self.is_red_light_zone(node):
                node.left.color = 0
                node.right.color = 0
                node.color = 1

            node.left = self.insert_main(node.left, data)

            if node.left: # IF NODE.LEFT IS NONE i.e. IF ITS EMPTY, IT WILL NOT GO INTO THE IF BLOCK
                if node.left.color == 1:
                    
                    if node.left.left: # LEFT GRANDCHILD
                        if node.left.left.color == 1:
                            node.left.color = 0
                            node.color = 1
                            node = self.rotate_right(node)
                    else :
                        if node.left.right: # RIGHT GRANDCHILD
                            if node.left.right.color == 1:
                                node.left = self.rotate_left(node.left)
                            node.left.color = 0
                            node.color = 1
                            node = self.rotate_right(node)


        elif data > node.data:
            if node.right == None:
                node.right = rb_Node(data)
            
            elif self.is_red_light_zone(node):
                node.right.color = 0
                node.left.color = 0
                node.color = 1

            node.right = self.insert_main(node.right, data)

            if node.right:
                if node.right.color == 1:
                    if node.right.right:
                        if node.right.right.color == 1:
                            node.right.color = 0
                            node.color = 1
                            # node = self.rotate_left(node)
                    else:
                        if node.right.left:
                            if node.right.left.color == 1:
                                node.right = self.rotate_right(node.right)
                            node.right.color = 0
                            node.color = 1
                            node = self.rotate_left(node)
            
        
        if node is self.root:
            self.root.color = 0
        return node
    
    def insert(self, data):
        self.root = root.insert_main(self.root, data)


import random
import time

if __name__ == "__main__":
    root = RBT()
    testcases = 20
    l = [random.randint(0,99) for i in range(testcases)]

    for i in l:
        root.insert(i)
        root.print_tree()
        time.sleep(1)

    
    # while True:
    #     # try:
    #         root.insert(int(input("ENTER DATA TO INSERT : ")))
    #         root.print_tree()
    #     # except:
    #         # break
    # root.print_tree()
    # pass
