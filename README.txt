==========================================================================================
    COMP 8851 Assignment 02
    
    Copyright 2018 Erick Fernandez de Arteaga. All rights reserved.
        https://www.linkedin.com/in/erick-fda
        https://github.com/erick-fda
        https://bitbucket.org/erick-fda
    
==========================================================================================

------------------------------------------------------------------------------------------
    TABLE OF CONTENTS
    
    ## Question Responses
    
------------------------------------------------------------------------------------------

==========================================================================================
    ## Question Responses
==========================================================================================
1.) --------------------------------------------------------------------------------------
    The response to this question can be found at 
        ./COMP8851_Asg02_A00925871/Question01/

2.) --------------------------------------------------------------------------------------
    The response to this question can be found at 
        ./COMP8851_Asg02_A00925871/Question02/

3.) --------------------------------------------------------------------------------------
    To allow for finding the Kth item in the tree, each node should keep two int fields 
    indicating its number of left and right children. To keep this value up-to-date, 
    the recursive insert() and remove() methods should each return a boolean indicating 
    whether a node was successfully added or removed. This boolean should propagate back 
    up through the insert() or remove() call stack, and every node should either 
    increment or decrement their appropriate child counter accordingly.

    The findKth() method itself should work as follows:

    Calling findKth(k) on the tree will call a private recursive method...
        
        BinaryNode& findKth(BinaryNode*& node, int k, int numSmaller)

    with arguments...
        
        findKth(root, k, 0)


    The private recursive method will be as follows:
    
    BinaryNode& findKth(BinaryNode*& node, int k, int numSmaller)
    {
        int numLeftChildrenRequired = (k - numSmaller - 1);

        if (node.numLeftChildren == numLeftChildrenRequired) 
        {
            return node;
        }
        else if (node.numLeftChildren > numLeftChildrenRequired)
        {
            return findKth(node.leftChild, k, numSmaller);
        }
        else
        {
            return findKth(node.rightChild, k, (numSmaller + numLeftChildren + 1));
        }
    }

    As a final note, the public findKth(k) method should obviously perform checking on k 
    to ensure it is valid before calling the private recursive method. For example, it 
    should ensure that k does not exceed the number of elements in the tree, which can be 
    easily checked by ensuring it does not exceed the sum of the number of left and right 
    children of the root node by more than one.  

4.) --------------------------------------------------------------------------------------
    a.)
        If the two input arrays to a mergesort are known to be sorted, then the mergesort 
        will have a worst-case running time of O(N), since only one comparison is needed 
        to sort each next item.

    b.)
        If the two input arrays to a mergesort are known to be reverse-sorted, then the 
        worst-case running time will be O(N), just as with the normally sorted case. This 
        is because the arrays can simply be read backwards, and otherwise the same 
        process can be followed, with one comparison per item.

    c.)
        If the two input arrays are not known to be sorted, then mergesort will have a 
        worst-case running time of O(NlogN), since the two arrays will first need to be 
        sorted with an O(NlogN) algorithm before being merged.
        
        In such a case, mergesort would provide no worst-case improvement over merging 
        the two arrays first and then sorting the combined array.
        
        Thus, mergesort is only an improvement over other sorting algorithms when the 
        two input arrays are known to be either forward- or reverse-sorted to begin with.

5.) --------------------------------------------------------------------------------------
    a.)
        O(NlogN)

    b.)
        O(NlogN)

    c.)
        O(NlogN)

6.) --------------------------------------------------------------------------------------
    The response to this question can be found at 
        ./COMP8851_Asg02_A00925871/Question06/

7.) --------------------------------------------------------------------------------------
    The response to this question can be found at 
        ./COMP8851_Asg02_A00925871/Question07/

8.) --------------------------------------------------------------------------------------
    a.)
        An O(N^2) algorithm for this problem would be to add every given number to every 
        other given number and see whether the result is K, returning true as soon as a 
        valid pair is found.

    b.)
        An O(NlogN) algorithm for this problem would be to first sort the array using one 
        of several existing O(NlogN) sorting algorithms (such as std::sort() in C++).

        Then for each item x in the array, use a binary search (O(logN)) to see whether 
        K-x exists in the array, returning true as soon as a match is found.

    c.)
        My source code for this question can be found at 
            ./COMP8851_Asg02_A00925871/Question09/

        The executable at 

            ./COMP8851_Asg02_A00925871/Debug/Question08.exe

        can be run without parameters to demonstrate the timing of each solution 
        (Warning: takes a while to run).

        N and K values are consts which can be modified in Question08.cpp.
        When the program is run, it will print the running time of each algorithm.

        To ensure a worst-case scenario for these algorithm's performances, I have made 
        them search for a third value "impossibleK", which will never be contained in the 
        array because of how the contents are generated. Thus both algorithms must 
        spend the maximum amount of checking. 
        
        Some sample running times are as follows:
        
        For N = 100,000:
            O(N^2) = 34,536 ms
            O(NlogN) = 177 ms

        For N = 200,000:
            O(N^2) = 148,064 ms
            O(NlogN) = 368 ms

        The sample running times reflect roughly the expected scaling for each algorithm.

        It is worth noting that before ensuring a worst-case scenario with impossibleK, 
        the O(N^2) solution was regularly outperforming the O(NlogN) solution. The former 
        would tend to find a match quickly in the unsorted array, while the latter would 
        spend a lot of time sorting.

        This suggests that if there is a good chance of a match existing, the O(N^2) 
        algorithm may have a better *average* performance (thought a worse worst-case 
        performance).
        
9.) --------------------------------------------------------------------------------------
    My source code for this question can be found at 
            ./COMP8851_Asg02_A00925871/Question09/

    The executable at 

        ./COMP8851_Asg02_A00925871/Debug/Question09.exe

    can be run without parameters to demonstrate the proper topological sorting of the 
    graph.

    I've used the graph in Figure 9.4 in chapter 9 of the textbook for this question.

10.) -------------------------------------------------------------------------------------
    This problem can be solved using a slightly modified form of what is known as the 
    Bellman-Ford algorithm as follows:

    1) Begin with the description of the problem as an undirected graph, described as a 
        list of V vertices and a list of E weighted edges. Each edge is described as a 
        pair of adjacent vertices, X and Y, with a different weight depending on whether 
        the edge is travelled from X to Y or from Y to X.
        
        Each vertex represents a type of currency and each edge represents a currency 
        conversion. The weights are floating point numbers which represent the conversion 
        rate from one type of currency to another. The two weights for an edge are always 
        inverses of each other, such that if the weight of going from X to Y is 2, the 
        weight of going from Y to X will be 0.5.
        
        For each vertex, keep track of its highest accumulated value ("distance" to 
        maximise financial gain) from the start vertex (your starting currency type) and 
        its immediate predecessor (last currency you converted from) along the path to 
        reach it from the start vertex.

    2) FOR EACH vertex (treating it as the start vertex):
    
        A) Initialize the value and path of every vertex to negative infinity and null, 
            respectively.

        B) FOR EACH vertex X, starting at the start vertex and branching out:
        
            a) FOR EACH edge (X, Y) adjacent to this vertex:
        
                i) If the value of X + (X, Y) is greater than the value of Y (i.e., 
                    converting from X to Y is beneficial), set Y's value to X + (X, Y) 
                    and Y's predecessor to X.
        
        C) FOR EACH edge (X, Y):

            a) If the value of X + (X, Y) > the value of Y (i.e., converting from X to Y 
                a second time is somehow more beneficial than converting to it the first 
                time), then a positive cycle exists, and it is possible to multiply your 
                money via currency exchange. To determine what the cycle is, do the 
                following:

                i) You know that the cycle included edge (X, Y), so simply start at 
                    vertex X and recursively follow its chain of predecessors, adding 
                    each to a list until you arrive at X again. The list now contains the 
                    positive cycle in reverse order.
                    
                    Simply reverse the list, start at any vertex in it, and convert your 
                    currency in the given order to multiply your money.

                    You can determine your percentage gain on each iteration of the cycle 
                    by starting with a value of 1 and applying each weight multiplier 
                    in order. The final value obtained will be some floating point number 
                    greater than 1 indicating the factor your money will increase by on 
                    each iteration.
