data Tree a = EmptyTree | Node{nvalue::(a) ,left::(Tree a) ,right::(Tree a)} deriving(Show,Ord,Eq)


depth::(Num a,Ord a)=> a-> Tree a-> a
depth x (Node r lt rt)
	| (x == r) = 0
	| (x<r) = 1 + depth x lt
	| otherwise = 1 + depth x rt

treeheight::(Num a,Ord a)=> Tree a-> a
treeheight EmptyTree = -1
treeheight (Node r lt rt) = max (treeheight lt) (treeheight rt) + 1

height::(Ord a,Num a)=>Tree a->a->a
height bs x = (treeheight bs) - (depth x bs)

postfix::(Ord a, Num a)=>Tree a->[a]
postfix EmptyTree = []
postfix (Node r lt rt)
	| otherwise = postfix lt ++ postfix rt ++ [r]

data BST a = EmptyBST | Nodebs{bsnvalue::(a) ,bsleft::(BST a) ,bsright::(BST a)} deriving(Show,Ord,Eq)

a = EmptyBST 
b= bstInsert 5 a
d = bstInsert 8 b
h = bstInsert 6 d
i = bstInsert 7 h
j = bstInsert 9 i
k = bstInsert 10 j

bstInsert :: (Ord a) => a -> BST a -> BST a
bstInsert a EmptyBST = Nodebs a EmptyBST EmptyBST 
bstInsert a (Nodebs x lt rt) 
	| ( a > x ) = Nodebs (x) lt (bstInsert a rt)
	| otherwise = Nodebs (x) (bstInsert a lt) rt


bstFind :: (Ord a)=> a-> BST a-> Bool
bstFind a EmptyBST = False
bstFind a (Nodebs x lt rt)
	| a==x = True
	| otherwise = (bstFind a lt) || (bstFind a rt) 
	
bstRemove :: (Ord a) => a -> BST a-> BST a
bstRemove p EmptyBST = EmptyBST 
bstRemove p (Nodebs x lt rt)	
	| (p<x) = Nodebs x (bstRemove p lt) rt
	| (p>x) = Nodebs x lt (bstRemove p rt)
	| (p==x && lt==EmptyBST && rt==EmptyBST) = EmptyBST 
	| (p==x) && (lt==EmptyBST) = rt 
	| (p==x) && (rt==EmptyBST) = lt
	| otherwise = Nodebs (minnode rt) lt (bstRemove (minnode rt) rt)

minnode :: (Ord a)=>BST a->a
minnode (Nodebs a EmptyBST EmptyBST) =a
minnode (Nodebs a lt rt)
	| lt /= EmptyBST = minnode lt
	| otherwise = min a (minnode rt)
	