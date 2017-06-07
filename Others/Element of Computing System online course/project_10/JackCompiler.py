import sys
import shlex
from pathlib import Path

class JackTokenizer(object):
    '''Removes all comments and white space from the input stream and
    breaks it into Jack-language tokens, as specified by the Jack
    grammar.'''
    
    def __init__(self,inputFile):
        '''Constructor - Opens inputFile and gets ready to tokenize it.'''
        KEYWORD          = ['class','constructor','function','method','field','static','var','int,'
        'char','boolean','void','true','false','null','this','let','do','if','else','while','return']
        SYMBOL           = ['[','(',')','{','}','[','\\',']','.',',',';','+','\\','-','*','/','&','|','<','>','=','~',']']
        self.SYMBOL = SYMBOL
        self.KEYWORD = KEYWORD
        letters = "a b c d e f g h i j k l m n o p q r s t u v w x y z"
        digits="1 2 3 4 5 6 7 8 9"
        self.letters = letters.split()
        self.digits = digits.split()
        

        v=""
        
        file1 = open(inputFile,"r")
        self.file1 = file1.readlines()
        for line in self.file1:
            if "//" in line.strip():
                cmntindex = line.find("//")
                endit = line[cmntindex:]
                cmnltess = line.replace(endit,"")
            elif "/*" in line.strip():
                cmnltess = line.replace(line[line.find("/*"):],"")
            elif line.strip().startswith("*"):
                cmnltess = ""
            else:
                cmnltess = line.strip()
            v= v + cmnltess + " "
        
        for x in SYMBOL:
            if x in v:
                
                rw = " "+ x + " "
                v=v.replace(x,rw,v.find(x))
        v= v.replace("  "," ")
        tokens = shlex.split(v,False,False)
        self.tokens = tokens
        
        pass
    
    def hasMoreTokens(self):
        '''JT.hasMoreTokens() -> bool

        Returns True if there are more tokens left, False otherwise.'''
        
        return bool(self.tokens)
        pass
    
    def advance(self):
        '''JT.advance() -> None

        Gets the next token from the input and makes it the current
        token. Should only be called if hasmoreTokens() is
        True. Initially there is no current token
        '''
        if self.hasMoreTokens() == True:
            self.currenttoken = self.tokens.pop(0)
        
        
    def tokenType(self):
        '''JT.tokenType() -> str

        Returns the type of the current token which is one of:
        KEYWORD
        SYMBOL
        IDENTIFIER
        INT_CONST
        STRING_CONST
        '''
        
        if self.currenttoken in self.KEYWORD:
            return "KEYWORD"
        elif self.currenttoken in self.SYMBOL:
            return "SYMBOL"
        elif self.rec(self.currenttoken)==True :
            return "IDENTIFIER"
        elif self.currenttoken.isdigit() == True and (int(self.currenttoken)<32767):
            return "INT_CONST"
        elif self.currenttoken[0]=='"' and self.currenttoken[-1]=='"':
            return "STRING_CONST"
    
        
        pass
    def rec(self,j):
        ''' A function defined to implement the rule of identifier'''
        digits = self.digits
        letters = self.letters
        if j == "":
            return False
        x = j[0].lower()
        return  (x in letters and self.rec(j[1:])) or (x =="_" and self.rec(j[1:])) or \
               (x in letters and x in digits) or (x =="_" and x in digits) or (self.rec(j[:-1]) and x in digits) or (x=="_") or (x in letters)
        
    def keyWord(self):
        '''JT.keyWord() -> str

        Returns the keyword which is the current token. Should be
        called only when tokentype() is KEYWORD. Return value is one of:
        CLASS, METHOD, FUNCTION, CONSTRUCTOR, INT,
        BOOLEAN, CHAR, VOID, VAR, STATIC, 'FIELD, LET,
        DO, IF, ELSE, WHILE, RETURN, TRUE, FALSE,
        NULL, THIS
        '''
        return self.currenttoken
        
        pass
    
    def symbol(self):
        '''JT.symbol() -> str

        Returns the character which is the current token. Should be
        called only when tokentype() is SYMBOL.
        '''
        
        return self.currenttoken
        pass
    
    def identifier(self):
        '''JT.identifier() -> str

        Returns the identifier which is the current token. Should be
        called only when tokenType() is IDENTIFIER.
        
        '''
        return self.currenttoken
        pass
    
    def intVal(self):
        '''JT.intVal() -> int

        Returns the integer value of the current token. Should be
        called only when tokenType() is INT_CONST.
        '''
        return self.currenttoken
        pass
    
    def stringVal(self):
        '''JT.stringVal() -> str

        Returns the string value of the current token, without double
        quotes. Should be called only when TokenType() is
        STRING_CONST.
        '''
        
        return self.currenttoken[1:-1]
        pass
    
class CompilationEngine(object):
    '''Effects the actual compilation output. Gets its input from a
    JackTokenizer and emits its parsed structure into an output file.
    '''

    def __init__(self,inputFile,outputFile):
        '''Constructor - Creates a new compilation engine with inputFile and
        outputFile. The next method called must be compileClass().
        '''
        self.outputFile = open(outputFile,"w")
        ifile = open(inputFile,"r")
        self.ifile = ifile.readlines()
        
        self.writing = ""
        self.c = 0
        self.funcflag= False
        pass
    
    def compileClass(self):
        '''CE.compileClass() -> None

        Compiles a complete class.'''
        self.outputFile.write('<class>' + "\n")
        self.line = self.ifile.pop(0)
        self.line = self.ifile.pop(0)
        self.outputFile.write(self.line)
        self.outputFile.write(self.ifile.pop(0))
        self.outputFile.write(self.ifile.pop(0))
        self.line=self.ifile.pop(0)

        
        while ("static" in self.line) or ("field" in self.line):
            
            self.compileClassVarDec()
       
        while ("constructor" in self.line) or ("function" in self.line) or ("method" in self.line):
            
            self.compileSubroutine()

        
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputFile.write("</class>" + "\n")
        
        self.outputFile.close()        
        pass
    

    
    def compileClassVarDec(self):
        '''CE.compileClassVarDec() -> None
        
        Compiles a static declaration or a field declaration.
        '''
        self.outputfile.write("<classVarDec>"+"\n")
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        while "," in self.line:
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputfile.write("</classVarDec>"+"\n")

        pass

    def compileSubroutine(self):
        '''CE.compileSubroutine() -> None

        Compiles a complete method, function, or constructor.
        '''
        
        self.outputFile.write("<subroutineDec>" + "\n")
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        if "void" in self.line:
            
            self.outputFile.write(self.line)
        elif ("char" in self.line) or ("int" in self.line) or ("boolean" in self.line):
            self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.compileParameterList()
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        
        self.subroutineBody()
        self.outputFile.write("</subroutineDec>" + "\n")
        
    
        pass
    def subroutineBody(self):
        self.outputFile.write("<subroutineBody>" + "\n")
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        
        while "var" in self.line:
            self.outputFile.write("<var>" + "\n")
            
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
            while "," in self.line:
                self.outputFile.write(self.line)
                self.line = self.ifile.pop(0)
                self.outputFile.write(self.line)
                self.line = self.ifile.pop(0)
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
            self.outputFile.write("</var>" + "\n")
        self.compileStatements()
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        
        self.outputFile.write("</subroutineBody>" + "\n")
        
    def compileParameterList(self):
        '''CE.compileParameterList() -> None

        Compiles a (possible empty) parameter list not including the
        enclosing "()".
        '''
        self.outputFile.write("<parameterList>" + "\n")
   
        if ')' not in self.line:
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)  
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)  


        while ')' not in self.line:
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
          
        self.outputFile.write("</parameterList>" + "\n")        
        pass

    
    def compileVarDec(self):
        '''CE.compileVarDec() -> None

        Compiles a var declaration.
        '''
        ##this is done in subroutinebody due to bad structured skeletonfile recieved by a friend.
        pass

    def compileStatements(self):
        '''CE.compileStatements() -> None

        Compiles a sequence of statement not including the enclosing "{}".
        '''
        self.outputFile.write("<statements>" + "\n")
        while ("if" in self.line) or ("let" in self.line) or ("while" in self.line) or ("do" in self.line) or ("return" in self.line):
            self.c +=1
            
            if ("if" in self.line):
                self.compileIf()
            elif ("let" in self.line):
                self.compileLet()
            elif ("do" in self.line):
                self.compileDo()
            elif ("while" in self.line):
                self.compileWhile()
            elif ("return" in self.line):
                self.compileReturn()
        
        self.outputFile.write("</statements>" + "\n")    
        pass

    def compileDo(self):
        '''CE.compileDo() -> None

        Compiles a do statement.
        '''
        self.outputFile.write("<dostatement>" + "\n")
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        if "." in self.line:
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.compileExpressionList()
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputFile.write("</dostatement>" + "\n")
        
        pass

    def compileLet(self):
        '''CE.compileLet() -> None

        Compiles a let statement.
        '''
        self.outputFile.write("<letstatement>" + "\n")
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
       
        if "[" in self.line:
            
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
            self.compileExpression()
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.compileExpression()
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputFile.write("</letstatement>" + "\n")
        pass

    def compileWhile(self):
        '''CE.compileWhile() -> None

        Compiles a while statement.
        '''
        self.outputFile.write("<whileStatement>" + "\n")
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.compileExpression()
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.compileStatements()
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputFile.write("</whileStatement>" + "\n")
        pass
    
    def compileReturn(self):
        '''CE.compileReturn() -> None

        Compiles a return statement.
        '''
        self.outputFile.write("<returnStatement>" + "\n")
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        if not ";" in self.line:
            self.compileExpression()
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputFile.write("</returnStatement>" + "\n")
        pass
    
    def compileIf(self):
        '''CE.compileIf() -> None

        Compiles an if statement possibly with a trailing else clause.
        '''
        self.outputFile.write("<ifStatement>" + "\n")
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.compileExpression()
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        self.compileStatements()
        self.outputFile.write(self.line)
        self.line = self.ifile.pop(0)
        if "else" in self.line:
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
            self.compileStatements()
            self.outputFile.write(self.line)
            self.line=self.ifile.pop(0)
        self.outputFile.write("</ifStatement>" + "\n")
        
        pass
    
    def compileExpression(self):
        '''CE.compileExpression() -> None
        
        Compiles an expression.
        '''
        self.outputFile.write("<expression>" + "\n")
        self.compileTerm()
        op = ["+","-","*","/","&","|","<",">","="]
        while ("+" in self.line) or("-" in self.line) or ("*" in self.line) or(self.line.count("/")>1) or("&" in self.line) or("|" in self.line) or(self.line.count("<")>2) or(self.line.count("<")>2) or("=" in self.line):
                
                if (self.line.count("<")>2):
                        
                    self.line = "<SYMBOL>lt</SYMBOL>" + "\n"
                if self.line.count("<")>2:
                    print("yes")
                    self.line="<SYMBOL>gt</SYMBOL>" + "\n"
                self.outputFile.write(self.line)
                self.line=self.ifile.pop(0)
                self.compileTerm()
        self.outputFile.write("</expression>" + "\n")
        pass

    def compileTerm(self):
        '''CE.compileTerm() -> None

        Compiles a term. Uses lookahead to decide between alternative
        parsing rules. If the current token is an indentifier, a
        look=ahead token of "[", "(", or "." distinguish between a
        variable, array, and subroutine call. Any other token is not
        part of this term and should not be advanced over.
        '''
        ctlist = ["INT_CONSTANT","stringconstant","keywordconstant","varName","varName[expression]","subroutineCall","(expression)", "unaryOp"]
        self.outputFile.write("<term>" + "\n")
        if ("-" or "~") in self.line:
            
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
            self.compileTerm()
            
        elif "(" in self.line:
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
            self.compileExpression()
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
            
            
        else:
            self.outputFile.write(self.line)
            self.line = self.ifile.pop(0)
            
                
                
            if "[" in self.line:
                
                self.outputFile.write(self.line)
                self.line = self.ifile.pop(0)
                self.compileExpression()
                self.outputFile.write(self.line)
                self.line = self.ifile.pop(0)
                
            
            elif "." in self.line:
                
                self.outputFile.write(self.line)
                self.line = self.ifile.pop(0)
                self.outputFile.write(self.line)
                self.line = self.ifile.pop(0)
                self.outputFile.write(self.line)
                self.line = self.ifile.pop(0)
                self.compileExpressionList()
                self.outputFile.write(self.line)
                self.line = self.ifile.pop(0)
                
            elif "(" in self.line:
                
                self.outputFile.write(self.line)
                self.outputFile.write(self.ifile.pop(0))
                self.compileExpressionList()
                self.outputFile.write(self.line)
                self.outputFile.write(self.ifile.pop(0))
            
        
            
            
        self.outputFile.write("</term>" + "\n")
        
            
        
        pass

    def keycons(self,inp):
        keylist = ["true","false","null","this"]
        for x in keylist:
            if x in inp:
                return true
        pass
    
    def compileExpressionList(self):
        '''CE.compileExpressionList() -> None

        Compiles a (possibly empty) comma separated list of expressions.
        '''
        
        self.outputFile.write("<expressionList>" + "\n")
        
        if ")" not in self.line:
            
            self.compileExpression()

        while not ")" in self.line:
            self.outputFile.write(self.line)
            self.line=self.ifile.pop(0)
            self.compileExpression()
        self.outputFile.write("</expressionList>" + "\n")
            
##        if "(" in self.line:
##            self.outputFile.write(self.line)
##            self.compileExpression()
##            self.outputFile.write(self.line)
##            
##        if ("IDENTIFIER" in self.line) or ("STRING_CONST" in self.line) or (self.keycons(self.line)==True) or ("INT_CONST" in self.line):
##            self.outputFile.write(self.line)
##            self.line=self.ifile.pop(0)
##        if "[" in self.line:
##            self.outputFile.write(self.line)
##            self.line = self.ifile.pop(0)
##            self.compileExpression()
##            self.outputFile.write(self.line)
##        if "." in self.line:
##        
##            self.outputFile.write(self.line)
##            self.line = self.ifile.pop(0)
##            self.outputFile.write(self.line)
##            self.line = self.ifile.pop(0)
##            self.outputFile.write(self.line)
##            self.compileExpressionList()
##            self.line = self.ifile.pop(0)
##            self.outputFile.write(self.line)
##        if "(" in self.line:
##        
##            self.outputFile.write(self.line)
##            self.outputFile.write(self.ifile.pop(0))
##            self.compileExpressionList()
##            self.outputFile.write(self.line)
##    
##        
##        if ("-" or "~") in self.line:
##        
##            self.outputFile.write(self.line)
##            self.line = self.ifile.pop(0)
##            self.compileTerm()
##        self.line = self.ifile.pop(0)
##        
##        op = ["+","-","*","/","&","|","<",">","="]
##        
##        while ("+" in self.line) or("-" in self.line) or ("*" in self.line) or("/" in self.line) or("&" in self.line) or("|" in self.line) or("<" in self.line) or(">" in self.line) or("=" in self.file):
##              self.compileTerm()
##        while "," in self.line:
##            self.outputFile.write(self.line)
##            self.line=self.ifile.pop(0)
##            self.complieExpression()
        


    
        
def printUsage():
    '''printUsage() -> None
    
    Prints infomration on how to invoke this program.
    '''
    print("Usage: {} dir".format(sys.argv[0]))
    print("dir is the program directory - it contains the .jack file(s) to be compiled.")

def getFileNames():
    '''getFileNames() -> list

    Returns a list containing the names of the Jack files in the given
    directory name. Prints help and exits this program gracefully if
    the program is invoked incorrectly.
    '''
    if len(sys.argv) != 2:
        printUsage()
        print('Invalid call:', str(sys.argv).translate(str.maketrans('','',"',[]")))
        sys.exit()
    p = Path(sys.argv[1])
    if not p.is_dir():
        printUsage()
        print('{} is not a directory'.format(p))
        sys.exit()
    jackFiles = list(p.glob('*.jack'))
    jackFiles = [str(f) for f in jackFiles]
    return jackFiles

def main():
    '''Compiles the Jack program in the directory whose name is supplied
    through the command line when invoking this program.
    '''
    jackFiles = getFileNames()
    xmlFiles = [s.replace('.jack','.xml') for s in jackFiles]
    tokenFiles = [s.replace('.jack','T.xml') for s in jackFiles]
    # jackFiles contains the names of the Jack files to be compiled.
    # vmFiles contains the names of the corresponding vm files to be written to.
    for index,item in enumerate(jackFiles):
        x1 = JackTokenizer(item)
        x2 = open(tokenFiles[index],"w")
        x2.write("<tokens>" + "\n")
        wrt = ""
        while x1.hasMoreTokens()== True:
            x1.advance()
            if x1.tokenType() == "KEYWORD":
                wrt = x1.keyWord()
            elif x1.tokenType()=="SYMBOL":
                wrt = x1.symbol()
            elif x1.tokenType()=="IDENTIFIER":
                wrt = x1.identifier()
            elif x1.tokenType()=="INT_CONST":
                wrt = x1.intVal()
            elif x1.tokenType() == "STRING_CONST":
                wrt = x1.stringVal()
            rif = x1.tokenType()
            
            temp = "<" + rif + ">" + wrt + "</" + rif + ">"
            
            x2.write(temp+"\n")
        x2.write("</tokens>" + "\n")
        x2.close()
    ##    tokens = JackTokenizer("Main.jack")
        xmlout = xmlFiles[index]
        x3=CompilationEngine(tokenFiles[index],xmlout)
        x3.compileClass()
    pass

if __name__ == '__main__':
    '''Leave as is.'''
    main()
