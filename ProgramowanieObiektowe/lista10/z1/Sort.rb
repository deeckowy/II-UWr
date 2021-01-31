require File.expand_path('../Collection.rb',__FILE__)


class Sort
    def Sort1(col)#insertion sort
        i=0
        while(i<col.Len)
            key=col.Get(i)
            j=i-1
            while (j>=0 && col.Get(j)>key)
                col.Swap(j,j+1)
                j-=1
            end
            col.Set(j+1,key)
            i+=1
        end
    end

    def Sort2(col)#buble sort
        i=col.Len-1
        while(i>1)
            j=0
            while(j<i)
                if(col.Get(j)>col.Get(j+1))
                    col.Swap(j,j+1)
                end
                j+=1
            end
            i-=1
        end
    end
end

puts "Tablica X:"
x=Collection.new
x<<12
x<<12312
x<<13
x<<1
x<<32
x<<32112
print x.getPrintable
puts 
sorter=Sort.new
sorter.Sort2(x)
puts "Sortowanie babelkowe"
print x.getPrintable
y=Collection.new 
y<<56
y<<12
y<<1
y<<(-1)
y<<23
y<<1200321
puts "\n\n\n"
puts "Tablica Y:"
print y.getPrintable
puts
puts "Sortowanie przez wstawianie"
sorter.Sort1(y)
print y.getPrintable
