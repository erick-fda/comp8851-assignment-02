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
1.)
    The response to this question can be found at 
        ./COMP8851_Asg02_A00925871/Question01/

2.)
    The response to this question can be found at 
        ./COMP8851_Asg02_A00925871/Question02/

3.)
    The response to this question can be found at 
        ./COMP8851_Asg02_A00925871/Question03/

4.)
    The response to this question can be found at 
        ./COMP8851_Asg02_A00925871/Question04/

5.)
    The response to this question can be found at 
        ./COMP8851_Asg02_A00925871/Question05/

6.)
    The response to this question can be found at 
        ./COMP8851_Asg02_A00925871/Question06/

7.)
    The response to this question can be found at 
        ./COMP8851_Asg02_A00925871/Question07/

8.)
    a.)
        An O(N^2) algorithm for this problem would be to add every given number to every 
        other given number and see whether the result is K, returning true as soon as a 
        valid pair is found.

    b.)
        An O(NlogN) algorithm for this problem would be to first sort the array using one 
        of several existing O(NlogN) sorting algorithms (such as std::sort() in C++).

        Then for each item x in the array, use a binary search to see whether K-x exists 
        in the array.

    c.)
        The response to this question can be found at 
        ./COMP8851_Asg02_A00925871/Question09/

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

        This suggests that if there is a good chance of a match, the O(N^2) algorithm may 
        have a better *average* performance (thought a worse worst-case performance).
        
9.)
    The response to this question can be found at 
        ./COMP8851_Asg02_A00925871/Question09/

10.)
    The response to this question can be found at 
        ./COMP8851_Asg02_A00925871/Question10/
    