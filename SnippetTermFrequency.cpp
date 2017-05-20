/*
 * SnippetTermFrequency.cpp
 *
 *  Created on: May 20, 2017
 *      Author: thepunchy
 */

#include "SnippetTermFrequency.h"

namespace snippets {

SnippetTermFrequency::SnippetTermFrequency(const TermBag& bag) {
	total = bag.size();
	for (Term term : bag) {
		if (rawTF.find(term) != rawTF.end()) {
			rawTF[term]++;
		} else {
			rawTF[term] = 1;
		}
	}
	for (auto x : rawTF) {
		x.second /= total;
	}
}

double SnippetTermFrequency::getTF(const Term& term) const {
	auto x = rawTF.find(term);
	if (x == rawTF.end()) {
		return 0;
	}
	return x -> second;
}

double SnippetTermFrequency::getTF_IDF(const Term& term) const {
	auto x = TF_IDF.find(term);
	if (x == TF_IDF.end()) {
		return 0;
	}
	return x -> second;
}

void SnippetTermFrequency::applyIDF(const TermDatabase& terms) {
	TF_IDF.clear();
	for (auto x: rawTF) {
		auto termData = terms.find(x.first);
		double idf = 0. ? termData == terms.end() : termData -> second.getIDF();
		TF_IDF[x.first] = x.second * idf;
	}
}

double SnippetTermFrequency::score(const TermSet& termSet) const {
	double score = 0;
	for (auto term : termSet) {
		score += getTF_IDF(term);
	}
	return score;
}

SnippetTermFrequency::~SnippetTermFrequency() {
	// TODO Auto-generated destructor stub
}

}

