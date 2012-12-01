//////////////////////////////////////////////////
Same Index Test
Produces 4 separate read addresses for the same index. 
Fills a particular way 

L1D misses = 4
L1D hit = 0

prints
//////////////////////////////////////////////////


//////////////////////////////////////////////////
Read Test 
2 reads from the same address. 

L1D misses = 1  
L1D hit = 1
//////////////////////////////////////////////////


//////////////////////////////////////////////////
Read Different Offset
Fills one address then reads every offset from that address. 

L1D misses = 1 
L1D Hit = 64
//////////////////////////////////////////////////


//////////////////////////////////////////////////
All Commands
Makes sure that all commands work properly. 

L1D miss = 2 
L1D hit = 1
L1I miss = 1
L1I hit = 1

Prints 

Clears cache

prints again to verify clear. 
//////////////////////////////////////////////////



//////////////////////////////////////////////////
Invalidate Full Set 

Fills one set, then invalidates 1 way and writes to the same index to verify it fills the invalidated way. 

L1D misses = 5
L1D Hits = 0
//////////////////////////////////////////////////


//////////////////////////////////////////////////
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

//////////////////////////////////////////////////		