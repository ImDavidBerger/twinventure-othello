Over the past two weeks, the two of us used David’s computer to implement our ideas, after brainstorming ideas. This involved one of us writing code while the other commented and threw out syntax, so the two of us wrote most of our code together in the same room on the same computer. For example, David focused on implementing the new Board class, while Sakthi focused on using the new Board class to develop a smarter player and debugging.

 

Sakthi created the original player that made random moves, and David implemented the heuristic algorithm that beat SimplePlayer, discussing the weighting of the board with Sakthi. Once again, the debugging was a joint effort.


The minimax algorithm was first attempted by Sakthi and then scrapped in favor of a cleaner implementation by David. This implementation was then debugged and fine-tuned by the two of us.

 

After David created the new Board class over the weekend, we set to work deciding how we wanted to develop the new player using the features of the new player. For example, we wanted to make it easier to check moves to a given depth, by using a recursive method. This was made much easier with our next board class, which created ‘child boards’ for every parent board, so it was easier to visualize and debug the player.

 

To improve our AI for the tournament, we improved the weighting for our board, using a trial and error method. We settled on weighting the corners of the board at 200 and the cells on the inside of the edges/corners with negative weights, since these moves make it very easy for the other player to attain a corner/edge piece and capture our pieces as well. The board class we created also has the minimax algorithm built into it as well as dynamic programming since it keeps track of the children of each board once a path has been explored.

 

We originally thought about programming in Java, however, after working with C++ for all of CS2 we felt like we knew it better than Java (which we had both taken in junior year for AP CS).

 

We also thought about making our player recursive as deep as possible, but we found that our player actually did better or as well when we looked four moves again instead of 6 or 7, and it was a better tradeoff for time as well.

 
