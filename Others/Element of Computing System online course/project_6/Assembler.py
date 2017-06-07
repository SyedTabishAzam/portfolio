import sys

class Parser(object):
    '''Parses a HACK assembly file.'''

    def __init__(self, fname):
        '''Constructor - opens the input file and gets ready to parse it.'''
        file = open(fname,"r")
        self.file = file.readlines()

        
        pass
    
    def __str__(self):
        return 'Parser object'
        
    def hasMoreCommands(self):
        '''P.hasMoreCommands() -> bool

        Returns True if there are commands left to parse, False otherwise.
        '''
     
        return bool(self.file)
        pass

    def advance(self):
        '''P.advance() -> None

        Makes the next command the current command. Should be called
        only if hasMoreCommands() is True. Initially there is no
        current command.
        '''
        
        if self.hasMoreCommands() == True:
            
            self.line = self.file.pop(0).strip()
            if self.line.find("//")==True:
                j=self.line[self.line.find+1:]
                self.line=self.line.replace(j,"")

        pass

    def commandType(self):
        '''P.commandType() -> str

        Returns the type of the current command: one of
        A_COMMAND
        L_COMMAND
        C_COMMAND
        '''
        line = self.line
        if "@" == line[0]:
            return "A"
        elif "(" == line[0]:
            return "L"
        else:
            return "C"
        pass
        
    def symbol(self):
        '''P.symbol() -> str

        Returns the symbol or decimal Xxx of the current
        command. Should be called only when commandType() is A_COMMAND
        or L_COMMAND.
        '''
        if self.commandType() == "A":
            return self.line[1:]
        elif self.commandType() == "L":
            return self.line[1:-1]
        else:
            return "null"
        pass
    
    def dest(self):
        '''P.dest() -> str
    
        Returns the dest mnemonic (8 possibilities) in the current
        command. Should be called only when commandType() is
        C_COMMAND.
        '''
        if self.commandType() == "C":
            i = self.line.find("=")
            return self.line[0:i+1]
            if self.line.find("=")==False:
                return "null"
        else:
            return "null"
            
        pass
    
    def comp(self):
        '''P.comp() -> str

        Returns the comp mnemonic (28 possibilities) in the current
        command. Should be called only when commandType() is
        C_COMMAND.
        '''
        if self.commandType() == "C":
            
            self.line = self.line.strip()
            
            line = self.line
            
            if "=" in line:
                if line.find(";")> -1:
                    return line[line.find("=")+1:line.find(";")]
                else:
                    return line[line.find("=")+1:]
            else:
                i = line.find(";")
                return self.line[0:i]
                
        else: pass
        
    def jump(self):
        '''P.jump() -> str

        Returns the jump mnemonic (8 possibilities) in the current
        command. Should be called only when commandType() is
        C_COMMAND.
        '''
        self.line = self.line.strip()
        if self.commandType() == "C":
            if self.line.find(";") != -1:
                i = self.line.find(";")
                return self.line[i+1:]
            else:
                return "NULL"
        else:
            return "NULL"
        
        pass
    
class Code(object):
    '''Gives binary codes for mnemonics as per the HACK machine language.'''

    def __init__(self):
        '''Constructor - initializes built-in codes.'''
        destination = {"A":"100","M":"001","D":"010"}
        self.destination = destination
        compute={"0":"101010","1":"111111","-1":"111010","D":"001100","*":"110000",
                 "!D":"001101","!*":"110001","-D":"001111","-*":"110011","D+1":"011111","*+1":"110111","D-1":"001110","*-1":"110010","D+*":"000010",
                 "D-*":"010011" ,"*-D":"000111","D&*":"000000" ,"D|*":"010101"}
        self.compute=compute
        jumper = {'NULL':'000', 'JGT':'001', 'JEQ':'010', 'JGE':'011',
                      'JLT':'100', 'JNE':'101', 'JLE':'110', 'JMP':'111'}
        self.jumper = jumper
        pass

    def __str__(self):
        return 'Code object'
    y = ''
    def dest(self, mnemonic):
        '''C.dest(str) -> str

        Returns the binary code of the dest mnemonic.
        
        >>> C.dest('A')
        '100'
        '''
        piece = int("000",2)
        current = 0
        dest = bin(piece)[2:]
        if mnemonic == "":
            return dest.zfill(3)
        while mnemonic[current] != "=":
                if mnemonic[current] in self.destination:
                    piece = piece + int(self.destination.get(mnemonic[current]),2)
                current = current + 1
        dest = bin(piece)[2:]
        dest = dest.zfill(3)
        return dest

        pass
    
    def comp(self, mnemonic):
        '''C.comp(str) -> str

        Returns the binary code of the comp mnemonic.
        
        >>> C.comp('D-M')
        '1010011'
        '''
        z = "000000"
        if mnemonic.find("M") != -1:
            a = "1"
        else:
            a = "0"
        
        mnemonic = mnemonic.replace("A","*")
        mnemonic = mnemonic.replace("M","*")
        if mnemonic in self.compute:
            z= self.compute.get(mnemonic)
        
        outp = str(a) + str(z)
        
        return outp
        pass
    
    def jump(self, mnemonic):
        '''C.jump(str) -> str

        Returns the binary code of the jump mnemonic.
        
        >>> C.jump('JGE')
        '011'
        '''
        k = "000"
        if mnemonic in self.jumper:
            return self.jumper.get(mnemonic)
        
        return k
        pass
    

class SymbolTable(object):
    '''Symbol table for the HACK machine language.'''
    def __init__(self):
        '''Constructor - initializes pre-defined symbols and addresses.'''
        st= {"SP":0, "LCL":1, "ARG":2, "THIS":3, "THAT":4, "R0":0, "R1":1, "R2":2, "R3":3, "R4":4,"R5":5, "R6":6,"R7":7,
             "R8":8, "R9":9, "R10":10, "R11":11, "R12":12, "R13":13, "R14":14, "R15":15, "SCREEN":16384, "KBD":24576}
        self.st = st
        
        self.index = 16
        pass
           
    def ___str___(self):
        return 'SymbolTable object'

    def addEntry(self, symbol, address):
        '''ST.addEntry(str, int) -> None

        Adds the pair (symbol,address) to the table.
        '''
        
        if symbol in self.st:
            
            return self.st
        else:
            self.st[symbol]= address
            
                
        return self.st
        pass
    
    def contains(self, symbol):
        '''ST.contains(str) -> bool

        Returns True if symbol is contained in the table, False otherwise.
        '''
        
        if symbol in self.st:
            return True
        else:
            return False
        pass

    def getAddress(self, symbol):
        '''ST.getAddress(str) -> int

        Returns the address of the symbol in the table. Should be
        called when contains(symbol) is True.
        '''
        for i in self.st:
            if symbol == i:
                return self.st.get(i)
        pass

def main():
    
    import sys
    import os
    af = sys.argv[1]
    os.chdir("C:\\Python34\\ass5")
    temp = open(af,"r")
    cless = af[:-4] + "temp" + ".asm"
    temp2 = open(cless,"w")
    x2= Code()
    
    for line in temp:
        
        li=line.strip()
        
        if not li.startswith("//"):
            if li.find("//") != -1:
                li = li[:(li.find("//"))]
            if bool(li)==True:
                temp2.write(li.strip() + "\n")
        
    temp.close()
    temp2.close()
    x1= Parser(cless)
    
    hackname = af[:-4] + ".hack"
    hackfile = open(hackname,"w")
    x3 = SymbolTable()
    index = 16
    pc = -1
    cd = "000000000"
    while x1.hasMoreCommands() ==True:
        x1.advance()
        pc = pc + 1
        if x1.commandType()=="L":
            x3.addEntry(x1.symbol(),pc)
            pc = pc - 1
            
    x1 = Parser(cless)
    x2 = Code()
    while x1.hasMoreCommands() == True:
        x1.advance()
        if x1.commandType() == "C":
            cmp=x1.comp()
            dst=x1.dest()
            jmp=x1.jump()
            bcmp =x2.comp(cmp)
            bdst = x2.dest(dst)
            bjmp=x2.jump(jmp)
            code = "111" + bcmp + bdst + bjmp
            hackfile.write(code + "\n")
            print(code)
        elif x1.commandType() == "A":
            if x3.contains(x1.symbol()) == True:
                cd = converttobinary(x3.getAddress(x1.symbol()))
               
            else:
                if x1.symbol().isdigit()==True:
                    
                    cd = converttobinary(int(x1.symbol()))
                else:
                    if x3.contains(x1.symbol()) == False:
                        
                        x3.addEntry(x1.symbol(),index)
                        
                        cd = converttobinary(index)
                        index = index + 1
                    else:
                        position = x3.getAddress(x1.symbol())
                        cd= converttobinary(position)
            cd = cd.zfill(16)
            hackfile.write(cd + "\n")
            print(cd)
        
    hackfile.close()
    os.remove(cless)
    return 
    pass

def converttobinary(alpha):
    if alpha == 0:
        return '0'
    else:
        return converttobinary(alpha//2) + str(alpha%2)
    
if __name__ == "__main__":
    main()
