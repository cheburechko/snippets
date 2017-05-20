/*
 * Parser.h
 *
 *  Created on: May 20, 2017
 *      Author: thepunchy
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "Snippet.h"
#include "TermData.h"

namespace snippets {

class Parser {
private:
	int textPos, snippetPos;
	const std::string * text;
	std::string snippet;
	Term term;
	bool finishedText, finishedSnippet;

	void nextSnippet();
	void nextTerm();

	void initSnippet(const std::string& snippet);
	TermBag getTermBag();

	static const std::unordered_set<char> sentenceEnds, delimiters;
public:
	Parser();

	TermBag getTermBag(std::string snippet);
	TermSet getTermSet(std::string snippet);
	void parse(const std::string& text, SnippetStorage& snippets, TermDatabase& terms);

	virtual ~Parser();
};

} /* namespace snippets */

#endif /* PARSER_H_ */
