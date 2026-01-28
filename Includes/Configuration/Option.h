#pragma once

class Option{
private:
	char **list{};
	int Nlist{};
public:
	int Nprocess,parallel;
	char directory[1024]{};
	Option() noexcept;
	int Management(char **argv, int argc) noexcept;
	void Record() noexcept;
};
