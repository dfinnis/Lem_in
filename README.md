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

```./lem-in < maps/pdf_example1.map```

<img src="https://github.com/dfinnis/Lem_in/blob/master/img/example1.png" width="42%">

*lem-in* prints the map then the solution.


## Map format

1. number_of_ants
2. rooms (name, coord_x, coord_y)
3. links (name1-name2)

For example:

<img src="https://github.com/dfinnis/Lem_in/blob/master/img/map.png" width="42%">

Can be represented.

<img src="https://github.com/dfinnis/Lem_in/blob/master/img/map2.png" width="20%">

Note: for this map, the best choice of path(s) depends on the number of ants.


## Solution format



## Flags

* -all, print all the following



## Tests

<img src="https://github.com/dfinnis/Lem_in/blob/master/img/test.png" width="42%">

### Generator



## Team

I wrote this project in a team with the wonderful [@svaskeli](https://github.com/sharvas)

## References

[Edmonds-Karp wiki](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm)
