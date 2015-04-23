from BRL_code import *
import sys

def check(rulesets):
    fname = 'data/titanic'
    #Prior hyperparameters
    lbda = 3. #prior hyperparameter for expected list length (excluding null rule)
    eta = 1. #prior hyperparameter for expected list average width (excluding null rule)
    alpha = array([1.,1.]) #prior hyperparameter for multinomial pseudocounts
    #rule mining parameters
    maxlhs = 2 #maximum cardinality of an itemset
    minsupport = 10 #minimum support (%) of an itemset
    X,Y,nruleslen,lhs_len,itemsets = get_freqitemsets(fname+'_train',minsupport,maxlhs) #Do frequent itemset mining from the training data
    beta_Z,logalpha_pmf,logbeta_pmf = prior_calculations(lbda,len(X),eta,maxlhs)
    for rs in rulesets:
        d_t = rs
        R_t = len(rs)-1
        N_t = compute_rule_usage(d_t, R_t, X, Y)
        logliklihood = fn_logliklihood(d_t,N_t,R_t,alpha)
        logprior = fn_logprior(d_t,R_t,logalpha_pmf,logbeta_pmf,maxlhs,beta_Z,nruleslen,lhs_len)
        print "logprior=", logprior, "\tloglikelihood =", logliklihood

if __name__ == '__main__':
    fname = sys.argv[1]
    print "\n", fname, "\n------Here is the calculation from python------:"
    f = open(fname, 'r')
    s = f.read()
    f.close()
    lines = s.split('\n');
    rulesets = [];
    for line in lines:
        if line:
            rulesets.append([int(x) for x in line.split(',')])
    check(rulesets)