import trees_python as bst
import random
import time

if __name__ == "__main__":
    
    root = None
    root = bst.BST()
    
    root2 = None
    root2 = bst.AVL()
    # root2.insert(1)

    root3 = None
    root3 = bst.RBT()

    n = 3

    arr = [random.randint(0, 50) for i in range(n)]
    print(arr)
    input()
    print(root)
    print(root2)
    print(root3)

    for i in arr:
        print(f"\ninserting {i}")        
        # root.insert(i)
        # root2.insert(i)
        root3.insert(i)

        # root.print_tree()
        # root2.print_tree()
        root3.print_tree()


        # time.sleep(1.5)
        input()
        # print("---")
    
    # root2.print_tree()
    root3.print_tree()


    # root.print(traversal_type="preorder")
    # print()
    # root.print_tree()
    # choice = 1
    # print("---- removing ----")

    # # root = None

    # # root.print_tree()
    '''
    while int(input("Do you want to remove ? (1:YES 0: NO)")):   
        d = int(input("Enter data to remove : "))
        # root.remove(d)
        # root.print_tree()
        # root.print(traversal_type="preorder")

        root2.remove(d)
        root2.print_tree()

    # print("---SEARCHING---")
    # while int(input("search ? : 1 or 0 : ")):
    #     index = root.search(int(input("Enter data to search : ")))
    #     print(f"Found {index.data}.") if index != None else print()
       
    print("\n\n\t ---- AVL TREE ---- \n\n")
    # root2 = None
    # root2 = bst.AVL()
    # root2.insert(1)
    root2.print_tree()
    root2.print()
    '''