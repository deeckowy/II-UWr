class Function
    def initialize(fun)
        @f=fun
    end

    def value(x)
        return @f.call(x)
    end

    def zero_places(a,b,e)
        x=a
        while (x<b)
            if(@f.call(x)<e&&@f.call(x)>=0.0)
                return @f.call(x)
            end
            x+=e
        end
        return nil
    end

    def integral(a,b,e)
        # e - is level of accuracy higher=better
        # but dont overact it can take really long for some funtions
        t1=b-a
        t1/=e
        dx=(@f.call(b)-@f.call(a))/e
        s=0
        while(a<b)
            s+=@f.call(a)
            a+=t1
        end
        return s*=dx
    end

    def deriv(x)
        #little cheat to make it easier ;)
        h=0.0000000001
        return (@f.call(x+h)-@f.call(x))/h
    end
end

