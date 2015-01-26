#include "genetic.h"

void pool_init(struct pool *s)
{
	unsigned int i;
	struct pool_node *default_node = malloc(sizeof(struct pool_node));
	for (i = 0; i < GENETIC_PLAYERS; i++) s->pn[i] = 0;
	s->pc = 0;
	default_node->p = default_generic;
	default_node->n = NULL;
	s->pl = default_node;
}

unsigned int pool_count(struct pool s)
{
	struct pool_node *t = s.pl;
	unsigned int i;
	for (i = 0; t != NULL; i++, t = t->n);
	return i;
}

struct genetic *pool_get(struct pool *s, unsigned int x)
{
	struct genetic ret;
	unsigned int i;
	struct pool_node *t = s->pl;
	for (i = 0; i < x; i++, t = t->n);
	return &t->p; //hehe, TP
}

unsigned char getvalue(card_t c)
{
	switch (c)
	{
		case kACE:
			return 11;
		case kJACK:
		case kKING:
		case kQUEEN:
			return 10;
	}
	return (unsigned char)c;
}
char cansplit(card_t c1, card_t c2) { return getvalue(c1) == getvalue(c2); }
struct genetic mutate1(const struct genetic s, card_t c1, card_t c2)
{
	const unsigned char mutations = rand() % MAX_MUTATIONS;
	unsigned char i;
	action_t mutator;
	unsigned int upcard, first, second;
	struct genetic ret = s;
	for (i = 0; i < mutations; i++)
	{
		mutator = rand() % 4;
		upcard = rand() % 10;
		first = rand() % 13;
		second = rand() % 13;
		if (mutator == kSPLIT)
			if (cansplit(c1, c2))
				ret.st1[first][second][upcard] = kSPLIT;
		ret.st1[first][second][upcard] = (enum enum_action)mutator;
	}
	return ret;
}
struct genetic mutate2(const struct genetic s, unsigned char total)
{
	const unsigned char mutations = rand() % MAX_MUTATIONS;
	unsigned char i;
	action_t mutator;
	unsigned int upcard, ttotal; /*ttotal=temp total*/
	struct genetic ret = s;
	for (i = 0; i < mutations; i++)
	{
		mutator = rand() % 3;
		upcard = rand() % 10;
		ttotal = rand() % 20;
		ret.st2[total][upcard] = (enum enum_action)mutator;
	}
	return ret;
}
struct genetic *mutate(const struct genetic s, card_t c1, card_t c2, unsigned char t)
{
	struct genetic *ret = malloc(sizeof(struct genetic));
	unsigned char mutations = rand() % 3;
	if (mutations == 3 || mutations == 1)
		*ret = mutate1(s, c1, c2);
	if (mutations == 3 || mutations == 2)
		*ret = mutate2(s, t);
	return ret;
}
void evaluate_genetic(struct genetic *s, double currcash)
{
	if (currcash < s->ba)
		s->dead = 1;
	s->tw = currcash - s->sc;
	s->wh = s->tw / s->th;
}
void evaluate_pool(struct pool *p)
{
	const unsigned int active = pool_count(*p) - 1; //sub 1 because pos 0 is default
	unsigned int i, k;
	struct genetic *tmp;
	/* remove dead players */
	for (i = 0; i < active; i++)
	{
		tmp = pool_get(p, i);
		if (tmp->dead)
		{
			p->pn[i] = 0;
			--p->pc;
		}
	}
	/* reorder the list */
	for (i = 1; i < GENETIC_PLAYERS; i++)
	{
		for (k = 1; k < i - 1; k++)
		{
			if (p->pn[k] == 0)
			{
				p->pn[k] = p->pn[k + 1];
				p->pn[k + 1] = 0;
			}
		}
	}
}
