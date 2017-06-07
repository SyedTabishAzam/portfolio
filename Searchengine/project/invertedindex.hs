import Control.Monad
import System.IO 
import Prelude hiding (head)
import qualified Text.Blaze.Html4.Strict as B
import Text.Blaze.Renderer.Text
import qualified Data.Text.Lazy.IO as T
import Text.Blaze.Html5.Attributes
import Data.List
import qualified Data.Text as D
import System.Environment
import System.IO.Error
import Data.Char
import System.IO.Unsafe
import Data.Function
import Web.Browser (openBrowser)
import System.Directory
--loads all the modules



------------------------------------------------------------Inverted document creator-----------------------------------------------
inverted doc=do
	all <- getDirectoryContents doc --receives the location of archived location
	let files = [y | y<-all , (isInfixOf "." y ==True), y/=".", y/=".."] --returns all the files in the directory, and exclude folders and ".."
	ls <- forM files (\a -> do	--apply the function to every file
		handle<-openFile (doc++a) ReadMode --open every file from file path
		contents <- hGetContents handle	--get its contents in contents
		let purify = filter (not . null )[[x | x<-b, x `elem` ['a'..'z'] || x `elem` ['A'..'Z']] | b<-words contents, (length b) < 10] --only keep pure words i.e no punctuation and special characters
		let parsed = nub $ [[toLower y | y<-x] | x<-purify]	--split the file according to its words, and just keeps small letters
		return $ indexi parsed a)
	writeFile "inverted.txt" (show (length files)) --write document count on first line of file
	appendFile "inverted.txt" "\n"
	appendFile "inverted.txt" doc
	writeTo (nub $ breakdown (sortBy (compare `on` fst) (concat ls)))	--write the unique copy of terms in inverted index along with list of documents 
	
--checks the list for the terms that appeared, and concatenate it in a single list , occurrence of single instance of term
breakdown::[(String,String)]->[(String,[String])]
breakdown ls =  [ (fst y, [snd x | x<-ls, fst x == fst y] ) | y<-ls]

--function to write to inverted index in a specific format (in advance version, this would be changed to xml)
writeTo::[(String,[String])]->IO()
writeTo ls = forM_ ls (\a -> do
	print $ ("Adding " ++ (fst a) ++ " To list") 
	appendFile "inverted.txt" ("\n")
	appendFile "inverted.txt" (fst a) --adds first element (term ) to list
	appendFile "inverted.txt" " = {" --adds space and { after the term
	forM_ (snd a) (\b -> do
		appendFile "inverted.txt" ""
		appendFile "inverted.txt" b	--adds the list of documents to the list 
		appendFile "inverted.txt" ""
		if b /= last (snd a) then appendFile "inverted.txt" " " else appendFile "inverted.txt" "")
	appendFile "inverted.txt" "}") --closes the curly brackets
	

	
--takes a term list, and document name, and returns term document list
indexi::[String]->String->[(String,String)]
indexi ls doc = [(x,doc) | x<-ls]

--checks the list. if first element of list is found,
look::String->[(String,[String])]->[String]
look _ [] = []
look st ls
	|(st==fst (head ls)) = snd(head ls)
	| otherwise= look st (tail ls)

--------------------------------------------------------Searching the term---------------------------------------------------
------ search the query. if error occurs, throw exception
searchquery term = do 
	if (unsafePerformIO (doesFileExist "searchresult.html")) then removeFile "searchresult.html" else return () --overrights previous searchresult.html
	toTry ([[toLower y | y<-x] | x<-(words term)]) `catchIOError` handler --converts query to small letters, and pass it
	openBrowser "searchresult.html" --opens the web browser if file found, and show the result in browser
	
----trying to search
toTry query = do
	handle <- openFile "inverted.txt" ReadMode -- open the inverted document file
	totaldoc <- hGetLine handle
	let doccount = (read totaldoc :: Int)  --first line of the index is document count
	archivedir <- hGetLine handle
	let direc = archivedir	--second line of index contains the archive directory
	contents <- hGetContents handle
	let p1 = concat [[x | x<-(lines contents), isPrefixOf y x] | y<-query]	--p1 contains the lines that has  query as prefix
	let p2 = [((takeWhile (/=' ') x) , words (takeWhile (/='}') (dropWhile (not.isAlpha) (dropWhile (/='{') x))) ) | x<-p1] -- p2 contains (word, [documents]) list
	ret <- forM query (\term -> do --every searched term is applied the function
		print $ "Calculating tf idf of " ++ term
		return $ tfidf (look term p2) direc term doccount) --if search term is in p2, then tfidf is calculated
	print $ "Adding total score"
	let result = reverse (sortBy (compare `on` snd) (addscore (concat ret))) --result is produced on basis of tfidf score
	if (length result == 0) then print $ "Nothing Found" else T.writeFile "searchresult.html" (renderHtml (draw direc query [(fst x,snd x)| x<-result])) --result is printed if found
	--result is in the format of ("document: tfidf score")

--writing the result to HTML file 
draw direc qu xs = B.html $ do
    B.head $ B.title (B.text (D.pack "Search Result"))
    B.body $ do
		B.h1  (B.text (D.pack ("Showing results for '" ++unwords qu ++ "'")))
		B.table (do forM_ xs (\(f,l)-> B.html $ do B.tr $ do (createcolumn direc f)))
				
        
        

createcolumn direc f = B.html $ do
	B.td (B.a B.! href (B.stringValue (direc ++ f)) $ (B.text (D.pack ([(toUpper (head f))] ++ (tail f)) ))) 
				

	

--score of all different term's tfidf is added 
addscore [] = []
addscore ls = [(fst (head ls),(totalscore (fst (head ls)) (ls)))] ++ addscore ([x | x<-(tail ls) , (fst x)/=(fst (head ls))])

--helper function for addscore , adds the respective scores	
totalscore _ [] = 0	
totalscore doc ls
	| doc == (fst (head ls)) = snd (head ls) + (totalscore doc (tail ls))
	| otherwise = (totalscore doc (tail ls))


-------------------------------------------------------------Tf IDF Calculator---------------------------------------------

--tf idf of every term in query is calculated
tfidf::[String]->String->String->Int->[(String,Float)]
tfidf ls direc term len= [ (x,(unsafePerformIO (tf term (direc++x)))*(idf len (length ls))) | x<-ls] 


lookfreq::String->[(String,Int)]->Int
lookfreq _ [] = 0
lookfreq st ls
	| (st==fst (head ls)) = snd(head ls)
	| otherwise= lookfreq st (tail ls)
	
--tf (Term frequency calculator)
tf :: Num b => String -> FilePath -> IO b
tf term doc = do 
	print $ "Finding frequency of '" ++ term ++ "' in " ++ doc
	handle <- openFile doc ReadMode
	contents <- hGetContents handle
	let e1 = words contents
	return (fromInteger (toInteger (lookfreq term (wordfrequency e1)))) --term frequency in the document is returned

--idf calculator
idf::Int->Int->Float
idf n td = logBase 10 (fromInteger (toInteger n) / fromInteger (toInteger td)) --log base 10 (N/TD) where n is number of documents and td is number of documents where t appears

--error handler
handler :: IOError -> IO ()  
handler e = putStrLn "IO Error"

--returns the word along with their frequency in the list
wordfrequency::[String]->[(String,Int)]
wordfrequency [] = []
wordfrequency ls = [(head ls,(count (head ls) (tail ls)))] ++ wordfrequency ([x | x<-(tail ls) , x/=(head ls)])

--helper function for word frequency, returns the count of word in list
count a ls = length ([x | x<-ls, x==a]) + 1

