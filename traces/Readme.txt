Same Index Test
Produces 4 separate read addresses for the same index. Will produce 4 misses. 

misses = 4
hit = 0

Read Test 
2 reads from the same address. 

misses = 1  
hit = 1

Read Different Offset
Fills one address then reads every offset from that address. 

misses =1 
Hit = 64

All Commands
Makes sure that all commands work properly. 

misses = 3
hits  = 2
Prints 
Clears cache
prints again to verify clear. 


Invalidate Full Set 

Fills one set, then invalidates 1 way and writes to the same index to verify it fills the invalidated way. 

misses = 5
Hits = 0

LRU TEST 

Fills the 1 set and evicts in every single order. 

OUTPUT( 0123 = 4000 0000, 4010 0000, 4020 0000, 4030 0000) 	
0123		
0132			
0312
0213		
0231	
0321		

1230	
1320
1302
1032	
1023	
1203		

2130	
2310		
2301	
2031		
2103		
2013		

3120		
3210		
3201		
3021		
3102		
3012		