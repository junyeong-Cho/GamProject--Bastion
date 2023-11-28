Tower Information Format:

- Editor	: <value>			(1 is editor mode and 0 is game mode)
- Map rows, cols: <value> <value>
- Map Info	: <value> <value> ...
	    	  <value> ...
	    	  ...

- Start Point	: <value> <value>
- End Point	: <value> <value>
- Total Wave	: <value>
- Wave Info	: WAVE <wave_time> <enemy_type> <enemy_num> WAVE <time> ... END
  	     	  WAVE <wave_time> <enemy_type> <enemy_num> WAVE <time> ... END
	          ...

Example:
0

9 16

P P P P P P P P P P P P B B B B
P P P P P P P P P P P P B B B B
B B B B B B B B B B P P B B B B
B B B B B B B B B B P P B B B B
B B B B B B B B B B P P P P P P
B B B B B B B B B B P P P P P P
B B B B B B B B B B B B B B B B
B B B B B B B B B B B B B B B B
B B B B B B B B B B B B B B B B

0 0
5 15

5

WAVE  5 BASIC  5 END
WAVE  5 BASIC 10 END
WAVE  5  SLOW 10 WAVE  3  NONE  1 WAVE  5 BASIC  5 END
WAVE  5 BASIC 10 WAVE  3  NONE  5 WAVE  5  FAST  5 END
WAVE  5  FAST 15 WAVE  3  NONE  5 WAVE  5  FAST 10 END

