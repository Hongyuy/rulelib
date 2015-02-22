/*
 * Copyright 2015 President and Fellows of Harvard College.
 * All rights reserved.
 */

/*
 * This library implements rule set management for Bayesian rule lists.
 */

/*
 * Rulelist is an ordered collection of rules.
 * A Rule is simply and ID combined with a large binary vector of length N
 * where N is the number of samples and a 1 indicates that the rule captures
 * the sample and a 0 indicates that it does not.
 *
 * Definitions:
 * captures(R, S) -- A rule, R, captures a sample, S, if the rule evaluates
 * true for Sample S.
 * captures(N, S, RS) -- In ruleset RS, the Nth rule captures S.
 */

/*
 * Even though every rule in a given experiment will have the same number of
 * samples (n_ys), we include it in the rule definition. Note that the size of
 * the captures array will be n_ys/sizeof(unsigned).
 *
 * Note that a rule outside a rule set stores captures(R, S) while a rule in
 * a rule set stores captures(N, S, RS).
 */

/*
 * Define types for bit vectors.
 */
typedef unsigned long v_entry;

/*
 * We have slightly different structures to represent the original rules 
 * and rulesets. The original structure contains the ascii representation
 * of the rule; the ruleset structure refers to rules by ID and contains
 * captures which is something computed off of the rule's truth table.
 */
typedef struct rule {
	char *features;			/* Representation of the rule. */
	int support;			/* Number of 1's in truth table. */
	v_entry *truthtable;		/* Truth table; one bit per sample. */
} rule_t;

typedef struct ruleset_entry {
	unsigned rule_id;
	int ncaptured;			/* Number of 1's in bit vector. */
	v_entry	 *captures;		/* Bit vector. */
} ruleset_entry_t;

typedef struct ruleset {
	int n_rules;
	int n_samples;
	ruleset_entry_t *rules;	/* Array of rules. */
} ruleset_t;

/*
 * Functions in the library
 */
int rules_init(const char *, int *, int *, rule_t **);
int ruleset_init(int, int, int *, rule_t *, ruleset_t **);
int rule_swap(ruleset_t *, int, int, rule_t *);
void ruleset_print(ruleset_t *, rule_t *);
void rule_print(rule_t *, int, int);
void rule_print_all(rule_t *, int, int);
void ruleset_entry_print(ruleset_entry_t *, int);
void rule_vector_print(v_entry *, int);
v_entry *rule_tt_copy(rule_t *, int);
v_entry *rule_tt_andnot(rule_t *, v_entry *, int, v_entry *, int *);
v_entry *rule_tt_and(rule_t *, v_entry *, int, v_entry *, int *);
v_entry *rule_tt_or(rule_t *, v_entry *, int, v_entry *, int *);
v_entry *rule_vandnot(v_entry *, v_entry *, int, int *);
v_entry *rule_vor(v_entry *, v_entry *, int);
int count_ones(v_entry);