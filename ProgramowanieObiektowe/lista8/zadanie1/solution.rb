
class Fixnums

    @val

    def initialize(a)
        @val=a
    end
    def dividers()
        x=1
        a=Array.new
        while x<=@val
            if @val.modulo(x)==0
                a<<x   
            end
            x+=1
        end
        return a
    end

    def Ack(n=@val,m)
        if n==0
            return m+1
        elsif m==0
            return Ack(n-1,1)
        else
            return Ack(n-1,Ack(n,m-1))
        end
    end

    def is_perfect()
        sum=0
        for num in dividers do
           sum+=num 
        end
        if (@val*2==sum)
            return true
        else 
            return false
        end
    end

    def in_words()
        t=@val
        t2=""
        while(t!=0)
            case (t%10)
            when 0
                t2="zero "+t2
            when 1
                t2="one "+t2
            when 2
                t2="two "+t2
            when 3
                t2="three "+t2
            when 4
                t2="four "+t2
            when 5
                t2="five "+t2
            when 6
                t2="six "+t2
            when 7
                t2="seven "+t2
            when 8
                t2="eight "+t2
            when 9
                t2="nine "+t2
            end
            t/=10
        end
        return t2
    end
end

z=Fixnums.new(6)
printf("#{z.dividers}\n")
x=Fixnums.new(2)
puts(x.Ack(1))
puts(z.is_perfect)
f=Fixnums.new(12334444444)
puts(f.in_words)