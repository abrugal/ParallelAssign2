# ParallelAssign2

For problem 2 I used the third approach which uses the queue. Each guest will try to enter the queue if they aren't already in it, with the chances of entering being a 50% chance. Only the guest that is first in line will try to enter the room, and they can only enter if the room is empty.

## Comparing the other approaches:

* Approach 1) This approach is very easy to implement but is very inefficient because there's no guarantee that every guest would see the vase. The same guests could keep hogging the vase.

* Approach 2) This approach is better since a guest won't try to enter since they'll know if the room is empty or not. Though it could still cause crowding because multiple guests could try to enter once they see the room is empty.

* Approach 3) This is the best approach since every guest will get the chance to see the vase. All they have to do is line up in the queue and they will eventually see the vase. They also won't try to enter unless they are first in line.

## How to run the programs

Labyrinth.cpp is problem 1 and Vase.cpp is problem 2.

To run the programs all you have to do is download the cpp file, and then in the terminal run the command:

To compile: g++ \<source file\> -o \<you name this file\>

To execute: ./\<name you gave\>
