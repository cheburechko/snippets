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
	snippetsByScore.emplace(TF, snippet);
}

void TermData::calculateScore(unsigned totalSnippets) {
	IDF = log(double(totalSnippets) / snippetsByScore.size());
}

TermData::TermDataIterator TermData::begin() const {
	return snippetsByScore.cbegin();
}

TermData::TermDataIterator TermData::end() const {
	return snippetsByScore.cend();
}

TermData::~TermData() {
}

} /* namespace snippets */
