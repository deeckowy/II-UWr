require File.expand_path('../fun.rb',__FILE__)

class Graph
    def initialize(fun)
        @f=fun
    end
    def draw(a,b,e)
        #e - for spacing between points
        #example ~ 1 points will be 0,1,2,3...
        # for 0.1 it will be 0.1,0.2
        off=4
        c=b-a
        c/=e
        c.round
        t=0
        graph=Array.new(c+1)
        x=0
        d=""
        z=0
        while (x<=c+1)
            y=0
            s=""
            while (y<=c+1)
                if ((@f.value(a+y*e)>=b-(x+1)*e)&&(@f.value(a+y*e)<=b-x*e))
                    s<<"!"
                else
                    s<<" "
                end
                y+=1
            end
            graph[x]=s
            x+=1
        end
        return graph
    end
end

bb=Proc.new{ |x|}
f=Function.new(bb)
g=Graph.new(f)
x=g.draw(-10,10,1)
puts x
