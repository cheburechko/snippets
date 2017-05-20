/*
 * TermData.h
 *
 *  Created on: May 20, 2017
 *      Author: thepunchy
 */

#ifndef TERMDATA_H_
#define TERMDATA_H_

#include "term.h"
#include <map>
#include <unordered_map>

namespace snippets {

class TermData {
public:
	typedef std::multimap<double, unsigned, std::greater<double>> SnipsByScore;
	typedef SnipsByScore::const_iterator TermDataIterator;
	TermData(Term term);

	void addSnippet(unsigned snippet, double TF);
	void calculateScore(unsigned totalSnippets);

	TermDataIterator begin() const;
	TermDataIterator end() const;

	virtual ~TermData();

	double getIDF() const {
		return IDF;
	}

private:
	Term term;
	SnipsByScore snippetsByScore;
	double IDF;
};

typedef std::unordered_map<Term, TermData> TermDatabase;

} /* namespace snippets */

#endif /* TERMDATA_H_ */
