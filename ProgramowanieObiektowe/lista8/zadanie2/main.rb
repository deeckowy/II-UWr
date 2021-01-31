require File.expand_path('../ImC.rb',__FILE__)
##testy dla czarno-bialych 
z=ImBW.new(4,4)
z.randomize
print "\nz =\n\n"
z.Print

x=ImBW.new(4,4)
x.randomize
print "\nx =\n\n"
x.Print

t=x.clone
x+z
print "\nx+z =\n\n"
x.Print

z*x
print "\nx*z=\n\n"
z.Print



##testy dla kolorowych 
z=ImC.new(4,4)
z.randomize
print "\nz =\n\n"
z.Print

x=ImC.new(4,4)
x.randomize
print "\nx =\n\n"
x.Print

t=x.clone
x+z
print "\nx+z =\n\n"
x.Print

z*x
print "\nx*z=\n\n"
z.Print

