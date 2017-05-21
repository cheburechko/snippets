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
		IDF(0)
{
}

void TermData::addSnippet(unsigned snippet, double TF) {
	snippetsTF[snippet] = TF;
}

void TermData::calculateScore(unsigned totalSnippets) {
	IDF = log(double(totalSnippets) / double(snippetsTF.size()));
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
