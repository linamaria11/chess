////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Steve Brandt and Philip LeBlanc
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////
#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <string.h>
#include "node.hpp"
#include "defs.hpp"
#include "data.hpp"
#include "main.hpp"
#include "board.hpp"
#include "eval.hpp"
#include <pthread.h>
#include <list>
#include <map>
#include "smart_ptr.hpp"
#include "hash.hpp"
#include "score.hpp"
#include "parallel_support.hpp"

int think(node_t& board,bool parallel);
score_t search(search_info*);
score_t search_ab(search_info*);
score_t mtdf(search_info*);
score_t qeval(search_info*);
score_t multistrike(search_info*);
int reps(const node_t& board);
bool compare_moves(chess_move a, chess_move b);
void sort_pv(std::vector<chess_move>& workq, int ply);
bool capture(const node_t& board,chess_move& g);
smart_ptr<task> parallel_task(int depth, bool *parallel);
int min(int a,int b);
int max(int a,int b);
void xboard();

extern pthread_mutex_t mutex;
extern const int num_proc;

#endif
