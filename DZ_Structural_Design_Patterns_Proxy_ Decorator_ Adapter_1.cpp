#include <iostream>
#include <string>
#include <algorithm>

class Text {
public:
	virtual ~Text() = default;
	virtual void render(const std::string& data) const {
		std::cout << data;
	}
};

class DecoratedText : public Text {
protected:
	Text* text_link;
public:
	explicit DecoratedText(Text* text) : text_link(text) {}
	~DecoratedText() { delete text_link; }
};

class Paragraph : public DecoratedText {
public:
	explicit Paragraph(Text* text) : DecoratedText(text) {}

	void render(const std::string& data) const override {
		std::cout << "<p>";
		text_link->render(data);
		std::cout << "</p>";

	}
};

class Reversed : public DecoratedText {
public:
	explicit Reversed(Text* text) : DecoratedText(text) {}

	void render(const std::string& data) const override {
		std::string reversed_data = data;
		std::reverse(reversed_data.begin(), reversed_data.end());
		text_link->render(reversed_data);

	}
};

class Link : public DecoratedText {
public:
	explicit Link(Text* text) : DecoratedText(text) {}

	void render(const std::string& url, const std::string& data) const {
		std::cout << "<a href=" << url << ">";
		text_link->render(data);
		std::cout << "</a>";
	}
};

int main() {
	auto text_p = new Paragraph(new Text());
	text_p->render("Hello world");
	std::cout << std::endl;
	delete text_p;
	auto text_rev = new Reversed(new Text());
	text_rev->render("Hello world");
	std::cout << std::endl;
	delete text_rev;
	auto text_link = new Link(new Text());
	text_link->render("netology.ru", "Hello world");
	std::cout << std::endl;
	delete text_link;


	return 0;
}