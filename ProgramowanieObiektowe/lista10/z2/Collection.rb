require File.expand_path('../Token.rb',__FILE__)

class Collection #list of Tokens where curr is always the smallest  
    def initialize()
        @curr=nil
        @len=0
    end
    def Add(val)
        if(@curr==nil)
            @curr=Token.new(val)
        else
            put(val)
        end
        @len+=1
    end
    def <<(val)
        if(@curr==nil)
            @curr=Token.new(val)
        else
            put(val)
        end
        @len+=1
    end

    def getPrintable
        tab=Array.new
        x=@curr
        while(!(x==nil))
            tab<<x.getVal
            x=x.getLeft
        end
        return tab
    end

    def getLen
        return @len
    end

    def getIVal(ind)
        if(@len-1<ind)
            puts "Index out of Collection"
            return nil
        else 
            i=0
            x=@curr
            while(i<ind)
                x=x.getLeft
                i+=1
            end
            return x.getVal
        end
    end


    private 
    def put(val)
        if (val>@curr.getVal)
            if(@curr.getLeft==nil)
                le=Token.new(val)
                le.setRight(@curr)
                @curr.setLeft(le)
            else 
                @curr=@curr.getLeft
                put(val)
                while(!(@curr.getRight==nil))
                    @curr=@curr.getRight
                end
            end
        else
            ri=Token.new(val)
            if(@curr.getRight==nil)
                @curr.setRight(ri)
                ri.setLeft(@curr)
                @curr=ri
            else
                temp=@curr.getRight
                temp.setLeft(ri)
                ri.setRight(temp)
                ri.setLeft(@curr)
                @curr.setRight(ri)
            end
        end
    end
end

