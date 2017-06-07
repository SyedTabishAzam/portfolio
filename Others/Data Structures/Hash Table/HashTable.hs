type HashTable = (Int,[[Int]])


--initializes hash table, creates empty lists inside the list depending on the dimension of table
initHashTable::Int->HashTable
initHashTable a = (2^a,(replicate (2^a) []))

--returns the dimension of hash table
dimension::HashTable->Int
dimension (a,_)=a

--returns the stored keys of the hash table
keys::HashTable->[Int]
keys (_,[ls]) = ls

--returns the number of elements in the hash table
keyCount::HashTable->Int
keyCount d = length (helper(snd d))

--finds a particular key in the table
find::HashTable->Int->[Int]
find (_,[]) k = [] 
find hs@(x,a) k
	| k `elem` head a = [k]
	| otherwise = find (x,tail a) k

--Hashing algorithm to hash any key to its index
hash::HashTable->Int->Int
hash ht a = (z*a) `div` (2^(32-(dimension ht))) 
	where
	z = 4 --random number
	
--normal add. adds a key to hash table using the hash generator function above
add::HashTable->Int->HashTable
add p k = (fst p,(take (hash p k) (snd p) ++ [(snd p !! (hash p k))++[k]] ++ drop ((hash p k)+1) (snd p)))

--removes a key from the hash table using the hash generator
sub::HashTable->Int->HashTable
sub p k = (fst p,(take (hash p k) (snd p) ++ [[x| x<-((snd p) !! (hash p k)), x/= k]] ++ drop ((hash p k)+1) (snd p)))

--a function used to copy items from one hashtable to another using the updated hash generator
rehash::HashTable->HashTable->HashTable
rehash h h1 = help2 h1 (helper(snd h))	--sends the argument (hash table in which elements has to be copied, and all elements of orignal hash table) to help2
	where
	help2 h@(d,_) [] = initHashTable d --if help2 recieves empty list, it generates a new hash table
	help2 h ls =  add (help2 h (init ls)) (last ls)	--otherwise, it adds every element of the list to new hash table 
	
	
helper::[[Int]]->[Int]
helper [] = []
helper ls = head ls ++ helper (tail ls)	--helper function, that returns all the elements of list within the list

insert::HashTable->Int->HashTable
insert ht k = if ((keyCount ht)==(dimension ht)) then add (rehash ht (initHashTable (2*(dimension ht)))) k else add ht k	--if the keycount reaches the dimension, increase the size of hashtable (by creating a new hash table)

remove::HashTable->Int->HashTable
remove ht k = if(((keyCount ht)) == ((dimension ht) `div` 3)) then rehash (sub ht k) (initHashTable ((dimension ht) `div` 3))  else sub ht k --if the size is reduced to one third of dimensions size, then create a new hash table of this size and store items to it