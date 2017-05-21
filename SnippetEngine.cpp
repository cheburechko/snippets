/*
 * SnippetEngine.cpp
 *
 *  Created on: May 20, 2017
 *      Author: thepunchy
 */

#include "SnippetEngine.h"
#include <chrono>
#include <iostream>

namespace snippets {

SnippetEngine::SnippetEngine(SnippetStorage& snippets, TermDatabase& terms) :
	snippets(snippets),
	terms(terms),
	bestPossibleScore(0),
	bestScore(0),
	analyzedSnippets(snippets.size()),
	snippetsWithMostMatches(snippets.size()),
	queryCounter(0)
{
}

SnippetEngine::Result SnippetEngine::getSnippet(const std::string& query) {
	using namespace std::chrono;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	SnippetEngine::Result result;
	queryCounter++;

	prepareQuery(query);
	calculateBestPossibleScore();
	while (bestScore < bestPossibleScore) {
		rankNextSnippet();
		selectNextBextTerm();
	}


	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	microseconds time_span = duration_cast<microseconds>(t2 - t1);
	result.time = time_span.count();
	result.snippet = bestSnippet;
	result.score = bestScore;
	return result;
}

void SnippetEngine::prepareQuery(const std::string& query) {
	queryTerms = parser.getTermSet(query);
	queryTermData.clear();
	queryTermDataEnds.clear();

	std::unordered_map<unsigned, unsigned> snippetMatchCount(snippets.size());
	unsigned maxTermCount = 0;

	for (Term term : queryTerms) {
		const auto& termData = terms.find(term);
		if (termData == terms.end()) {
			continue;
		}
		for (auto it = termData->second.begin(); it != termData->second.end(); it++) {
			snippetMatchCount[it->second]++;
			maxTermCount = std::max(maxTermCount, snippetMatchCount[it->second]);
		}

		queryTermData.push_back(termData->second.begin());
		queryTermDataEnds.push_back(termData->second.end());
	}

	for (auto& snipMatchCount : snippetMatchCount) {
		if (snipMatchCount.second == maxTermCount) {
			snippetsWithMostMatches[snipMatchCount.first] = queryCounter;
		}
	}

	bestScore = 0;
	bestSnippet = "!!! Query had no matches. !!!";
}

void SnippetEngine::calculateBestPossibleScore() {
	bestPossibleScore = 0;
	termRank.clear();
	for (unsigned i = 0; i < queryTermData.size(); i++) {
		TermData::iterator& termData = queryTermData[i];
		bestPossibleScore += termData->first;
		termRank.emplace(termData->first, i);
	}
}

void SnippetEngine::rankNextSnippet() {
	unsigned snippetID = queryTermData[termRank.begin()->second]->second;
	if (!isSnippetValid(snippetID)) {
		return;
	}
	Snippet& snippet = snippets.at(snippetID);
	analyzedSnippets[snippetID] = queryCounter;
	double score = snippet.getTF().score(queryTerms);
	if (score > bestScore) {
		bestScore = score;
		bestSnippet = snippet.getSnippet();
	}
}

void SnippetEngine::selectNextBextTerm() {
	unsigned termID = termRank.begin()->second;
	auto& iter = queryTermData[termID];

	termRank.erase(termRank.begin());
	bestPossibleScore -= iter->first;
	iter++;

	while (
		iter != queryTermDataEnds[termID] &&
		!isSnippetValid(iter->second)
	) {
		iter++;
	}
	if (iter == queryTermDataEnds[termID]) {
		return;
	}

	termRank.emplace(iter->first, termID);
	bestPossibleScore += iter->first;
}

bool SnippetEngine::isSnippetValid(unsigned snippetID) {
	return analyzedSnippets[snippetID] != queryCounter &&
		   snippetsWithMostMatches[snippetID] == queryCounter;
}

SnippetEngine::~SnippetEngine() {
	// TODO Auto-generated destructor stub
}

} /* namespace snippets */
