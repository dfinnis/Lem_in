# Lem_in

Find the fastest way to get *n* ants across a colony (network of rooms and tunnels).

Max flow algorithm using breadth-first path search, based on Edmonds–Karp.

### Goal

Initially, all ants are in room ##start.
The goal is to bring them to room ##end in as few turns as possible.
Each room can only contain one ant at a time (except ##start and ##end).
The algorithm must be able to use the best combination of paths according to the number of ants.

#### Final Score 125/100


## Getting Started

First clone this repo.

```git clone https://github.com/dfinnis/Lem_in.git; cd Lem_in```

Make the binary *lem-in*.

```make```

Then run *lem-in* with a map redirected into stdin. You'll find example maps in maps/.

```./lem-in < maps/pdf_example3.map```

<img src="https://github.com/dfinnis/Lem_in/blob/master/img/example3.png" width="45%">

*lem-in* prints the map then the solution.


## Map format

1. number_of_ants
2. rooms (name, coord_x, coord_y)
3. links (name1-name2)

In the example above (maps/pdf_example3.map), the first line denotes 4 ants, the second line denotes a room named *3*.
This map can be represented:

<img src="https://github.com/dfinnis/Lem_in/blob/master/img/map2.png" width="17%">

Note: for this map, the best choice of path(s) depends on the number of ants.


## Solution format

L(ant number)-(room number). For example ```L1-1``` means ant *1* moves to room *1*.

Here is our solution to pdf_example3.map again.

<img src="https://github.com/dfinnis/Lem_in/blob/master/img/solution.png" width="25%">

On the first line (the first turn) we see 2 ants moved. With 4 ants the algo chose to take the 2 longer paths to minimize number of turns. In the first (and second) turn 1 ant is sent down each path. This solution takes 5 turns, it is 5 lines long.

With 1 or 2 ants the algo would chose the 1 shorter path (start -> 1 -> 2 -> end).


## Flags

* -all, display all the following.

```./lem-in -all < maps/pdf_example3.map```


* -a, display number of ants.

```./lem-in -a < maps/pdf_example3.map```

<img src="https://github.com/dfinnis/Lem_in/blob/master/img/a.png" width="17%">


* -r, display rooms.

```./lem-in -r < maps/pdf_example3.map```

<img src="https://github.com/dfinnis/Lem_in/blob/master/img/r.png" width="42%">


* -l, display links.

```./lem-in -l < maps/pdf_example3.map```

<img src="https://github.com/dfinnis/Lem_in/blob/master/img/l.png" width="42%">


* -rl, display rooms with links.

A graph is created by linking the rooms.

```./lem-in -rl < maps/pdf_example3.map```

<img src="https://github.com/dfinnis/Lem_in/blob/master/img/rl.png" width="42%">


* -p, display paths.

All possible paths from start to end.

```./lem-in -p < maps/pdf_example3.map```

<img src="https://github.com/dfinnis/Lem_in/blob/master/img/p.png" width="12%">


* -g, display path groups.

Paths grouped by which are possible to take at the same time without blocking each other.

```./lem-in -g < maps/pdf_example3.map```

<img src="https://github.com/dfinnis/Lem_in/blob/master/img/g1.png" width="15%">

The chosen group (depending on how many ants) is then shown.

<img src="https://github.com/dfinnis/Lem_in/blob/master/img/g2.png" width="15%">


* -t, display number of turns.

```./lem-in -t < maps/pdf_example3.map```

<img src="https://github.com/dfinnis/Lem_in/blob/master/img/t.png" width="17%">



## Tests

<img src="https://github.com/dfinnis/Lem_in/blob/master/img/test.png" width="42%">

### Generator



## Team

I wrote this project in a team with the wonderful [@svaskeli](https://github.com/sharvas)

## References

[Edmonds-Karp wiki](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm)
