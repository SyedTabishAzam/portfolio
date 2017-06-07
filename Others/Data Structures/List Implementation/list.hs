b=[2,3,4,5,5,11,7,9]
areverse::(Ord a)=> [a] -> [a]
areverse ls
    |ls == [] = []
    |otherwise =(areverse xs) ++ [x]
	where (x:_) = ls
	      (_:xs) = ls

bmaximum::(Ord a)=>[a] -> a
bmaximum (x:xs)
	|xs == [] = x
	|x > xst = x
	|otherwise = xst
	where xst = bmaximum xs
		  
ckthelement::(Ord a, Real a)=>[a]->a->a
ckthelement ls k
	| ls==[]= error "Error"
	| k==0 = x
	| otherwise= (ckthelement xs (k-1))
	where (x:xs) = ls

duniqueelement::(Ord a)=>[a]->[a]
duniqueelement ls
	| length ls == 1 = ls
	| x `elem` xs = duniqueelement xs
	| otherwise = [x] ++ duniqueelement xs
	where (x:xs) = ls

eun ls = euniquewtihfreq (duniqueelement ls) ls

--euniquewtihfreq::(Ord a)=>[a]->[(a,a)]
euniquewtihfreq [] [] = []
euniquewtihfreq un ls  
	|	(length un == 1) = [(head un,checkfreq ls (head un))]
	|   otherwise = [(head un, checkfreq ls (head un))] ++ (euniquewtihfreq (tail un) ls)
		

--checkfreq::(Ord a)=>[a]->a->a
checkfreq ls e
	|(length ls == 0) =0
	| (e==(head ls)) = 1 + checkfreq(tail ls) e
	| otherwise = 0 + checkfreq(tail ls) e
	