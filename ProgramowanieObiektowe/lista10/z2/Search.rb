require File.expand_path('../Collection.rb',__FILE__)


class Search

    def BinSearch(col,val)
        l=0
        r=col.getLen-1
        return Bin(l,r,val,col)
    end

    def BasicSearch(col,val)
        i=0
        max=col.getLen-1
        while(i<max)
            if(col.getIVal(i)==val)
                return i
            end
            i+=1
        end
        return nil
    end

    private 
    def Bin(l,r,val,col)
        if(r>=l)
            mid=l+(r-l)/2
            temp=col.getIVal(mid)
            if(temp==val)
                return mid
            elsif(temp>val)
                return Bin(l,mid-1,val,col)
            else 
                return Bin(mid+1,r,val,col)
            end
        end
        return nil
    end
end

x=Collection.new

x<<7
x<<4
x<<231
x<<9992
x<<32132453151
printf  ("Sample collection :\n#{x.getPrintable}\n")

se=Search.new
printf ("Element 7 is at #{se.BinSearch(x,7)} index ~ BinSearch\n")

printf("Element 9992 is at #{se.BasicSearch(x,9992)} index ~ Linear search \n")

