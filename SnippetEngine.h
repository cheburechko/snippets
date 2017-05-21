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
		unsigned matches;
	};

	std::vector<TermData::iterator> queryTermData, queryTermDataEnds;
	TermSet queryTerms;
	std::vector<unsigned> analyzedSnippets, snippetsWithMostMatches;
	unsigned queryCounter;
	double bestScore, bestPossibleScore;
	std::string bestSnippet;
	std::multimap<double, unsigned, std::greater<double>> termRank;
	bool useMostMatches;

	void prepareQuery(const std::string& query);
	void calculateBestPossibleScore();
	void selectNextBextTerm();
	void rankNextSnippet();
	bool isSnippetValid(unsigned snippetID);
public:
	SnippetEngine(SnippetStorage& snippets, TermDatabase& terms, bool useMostMatches = true);
	Result getSnippet(const std::string& query);
	virtual ~SnippetEngine();
};

} /* namespace snippets */

#endif /* SNIPPETENGINE_H_ */
