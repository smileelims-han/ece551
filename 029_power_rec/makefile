CFLASS=-std =gnu99 -pedantic -wall

linkfile: power.o test-power.o
   gcc -o linkfile power.o test-power.o
power.o : power.c
   gcc $(CFLASS) -c power.c 
test-power: test-power.c
   gcc $(CFLASS) -c test-power.c
