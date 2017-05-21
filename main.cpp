#include "SnippetEngine.h"
#include <iostream>
#include <fstream>

const unsigned minTermsInSnippet = 15;
const bool useMostMatches = true;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Filename is required as first argument\n";
		return 1;
	}
	std::cout << "Reading file: " << argv[1] << std::endl;
	std::ifstream ifs(argv[1]);
	if (!ifs) {
		std::cerr << "File can not be opened\n";
		return 1;
	}

	std::string text;
	ifs.seekg(0, std::ios::end);
	text.resize(ifs.tellg());
	ifs.seekg(0, std::ios::beg);
	ifs.read(&text[0], text.size());
	ifs.close();

	std::cout << "Processing text..." << std::endl;

	snippets::TermDatabase terms;
	snippets::SnippetStorage snippets;
	snippets::Parser parser(minTermsInSnippet);
	parser.parse(text, snippets, terms);

#ifdef DEBUG
	std::cout << "DEBUG enabled!\n" << std::endl
			  << "Writing terms to terms.txt" << std::endl;
	std::ofstream termsOutput("terms.txt");
	if (termsOutput) {
		for (auto pair : terms) {
			termsOutput << pair.first << ' ' << pair.second.getIDF() << '\n';
		}
	}
	termsOutput.close();

	std::cout << "Writing snippets to snippets.txt" << std::endl;
	std::ofstream snipOutput("snippets.txt");
	if (snipOutput) {
		for (auto snip : snippets) {
			snipOutput << snip.getSnippet() << "\n========\n";
		}
	}
	snipOutput.close();
#endif
	std::cout << "Preprocessing finished." << std::endl;
	snippets::SnippetEngine engine(snippets, terms, useMostMatches);
	std::string query;
	std::cout << "Input query: ";
	while (std::getline(std::cin, query)) {
		auto result = engine.getSnippet(query);
		std::cout << "Query: " << query << std::endl
				  << "Snippet: " << result.snippet << std::endl
				  << "Score: " << result.score << std::endl
				  << "Time (us): " << result.time << std::endl
				  << "==========================================" << std::endl
				  << "Input next query: ";
	}
}
