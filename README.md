# ParallelAssign2

For problem 2 I used the third approach which uses the queue.

Approach 1) This approach is very easy to implement but is very inefficient because there's no guarantee that every guest would see the vase. The same guests could keep hogging the vase.

Approach 2) This approach is better since a guest won't try to enter since they'll know if the room is empty or not. Though it could still cause crowding if multiple guests try to enter at the same time when they see that the room is empty. If this happens then the guest that enters is random.

Approach 3) This is the best approach since every guest will get the chance to see the vase. All they have to do is line up in the queue and they will eventually see the vase.

To run this program all you have to do is download the cpp file, and then in the terminal run the command:

To compile: g++ <source file> -o <you name this file>

To execute: ./<name you gave>
