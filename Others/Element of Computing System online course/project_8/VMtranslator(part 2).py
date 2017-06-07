import sys
from pathlib import Path
import os
os.chdir("x:\check")

class Parser(object):
    '''Parses a single vm file to provide convenient access to the
    contained commands and their components.
    '''

    def __init__(self, fname):
        '''Opens the input file at fname and get ready to parse it.
        '''
        linec = 0
        self.linec = linec
        file1 = open(fname,"r")
        self.file1 = file1.readlines()
        pass
    
    def __str__(self):
        '''Leave as is.'''
        return 'Parser object'

    def hasMoreCommands(self):
        '''P.hasMoreCommands() -> bool
    
        Returns True if there are commands in the input, False
        otherwise.
        '''
        
        return bool(self.file1)
        pass

    def advance(self):
        '''P.advance() -> None

        Makes the next command the current command. Should be called
        only if hasMoreCommands() is True.
        '''
        if self.hasMoreCommands() == True:
           
            self.line = self.file1.pop(0).strip()
            if self.line.find("//")==True:
                j=self.line[self.line.find+1:]
                self.line=self.line.replace(j,"")
        pass

    def commandType(self):
        '''P.commandType() -> str

        Returns the type of the current VM command: one of
        C_ARITHMETIC
        C_PUSH, C_POP
        C_LABEL
        C_GOTO
        C_IF
        C_FUNCTION
        C_RETURN
        C_CALL
        '''
        
        line = self.line
        space = line.find(" ")
        arithmetic = ["gt","lt","eq","and","or","not","add","sub","neg"]
        if "push" == line[:space]:
            return "C_PUSH"
        elif "pop" == line[:space]:
            return "C_POP"
        elif "label" == line[:space]:
            return "C_LABEL"
        elif "if-goto" == line[:space]:
            return "C_IF"
        elif "goto"== line[:space]:
            return "C_GOTO"
        elif "function"== line[:space]:
            
            return "C_FUNCTION"
        elif "return" == line[:6]:
            return "C_RETURN"
        elif "call" == line[:space]:
            
            return "C_CALL"
        elif line[:4].strip() in arithmetic:
            
            
            return "C_ARITHMETIC"
        pass
    
    def arg1(self):
        '''P.arg1() -> string

        Returns the first argument of the current command. In the case
        of C_ARTIHMETIC, the command itself (e.g. sub, add) is
        returned. Should not be called if the current command is
        C_RETURN.
        '''
        if self.commandType()=="C_ARITHMETIC":
            
            return self.line.split()[0].strip()
        if self.commandType()=="C_LABEL" or self.commandType()=="C_IF" or self.commandType()=="C_GOTO":
            return self.line.split()[1].strip()
        elif self.commandType()=="C_FUNCTION" or self.commandType()=="C_CALL":
            return self.line.split()[1].strip()
        elif self.commandType()=="C_PUSH" or self.commandType()=="C_POP":
            return self.line.split()[1].strip()
        pass

    def arg2(self):
        '''P.arg2() -> int

        Returns the second argument of the current command. Should be
        called only if the current command is any of
        C_PUSH
        C_POP
        C_FUNCTION
        C_CALL
        '''
        if self.commandType()=="C_PUSH" or self.commandType()=="C_POP":
            return self.line.split()[2].strip()
        elif self.commandType()=="C_FUNCTION" or self.commandType()=="C_CALL":
            return self.line.split()[2].strip()
        pass
    
class CodeWriter(object):
    '''Translates VM commands into Hack assembly code.'''
    
    def __init__(self, fname):
        '''Opens the output file at fname and gets ready to write to it.'''
        linepc = 0
        rc = 0
        self.linepc = linepc
        self.rc = rc
        filex = open(fname,"w")
        self.filex=filex
        segment = {"local":"LCL","argument":"ARG","this":"THIS","that":"THAT","temp":"R6"}
        self.segment = segment
        flag = False
        self.flag = flag
        
        pass
    
    def __str__(self):
        '''Leave as is.'''
        return 'CodeWriter object.'

    def setFileName(self, fname):
        '''CW.setFileName(str) -> None
    
        Informs the code writer that the translation of the VM file at
        fname is to be started.
        '''
        
        fileName = fname[fname.find("\\")+1:-3]
        self.fileName = fileName
        
        functionName = fileName
        
        
        self.functionName = fileName
        if fileName == "Sys":
            
            self.writeInit()
        
        
        pass
    def writeInit(self):
        ''' Writes the initial file, that has to be placed at top of code'''
        wtf = "@256 D=A @SP M=D "
        wtf = wtf.replace(" ","\n")
        self.filex.write(wtf)
        self.writeCall("Sys.init","0")
    
    def writeArithmetic(self, command):
        '''CW.writeArithmetic(str) -> None

        Writes to the output file the assmebly code that is the
        translation of the given arithmetic command.
        '''
        
        self.linepc = self.linepc + 1
        if command == "add":
            wtf = "@SP AM=M-1 D=M M=0 @SP A=M-1 M=M+D "
            wtf = wtf.replace(" ","\n")
            self.filex.write(wtf)
        elif command == "lt":
            wtf= "@SP AM=M-1 D=M M=0 @SP A=M-1 D=M-D @FLT" + str(self.linepc) +" D;JLT @FALSE" + str(self.linepc) + " 0;JMP (FLT"+ str(self.linepc) +") @SP A=M-1 M=-1 @p"+ str(self.linepc) +" 0;JMP (FALSE"+str(self.linepc)+") @SP A=M-1 M=0 (p"+ str(self.linepc) +") @SP "
            wtf = wtf.replace(" ","\n")
            self.filex.write(wtf)
        elif command == "eq":
            wtf = "@SP AM=M-1 D=M M=0 @SP A=M-1 D=M-D @FEQ"+ str(self.linepc) +" D;JEQ @FALSE" + str(self.linepc)+ " 0;JMP (FEQ"+ str(self.linepc) +") @SP A=M-1 M=-1 @p"+ str(self.linepc) +" 0;JMP (FALSE"+str(self.linepc)+") @SP A=M-1 M=0 (p"+ str(self.linepc) +") @SP "
            wtf = wtf.replace(" ","\n")
            self.filex.write(wtf)
        elif command == "gt":
            wtf = "@SP AM=M-1 D=M M=0 @SP A=M-1 D=M-D @FGT"+ str(self.linepc) +" D;JGT @FALSE"+str(self.linepc)+" 0;JMP (FGT"+ str(self.linepc) +") @SP A=M-1 M=-1 @p"+ str(self.linepc) +" 0;JMP (FALSE"+str(self.linepc)+") @SP A=M-1 M=0 (p"+ str(self.linepc) +") @SP "
            wtf = wtf.replace(" ","\n")
            self.filex.write(wtf)
        elif command== "sub":
            wtf = "@SP AM=M-1 D=M M=0 @SP A=M-1 M=M-D "
            wtf = wtf.replace(" ","\n")
            self.filex.write(wtf)
        elif command== "and":
            wtf = "@SP AM=M-1 D=M M=0 @SP A=M-1 M=D&M "
            wtf = wtf.replace(" ","\n")
            self.filex.write(wtf)
        elif command== "or":
            wtf = "@SP AM=M-1 D=M M=0 @SP A=M-1 M=D|M "
            wtf = wtf.replace(" ","\n")
            self.filex.write(wtf)
        elif command == "not":
            wtf = "@SP A=M-1 M=!M "
            wtf = wtf.replace(" ","\n")
            self.filex.write(wtf)
        elif command == "neg":
            wtf = "@SP A=M-1 M=-M "
            wtf = wtf.replace(" ","\n")
            self.filex.write(wtf)
        
        pass

    def writePushPop(self, command):
        '''CW.writePushPop(str) -> None

        Writes to the output file the assmebly code that is the
        translation of the given command, where command is either
        C_PUSH or C_POP.
        '''
        wtf = ""
        fname = self.fileName
        
        pp = command.split().pop(0)
        segmentv = command.split().pop(1)
        index = command.split().pop(2)
        
        if pp == "C_PUSH":
            if segmentv == "temp":
                pos = "R" + str(int(index)+5)
                
                wtf = "@"+pos+" D=M @SP AM=M+1 A=A-1 M=D "
            
            elif segmentv =="constant":
                wtf = "@" + index + " D=A @SP AM=M+1 A=A-1 M=D "
            elif segmentv =="pointer":
                if index=="0":
                    wtf = "@THIS D=M @SP AM=M+1 A=A-1 M=D "
                if index=="1":
                    wtf = "@THAT D=M @SP AM=M+1 A=A-1 M=D "
            elif segmentv=="static":
                wtf = "@" + fname + "." + index + " D=M @SP AM=M+1 A=A-1 M=D "
                
            else:
                wtf = "@" + index + " D=A @" + self.segment[segmentv] + " A=M+D D=M @SP AM=M+1 A=A-1 M=D "
        elif pp == "C_POP":
            if segmentv == "temp":
                pos = "R" + str(int(index)+5)
                
                wtf = "@SP AM=M-1 D=M M=0 @" + pos + " M=D "
            elif segmentv == "pointer":
                if index=="0":
                    wtf ="@SP AM=M-1 D=M M=0 @THIS M=D "
                elif index=="1":
                    wtf ="@SP AM=M-1 D=M M=0 @THAT M=D "
            elif segmentv =="static":
                wtf = "@SP AM=M-1 D=M M=0 @" + fname + "." + index + " M=D "
            
            else:
                wtf = "@" + index + " D=A @" + self.segment[segmentv] + " M=M+D @SP AM=M-1 D=M M=0 @" + self.segment[segmentv] + " A=M M=D @" + index + " D=A @" + self.segment[segmentv] + " M=M-D "
        wtf = wtf.replace(" ","\n")
        self.filex.write(wtf)
        pass
    
    def writeLabel(self, label):
        '''This command labels the current location in the function’s code'''
        ln = self.genLabel(label)
        wtf = "("+ln+")\n"
        self.filex.write(wtf)
        
        pass

    def writeGoto(self,label):
        '''This command effects an unconditional goto operation, causing execution to continue from the location marked by the label'''
        ln = self.genLabel(label)
        wtf = "@" + ln + " 0;JMP "
        wtf = wtf.replace(" ","\n")
        self.filex.write(wtf)
        pass

    def writeIf(self, label):
        ''' This command effects a conditional goto operation. The stack’s topmost value is popped;
        if the value is not zero, execution continues from the location marked by the label; otherwise,
        execution continues from the next command in the program'''
        ln = self.genLabel(label)
        wtf = "@SP AM=M-1 D=M @" + ln + " D;JNE "
        wtf = wtf.replace(" ","\n")
        self.filex.write(wtf)
        pass
    
    def writeCall(self,functionName, numArgs):
        ''' Calls function functionName after numArgs arguments have been pushed to stack'''
        
        self.rc = self.rc + 1
        retlabel = "returnto" + str(self.rc)
        self.retlabel =retlabel
        wtf1 = "@" + str(retlabel) + " D=A @SP A=M M=D @SP M=M+1 @LCL D=M @SP A=M M=D @SP M=M+1 @ARG D=M @SP A=M M=D @SP M=M+1 @THIS D=M @SP A=M M=D @SP M=M+1 @THAT D=M @SP A=M M=D @SP M=M+1 @SP D=M"
        wtf2 = " @" + str(numArgs) + " D=D-A @5 D=D-A @ARG M=D @SP D=M @LCL M=D "
        
        wtf = wtf1 + wtf2
        wtf = wtf.replace(" ","\n")
        self.filex.write(wtf)
        self.writeGoto(functionName)
        self.writeLabel(str(retlabel))
        pass
    
    def writeReturn(self):
        '''retrun from a function'''
        wtf = "@LCL D=M @FRAME M=D @5 A=D-A D=M @RET M=D @SP A=M-1 D=M @ARG A=M M=D"
        wtf1= " @ARG D=M+1 @SP M=D @1 D=A @FRAME A=M-D D=M @THAT M=D @2 D=A @FRAME A=M-D D=M @THIS M=D @3 D=A @FRAME A=M-D D=M @ARG M=D @4 D=A @FRAME A=M-D D=M @LCL M=D"
        wtf2= " @RET A=M 0;JMP "
        
        writing = wtf + wtf1 + wtf2
        writing = writing.replace(" ","\n")
        
        self.filex.write(writing)
        
        pass 
    def genLabel(self,label):
        '''kind of dead code'''
        r=""
        
        if self.functionName == "Sys.init":
            r = self.functionName + "&" + label
        else:
            r= label
        return label
        pass
    
    def writeFunction(self, functionName, numLocals):
        '''declare a function functionName that has numLocals local variables'''
        self.functionName = functionName
        self.flag= True
        wtf = "(" + functionName +")\n"
        numLocals = int(numLocals)
        
        self.filex.write(wtf)
        i = 0
        while i<numLocals:
            self.writePushPop("C_PUSH constant 0")
            i +=1
            
        pass
    def close(self):
        '''CW.close() -> None

        Close the output file.
        '''
        closesynt = "(END) @END 0;JMP "
        closesynt = closesynt.replace(" ","\n")
        self.filex.write(closesynt)
        self.filex.close()
        pass

def printUsage():
    '''printUsage() -> None
    
    Prints infomration on how to call this file.
    '''
    print("Usage: VMtranslator source")
    print("source is one of")
    print("\ta .vm file\n\ta directory containing .vm files")

def getFileNames():
    '''getFileNames() -> tuple

    Returns a tuple contianing the name of the output ASM file and a
    list of names of the VM files to operate on, as per the call to
    the program from command line.
    '''
    
    if len(sys.argv) != 2:
        
        printUsage()
        print('Invalid call:', end=' ')
        for x in sys.argv:
            print(x, end=' ')
        print()
        sys.exit()  # End program.
    p = Path(sys.argv[1])
    
    fname = str(p)
    
    
    if p.is_dir():
        
        while fname[-1] == "\\":
            
            fname = fname[:-1]
        asmFname = fname + '.asm'
        
        vmFiles = list(p.glob('*.vm'))
        
        
    elif fname[-3:] == '.vm' and p.exists():
        asmFname = fname[:-3]+'.asm'
        vmFiles = [p]
        
    else:
        printUsage()
        print('Invalid file:', fname,'\nAborting!')
        sys.exit() # End program.
    vmFiles = [str(f) for f in vmFiles]
    
    "Making sys.vm the first file in the list of vmFiles"
    st = fname + "\\Sys.vm"
    if st in vmFiles:
            
            ap=vmFiles.pop(vmFiles.index(st))
            vmFiles.append(ap)
            vmFiles.reverse()
    
    return (asmFname, vmFiles)

def main():
    asmFname, vmFiles = getFileNames()
    # asmFname now contains the name of the file to output to.
    # vmFiles is a list contianing the names of VM files to be translated.
    import time
    
    "Making x1 the caller for Parser with first file in list of vmFiles"
    x1 = Parser(vmFiles[0])
    "ff percent fun and w2 are just for sake of design, they arent related to the actual code in anyway"
    ff = 10
    percent = ""
    fun = "||| Loading "
    
    "Making x2 the caller for CodeWrite at asmFname"
    x2 = CodeWriter(asmFname)
    w2 = "|"
    x = 0

    "looping for every file in list of vmFiles"
    for x in vmFiles:
        "Making x1 the caller for Parser with file x in list of vmFiles"
        x1 = Parser(x)
        x2.setFileName(x)
        while x1.hasMoreCommands()==True:
            x1.advance()
            percent = str(ff) + "%" + ("|||") + w2
            if ff<=100:
                time.sleep(.1)
                print(fun,percent)
                if ff==30:
                    print("( You can remove this delay )")
            else:
                time.sleep(0)
                
            
            if x1.commandType()=="C_PUSH" or x1.commandType()=="C_POP":
                
                x2.writePushPop(str(x1.commandType() + " " + x1.arg1() + " " + x1.arg2()))
            elif x1.commandType()=="C_ARITHMETIC":
                x2.writeArithmetic(x1.arg1())
            elif x1.commandType()=="C_LABEL":
                x2.writeLabel(x1.arg1())
                
            elif x1.commandType()=="C_IF":
                
                x2.writeIf(x1.arg1())
            elif x1.commandType()=="C_GOTO":
                 x2.writeGoto(x1.arg1())
            elif x1.commandType()=="C_FUNCTION":
                
                x2.writeFunction(x1.arg1(),x1.arg2())
            elif x1.commandType()=="C_RETURN":
                
                x2.writeReturn()
            elif x1.commandType()=="C_CALL":
                
                x2.writeCall(x1.arg1(),x1.arg2())
            ff = ff + 10
            fun = "|" + fun
            w2 = w2 + "|"
    print("******VM to ASM CONVERSION COMPLETED******")    
    x2.close()
    
    pass
    
if __name__ == "__main__":
    # Leave as is.
    main()
