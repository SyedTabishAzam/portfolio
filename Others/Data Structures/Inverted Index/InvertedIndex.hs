--import Data.List

data BoolIndex = BoolIndex { word :: [[Char]] , 
							indexx :: [[Integer]]
							} deriving (Show)

type Doc = [[Char]]

--returns the list that contains unique words and no stop words
preprocess::Doc->Doc->Doc
preprocess dc sw = [x | x<-uniq dc, (x `elem` sw)==False] --uniq dc is the unique list, and (x `elem` sw) ensures that it isnt in stop word list




--builds index for given documents
buildIndex::[Doc]->Doc->BoolIndex
buildIndex ls sw = BoolIndex (uniq (concat uniquelist)) [mat y uniquelist | y <- uniq (concat uniquelist)] --creates a unique list of words, and checks if each word occurs in each document
	where uniquelist = map (`preprocess` sw) ls --preprocess the documents
	
--helper function
mat::String->[Doc]->[Integer]
mat _ [] = []
mat a ls
	| (a `elem` (head ls)) = [1] ++ mat a (tail ls) --if a word occurs in list of words of document, append[1]
	| otherwise = [0] ++ mat a (tail ls) --else append 0, do this till empty list is reached

--adds the document to index
addDoctoIndex::Doc->BoolIndex->BoolIndex
addDoctoIndex a ls = BoolIndex (uniq((concat [words x | x<-a])++(word ls))) (zipWith (++) (indexx ls) ([check y (concat [words x | x<- a]) | y<-(uniq((concat [words x | x<- a])++(word ls)))]))
--joins the previous word list with list of new doucments, and performs the function of ++ for every previous index
--appends [1] if term appears in new document, otherwise appends [0]


--helper function to check if a term appears in document
check::String->Doc->[Integer]
check y a
	| (y `elem` a) = [1]
	| otherwise = [0]

--function to add word to bool index
addWordToIndex::[Char]->BoolIndex->BoolIndex
addWordToIndex a ls
	| (findx a (word ls) == -1) = BoolIndex ((word ls)++[a]) ((indexx ls )++ [(take (length (head (indexx ls))) (repeat 0))])
--if word is not already there, add the word to end of word list, and add the row of all 0's in matrix


--finds the element in the list
findx::(Eq a)=>a->[a]->Int
findx a ls
	| ((a `elem` ls) == False) = -1 --if elements isnt in list, return -1
	| a == (head ls) = 0
	| otherwise = 1 + (findx a (tail ls))

--Returns the unique elements in the list
uniq::(Eq a)=>[a]->[a]
uniq [] = []
uniq ls
	| ((head ls) `elem` (tail ls)) =  uniq (tail ls)
	| otherwise = [(head ls)] ++ uniq (tail ls)

--uniq ls = nub ls is another implementation through Data.List of uniq ls


