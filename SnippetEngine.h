/*
 * SnippetEngine.h
 *
 *  Created on: May 20, 2017
 *      Author: thepunchy
 */

#ifndef SNIPPETENGINE_H_
#define SNIPPETENGINE_H_

#include "Parser.h"

namespace snippets {

class SnippetEngine {
private:
	SnippetStorage& snippets;
	TermDatabase& terms;
	Parser parser;

	struct Result {
		std::string snippet;
		long time;
		double score;
	};

	std::vector<TermData::iterator> queryTermData, queryTermDataEnds;
	TermSet queryTerms;
	std::unordered_set<unsigned> analyzedSnippets;
	double bestScore, bestPossibleScore;
	std::string bestSnippet;
	std::multimap<double, unsigned, std::greater<double>> termRank;

	void prepareQuery(const std::string& query);
	void calculateBestPossibleScore();
	void selectNextBextTerm();
	void rankNextSnippet();
public:
	SnippetEngine(SnippetStorage& snippets, TermDatabase& terms);
	Result getSnippet(const std::string& query);
	virtual ~SnippetEngine();
};

} /* namespace snippets */

#endif /* SNIPPETENGINE_H_ */
