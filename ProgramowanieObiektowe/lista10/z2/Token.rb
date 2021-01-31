class Token 
    def initialize(value)
        @left=nil
        @right=nil
        @val=value
    end
    def getVal()
        return @val
    end

    def getRight
        return @right
    end

    def getLeft
        return @left
    end

    def setRight(tok)
        if tok.instance_of?(Token)
            @right=tok
        else 
            puts "Value is not a token!"
        end
    end

    def setLeft(tok)
        if tok.instance_of?(Token)
            @left=tok
        else 
            puts "Value is not a token!"
        end
    end

end
