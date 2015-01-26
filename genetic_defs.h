#ifndef GENETIC_DEFS_H
#define GENETIC_DEFS_H

void pool_init(struct pool *);
unsigned int pool_count(struct pool);
struct genetic *pool_get(struct pool *, unsigned int);
unsigned char getvalue(card_t);
char cansplit(card_t, card_t);
struct genetic mutate1(const struct genetic, card_t, card_t);
struct genetic mutate2(const struct genetic, unsigned char);
struct genetic *mutate(const struct genetic, card_t, card_t, unsigned char);
void evaluate_genetic(struct genetic *, double);
void evaluate_pool(struct pool *);

#endif
