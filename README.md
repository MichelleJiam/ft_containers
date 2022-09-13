# ft_containers
42/Codam deep dive into standard C++ containers.

## Description
Reimplementing STL containers: `vector`, `stack`, `map`, and `set`.  
This includes all member and non-member functions and overloads, and also iterator systems.  
Inner data structures should be appropriate to the container.  
I therefore also reimplemented a [Red-Black tree](https://www.programiz.com/dsa/red-black-tree) class (complete with iterator and nodes) for use with `map` and `set`, as is done by the [STL](https://github.com/gcc-mirror/gcc/blob/d89fa97ff318b1f892e2629c5a249313872a01b1/libstdc%2B%2B-v3/include/bits/stl_map.h#L152).

### Red-Black Tree
I followed the implementation of Red-Black Trees as described in "Introduction to Algorithms" (3rd ed.) by Cormen et al.  
A RB tree differs from a regular binary search tree by having 1 extra attribute in its nodes: colour, which is either red or black.  
This property and the constraints surrounding it ensure that a RB tree is approximately balanced and require less rotations (compared to say AVL trees).

My RB tree also makes use of a single [sentinel node](https://stackoverflow.com/questions/25068106/red-black-tree-insert-implementation-what-is-a-sentinel/25068229) instead of a nullptr to simplify handling of last and root nodes (as we can treat the sentinel node like a normal node).

The tree is therefore somewhat circular, as both the root's parent and the leaves child points to the single sentinel.
| ![RB tree diagrams](https://i.imgur.com/1rRUCb9.png) |
|:--:|
| <b>(a) conventional RB tree (b) RB tree using single sentinel node

## Compilation
I've included extensive test files that compare my implementation of the containers against the STL ones.  
Each function of the containers is tested against its STL version.  
I also apply "stress tests" that utilize large container sizes to test complexity.  
The compilation commands below will create 2 binaries - one compiled with my library "ft" and one compiled with the STL.

**Build**  
Run `make` in the root directory to compile the test files with the container library headers.  
This will compile with stress tests included (see above).  
Binaries `ft_bin` and `std_bin` may then be executed to see behaviour of respective libraries.  

For compiling **without** stress tests:  
`make quick`

**Quick Build-n-Run**  
```
make run    # runs simple output comparison using diff, ignores performance
make compare    # detailed comparison program that shows output and performance differences
make qcompare    # same as above but without stress test, faster
```

Output of binary compiled by `make`             |  Output of `make qcompare`
:-------------------------:|:-------------------------:
![](https://i.imgur.com/763Gaju.png?2)  |  ![](https://i.imgur.com/kOgLZWb.png?2)

## Resources
General:
- [C++ Primer](https://github.com/yanshengjia/cpp-playground/blob/master/cpp-primer/resource/C%2B%2B%20Primer%20(5th%20Edition).pdf)  

Vector:
- [How a vector grows exponentially](https://stackoverflow.com/questions/5232198/how-does-the-capacity-of-stdvector-grow-automatically-what-is-the-rate)  

SFINAE:
- [Explanation of enable-if and SFINAE from More C++ Idioms](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/enable-if)  

Red-Black Tree:
- [Introduction to RB Trees](https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2)
- [Explanation of Insertion with Diagrams](https://www.geeksforgeeks.org/red-black-tree-set-2-insert)
- [Breakdown of insert/delete/rebalance algorithms](https://www.programiz.com/dsa/red-black-tree)
- [Chapter 13 of Introduction to Algorithms, 3rd edition](https://edutechlearners.com/download/Introduction_to_algorithms-3rd%20Edition.pdf)
- [RB iterator in/decrement source code](https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-3.4/tree_8cc-source.html)  

Sentinel nodes in binary search trees:
- [Introduction to Algorithms, page 309](https://edutechlearners.com/download/Introduction_to_algorithms-3rd%20Edition.pdf)

Rebind:
- [What does template rebind do](https://stackoverflow.com/questions/14148756/what-does-template-rebind-do)
- [Using rebind for node allocation](https://stackoverflow.com/questions/4062503/stl-allocator-copy-constructor-of-other-type-rebind)  
