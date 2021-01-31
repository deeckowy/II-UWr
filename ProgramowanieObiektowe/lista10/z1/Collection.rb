class Collection
    def initialize()
        @col=Array.new
        @length=0
    end
    def Add(e)
        @col<<e
        @length+=1
    end
    def <<(elem)
        @col<<elem
        @length+=1
    end
    def Len()
        return @length
    end
    def Get(i)
        return @col[i]
    end
    def Swap(i,j)
        temp=@col[i]
        @col[i]=@col[j]
        @col[j]=temp
    end
    def getPrintable()
        return @col
    end
    def Set(index,val)
        @col[index]=val
    end
end 

