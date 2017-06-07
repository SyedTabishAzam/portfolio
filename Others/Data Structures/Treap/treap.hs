data Treap k a = EmptyTreap | Node k a (Treap k a) (Treap k a) deriving (Show)

leftRotate:: (Treap k a) -> (Treap k a)
leftRotate (Node k a l (Node rk ra rl rr))= Node rk ra(Node k a l rl) rr
leftRotate t =t

rightRotate::(Treap k a) -> (Treap k a)
rightRotate (Node k a (Node lk la ll lr) r)= Node lk la ll (Node k a lr r)
rightRotate t =t  


