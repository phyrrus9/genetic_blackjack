#ifndef GENETIC_STRUCT_H
#define GENETIC_STRUCT_H

typedef enum enum_action { kSTAND, kHIT, kDOUBLE, kSPLIT } action_t;
typedef enum enum_card { kACE, k2, k3, k4, k5, k6, k7, k8, k9, k10,
			 kJACK, kKING, kQUEEN } card_t;

struct genetic
{
	double wh; //cash won per hand (avg)
	double tw; //total winnings $(curr - orig)
	double sc; //starting cash
	double ba; //bet ammount
	unsigned int th; //total hands played
	action_t st1[13][13][10]; //strategy1 (initial deal)
	action_t st2[20][10]; //strategy2 (everything else)
	char dead; //set once removed from the pool or zero cash
};

struct pool_node
{
	struct genetic p;
	struct pool_node *n;
};

struct pool
{
	unsigned int pn[GENETIC_PLAYERS]; //numbers of in-use strategies
	unsigned int pc; //in-use count (say we start with 5, 3 zero,
			 //we have to fill those players with 0-betters
			 //but still be able to replace them with real
			 //players when one mutates
	struct pool_node *pl; //player list
};

#endif
