/*
 *	search2.c
 *	A collection of related search functions for the
 *	parallex chess program.
*/

#include "common.h"

/* This function can be seen as the public interface to the search method.
 * This is called in the main function, and like its name suggests, it tries
 * to pick the best move. It calls the search function.
 */

int pickbestmove(board_t board, int max_depth, int side)
{
    int i, x, lastmove, best_score = -20000;
    move best_move;
    board_t newboard;

    movestack legal_moves[MAX_MOVES];	//data to hold all of the pseudo-legal moves for this board

    lastmove = genmoves(board, legal_moves, side);	//generate and store all of the pseudo-legal moves
    
    for (i = 0; i < lastmove; i++) {
        if(!makeourmove(board, legal_moves[i].m.b, &newboard, side))	//Make the move, store it into newmove. Test for legality
		continue;	//If this move isn't legal, move onto the next one
        
        x = search(-10000, 10000, max_depth, newboard, side);
        
        if (x > best_score) {
            best_score = x;
            best_move.u = legal_moves[i].m.u;
        }
    }

    if (best_score == -20000)   //No moves, game is over
        return -1;

    return best_move.u;
}

int search(int alpha, int beta, int depth, board_t board, int side)
{
	int lastmove, i, move_score;
	board_t newmove;

        if (!depth)
            return eval(board, side);

	movestack legal_moves[MAX_MOVES];	//data to hold all of the pseudo-legal moves for this board

        /*******************************MOVE GENERATION*******************************/
	lastmove = genmoves(board, legal_moves, side);	//generate and store all of the pseudo-legal moves

	for (i = 0; i < lastmove; i++) {
		if(!makeourmove(board, legal_moves[i].m.b, &newmove, side))	//Make the move, store it into newmove. Test for legality
			continue;	//If this move isn't legal, move onto the next one

		move_score = -search(-beta, -alpha, depth - 1, newmove, side ^ 1);	//Search again with this move to see opponent's responses

                if (move_score >= beta)
                    return beta;

		if (move_score > alpha)
			alpha = move_score;
	} //end for()

	return alpha;
}