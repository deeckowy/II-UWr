require File.expand_path('../ImBw.rb',__FILE__)

class ImC<ImBW

    def randomize()
        k=0
        t1=Random.new
        while(k<@H)
            t=Array.new
            i=0
            while (i<@W)
                t<<t1.rand(0..8)
                i+=1
            end
            @map<<(t)
            k+=1
        end
    end

    def Print()
        for i in 0..(@H-1)
            for k in 0..(@W-1)
                case @map[i][k]
                when 0
                    print " "
                when 1
                    print "@"
                when 2
                    print "~"
                when 3
                    print "!"
                when 4
                    print "."
                when 5
                    print "<"
                when 6
                    print ">"
                when 7
                    print "/"
                end
            end
            print "\n"
        end
    end
end

