CC=gcc
CFLAGS=-std=c99 -D_BSD_SOURCE
DBFLAGS=-g

make: Vote_Counter Aggregate_Votes Leaf_Counter

Vote_Counter: Vote_Counter.c
	$(CC) $(CFLAGS) -o Vote_Counter Vote_Counter.c

Aggregate_Votes: Aggregate_Votes.c
	$(CC) $(CFLAGS) -o Aggregate_Votes Aggregate_Votes.c

Leaf_Counter: Leaf_Counter.c
	$(CC) $(CFLAGS) -o Leaf_Counter Leaf_Counter.c

clean:
	rm Vote_Counter Aggregate_Votes Leaf_Counter
