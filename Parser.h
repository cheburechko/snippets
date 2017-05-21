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
#include <regex>

namespace snippets {

class Parser {
private:
	unsigned minTermsInSnippet;

	static const std::regex sentenceRegex, termRegex;
public:
	Parser(unsigned minTermsInSnippet = 15);

	TermBag getTermBag(std::string snippet);
	TermSet getTermSet(std::string snippet);
	void parse(const std::string& text, SnippetStorage& snippets, TermDatabase& terms);

	virtual ~Parser();
};

} /* namespace snippets */

#endif /* PARSER_H_ */
