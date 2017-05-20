/*
 * Snippet.h
 *
 *  Created on: May 20, 2017
 *      Author: thepunchy
 */

#ifndef SNIPPET_H_
#define SNIPPET_H_

#include "SnippetTermFrequency.h"

namespace snippets {

class Snippet {
private:
	SnippetTermFrequency TF;
	std::string snippet;
public:
	Snippet(std::string snippet, TermBag bag);

	const std::string& getSnippet();
	const SnippetTermFrequency& getTF();

	virtual ~Snippet();
};

typedef std::vector<Snippet> SnippetStorage;

} /* namespace snippets */

#endif /* SNIPPET_H_ */
