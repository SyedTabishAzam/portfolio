
data C = R | B deriving Show		--Data type for color
data RB a = EmptyRb| Node C a (RB a) (RB a) deriving Show	--Data type for RB tree (Color Value (left tree) (Right tree))


insert :: (Ord a) => a -> RB a -> RB a	--insert takes as argument a number to be added to the tree, and a tree
insert x s = Node B z a b		--naming the number as x, and the tree as s. Returning a new Node that is of color B
	where
	Node _ z a b = ins s		--ins is a helper function that checks the status of the tree
	ins EmptyRb= Node R x EmptyRb EmptyRb --if tree is empty, that means new value to be added is the root. Color the root Red and add x as the value of it
	ins s@(Node B y a b)		--otherwise, if the tree's root is B, 
		| x<y = fix y (ins a) b	--and x is the lesser value of x, then fix the current tree's children and insert recursively x to left tree of current tree
		| x>y = fix y a (ins b)	
		| otherwise = s	--return the current tree if x equals y (already added node)
	ins s@(Node R y a b)		--else if the tree root is red
		| x<y = Node R y (ins a) b	-- x is lesser then root value, insert x in left tree
		| x>y = Node R y a (ins b)
		| otherwise = s



--help taken from internet, because i have implemented the code using a parent node, so doing it again was tedious, but i understand each and every part of it
fix :: a->RB a -> RB a -> RB a
fix y (Node R x a b) (Node R z c d) = Node R y (Node B x a b) (Node B z c d)
fix z (Node R y (Node R x a b) c) d = Node R y (Node B x a b) (Node B z c d)
fix z (Node R x a (Node R y b c)) d = Node R y (Node B x a b) (Node B z c d)
fix x a (Node R y b (Node R z c d)) = Node R y (Node B x a b) (Node B z c d)
fix x a (Node R z (Node R y b c) d) = Node R y (Node B x a b) (Node B z c d)
fix x a b = Node B x a b
	
	