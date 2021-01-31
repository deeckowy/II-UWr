class ImBW
    attr_accessor :map
    def initialize(h,w)
        @H=h
        @W=w
        @map=Array.new
    end

    def randomize()
        k=0
        t1=Random.new
        while(k<@H)
            t=Array.new
            i=0
            while (i<@W)
                t<<t1.rand(0..1)
                i+=1
            end
            # puts(t)
            @map<<(t)
            k+=1
        end
    end

    def Print()
        for i in 0..(@H-1)
            for k in 0..(@W-1)
                if (@map[i][k]==1)
                    print '@'
                else
                    print " "
                end
            end
            print "\n"
        end
    end

    def +(arg)
        for i in 0..(@H-1)
            for k in 0..(@W-1)
                @map[i][k]|=arg.map[i][k]
            end
        end
    end

    def *(arg)
        for i in 0..(@H-1)
            for k in 0..(@W-1)
                @map[i][k]&=arg.map[i][k]
            end
        end
    end

end
