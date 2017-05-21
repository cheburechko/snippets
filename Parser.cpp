/*
 * Parser.cpp
 *
 *  Created on: May 20, 2017
 *      Author: thepunchy
 */

#include "Parser.h"
#include <algorithm>

namespace snippets {

const std::regex Parser::sentenceRegex("[^.!?]+[[:punct:][:space:]]*");

const std::regex Parser::termRegex("[^[:punct:][:space:]]+");

Parser::Parser(unsigned minTermsInSnippet) :
	minTermsInSnippet(minTermsInSnippet)
{
}

void lower(std::string& inp) {
	std::transform(inp.begin(), inp.end(), inp.begin(), ::tolower);
}

TermBag Parser::getTermBag(std::string snippet) {
	TermBag result;
	auto terms_begin = std::sregex_iterator(snippet.cbegin(), snippet.cend(), termRegex);
	auto term_end = std::sregex_iterator();
	for (std::sregex_iterator term = terms_begin;
		 term != term_end;
		 ++term
	) {
		result.push_back(term->str());
	}
	return result;
}

TermSet Parser::getTermSet(std::string snippet) {
	TermSet result;
	auto terms_begin = std::sregex_iterator(snippet.cbegin(), snippet.cend(), termRegex);
	auto term_end = std::sregex_iterator();
	for (std::sregex_iterator term = terms_begin;
		 term != term_end;
		 ++term
	) {
		result.emplace(term->str());
	}
	return result;
}

void Parser::parse(const std::string& text, SnippetStorage& snippets,
		TermDatabase& terms) {
	std::string accumulatedSnippet;
	TermBag accumulatedBag;

	auto sentences_begin = std::sregex_iterator(text.cbegin(), text.cend(), sentenceRegex);
	auto sentences_end = std::sregex_iterator();

	unsigned termsTotal = 0;

	for (std::sregex_iterator sentence = sentences_begin;
		 sentence != sentences_end;
		 ++sentence
	) {
		std::string snippet = sentence->str();

		TermBag bag = getTermBag(snippet);
		if (bag.size() == 0) {
			continue;
		}
		accumulatedSnippet += snippet;
		accumulatedBag.insert(accumulatedBag.end(), bag.begin(), bag.end());
		if (accumulatedBag.size() >= minTermsInSnippet) {
			addSnippet(accumulatedBag, accumulatedSnippet, snippets, terms, termsTotal);
		}
	}
	if (accumulatedBag.size() > 0) {
		addSnippet(accumulatedBag, accumulatedSnippet, snippets, terms, termsTotal);
	}

	for (auto& termPair : terms) {
		termPair.second.calculateScore(termsTotal);
	}

	for (auto& snipObj : snippets) {
		snipObj.getTF().applyIDF(terms);
	}
}

void Parser::addSnippet(TermBag& bag, std::string& snippet,
		SnippetStorage& snippets, TermDatabase& terms,
		unsigned & termsTotal) {
	Snippet snipObj = Snippet(snippet, bag);
	snippets.push_back(snipObj);

	TermSet set(bag.begin(), bag.end());
	const SnippetTermFrequency& TF = snipObj.getTF();
	for (Term term : set) {
		auto termData = terms.find(term);
		if (termData == terms.end()) {
			termData = terms.emplace(term, TermData(term)).first;
		}
		termData->second.addSnippet(snippets.size()-1, TF.getTF(term), TF.getCount(term));
	}

	termsTotal += bag.size();
	bag.clear();
	snippet.clear();
}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

} /* namespace snippets */
