# Fibonacci-Heap

<h2> Introduction </h2>

A Fibonacci heap is a heap data structure similar to the binomial heap, only with a few modifications and a looser structure. The Fibonacci heap was designed in order to improve Dijkstra’s shortest path algorithm from O(m logn)O(m logn) to O(m + nlogn)O(m + nlogn) by optimising the operations used most by the algorithm. Its name derives from the fact that the Fibonacci sequence is used in the complexity analysis of its operations.

<h2> Structure and Time Complexity </h2>

Like the binomial heap, a Fibonacci heap is a collection of heap-ordered trees. They do not need to be binomial trees however, this is where the relaxation of some of the binomial heap’s properties comes in.

Each tree has an order just like the binomial heap that is based on the number of children. Nodes within a Fibonacci heap can be removed from their tree without restructuring them, so the order does not necessarily indicate the maximum height of the tree or number of nodes it contains.


![image](https://user-images.githubusercontent.com/101597846/170057023-e0a562a8-e167-4e75-8868-73e64539190c.png)


![image](https://user-images.githubusercontent.com/101597846/170062073-d05b9758-f198-40fa-9932-f1a6d6e1b66f.png)


<h3> Links </h3>

The pointers between nodes in a Fibonacci heap are very similar to that of the binomial heap, only that each node in a Fibonacci heap contains a doubly linked list of all its children. This allows node removal and child list concatenation to both be performed in linear time. The child node whose parent links to it is always the node with the smallest value among its siblings.

![image](https://user-images.githubusercontent.com/101597846/170057482-90225467-e5c4-490c-b806-33a3adef1435.png)


<h2> Methods </h2>

<font size = "100"> **1. Insertion** </font>

Insertion creates a new tree containing only the new node which is being added to the heap. The total number of nodes in the tree is incremented and the pointer to the minimum value is updated if necessary.

![image](https://user-images.githubusercontent.com/101597846/170057901-34afcc9e-f6fb-40c6-8836-805a34f308cd.png)


<font size = 100>**2. Union**</font>

Union concatenates the root lists of two Fibonacci heaps and sets the minimum node to which ever tree’s minimum node is smaller.
Union of two Fibonacci heaps H1 and H2 can be accomplished as follows: 


```
1) Join root lists of Fibonacci heaps H1 and H2 and make a single Fibonacci heap H.
2) If H1(min) < H2(min) then: 
		H(min) = H1(min).
3) Else: 
    H(min) = H2(min).
```

<font size = 100>**3. Decrease key**</font>

Decrease key lowers the key of a node. The node is then cut from the tree, joining the root list as its own tree. The parent of the node is then cut if it is marked, this continues for each anscestor until a parent that is not marked is encountered, which is then marked. The pointer to the minimum node is then updated if the node’s new value is less than the current minimum.

<font size = 100>**4. Extract minimum**</font>

Extract minimum is the most complex operation of a Fibonacci Heap as it’s where the actions that were deferred by the other operations occur. It starts by removing the minimum node from the root list and adding its children to the root list.

![image](https://user-images.githubusercontent.com/101597846/170060160-68dddfcf-f700-450a-bdb0-82da1057e081.png)




![image](https://user-images.githubusercontent.com/101597846/170060278-76977f67-ce73-4cc6-a45b-676f1fd549be.png)




![image](https://user-images.githubusercontent.com/101597846/170060419-0473f9de-53c9-4978-abfb-ab8d56ead7a5.png)




![image](https://user-images.githubusercontent.com/101597846/170060489-6daa5089-0e3c-4aad-bd7e-e480c8c4c4fa.png)




![image](https://user-images.githubusercontent.com/101597846/170060527-7ebba766-1eb9-46f9-beba-0c418f95520c.png)


If the minimum was the only node in the root list, the pointer to the minimum node is set to the smallest node in the root list and the operation is completed.

If not, the ‘consolidate’ operation is performed which merges all trees of the same order together until there are no two trees of the same order. The minimum is then set to the smallest node in the root list.

<font size = 100>**5. Delete**</font>

Delete is performed by calling decrease key to reduce the node to negative infinity which pulls the node to the top of the tree. Extract minimum is then called on the node to remove it from the heap.
