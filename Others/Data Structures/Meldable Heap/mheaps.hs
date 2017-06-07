import Data.Bits
a = Node 35 Nil Nil

data MeldableHeap a = Node a ( MeldableHeap a) ( MeldableHeap a) | Nil deriving(Show,Eq)



bitwiseAnd::(Bits a)=>a->a->a
bitwiseAnd a b = (.&.) a b

mergeHeaps::(Num a,Ord a,Bits a)=> MeldableHeap a-> MeldableHeap a-> MeldableHeap a
mergeHeaps Nil h2 = h2	--if h1 is NIL then return h2, and vice versa for h2
mergeHeaps h1 Nil = h1
mergeHeaps h1@(Node nh1 lh1 rh1) h2@(Node nh2 lh2 rh2)
	| nh1 > nh2 = mergeHeaps h2 h1	--if h1 value is greater than h2 value, then swap the trees 
	| ((bitwiseAnd nh1 nh2) == 0) = Node nh1 (mergeHeaps lh1 h2) rh1	--bitwise nh1 nh2. this produces any number that is used as random. if that is the case, then mergeheap with left tree
	| otherwise = Node nh1 lh1 (mergeHeaps rh1 h2)	--otherwise with right tree


addHeap::(Num a,Ord a, Bits a)=> a->MeldableHeap a->MeldableHeap a
addHeap x ht = mergeHeaps (Node x Nil Nil) ht  --creates a new node with value of x and adds to the tree

removeHeap::(Ord a, Bits a, Num a)=> MeldableHeap a-> MeldableHeap a
removeHeap (Node x lc rc) = mergeHeaps lc rc	--removes the root, and mergeHeaps the roots left and right trees

heapSort::(Ord a, Num a, Bits a)=>[a]->[a]
heapSort ls = heapRemove (heapAdd ls)	--heap sort basically calls two helpers, heapAdd adds elements to tree from list, while heapRemove extract elements from trees as list

heapAdd::(Ord a,Num a, Bits a)=>[a]->MeldableHeap a
heapAdd [] = Nil	--if list is empty return Nul
heapAdd ls = addHeap (head ls) (heapAdd (tail ls))	--otherwise add to the tree, the head of list, and recurse on the tail of list

heapRemove::(Ord a,Num a,Bits a)=>MeldableHeap a->[a]
heapRemove Nil = []	--if tree is empty, return empty list
heapRemove (Node r lt rt) = [r] ++ heapRemove (mergeHeaps lt rt) -- add the root value of tree to list, and recurs on remaining list