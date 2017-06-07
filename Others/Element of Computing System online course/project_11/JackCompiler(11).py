import sys
import shlex
from pathlib import Path
import subprocess


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
        file1 = open(inputFile,"r")
        self.file1 = file1.readlines()
        v=""
        for line in self.file1:
            
            v= v + line.strip() + " "
                
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
        self.temp = []
        ifile = open(inputFile,"r")
        self.ifile = ifile.readlines()
        self.vmout = outputFile
        self.symboltable = SymbolTable()
        self.ifcount = -1
        
        pass
    
        
    def compileClass(self):
        '''CE.compileClass() -> None

        Compiles a complete class.'''
        self.test = {"if":0,"let":0,"do":0,"while":0,"return":0}
        self.line = self.ifile.pop(0)
        self.line = self.ifile.pop(0)
        self.line = self.ifile.pop(0)
        
        self.classname =self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
        
        self.line = self.ifile.pop(0)
        self.line = self.ifile.pop(0)
        
        while ("static" in self.line) or ("field" in self.line):
            
            self.compileClassVarDec()
        
        while ("constructor" in self.line) or ("function" in self.line) or ("method" in self.line):
            
            self.compileSubroutine()

        
        self.vmout.close()        
        pass
    
    
    def compileClassVarDec(self):
        '''CE.compileClassVarDec() -> None
        
        Compiles a static declaration or a field declaration.
        '''
        cvkind = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
        self.line = self.ifile.pop(0)
        cvtype = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
        self.line = self.ifile.pop(0)
        cvname = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
        
        self.symboltable.define(cvname,cvtype,cvkind.upper())

        self.line = self.ifile.pop(0)
        while not ";" in self.line:
            
            self.line = self.ifile.pop(0)
            self.line = self.ifile.pop(0)
            cvname = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
            self.symboltable.define(cvname,cvtype,cvkind)
            self.line = self.ifile.pop(0)

        self.line = self.ifile.pop(0)
        pass

    def compileSubroutine(self):
        '''CE.compileSubroutine() -> None

        Compiles a complete method, function, or constructor.
        '''
        self.wcounter = -1
        ftype = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
       
        self.line = self.ifile.pop(0)
        
        self.line = self.ifile.pop(0)
        
        
        subname = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
        
        self.symboltable.startSubroutine()
        if ftype=="method":
            self.symboltable.define("instance",self.classname,"ARG")

        self.line = self.ifile.pop(0)
        
        self.compileParameterList()
        self.line = self.ifile.pop(0)
        self.line = self.ifile.pop(0)
        
        while "var"in self.line:
            
            self.compileVarDec()


        functionname = '{}.{}'.format(self.classname,subname)
        localcount= self.symboltable.varCount("VAR")

        self.vmout.writeFunction(functionname,localcount)

        if ftype =="constructor":
            fieldscount = self.symboltable.varCount("FIELD")
            self.vmout.writePush("constant",fieldscount)
            self.vmout.writeCall("Memory.alloc",1)
            self.vmout.writePop("POINTER",0)
        elif ftype=="method":
            self.vmout.writePush("ARG",0)
            self.vmout.writePop("POINTER",0)
        
        self.compileStatements()
        print(self.line,"sub")
        if ("}" in self.line) or ("{" in self.line):
            self.line = self.ifile.pop(0)
    
        
    
        pass
   
        
    def compileParameterList(self):
        '''CE.compileParameterList() -> None

        Compiles a (possible empty) parameter list not including the
        enclosing "()".
        '''
##        self.line = self.ifile.pop(0)
##        if ("," in self.line) or ("int" in self.line) or ("char" in self.line) or ("boolen" in self.line):
##            if "int" or "char" or "boolen" in self.line:
##                self.outputFile.write(self.line)
##                self.outputFile.write(self.ifile.pop(0))
##            self.line = self.ifile.pop(0)
##            while "," in self.line:
##                self.line = self.ifile.pop(0)
##                if ("int" in self.line) or ("char" in self.line) or ("boolen" in self.line):
##                    self.outputFile.write(self.line)
##                    self.line = self.ifile.pop(0)
##                    self.outputFile.write(self.line)
##                    self.line = self.ifile.pop(0)
##        self.outputFile.write("</parameterList>" + "\n")
        self.line = self.ifile.pop(0)
        if not ")" in self.line:
            typee = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
            self.line = self.ifile.pop(0)
            name= self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
            self.symboltable.define(name,typee,"ARG")
            self.line = self.ifile.pop(0)
        

        while ')' not in self.line:
            self.line = self.ifile.pop(0)
            typee = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
            self.line = self.ifile.pop(0)
            name= self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
            self.symboltable.define(name,typee,"ARG")
            self.line = self.ifile.pop(0) 
                
        pass

    def compileVarDec(self):
        '''CE.compileVarDec() -> None

        Compiles a var declaration.
        '''
        self.line=self.ifile.pop(0)
        vartype = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
        self.line=self.ifile.pop(0)
        varname = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
        self.symboltable.define(varname,vartype,"VAR")
        self.line=self.ifile.pop(0)
        
        while ";" not in self.line:
            self.line=self.ifile.pop(0)
            self.line=self.ifile.pop(0)
            varname = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
            self.symboltable.define(varname,vartype,"VAR")
            self.line=self.ifile.pop(0)

        self.line=self.ifile.pop(0)
        
        
        pass

    def compileStatements(self):
        '''CE.compileStatements() -> None

        Compiles a sequence of statement not including the enclosing "{}".
        '''
        self.ifflag="FALSE"
        test = self.test
        while ("if" in self.line) or ("let" in self.line) or ("while" in self.line) or ("do" in self.line) or ("return" in self.line):
            
            if ("if" in self.line):
                test["if"] +=1
                print("if",test["if"])
                self.compileIf()
            elif ("let" in self.line):
                test["let"] +=1
                print("let",test["let"])
                self.compileLet()
            elif ("do" in self.line):
                test["do"] +=1
                print("do",test["do"])
                self.compileDo()
            elif ("while" in self.line):
                test["while"] +=1
                print("while",test["while"])
                
                self.compileWhile()
            elif ("return" in self.line):
                test["return"] +=1
                print("return",test["return"])
                self.compileReturn()
                
                
             
        pass

    def compileDo(self):
        '''CE.compileDo() -> None

        Compiles a do statement.
        '''
        
        numargs=0
        self.line = self.ifile.pop(0)
        
        unk = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
        print("reaching here",self.line)    
        self.line = self.ifile.pop(0)
        if "." in self.line:
            
            
            self.line = self.ifile.pop(0)
            subname = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
            typee = self.symboltable.typeOf(unk)
            
            if typee != False:
                instancekind= self.symboltable.kindOf(unk)
                instanceindex= self.symboltable.indexOf(unk)
                if instancekind == "VAR":
                    ik = "LOCAL"
                elif instancekind == "FIELD":
                    ik = "THIS"
                else:
                    ik = instancekind
                
                self.vmout.writePush(ik,instanceindex)
                functionname = '{}.{}'.format(typee, subname)
                numargs +=1
                
            else:
                classname = unk
                functionname = '{}.{}'.format(classname, subname)
            self.line=self.ifile.pop(0)        
        elif "(" in self.line:
            subname=unk
            functionname= '{}.{}'.format(self.classname, subname)
            numargs+=1
            self.vmout.writePush("POINTER",0)
        
        
        numargs += self.compileExpressionList()
        
        self.line = self.ifile.pop(0)
        
        self.vmout.writeCall(functionname,numargs)
        self.vmout.writePop("TEMP",0)
        self.line = self.ifile.pop(0)
        
        
        
        pass

    def compileLet(self):
        '''CE.compileLet() -> None

        Compiles a let statement.
        '''
        self.line = self.ifile.pop(0)
        varname = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
        
        varkind = self.symboltable.kindOf(varname)
        
        if varkind=="VAR":
            jk="this"
        elif varkind=="FIELD":
            jk="this"
        else:
            jk=varname
        varindex = self.symboltable.indexOf(varname)
        self.line = self.ifile.pop(0)
        
        if "[" in self.line:
            self.line = self.ifile.pop(0)
            self.compileExpression()
            self.line = self.ifile.pop(0)
            
            self.vmout.writePush(varkind,varindex)
            self.vmout.writeArithmetic("ADD")
            self.vmout.writePop("TEMP",0)

            self.line = self.ifile.pop(0)
            self.compileExpression()
            self.line= self.ifile.pop(0)

            self.vmout.writePush("TEMP",0)
            self.vmout.writePop("POINTER",1)
            self.vmout.writePOP("THAT",0)
        else:
            self.line = self.ifile.pop(0)
        
            self.compileExpression()
            
            self.line = self.ifile.pop(0)
            self.vmout.writePop(jk,varindex)
            
        pass

    def compileWhile(self):
        '''CE.compileWhile() -> None

        Compiles a while statement.
        '''
        self.wcounter +=1
        wcounter = self.wcounter
        
        self.vmout.writeLabel("WHILE{}".format(wcounter))
        self.line = self.ifile.pop(0)
        
        self.compileExpression()
        
        
        self.vmout.writeArithmetic("NOT")
        #self.line = self.ifile.pop(0)
        #self.line = self.ifile.pop(0)
        
        
        self.vmout.writeIf("WHILE_END{}".format(wcounter))
        print(self.test)
        self.compileStatements()
        self.vmout.writeGoto("WHILE{}".format(wcounter))
        self.vmout.writeLabel("WHILE_END{}".format(wcounter))
        
        self.line = self.ifile.pop(0)
        
        pass
    
    def compileReturn(self):
        '''CE.compileReturn() -> None

        Compiles a return statement.
        '''
        self.line = self.ifile.pop(0)

        if ";" not in self.line:
            self.compileExpression()
            
            self.line = self.ifile.pop(0)
           
        else:
            self.vmout.writePush("constant",0)
            self.line = self.ifile.pop(0)
        self.vmout.writeReturn()
        
        self.line = self.ifile.pop(0)
        print(self.line,"kam")
        
        pass
    
    def compileIf(self):
        '''CE.compileIf() -> None

        Compiles an if statement possibly with a trailing else clause.
        '''
        self.ifcount +=1
        ifcount = self.ifcount
        
        self.line = self.ifile.pop(0)
        self.compileExpression()
        self.line = self.ifile.pop(0)
        
        
        self.vmout.writeIf('IF_TRUE{}'.format(ifcount))
        self.vmout.writeGoto('IF_FALSE{}'.format(ifcount))
        self.vmout.writeLabel('IF_TRUE{}'.format(ifcount))
        print(self.test)
        self.compileStatements() # statements
        self.vmout.writeGoto('IF_END{}'.format(ifcount))
        
        self.line = self.ifile.pop(0)
        
        self.compileStatements()
        self.vmout.writeLabel("IF_FALSE{}".format(ifcount))
        self.line = self.ifile.pop(0)
        if "else" in self.line:
            self.line = self.ifile.pop(0)
            self.compileStatements()
            self.line=self.ifile.pop(0)
            
        self.vmout.writeLabel('IF_END{}'.format(ifcount))

        
        pass
    
    def compileExpression(self):
        '''CE.compileExpression() -> None
        
        Compiles an expression.
        '''
        self.compileTerm()
        builtin = {"+":"ADD","-":"SUB","&":"AND","|":"OR","<":"LT",">":"GT","=":"EQ"}
        
        while ("+" in self.line) or("-" in self.line) or ("*" in self.line) or(self.line.count("/")>1) or("&" in self.line) or("|" in self.line) or(self.line.count("<")>2) or(self.line.count("<")>2) or("=" in self.line):
                
                op =  self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
                
                self.line=self.ifile.pop(0)
                
                self.compileTerm()
                if op in builtin.keys():
                    
                    self.vmout.writeArithmetic(builtin[op])
                elif op=="*":
                    self.vmout.writeCall("Math.multiply",2)
                elif op=="/":
                    self.vmout.writeCall("Math.divide",2)
                
        pass
    
    def compileTerm(self):
        '''CE.compileTerm() -> None

        Compiles a term. Uses lookahead to decide between alternative
        parsing rules. If the current token is an indentifier, a
        look=ahead token of "[", "(", or "." distinguish between a
        variable, array, and subroutine call. Any other token is not
        part of this term and should not be advanced over.
        '''
        numargs = 0
        
        if ("-" in self.line) or ("~" in self.line):
            op =  self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
            
            self.line = self.ifile.pop(0)
            
            self.compileTerm()
            if "-" in op:
                un = "neg"
            elif "~" in op:
                un = "not"
            self.vmout.writeArithmetic(un)
        elif "(" in self.line:
            self.line = self.ifile.pop(0)
            
            self.compileExpression()
            if "INT_CONST" in self.line:
                intvalue =  self.line[(self.line.find(">"))+1:(self.line.find("<",1))]

                
                self.vmout.writePush("constant",intvalue)
                self.line = self.ifile.pop(0)
            self.line=self.ifile.pop(0)
        elif "INT_CONST" in self.line:
            intvalue =  self.line[(self.line.find(">"))+1:(self.line.find("<",1))]

            
            self.vmout.writePush("constant",intvalue)
            self.line = self.ifile.pop(0)
            
        elif "STR_CONST" in self.line:
            stringvalue = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
            self.vmout.writePush("constant",len(stringvalue))
            self.vmout.writeCall("String.new",1)
            for x in stringvalue:
                self.vmout.writePush("constant",ord(char))
                self.vmout.writeCall("String.appendChar",2)
                
        elif ("true" in self.line) or ("this" in self.line) or ("false" in self.line) or ("null" in self.line):
            key= self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
            self.line = self.ifile.pop(0)
            
            if key == "this":
                self.vmout.writePush("POINTER",0)
            else:
                self.vmout.writePush("constant",0)
                if key=="true":
                    self.vmout.writeArithmetic("not")
        else:
            unk = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
            
            self.line = self.ifile.pop(0)
            
            if "[" in self.line:
                arayname = unk
                self.line = self.ifile.pop(0)
                self.compileExpression()
                self.line = self.ifile.pop(0)

                araykind = self.symboltable.kindOf(arayname)
                arayindex = self.symboltable.indexOf(arayname)
                if araykind == "VAR":
                    wak = "LOCAL"
                elif araykind == "FIELD":
                    wak = "THIS"
                else:
                    wak = araykind
                
                self.vmout.writePush(wak,arayindex)
                self.vmout.writeArithmetic("ADD")
                self.vmout.writePop("POINTER",1)
                self.vmout.writePush("THAT",0)
            elif ("." in self.line) or ("(" in self.line):
                if "." in self.line:
                    self.line = self.ifile.pop(0)
                    subname = self.line[(self.line.find(">"))+1:(self.line.find("<",1))]
                    typee = self.symboltable.typeOf(unk)
                    
                    if typee != False:
                        
                        instancekind= self.symboltable.kindOf(unk)
                        instanceindex= self.symboltable.indexOf(unk)
                        if instancekind == "VAR":
                            ik = "LOCAL"
                        elif instancekind == "FIELD":
                            ik = "THIS"
                        else:
                            ik = instancekind
                        
                        self.vmout.writePush(ik,instanceindex)
                        functionname = '{}.{}'.format(typee, subname)
                        numargs +=1
                        
                    else:
                        classname = unk
                        
                        functionname = '{}.{}'.format(classname, subname)
                        
                elif "(" in self.line:
                    subname=unk
                    functionname= '{}.{}'.format(self.classname, subname)
                    
                    numargs+=1
                    self.vmout.writePush("POINTER",0)
                self.line = self.ifile.pop(0)
                
                numargs += self.compileExpressionList()
                self.line = self.ifile.pop(0)
                if functionname=="SquareGame.moveSquare": print(self.line)
                self.vmout.writeCall(functionname,numargs)
            else:
                
                if self.ifflag!="TRUE":
                    
                    self.line = self.ifile.pop(0)
                    self.ifflag=="TRUE"
                variable = unk
                
                varkind = self.symboltable.kindOf(variable)
                
                if varkind == "VAR":
                    vak = "LOCAL"
                elif varkind == "FIELD":
                    vak = "THIS"
                else:
                    vak = varkind
                varindex = self.symboltable.indexOf(variable)
                (self.line,"kame",variable,vak,varindex)
                
                self.vmout.writePush(vak,varindex)
                
            
        
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
        numargs = 0
        
        self.line = self.ifile.pop(0)
        
        if ")" not in self.line:
            numargs +=1
            self.compileExpression()
            
        
        while not ")" in self.line:
            numargs +=1
            self.line = self.ifile.pop(0)
            
            self.compileExpression()
            
            
        return numargs
    pass

class SymbolTable(object):
    staticscope = {}
    counter = {"FIELD":0,"STATIC":0,"VAR":0,"ARG":0}
    def __init__(self):
        self.counter["FIELD"] =0
        self.subroutinescope = {}
        self.fieldscope = {}
        pass
    def startSubroutine(self):
        self.subroutinescope = {}
        self.counter['ARG']    = 0
        self.counter['VAR']    = 0
        pass
    
    def define(self,name,typee,kind):
        number = None
        if kind == "ARG" or kind == "VAR":
            if kind == "ARG":
                number = self.counter["ARG"]
                self.counter["ARG"] +=1
            elif kind == "VAR":
                number = self.counter["VAR"]
                self.counter["VAR"]+=1
            self.subroutinescope[name]=(typee,kind,number)
        elif kind == "STATIC" or kind == "FIELD":
            if kind == "STATIC":
                number = self.counter["STATIC"]
                self.counter["STATIC"] +=1
                self.staticscope[name]=(typee,kind,number)
            if kind == "FIELD":
                number = self.counter["FIELD"]
                self.counter["FIELD"]+=1
                self.fieldscope[name]=(typee,kind,number)
        pass
    def varCount(self,kind):
        return self.counter[kind]
        pass
    def kindOf(self,name):
        if name in self.subroutinescope.keys():
          return self.subroutinescope[name][1]
        elif name in self.fieldscope.keys():
          return self.fieldscope[name][1]
        elif name in self.staticscope.keys():
          return self.staticscope[name][1]
        else:
          return False
        
    def typeOf(self,name):
        if name in self.subroutinescope.keys():
          return self.subroutinescope[name][0]
        elif name in self.fieldscope.keys():
          return self.fieldscope[name][0]
        elif name in self.staticscope.keys():
          return self.staticscope[name][0]
        else:
          return False
        
        pass
    def indexOf(self,name):
        if name in self.subroutinescope.keys():
          return self.subroutinescope[name][2]
        elif name in self.fieldscope.keys():
          return self.fieldscope[name][2]
        elif name in self.staticscope.keys():
          return self.staticscope[name][2]
        else:
          return False
        pass
    
class VMWriter(object):
    
  def __init__(self, output_file):
    self.outputFile = output_file
  def writePush(self, segment, index):
    self.outputFile.write("push " + str(segment) + str(index)+ "\n")
  def writePop(self, segment, index):
    self.outputFile.write("pop " + str(segment) + str(index)+ "\n")
  def writeArithmetic(self, command):
    self.outputFile.write(command+ "\n")
  def writeLabel(self, label):
    self.outputFile.write("label " + label + "\n")
  def writeGoto(self, label):
    self.outputFile.write("goto " + label+ "\n")
  def writeIf(self, label):
    self.outputFile.write("if-goto " + label+ "\n")
  def writeCall(self, name, nArgs):
    self.outputFile.write("call " + name+ str(nArgs) + "\n")
  def writeFunction(self, name, nLocals):
    self.outputFile.write("function " + str(name) + str(nLocals) + "\n")
  def writeReturn(self):
    self.outputFile.write("return " + "\n")
  def close(self):
    self.outputFile.close()
        
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
    print(jackFiles)
    vmFiles = [s.replace('.jack','.vm') for s in jackFiles]
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
        vmfile = open(vmFiles[index],"w")
        vmout = VMWriter(vmfile)
        x3=CompilationEngine(tokenFiles[index],vmout)
        x3.compileClass()
    pass

if __name__ == '__main__':
    '''Leave as is.'''
    main()
