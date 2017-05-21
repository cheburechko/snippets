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
		term(term),
		count(0),
		IDF(0)
{
}

void TermData::addSnippet(unsigned snippet, double TF, unsigned count) {
	snippetsTF[snippet] = TF;
	this->count += count;
}

void TermData::calculateScore(unsigned totalWords) {
	IDF = double(totalWords) / double(count);
	snippetsByScore.clear();
	for (auto pair : snippetsTF) {
		snippetsByScore.emplace(pair.second*IDF, pair.first);
	}
}

TermData::iterator TermData::begin() const {
	return snippetsByScore.cbegin();
}

TermData::iterator TermData::end() const {
	return snippetsByScore.cend();
}

TermData::~TermData() {
}

} /* namespace snippets */
