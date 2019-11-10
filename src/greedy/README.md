DOCUMENTATION
=============

need to rewrite code to conform to this outline

<CODE>dijkstra</CODE>
---------------------

breadth-first search for point B

move blindly from next live node until B is reached, using shortest running distance from A

<CODE>a_star</CODE>
-------------------

depth-first search for point B

1 move twords point b using shortest path using both running distance from A and norm distance from B
2 if no closer tile can be found, mark as dead and find best live node; <CODE>goto 1</CODE>

(<CODE>dijkstra</CODE>|<CODE>a_star</CODE>)<CODE>_net</CODE>
------------------------------------------------------------

finds the shortest path over a net of paths.
(the normal functions find a shortest path between 2 points accross
the discreet room space)

(<CODE>prim</CODE>|(<CODE>rev</CODE>)?<CODE>kruskel</CODE>|<CODE>sollin</CODE>)
-------------------------------------------------------------------------------

make a minimal spanning tree given a set of points.
each algorithem may produce a slightly different tree, especially when given equidistant points.

can specify either path generator and can use any fine tuning options

<CODE>full_net</CODE>
---------------------

generate a non-overlapping net between a list of points

tba:
----

- the existing grid generator functions
- the existing blit functions

WEIGHT
======

node weighting is done according to distance.
the norm used to specify this distance is independent from the norm for mesuring distance from B.

forward is always considered most optimal. after that:
- an optional elevation weighting level may be added that follows the ground.
- for elevation, horizontal is considered best, then pitches from down to up.
- azimuthly, north is weighted as best, then other directions moving clockwise.
elevations are weighted heavier than azimuths.

finer control over the pathing may be given:
- no flying - nonground nodes are never checked
- meteor falling - ground nodes and horizontal are checked when on a ground node, but only down nodes are checked when not on a ground node.
- featherfalling - only ground nodes and nodes with a nonpositive azimuth are considered.
- flying (default) - all nodes are considered

- no swimming - wet nodes are never considered
- no diving - only wet surface nodes are considered
- swimming (default) - all wet nodes are considered

- weight flying by n - add n to the distance calculation of a nonground node, default 0
- weight swimming by n - add n to the distance calculation of a wet node, default 0

- avoid foo - where foo is a type of hazard, avoid that hazard
- ortho - restrict to orthogonal movement
- nocollision
