/*
 * TermData.cpp
 *
 *  Created on: May 20, 2017
 *      Author: thepunchy
 */

#include "TermData.h"
#include <cmath>

namespace snippets {

TermData::TermData(Term term) :
		term(term)
{
}

void TermData::addSnippet(unsigned snippet, double TF) {
	snippetsTF[snippet] = TF;
}

void TermData::calculateScore(unsigned totalSnippets) {
	double IDF = log(double(totalSnippets) / snippetsTF.size());
	for (auto entry : snippetsTF) {
		snippetsByScore.emplace(IDF * entry.second, entry.first);
	}
}

TermData::TermDataIterator TermData::begin() {
	return snippetsByScore.begin();
}

TermData::TermDataIterator TermData::end() {
	return snippetsByScore.end();
}

TermData::~TermData() {
}

} /* namespace snippets */
