/*
 * SnippetTermFrequency.cpp
 *
 *  Created on: May 20, 2017
 *      Author: thepunchy
 */

#include "SnippetTermFrequency.h"

namespace snippets {

SnippetTermFrequency::SnippetTermFrequency(TermBag bag) {
	total = bag.size();
	for (Term term : bag) {
		if (data.find(term) != data.end()) {
			data[term]++;
		} else {
			data[term] = 1;
		}
	}
	for (auto x : data) {
		x.second /= total;
	}
}

double SnippetTermFrequency::getTF(Term term) const {
	auto x = data.find(term);
	if (x == data.end()) {
		return 0;
	}
	return x -> second;
}

SnippetTermFrequency::~SnippetTermFrequency() {
	// TODO Auto-generated destructor stub
}

}

