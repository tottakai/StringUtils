#ifndef TOTTAKAI_STRINGUTILS_H_
#define TOTTAKAI_STRINGUTILS_H_

namespace tottakai {
	void split_map(const std::string& s, char delim, std::tr1::function<void(const std::string&)> func) {
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			func(item);
		}
	}
};

#endif