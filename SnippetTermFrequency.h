/*
 * SnippetTermFrequency.h
 *
 *  Created on: May 20, 2017
 *      Author: thepunchy
 */

#ifndef SNIPPETTERMFREQUENCY_H_
#define SNIPPETTERMFREQUENCY_H_

#include <unordered_map>
#include "term.h"
#include "TermData.h"

namespace snippets {

class SnippetTermFrequency {
private:
	std::unordered_map<Term, double> rawTF, TF_IDF;
	std::unordered_map<Term, unsigned> rawCounts;
	unsigned total;

public:
	SnippetTermFrequency(const TermBag& bag);

	double getTF(const Term& term) const;
	double getTF_IDF(const Term& term) const;
	unsigned getCount(const Term& term) const;
	void applyIDF(const TermDatabase& terms);
	double score(const TermSet& termSet) const;

	virtual ~SnippetTermFrequency();
};

}

#endif /* SNIPPETTERMFREQUENCY_H_ */
