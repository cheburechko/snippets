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

namespace snippets {

class SnippetTermFrequency {
private:
	std::unordered_map<Term, double> data;
	unsigned total;

public:
	SnippetTermFrequency(TermBag bag);

	double getTF(Term term) const;

	virtual ~SnippetTermFrequency();
};

}

#endif /* SNIPPETTERMFREQUENCY_H_ */
