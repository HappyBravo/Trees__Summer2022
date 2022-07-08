import Python.trees_python as trees
import time

bst_root = None
bst_root = trees.BST()

avl_root = None
avl_root = trees.AVL()

rbt_root = None
rbt_root = trees.RBT()

tree_d = {
        "bst" : bst_root,
        "avl" : avl_root,
        "rbt" : rbt_root
}

def timetaken(start, end):
    return end-start

def reader(tree, testfile_loc, resultfile):
    print("ENTERED READER")
    # time.sleep(0.5)
    with open(testfile_loc) as f:
        for i in f:
            data = [int(n) for n in i.split(", ") if len(n) != 0]
            # print(data)
            for t in range(10):
                # exec("tree_d[tree] = trees." + f"{tree.upper()}()")
                if tree == "avl":
                    tree_d[tree] = trees.AVL()
                elif tree == "bst":
                    tree_d[tree] = trees.BST()
                elif tree == "rbt":
                    tree_d[tree] = trees.RBT()
                else:
                    print("ERROR!!!")
                    return
                
                start = time.time()
                for j in data:
                    tree_d[tree].insert(j)
                end = time.time()
                
                time_taken = timetaken(start, end)

                print(f"\tIT TOOK {time_taken} sec")
                resultfile.write(f"{time_taken}\t")
                # time.sleep(2)

    

if __name__ == "__main__":
    di = {
        0 : "bst",
        1 : "avl",
        2 : "rbt"
    }
    location = "test_files/test_"
    
    for i in range(3):
        result_location = "res_PY_"+f"{di[i]}".upper()+".txt"
        print("= "*15+"\n"+f"\tTESTING {di[i]}\n"+"= "*15+"\n")
        res = open(result_location, "w")
        for j in range(1, 7):
            test_f = location+f"{10**j}.txt"
            print(f"READING {test_f}")
            res.write(f"\nTESTCASE : {10**j}\n")
            reader(di[i], test_f, res)
            print(f"READING {test_f} DONE\n")
            time.sleep(2)
        res.close()
            



